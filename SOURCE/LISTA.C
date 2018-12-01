/***************************************************************************
*  $MCI Módulo de implementação: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores:   avs   Arndt Von Staa
*             cai   Caique Molina Soares
*             gui   Guilherme Dantas de Oliveira
*             nag   Nagib Moura Suaid
*
*  $HA Histórico de evolução:
*     Versão  Autor        Data     Observações
*     6       gui       30/nov/2018 contadores, verificar e deturpar
*     5       gui,nag   21/nov/2018 modificações na estrutura para ser auto-verificável
*     4       avs       01/fev/2006 criar linguagem script simbólica
*     3       avs       08/dez/2004 uniformização dos exemplos
*     2       avs       07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs       16/abr/2003 início desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#ifdef _DEBUG
#include "GENERICO.H"
#include "CESPDIN.H"
#include "CONTA.H"
#include "Tabelas\\IdTiposEspaco.def"
#endif

#define LISTA_OWN
#include "LISTA.h"
#undef LISTA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/

   typedef struct tagElemLista {

         void * pValor ;
               /* Ponteiro para o valor contido no elemento */

         struct tagElemLista * pAnt ;
               /* Ponteiro para o elemento predecessor */

         struct tagElemLista * pProx ;
               /* Ponteiro para o elemento sucessor */

#ifdef _DEBUG

         char TipoValor ;
               /* Descritor de tipo do valor apontado pelo elemento de lista */

         LIS_tppLista pCab ;
               /* Ponteiro para cabeça da lista a qual o elemento pertence */

         unsigned long tam ;
               /* Tamanho da estrutura apontada pelo elemento */

#endif

   } tpElemLista ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabeça de lista
*
*
***********************************************************************/

   typedef struct LIS_tagLista {

         tpElemLista * pOrigemLista ;
               /* Ponteiro para a origem da lista */

         tpElemLista * pFimLista ;
               /* Ponteiro para o final da lista */

         tpElemLista * pElemCorr ;
               /* Ponteiro para o elemento corrente da lista */

         int numElem ;
               /* Número de elementos da lista */

         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a função de destruição do valor contido em um elemento */

#ifdef _DEBUG

         char TipoValor ;
               /* Descritor de tipo do valor apontado pelo elemento de lista */

#endif


   } LIS_tpLista ;

/*****  Dados encapsulados no módulo  *****/

      #ifdef _DEBUG

      static char EspacoLixo[ 256 ] =
             "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" ;
            /* Espaço de dados lixo usado ao testar */

      #endif
/***** Protótipos das funções encapuladas no módulo *****/

   typedef struct tagElemLista * LIS_tppElemLista;

   static void VerificaMemoria ( void * Ponteiro , int IdTipoEspaco ) ;

   static void LiberarElemento( LIS_tppLista   pLista ,
                                tpElemLista  * pElem   ) ;

   static tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                       void *       pValor
#ifdef _DEBUG
                                       , char TipoValor
                                       , unsigned long tam
#endif
      ) ;

   static void LimparCabeca( LIS_tppLista pLista ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: LIS  &Criar lista
*  ****/

   LIS_tppLista LIS_CriarLista( void   ( * ExcluirValor ) ( void * pDado )
#ifdef _DEBUG
                              , char TipoValor
#endif
      )
   {

      LIS_tpLista * pLista = NULL ;

      pLista = ( LIS_tpLista * ) malloc( sizeof( LIS_tpLista )) ;
      if ( pLista == NULL )
      {
         return NULL ;
      } /* if */

      LimparCabeca( pLista ) ;

#ifdef _DEBUG

      pLista->TipoValor = TipoValor;
      CED_DefinirTipoEspaco( pLista , LIS_TipoEspacoCabeca );

#endif

      pLista->ExcluirValor = ExcluirValor ;

      return pLista ;

   } /* Fim função: LIS  &Criar lista */

/***************************************************************************
*
*  Função: LIS  &Destruir lista
*  ****/

   void LIS_DestruirLista( LIS_tppLista pLista )
   {

      LIS_EsvaziarLista( pLista ) ;

      free( pLista ) ;

   } /* Fim função: LIS  &Destruir lista */

/***************************************************************************
*
*  Função: LIS  &Esvaziar lista
*  ****/

   void LIS_EsvaziarLista( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;
      tpElemLista * pProx ;

      pElem = pLista->pOrigemLista ;
      while ( pElem != NULL )
      {
         pProx = pElem->pProx ;
         LiberarElemento( pLista , pElem ) ;
         pElem = pProx ;
      } /* while */

      LimparCabeca( pLista ) ;

   } /* Fim função: LIS  &Esvaziar lista */

/***************************************************************************
*
*  Função: LIS  &Inserir elemento antes
*  ****/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor
#ifdef _DEBUG
                                          , char TipoValor
                                          , unsigned tam
#endif
      )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG

         if( TipoValor != pLista->TipoValor )
         {
            return LIS_CondRetErroEstrutura;
         } /* if */

      #endif

      /* Criar elemento a inerir antes */

         pElem = CriarElemento( pLista , pValor

#ifdef _DEBUG
                               , TipoValor
                               , tam
#endif 
                               ) ;

         if ( pElem == NULL )
         {
            return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento antes do elemento corrente */

         if ( pLista->pElemCorr == NULL )
         {
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } /* if */
         else
         {
            if ( pLista->pElemCorr->pAnt != NULL )
            {
               pElem->pAnt  = pLista->pElemCorr->pAnt ;
               pLista->pElemCorr->pAnt->pProx = pElem ;
            } /* if */
            else
            {
               pLista->pOrigemLista = pElem ;
            } /* else */

            pElem->pProx = pLista->pElemCorr ;
            pLista->pElemCorr->pAnt = pElem ;
         } /* else */

         pLista->pElemCorr = pElem ;

         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Inserir elemento antes */

/***************************************************************************
*
*  Função: LIS  &Inserir elemento após
*  ****/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor
#ifdef _DEBUG
                                          , char TipoValor
                                          , unsigned long tam
#endif
      )
      
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG

         if( TipoValor != pLista->TipoValor )
         {
            return LIS_CondRetErroEstrutura;
         } /* if */

      #endif

      /* Criar elemento a inerir após */

         pElem = CriarElemento( pLista , pValor

#ifdef _DEBUG
                               , TipoValor
                               , tam
#endif 
                               ) ;
         if ( pElem == NULL )
         {
            return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento após o elemento */

         if ( pLista->pElemCorr == NULL )
         {
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } /* if */
         else
         {
            if ( pLista->pElemCorr->pProx != NULL )
            {
               pElem->pProx  = pLista->pElemCorr->pProx ;
               pLista->pElemCorr->pProx->pAnt = pElem ;
            } /* if */
            else
            {
               pLista->pFimLista = pElem ;
            } /* else */

            pElem->pAnt = pLista->pElemCorr ;
            pLista->pElemCorr->pProx = pElem ;

         } /* else */
                  
         pLista->pElemCorr = pElem ;
                  
         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Inserir elemento após */

/***************************************************************************
*
*  Função: LIS  &Excluir elemento
*  ****/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;

      if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */

      pElem = pLista->pElemCorr ;

      /* Desencadeia à esquerda */

         if ( pElem->pAnt != NULL )
         {
            pElem->pAnt->pProx   = pElem->pProx ;
            pLista->pElemCorr    = pElem->pAnt ;
         } /* if */
         else
         {
            pLista->pElemCorr    = pElem->pProx ;
            pLista->pOrigemLista = pLista->pElemCorr ;
         } /* else */

      /* Desencadeia à direita */

         if ( pElem->pProx != NULL )
         {
            pElem->pProx->pAnt = pElem->pAnt ;
         } /* if */
         else
         {
            pLista->pFimLista = pElem->pAnt ;
         } /* else */

      LiberarElemento( pLista , pElem ) ;

      return LIS_CondRetOK ;

   } /* Fim função: LIS  &Excluir elemento */

/***************************************************************************
*
*  Função: LIS  &Obter referência para o valor contido no elemento
*  ****/

   void * LIS_ObterValor( LIS_tppLista pLista )
   {

      if ( pLista->pElemCorr == NULL )
      {
         return NULL ;
      } /* if */

      return pLista->pElemCorr->pValor ;

   } /* Fim função: LIS  &Obter referência para o valor contido no elemento */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento inicial
*  ****/

   void IrInicioLista( LIS_tppLista pLista )
   {

      pLista->pElemCorr = pLista->pOrigemLista ;

   } /* Fim função: LIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento final
*  ****/

   void IrFinalLista( LIS_tppLista pLista )
   {

      pLista->pElemCorr = pLista->pFimLista ;

   } /* Fim função: LIS  &Ir para o elemento final */

/***************************************************************************
*
*  Função: LIS  &Avançar elemento
*  ****/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem )
   {

      int i ;

      tpElemLista * pElem ;

      /* Tratar lista vazia */

         if ( pLista->pElemCorr == NULL )
         {

            return LIS_CondRetListaVazia ;

         } /* fim ativa: Tratar lista vazia */

      /* Tratar avançar para frente */

         if ( numElem > 0 )
         {

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i > 0 ; i-- )
            {
               if ( pElem == NULL )
               {
                  break ;
               } /* if */
               pElem    = pElem->pProx ;
            } /* for */

            if ( pElem != NULL )
            {
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pFimLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avançar para frente */

      /* Tratar avançar para trás */

         else if ( numElem < 0 )
         {

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i < 0 ; i++ )
            {
               if ( pElem == NULL )
               {
                  break ;
               } /* if */
               pElem    = pElem->pAnt ;
            } /* for */

            if ( pElem != NULL )
            {
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pOrigemLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avançar para trás */

      /* Tratar não avançar */

         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Avançar elemento */

/***************************************************************************
*
*  Função: LIS  &Procurar elemento contendo valor
*  ****/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor        )
   {

      tpElemLista * pElem ;

      if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */

      for ( pElem  = pLista->pElemCorr ;
            pElem != NULL ;
            pElem  = pElem->pProx )
      {
         if ( pElem->pValor == pValor )
         {
            pLista->pElemCorr = pElem ;
            return LIS_CondRetOK ;
         } /* if */
      } /* for */

      return LIS_CondRetNaoAchou ;

   } /* Fim função: LIS  &Procurar elemento contendo valor */

#ifdef _DEBUG

/***************************************************************************
*
*  Função: LIS  &Verificar Lista
*  ****/

   int LIS_VerificarLista( void * pListaParam )
   {
      
      LIS_tppLista pCab = NULL;
      LIS_tppElemLista pCorr = NULL , pOrig = NULL , pFinal = NULL , pAux = NULL;
      char TipoValor;
      int achou , numElem , calc_numElem, numElem_correto = 0 ;

      int numFalhas = 0;

      if( pListaParam == NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "1" ) ;
         #endif
         TST_NotificarFalha( "Tentou verificar cabeça de lista inexistente." ) ;
         numFalhas++;
      } /* if */

      if ( ! CED_VerificarEspaco( pListaParam , NULL ) )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "2" ) ;
         #endif
         TST_NotificarFalha( "Controle do espaço acusou erro." ) ;
         numFalhas++;
      } /* if */

      if ( TST_CompararInt( LIS_TipoEspacoCabeca ,
           CED_ObterTipoEspaco( pListaParam ) ,
           "Tipo do espaço de dados não é cabeça de lista." ) != TST_CondRetOK )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "3" ) ;
         #endif
         numFalhas++;
      } /* if */

      pCab = (LIS_tppLista) pListaParam;
      pCorr = pCab->pElemCorr;
      pOrig = pCab->pOrigemLista;
      pFinal = pCab->pFimLista;
      TipoValor = pCab->TipoValor;
      numElem = pCab->numElem;

      /* Verificar espaço apontado por pCorr */

      if ( ! CED_VerificarEspaco( pCorr , NULL ) )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "4" ) ;
         #endif
         TST_NotificarFalha( "Controle do espaço acusou erro." ) ;
         numFalhas++;
      } /* if */
      else
      {
         CED_MarcarEspacoAtivo( pCorr );
      } /* else */

      /* Verificar espaço apontado por pOrig */

      if ( ! CED_VerificarEspaco( pOrig , NULL ) )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "5" ) ;
         #endif
         TST_NotificarFalha( "Controle do espaço acusou erro." ) ;
         numFalhas++;
      } /* if */
      else
      {
         CED_MarcarEspacoAtivo( pOrig );
      } /* else */

      /* Verificar espaço apontado por pFinal */

      if ( ! CED_VerificarEspaco( pFinal , NULL ) )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "6" ) ;
         #endif
         TST_NotificarFalha( "Controle do espaço acusou erro." ) ;
         numFalhas++;
      } /* if */
      else
      {
         CED_MarcarEspacoAtivo( pFinal );
      } /* else */

      /* Verificar cabeça */

      calc_numElem = 0;
      pAux = pOrig;
      achou = 0;
      while( pAux != NULL )
      {
         if( pAux == pCorr )
         {
            numElem_correto = -1;
            achou = 1;
         } /* if */

         calc_numElem++;
         pAux = pAux->pProx;

      } /* while */

      if( calc_numElem == 0 && numElem == 0 )
      {
         numElem_correto = -1;
      } /* if */

      if ( TST_CompararInt(  calc_numElem , numElem ,
           "Campo de número de elementos incorreto (percorrendo pela origem)" ) != TST_CondRetOK )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "7" ) ;
         #endif
         numFalhas++;
      } /* if */

      if ( calc_numElem > 0 && TST_CompararInt( achou , 1 ,
           "Não achou elemento corrente (percorrendo pela origem)" ) != TST_CondRetOK )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "8" ) ;
         #endif
         numFalhas++;
      } /* if */

      calc_numElem = 0;
      pAux = pFinal;
      achou = 0;
      while( pAux != NULL )
      {
         if( pAux == pCorr )
         {
            if( numElem_correto == -1 )
            {
               numElem_correto = 1;
            } /* if */
            achou = 1;
         } /* if */

         calc_numElem++;
         pAux = pAux->pAnt;

      } /* while */

      if( calc_numElem == 0 && numElem == 0 && numElem_correto == -1 )
      {
         numElem_correto = 1;
      } /* if */

      /* Verificar espaços alocados dinamicamente */

      CED_MarcarTodosEspacosInativos();
      VerificaMemoria( pCab , LIS_TipoEspacoCabeca );

      CED_InicializarIteradorEspacos();

      while ( CED_ExisteEspacoCorrente() )
      {
         void * Ponteiro = CED_ObterPonteiroEspacoCorrente();

         if( ! CED_EhEspacoAtivo( Ponteiro ) )
         {
            int tipo = CED_ObterTipoEspaco( Ponteiro );

            if( tipo == LIS_TipoEspacoElemento  ||
                tipo == LIS_TipoEspacoCabeca    ||
                tipo == LIS_TipoEspacoEstrutura )
            {
               TST_NotificarFalha( "Vazamento de espaço de memória detectado" );
               numFalhas++;
            } /* if */

         } /* if */

         CED_AvancarProximoEspaco();

      } /* while */

      CED_TerminarIteradorEspacos();

      /* Assertivas quanto ao número de elementos e elemento corrente */

      if( numElem_correto == -1 )
      {
         numElem_correto = 0;
      } /* if */

      if ( TST_CompararInt(  calc_numElem , numElem ,
           "Campo de número de elementos incorreto (percorrendo pelo final)" ) != TST_CondRetOK )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "9" ) ;
         #endif
         numFalhas++;
      } /* if */

      if ( calc_numElem > 0 && TST_CompararInt( achou , 1 ,
           "Não achou elemento corrente (percorrendo pelo final)" ) != TST_CondRetOK )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "10" ) ;
         #endif
         numFalhas++;
      } /* if */

      if( numElem_correto )
      {
         if( numElem < 0 )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "11" ) ;
            #endif
            TST_NotificarFalha( "Número de elementos negativo" ) ;
            numFalhas++;
         } /* if */

         if( numElem == 0 )
         {
            if( pCorr != NULL  )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "12" ) ;
               #endif
               TST_NotificarFalha( "pCorr deve ser NULL para numElem = 0" ) ;
               numFalhas++;
            } /* if */
            if( pOrig != NULL  )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "13" ) ;
               #endif
               TST_NotificarFalha( "pOrig deve ser NULL para numElem = 0" ) ;
               numFalhas++;
            } /* if */
            if( pFinal != NULL  )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "14" ) ;
               #endif
               TST_NotificarFalha( "pFinal deve ser NULL para numElem = 0" ) ;
               numFalhas++;
            } /* if */
         } /* if */
         else if( numElem == 1 )
         {
            if( pCorr == NULL  )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "15" ) ;
               #endif
               TST_NotificarFalha( "pCorr deve ser diferente de NULL para numElem = 1" ) ;
               numFalhas++;
            } /* if */
            if( pOrig == NULL  )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "16" ) ;
               #endif
               TST_NotificarFalha( "pOrig deve ser diferente de NULL para numElem = 1" ) ;
               numFalhas++;
            } /* if */
            if( pFinal == NULL  )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "17" ) ;
               #endif
               TST_NotificarFalha( "pFinal deve ser diferente de NULL para numElem = 1" ) ;
               numFalhas++;
            } /* if */
            if(   TST_CompararPonteiro( pOrig , pFinal ,
                  "pOrig e pFinal devem apontar para o mesmo elemento para numElem = 1" )
                  != TST_CondRetOK )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "18" ) ;
               #endif
               numFalhas++;
            } /* if */
            if(   TST_CompararPonteiro( pOrig , pCorr ,
                  "pOrig e pCorr devem apontar para o mesmo elemento para numElem = 1" )
                  != TST_CondRetOK )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "19" ) ;
               #endif
               numFalhas++;
            } /* if */
         } /* else if */
         else if( numElem > 1 )
         {
            if( pCorr == NULL  )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "20" ) ;
               #endif
               TST_NotificarFalha( "pCorr deve ser diferente de NULL para numElem > 1" ) ;
               numFalhas++;
            } /* if */
            if( pOrig == NULL  )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "21" ) ;
               #endif
               TST_NotificarFalha( "pOrig deve ser diferente de NULL para numElem > 1" ) ;
               numFalhas++;
            } /* if */
            if( pFinal == NULL  )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "22" ) ;
               #endif
               TST_NotificarFalha( "pFinal deve ser diferente de NULL para numElem > 1" ) ;
               numFalhas++;
            } /* if */
         } /* else */
      
         /* Verificar elemento corrente */

         if( numElem > 0 )
         {
            if ( ! CED_VerificarEspaco( pCorr , NULL ) )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "23" ) ;
               #endif
               TST_NotificarFalha( "Controle do espaço acusou erro." ) ;
               numFalhas++;
            } /* if */
            if ( TST_CompararInt( LIS_TipoEspacoElemento ,
              CED_ObterTipoEspaco( pCorr ) ,
              "Tipo do espaço de dados não é elemento." ) != TST_CondRetOK )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "24" ) ;
               #endif
               numFalhas++;
            } /* if */
            if( TST_CompararPonteiro( pCab , pCorr->pCab ,
                "Elemento corrente não faz parte da lista" ) != TST_CondRetOK )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "25" ) ;
               #endif
               numFalhas++;
            } /* if */
            if( pCorr->pAnt == NULL )
            {
               if( TST_CompararPonteiro( pCorr , pCorr->pCab->pOrigemLista ,
                   "Elemento corrente não é origem da lista" ) != TST_CondRetOK )
               {
                  #ifdef _DEBUG
                     CNT_CONTAR( "26" ) ;
                  #endif
                  numFalhas++;
               } /* if */
            } /* else */
            else
            {
               if( TST_CompararPonteiro( pCorr , pCorr->pAnt->pProx ,
                   "Elemento corrente não está corretamente encadeado pela esquerda" ) != TST_CondRetOK )
               {
                  #ifdef _DEBUG
                     CNT_CONTAR( "27" ) ;
                  #endif
                  numFalhas++;
               } /* if */
            } /* else */
            if( pCorr->pProx == NULL )
            {
               if( TST_CompararPonteiro( pCorr , pCorr->pCab->pFimLista ,
                   "Elemento corrente não é fim da lista" ) != TST_CondRetOK )
               {
                  #ifdef _DEBUG
                     CNT_CONTAR( "28" ) ;
                  #endif
                  numFalhas++;
               } /* if */
            } /* else */
            else
            {
               if( TST_CompararPonteiro( pCorr , pCorr->pProx->pAnt ,
                   "Elemento corrente não está corretamente encadeado pela direita" ) != TST_CondRetOK )
               {
                  #ifdef _DEBUG
                     CNT_CONTAR( "29" ) ;
                  #endif
                  numFalhas++;
               } /* if */
            } /* else */
            if( TST_CompararChar( TipoValor , pCorr->TipoValor ,
                "Elemento corrente tem tipo de valor diferente da cabeça" ) != TST_CondRetOK )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "30" ) ;
               #endif
               numFalhas++;
            } /* if */
         } /* if */
      } /* if */
      else
      {
         #ifdef _DEBUG
            CNT_CONTAR( "31" ) ;
         #endif
         TST_NotificarFalha( "O número de elementos é inconsistente" ) ;
         numFalhas++;
      } /* else */

      return numFalhas;

   } /* Fim função: LIS  &Verificar Lista */

/***************************************************************************
*
*  Função: LIS  &Deturpar lista
*  ****/

   void LIS_Deturpar( void * pListaParam ,
                      LIS_tpModosDeturpacao ModoDeturpar )
   {
      LIS_tppLista pLista = NULL;
      LIS_tppElemLista pCorr = NULL;

      if( pListaParam == NULL )
      {
         return ;
      } /* if */

      pLista = (LIS_tppLista) pListaParam;
      pCorr = pLista->pElemCorr;

      switch ( ModoDeturpar )
      {

      case LIS_ModoDeturpacaoEliminaCorr:
         /* Elimina o elemento corrente da lista */

         free( pCorr );

         break;
         /* fim ativa: Elimina o elemento corrente da lista */

      case LIS_ModoDeturpacaoProxNULL:
         /* Atribui NULL ao ponteiro para o próximo nó */

         pCorr->pProx = NULL;

         break;
         /* fim ativa: Atribui NULL ao ponteiro para o próximo nó */

      case LIS_ModoDeturpacaoAntNULL:
         /* Atribui NULL ao ponteiro para o nó anterior */

         pCorr->pAnt = NULL;

         break;
         /* fim ativa: Atribui NULL ao ponteiro para o nó anterior */

      case LIS_ModoDeturpacaoProxLixo:
         /* Atribui lixo ao ponteiro para o próximo nó */

         pCorr->pProx = ( LIS_tppElemLista )( EspacoLixo );

         break;
         /* fim ativa: Atribui lixo ao ponteiro para o próximo nó */

      case LIS_ModoDeturpacaoAntLixo:
         /* Atribui lixo ao ponteiro para o nó anterior */

          pCorr->pAnt = ( LIS_tppElemLista )( EspacoLixo );

         break;
         /* fim ativa: Atribui lixo ao ponteiro para o nó anterior */

      case LIS_ModoDeturpacaoConteudoNULL:
         /* Atribui NULL ao ponteiro para o conteúdo do nó */

         pCorr->pValor = NULL;

         break;
         /* fim ativa: Atribui NULL ao ponteiro para o conteúdo do nó */

      case LIS_ModoDeturpacaoAlteraTipoNo:
         /* Altera o tipo de estrutura apontado no nó */

         pCorr->TipoValor += 1;

         break;
         /* fim ativa: Altera o tipo de estrutura apontado no nó */

      case LIS_ModoDeturpacaoDesencadeiaNo:
         /* Desencadeia nó sem liberá-lo com free */

         if ( pCorr->pAnt == NULL )
         {
            pLista->pOrigemLista = pCorr->pProx;
            pLista->pElemCorr = pCorr->pProx;
         }/* if */
         else
         {
            pCorr->pAnt->pProx = pCorr-> pProx;
            pLista->pElemCorr = pCorr->pAnt;
         }/* else */


         if ( pCorr->pProx == NULL )
         {
            pLista->pFimLista = pCorr->pAnt;
         }/* if */
         else
         {
            pCorr->pProx->pAnt = pCorr-> pAnt;
         }/* else */

         break;
         /* fim ativa: Desencadeia nó sem liberá-lo com free */

      case LIS_ModoDeturpacaoPontCorrNULL:
         /* Atribui NULL ao ponteiro corrente */

         pLista->pElemCorr = NULL;

         break;
         /* fim ativa: Atribui NULL ao ponteiro corrente */

      case LIS_ModoDeturpacaoPontOrigNULL:
         /* Atribui NULL ao ponteiro de origem */

         pLista->pOrigemLista = NULL;

         break;
         /* fim ativa: Atribui NULL ao ponteiro de origem */

      case LIS_ModoDeturpacaoPontFimNULL:
         /* Atribui NULL ao ponteiro de final */

         pLista->pFimLista = NULL;

         break;
         /* fim ativa: Atribui NULL ao ponteiro de final */

      } /* switch */
      
   } /* Fim função: LIS  &Deturpar lista */

#endif

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: LIS  -Verificar memória
*
*  $ED Descrição da função
*     Recursivamente marca espaços ativos no LEA.
*
***********************************************************************/

   void VerificaMemoria ( void * Ponteiro , int IdTipoEspaco )
   {
      LIS_tppLista pLista = NULL;
      LIS_tppElemLista pElem = NULL, pElemLoop = NULL;
      LIS_tpCondRet RetLis = LIS_CondRetOK;

      if( ! CED_VerificarEspaco( Ponteiro , NULL ) )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "32" ) ;
         #endif
         return;
      } /* if */

      if ( Ponteiro == NULL || CED_EhEspacoAtivo( Ponteiro ) )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "33" ) ;
         #endif
         return;
      } /* if */

      CED_DefinirTipoEspaco( Ponteiro , IdTipoEspaco );

      switch( IdTipoEspaco )
      {
         case LIS_TipoEspacoEstrutura:
            /* Estrutura apontada por elemento */

            #ifdef _DEBUG
               CNT_CONTAR( "34" ) ;
            #endif

            CED_MarcarEspacoAtivo( Ponteiro );
            break;

         case LIS_TipoEspacoCabeca:
            /* Cabeça de lista */

            #ifdef _DEBUG
               CNT_CONTAR( "35" ) ;
            #endif

            pLista = (LIS_tppLista) Ponteiro;

            CED_MarcarEspacoAtivo( pLista );

            pElemLoop = pLista->pOrigemLista;
            while( pElemLoop != NULL )
            {
               VerificaMemoria( pElem , LIS_TipoEspacoElemento );
               pElemLoop = pElemLoop->pProx;
            } /* while */

            VerificaMemoria( pLista->pElemCorr , LIS_TipoEspacoElemento );
            VerificaMemoria( pLista->pFimLista , LIS_TipoEspacoElemento );
            VerificaMemoria( pLista->pOrigemLista , LIS_TipoEspacoElemento );

            break;

         case LIS_TipoEspacoElemento:
            /* Elemento de lista */

            #ifdef _DEBUG
               CNT_CONTAR( "36" ) ;
            #endif

            pElem = (LIS_tppElemLista) Ponteiro;

            CED_MarcarEspacoAtivo( pElem );

            VerificaMemoria( pElem->pCab , LIS_TipoEspacoCabeca );
            VerificaMemoria( pElem->pAnt , LIS_TipoEspacoElemento );
            VerificaMemoria( pElem->pProx , LIS_TipoEspacoElemento );
            VerificaMemoria( pElem->pValor , LIS_TipoEspacoEstrutura );

            break;

         default:

            CED_MarcarEspacoAtivo( Ponteiro );

            break;

      } /* switch */

   } /* Fim função: LIS  -Verificar memória */

/***********************************************************************
*
*  $FC Função: LIS  -Liberar elemento da lista
*
*  $ED Descrição da função
*     Elimina os espaços apontados pelo valor do elemento e o
*     próprio elemento.
*
***********************************************************************/

   void LiberarElemento( LIS_tppLista   pLista ,
                         tpElemLista  * pElem   )
   {

      if ( ( pLista->ExcluirValor != NULL )
        && ( pElem->pValor != NULL        ))
      {
         pLista->ExcluirValor( pElem->pValor ) ;
      } /* if */

      free( pElem ) ;

      pLista->numElem-- ;

   } /* Fim função: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Função: LIS  -Criar o elemento
*
***********************************************************************/

   tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                void *       pValor
#ifdef _DEBUG
                              , char TipoValor
                              , unsigned long tam
#endif
                              )
   {

      tpElemLista * pElem ;

      pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )) ;
      if ( pElem == NULL )
      {
         return NULL ;
      } /* if */

      pElem->pValor = pValor ;
      pElem->pAnt   = NULL  ;
      pElem->pProx  = NULL  ;

#ifdef _DEBUG

      pElem->TipoValor = TipoValor;
      pElem->pCab = pLista;
      pElem->tam = tam;
      
      CED_DefinirTipoEspaco( pElem , LIS_TipoEspacoElemento );

#endif

      pLista->numElem ++ ;

      return pElem ;

   } /* Fim função: LIS  -Criar o elemento */


/***********************************************************************
*
*  $FC Função: LIS  -Limpar a cabeça da lista
*
***********************************************************************/

   void LimparCabeca( LIS_tppLista pLista )
   {

      pLista->pOrigemLista = NULL ;
      pLista->pFimLista = NULL ;
      pLista->pElemCorr = NULL ;
      pLista->numElem   = 0 ;

   } /* Fim função: LIS  -Limpar a cabeça da lista */

/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/

