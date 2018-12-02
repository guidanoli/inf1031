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
*     7       nag       30/nov/2018 deturpar
*     6       gui       30/nov/2018 contadores, verificar
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

         int tam ;
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
                                       , int tam
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
                                          , int tam
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
                                          , int tam
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
      int achou , numElem , calc_numElem, numElem_correto = 0 , LixoNosPonteiros = 0 ;

      /*
      
      Variáveis locais:
      
      achou             1 se achou pCorr percorrendo a lista, 0 caso contrário.
      numElem           número de elementos acusado pela cabeça da lista
      calc_numElem      número de elementos calculado ao percorrer a lista pelos dois sentidos.
      num_Elem_correto  -1, se numElem == calc_numElem ao percorrer por pOrig
                        1, se numElem == calc_numElem ao percorrer por pOrig e por pFinal
                        0, se algum dos dois percursos resultou em numElem != calc_numElem
      LixoNosPonteiros  0, se nenhum ponteiro aponta para lixo
                        1, se algum ponteiro aponta para lixo

      */

      int numFalhas = 0;

      if( pListaParam == NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "1" ) ;
         #endif
         TST_NotificarFalha( "Tentou verificar cabeça de lista inexistente." ) ;

         /* Função é abortada antes que o programa voe. */
         return 1;
      } /* if */

      if ( ! CED_VerificarEspaco( pListaParam , NULL ) )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "2" ) ;
         #endif
         TST_NotificarFalha( "Controle do espaço acusou erro." ) ;
         
         /* Função é abortada antes que o programa voe. */
         return 1;
      } /* if */

      if ( TST_CompararInt( LIS_TipoEspacoCabeca ,
           CED_ObterTipoEspaco( pListaParam ) ,
           "Id do tipo do espaço de dados não é cabeça de lista." ) != TST_CondRetOK )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "3" ) ;
         #endif

         /* Função é abortada antes que o programa voe. */
         return 1;
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
         LixoNosPonteiros = 1;
         numFalhas++;
      } /* if */
      else if ( pCorr != NULL )
      {
         if( TST_CompararInt( LIS_TipoEspacoElemento ,
             CED_ObterTipoEspaco( pCorr ) ,
             "Id do tipo do espaço de dados não é elemento." ) != TST_CondRetOK )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "4b" ) ;
            #endif

            /* Função é abortada antes que o programa voe. */
            LixoNosPonteiros = 1;
            numFalhas++;
         } /* if */
         else
         {
            if ( ! CED_VerificarEspaco( pCorr->pAnt , NULL ) )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "CorrAntLixo" ) ;
               #endif
               TST_NotificarFalha( "Controle do espaço acusou erro." ) ;
               LixoNosPonteiros = 1;
               numFalhas++;
            } /* if */
            else if ( pCorr->pAnt != NULL )
            {
               if( TST_CompararInt( LIS_TipoEspacoElemento ,
                     CED_ObterTipoEspaco( pCorr->pAnt ) ,
                     "Id do tipo do espaço de dados não é elemento." ) != TST_CondRetOK )
               {
                  #ifdef _DEBUG
                     CNT_CONTAR( "CorrAntNaoElem" ) ;
                  #endif

                  /* Função é abortada antes que o programa voe. */
                  LixoNosPonteiros = 1;
                  numFalhas++;
               } /* if */
            } /* else if */

            if ( ! CED_VerificarEspaco( pCorr->pProx , NULL ) )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "CorrProxLixo" ) ;
               #endif
               TST_NotificarFalha( "Controle do espaço acusou erro." ) ;
               LixoNosPonteiros = 1;
               numFalhas++;
            } /* if */
            else if ( pCorr->pProx != NULL )
            {
               if( TST_CompararInt( LIS_TipoEspacoElemento ,
                     CED_ObterTipoEspaco( pCorr->pProx ) ,
                     "Id do tipo do espaço de dados não é elemento." ) != TST_CondRetOK )
               {
                  #ifdef _DEBUG
                     CNT_CONTAR( "CorrProxNaoElem" ) ;
                  #endif

                  /* Função é abortada antes que o programa voe. */
                  LixoNosPonteiros = 1;
                  numFalhas++;
               } /* if */
            } /* else if */
         } /* else */

      } /* else if */

      /* Verificar espaço apontado por pOrig */

      if ( ! CED_VerificarEspaco( pOrig , NULL ) )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "5" ) ;
         #endif
         TST_NotificarFalha( "Controle do espaço acusou erro." ) ;
         LixoNosPonteiros = 1;
         numFalhas++;
      } /* if */
      else if ( pOrig != NULL )
      {
         if( TST_CompararInt( LIS_TipoEspacoElemento ,
             CED_ObterTipoEspaco( pOrig ) ,
             "Id do tipo do espaço de dados não é elemento." ) != TST_CondRetOK )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "5b" ) ;
            #endif

            /* Função é abortada antes que o programa voe. */
            LixoNosPonteiros = 1;
            numFalhas++;
         } /* if */
      } /* else if */

      /* Verificar espaço apontado por pFinal */

      if ( ! CED_VerificarEspaco( pFinal , NULL ) )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "6" ) ;
         #endif
         TST_NotificarFalha( "Controle do espaço acusou erro." ) ;
         LixoNosPonteiros = 1;
         numFalhas++;
      } /* if */
      else if ( pFinal != NULL )
      {
         if( TST_CompararInt( LIS_TipoEspacoElemento ,
             CED_ObterTipoEspaco( pFinal ) ,
             "Id do tipo do espaço de dados não é elemento." ) != TST_CondRetOK )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "6b" ) ;
            #endif

            /* Função é abortada antes que o programa voe. */
            LixoNosPonteiros = 1;
            numFalhas++;
         } /* if */
      } /* else if */
      
      if( LixoNosPonteiros ) 
      {
         return numFalhas;
      } /* if */

      /* Verificar cabeça */

      calc_numElem = 0;
      pAux = pOrig;
      achou = 0;
      while( pAux != NULL )
      {
         if( pAux == pCorr )
         {
            achou = 1;
         } /* if */

         calc_numElem++;
         pAux = pAux->pProx;

      } /* while */

      if( calc_numElem == numElem )
      {
         numElem_correto = -1;
      } /* if */

      if ( TST_CompararInt(  calc_numElem , numElem ,
           "Campo de número de elementos incorreto (percorrendo pela origem)." ) != TST_CondRetOK )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "7" ) ;
         #endif

         numFalhas++;
      } /* if */

      if ( calc_numElem > 0 && achou != 1 )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "8" ) ;
         #endif

         TST_NotificarFalha( "Não achou elemento corrente (percorrendo pela origem)." );
         numFalhas++;
      } /* if */

      calc_numElem = 0;
      pAux = pFinal;
      achou = 0;
      while( pAux != NULL )
      {
         if( pAux == pCorr )
         {
            achou = 1;
         } /* if */

         calc_numElem++;
         pAux = pAux->pAnt;

      } /* while */

      /* Este if certifica-se que, mesmo não tendo nenhum elemento,
         uma lista vazia está com o número correto de elementos (0) */
      if( calc_numElem == numElem && numElem_correto == -1 )
      {
         numElem_correto = 1;
      } /* if */

      /* Assertivas quanto ao número de elementos e elemento corrente */

      if( numElem_correto == -1 )
      {
         numElem_correto = 0;
      } /* if */

      if ( TST_CompararInt(  calc_numElem , numElem ,
           "Campo de número de elementos incorreto (percorrendo pelo final)." ) != TST_CondRetOK )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "9" ) ;
         #endif

         numFalhas++;
      } /* if */

      if ( calc_numElem > 0 && achou != 1 )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "10" ) ;
         #endif

         TST_NotificarFalha( "Não achou elemento corrente (percorrendo pelo final)." );
         numFalhas++;
      } /* if */

      /* Verificar espaços alocados dinamicamente */

      CED_MarcarTodosEspacosInativos();
      VerificaMemoria( pCab , LIS_TipoEspacoCabeca );

      /* Sempre haverá ao menos um espaço corrente, pois se chegou até aqui, é porque
         o ponteiro para lista aponta para um espaço de dados válido, portanto sempre
         entrará no loop da função LIS_LiberarEspacosInativos ao menos uma vez */

      numFalhas += LIS_LiberarEspacosInativos();
      
      if( numElem < 0 )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "11" ) ;
         #endif
         TST_NotificarFalha( "Número de elementos negativo." ) ;
         numFalhas++;
      } /* if */

      if( numElem_correto )
      {
         if( numElem == 0 )
         {
            if( pCorr != NULL  )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "12" ) ;
               #endif
               TST_NotificarFalha( "pCorr deve ser NULL para numElem = 0." ) ;
               numFalhas++;
            } /* if */
            
            /* --------------------------------------------------------------------------------

               >> ESCLARECIMENTO
            
               Segundo as assertivas estruturais do modelo de lista auto-verificável,
               é necessário que TODOS os ponteiros da cabeça de lista sejam NULOS.
               Neste if, é verificado apenas se pCorr é nulo. Isso porque se chegou-se
               até aqui, é porque: numElem == 0 , numElem_correto = 1. Se o segundo é
               verdadeiro, então, com certeza, o contador atestado pela cabeça (numElem)
               está correto, e é idêntico à calc_numElem, os contadores calculados ao
               percorrer-se a lista pelos ponteiros pFinal e pOrigem. Se estes contadores
               calculados são zero, isso significa que pFinal = pOrigem = NULL , pois,
               caso não fossem, somariam 1 ao contador, e numElem_correto = 0. E, mesmo
               que não fossem NULL, mas apontassem para lixo, o verificador abortaria
               antes de chegar até este ponto do código. Portanto, essas assertivas
               estruturais foram já verificadas e não deve haver contadores aqui para
               verificar se pFinal != NULL ou pOrig != NULL , pois sempre serão e o contador
               indicará zero.

               -------------------------------------------------------------------------------*/

         } /* if */
         else if( numElem == 1 )
         {
            if( pCorr == NULL  )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "15" ) ;
               #endif
               TST_NotificarFalha( "pCorr deve ser diferente de NULL para numElem = 1." ) ;
               numFalhas++;
            } /* if */
            
            /* --------------------------------------------------------------------------------

               >> ESCLARECIMENTO
            
               De forma similar ao esclarecimento anterior, não é possível chegar aqui com
               uma cabeça de lista com ambos pFinal e pOrigem nulos, porque isso causaria
               em calc_numElem = 0, mas como o número na cabeça é 1, numElem_correto = 0.
               Como não é possível constatar o número de elementos da lista, as assertivas
               estruturais quanto a uma lista unitária não serão verificadas.

               -------------------------------------------------------------------------------*/
            
            if(   TST_CompararPonteiro( pFinal , pCorr ,
                  "pFinal e pCorr devem apontar para o mesmo elemento para numElem = 1." )
                  != TST_CondRetOK )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "17" ) ;
               #endif
               numFalhas++;
            } /* if */

            if(   TST_CompararPonteiro( pOrig , pFinal ,
                  "pOrig e pFinal devem apontar para o mesmo elemento para numElem = 1." )
                  != TST_CondRetOK )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "18" ) ;
               #endif
               numFalhas++;
            } /* if */

            if(   TST_CompararPonteiro( pOrig , pCorr ,
                  "pOrig e pCorr devem apontar para o mesmo elemento para numElem = 1." )
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
               TST_NotificarFalha( "pCorr deve ser diferente de NULL para numElem > 1." ) ;
               numFalhas++;
            } /* if */

            /* --------------------------------------------------------------------------------

               >> ESCLARECIMENTO
            
               De forma similar ao esclarecimento anterior, não é possível chegar aqui com
               uma cabeça de lista com ambos pFinal e pOrigem nulos, porque isso causaria
               em calc_numElem = 0, mas como o número na cabeça é >1, numElem_correto = 0.
               Como não é possível constatar o número de elementos da lista, as assertivas
               estruturais quanto a uma lista com mais de um elemento não serão verificadas.

               -------------------------------------------------------------------------------*/

         } /* else */
      
         /* Verificar elemento corrente */

         if( numElem > 0 )
         {
            /* Por mais que seja óbvio que para uma lista não-vazia, o ponteiro
               corrento não pode ser nulo, é necessário esta verificação pois
               há casos de teste justamente com este cenário, que já foi checado
               e apresentado como falha pelo verificador. Portanto, este if é
               apenas para o programa não voar. */

            if( pCorr != NULL )
            {
               if( TST_CompararPonteiro( pCab , pCorr->pCab ,
                   "Elemento corrente não faz parte da lista." ) != TST_CondRetOK )
               {
                  #ifdef _DEBUG
                     CNT_CONTAR( "25" ) ;
                  #endif
                  numFalhas++;
               } /* if */

               /* Verificar pAnt */

               if( pCorr->pAnt == NULL )
               {
                  if( pCorr->pCab != NULL )
                  {
                     if( TST_CompararPonteiro( pCorr , pCorr->pCab->pOrigemLista ,
                         "Elemento corrente tem pAnt nulo mas não é origem da lista." ) != TST_CondRetOK )
                     {
                        #ifdef _DEBUG
                           CNT_CONTAR( "26" ) ;
                        #endif
                        numFalhas++;
                     } /* if */
                  } /* if */
               } /* else */
               else
               {
                  if( TST_CompararPonteiro( pCorr , pCorr->pAnt->pProx ,
                      "Elemento corrente não está corretamente encadeado pela esquerda." ) != TST_CondRetOK )
                  {
                     #ifdef _DEBUG
                        CNT_CONTAR( "27" ) ;
                     #endif
                     numFalhas++;
                  } /* if */
               } /* else */

               /* Verificar pProx */

               if( pCorr->pProx == NULL )
               {
                  if( pCorr->pCab != NULL )
                  {
                     if( TST_CompararPonteiro( pCorr , pCorr->pCab->pFimLista ,
                         "Elemento corrente tem pProx nulo mas não é fim da lista." ) != TST_CondRetOK )
                     {
                        #ifdef _DEBUG
                           CNT_CONTAR( "28" ) ;
                        #endif
                        numFalhas++;
                     } /* if */
                  } /* if */
               } /* else */
               else
               {
                  if( TST_CompararPonteiro( pCorr , pCorr->pProx->pAnt ,
                      "Elemento corrente não está corretamente encadeado pela direita." ) != TST_CondRetOK )
                  {
                     #ifdef _DEBUG
                        CNT_CONTAR( "29" ) ;
                     #endif
                     numFalhas++;
                  } /* if */
               } /* else */

               /* Verificar TipoValor */

               if( TST_CompararChar( TipoValor , pCorr->TipoValor ,
                   "Elemento corrente tem tipo de valor diferente da cabeça." ) != TST_CondRetOK )
               {
                  #ifdef _DEBUG
                     CNT_CONTAR( "30" ) ;
                  #endif
                  numFalhas++;
               } /* if */
               
               /* Verificar tamanho negativo */

               if( pCorr->tam < 0 )
               {
                  #ifdef _DEBUG
                     CNT_CONTAR( "TAM1" ) ;
                  #endif
                  TST_NotificarFalha( "Elemento corrente acusa tamanho negativo" );
                  numFalhas++;
               } /* if */

               if ( ! CED_VerificarEspaco( pCorr->pValor , NULL ) )
               {
                  #ifdef _DEBUG
                     CNT_CONTAR( "TAM2" ) ;
                  #endif
                  TST_NotificarFalha( "Controle do espaço acusou erro." ) ;
                  LixoNosPonteiros = 1;
                  numFalhas++;
               } /* if */
               else if ( pCorr->pValor != NULL )
               {
                  if( TST_CompararInt( LIS_TipoEspacoEstrutura ,
                      CED_ObterTipoEspaco( pCorr->pValor ) ,
                      "Id do tipo do espaço de dados não é estrutura." ) != TST_CondRetOK )
                  {
                     #ifdef _DEBUG
                        CNT_CONTAR( "TAM3" ) ;
                     #endif

                     /* Função é abortada antes que o programa voe. */
                     LixoNosPonteiros = 1;
                     numFalhas++;
                  } /* if */
               } /* else if */

               /* Abortar caso pValor não aponte
                  para estrutura ou aponte para lixo */

               if( LixoNosPonteiros )
               {
                  return numFalhas;
               } /* if */

               /* Verificar tamanho dependendo de pValor */

               if( pCorr->pValor == NULL )
               {
                  if( pCorr->tam != 0 )
                  {
                     #ifdef _DEBUG
                        CNT_CONTAR( "TAM4" ) ;
                     #endif
                     TST_NotificarFalha( "Elemento corrente sem estrutura acusa tamanho diferente de zero" );
                     numFalhas++;
                  } /* if */
               } /* if */
               else
               {
                  if( TST_CompararInt( pCorr->tam ,
                     CED_ObterTamanhoValor( pCorr->pValor ) ,
                     "Tamanho da estrutura apontara pelo elemento corrente não confere" ) != TST_CondRetOK )
                  {
                     #ifdef _DEBUG
                        CNT_CONTAR( "TAM5" ) ;
                     #endif
                     numFalhas++;
                  } /* if */
               } /* else */

            } /* if */
         } /* if */
      } /* if */
      else
      {
         #ifdef _DEBUG
            CNT_CONTAR( "31" ) ;
         #endif
         TST_NotificarFalha( "O número de elementos é inconsistente." ) ;
         numFalhas++;
      } /* else */

      return numFalhas;

   } /* Fim função: LIS  &Verificar Lista */

/***************************************************************************
*
*  Função: LIS  &Deturpar lista
*  ****/

   void LIS_Deturpar( void ** pListaParam ,
                      LIS_tpModosDeturpacao ModoDeturpar )
   {
      LIS_tppLista pLista = NULL;
      LIS_tppElemLista pCorr = NULL;
      LIS_tppElemLista Elem = NULL;
      char * pValorDummy = NULL;

      /* Se o pListaParam for nulo, a função é abortada 
         para que o programa não voe */
      if( pListaParam == NULL || *pListaParam == NULL )
      {
         return ;
      } /* if */

      pLista = (LIS_tppLista) *pListaParam;
      pCorr = pLista->pElemCorr;

      /* Modos de deturpação que usam pCorr não podem ser rodados
         quando pCorr for nulo, senão o programa voa */
      if( ModoDeturpar != LIS_ModoDeturpacaoPontCorrNULL &&
          ModoDeturpar != LIS_ModoDeturpacaoPontOrigNULL &&
          ModoDeturpar != LIS_ModoDeturpacaoPontFimNULL  &&
          ModoDeturpar != LIS_ModoDeturpacaoEliminaLista &&
          ModoDeturpar != LIS_ModoDeturpacaoCorrLixo &&
          ModoDeturpar != LIS_ModoDeturpacaoOrigLixo &&
          ModoDeturpar != LIS_ModoDeturpacaoFinalLixo &&
          ModoDeturpar != LIS_ModoDeturpacaoCorrElemNovo &&
          ModoDeturpar != LIS_ModoDeturpacaoCorrTipoErrado && 
          ModoDeturpar != LIS_ModoDeturpacaoOrigTipoErrado && 
          ModoDeturpar != LIS_ModoDeturpacaoFinalTipoErrado )
      {
         if( pCorr == NULL )
         {
            return ;
         } /* if */
      } /* if */

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

         // Não faz pLista->pElemCorr apontar para pProx
         // Assim, o contador 8 e 10 será atendido

         if ( pCorr->pAnt == NULL )
         {
            pLista->pOrigemLista = pCorr->pProx;
         } /* if */
         else
         {
            pCorr->pAnt->pProx = pCorr-> pProx;
         } /* else */

         if ( pCorr->pProx == NULL )
         {
            pLista->pFimLista = pCorr->pAnt;
         } /* if */
         else
         {
            pCorr->pProx->pAnt = pCorr-> pAnt;
         } /* else */

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

      case LIS_ModoDeturpacaoEliminaLista:
         /* Elimina lista */

         free(pLista);

         break;

      case LIS_ModoDeturpacaoCorrLixo:
         /* Atribui lixo ao ponteiro para nó corrente */

         pLista->pElemCorr = (LIS_tppElemLista)( EspacoLixo );

         break;

      case LIS_ModoDeturpacaoOrigLixo:
         /* Atribui lixo ao ponteiro para nó origem */

         pLista->pOrigemLista = (LIS_tppElemLista)( EspacoLixo );

         break;

      case LIS_ModoDeturpacaoFinalLixo:
         /* Atribui lixo ao ponteiro para nó final */

         pLista->pFimLista = (LIS_tppElemLista)( EspacoLixo );

         break;

      case LIS_ModoDeturpacaoNumElemNegativo:
         /* Atribui valor negativo ao contador de elementos */

         pLista->numElem = -1;

         break;

      case LIS_ModoDeturpacaoCorrElemNovo:
         /* Fazer ponteiro corrente apontar para novo elemento */

         pValorDummy = (char *) malloc(8);
         
         if( pValorDummy == NULL )
         {
            TST_NotificarFalha( "Faltou memória" );
            return;
         } /* if */

         strcpy(pValorDummy,"dummy");

         Elem = CriarElemento( pLista, pValorDummy, 's', 8 );

         pLista->pElemCorr = Elem;
         pLista->numElem --;

         break;

      case LIS_ModoDeturpacaoCorrTipoErrado:
            /* Fazer ponteiro corrente apontar para lista */

         pLista->pElemCorr = (LIS_tppElemLista) pLista;

         break;

      case LIS_ModoDeturpacaoOrigTipoErrado:
            /* Fazer ponteiro origem apontar para lista */

         pLista->pOrigemLista = (LIS_tppElemLista) pLista;

         break;

      case LIS_ModoDeturpacaoFinalTipoErrado:
            /* Fazer ponteiro final apontar para lista */

         pLista->pFimLista = (LIS_tppElemLista) pLista;

         break;

      case LIS_ModoDeturpacaoOrigElemNovo:
            /* Fazer ponteiro origem apontar para novo elemento */

         pValorDummy = (char *) malloc( 8 );
         
         if( pValorDummy == NULL )
         {
            TST_NotificarFalha( "Faltou memória" );
            return;
         } /* if */

         strcpy(pValorDummy,"dummy");

         Elem = CriarElemento( pLista, pValorDummy, 's', 8 );

         pLista->pOrigemLista = Elem;
         pLista->numElem --;

         break;

      case LIS_ModoDeturpacaoElemCorrCabNULL:
         /* Fazer pCab do elemento corrente NULL */

         pCorr->pCab = NULL;

         break;

      case LIS_ModoDeturpacaoDuplicarElem:
         /* Duplica elemento de modo que se possa continuar
               a percorrer em ambos os sentidos por caminhos diferentes */

         pValorDummy = (char *) malloc(8);
         
         if( pValorDummy == NULL )
         {
            TST_NotificarFalha( "Faltou memória" );
            return;
         } /* if */

         strcpy(pValorDummy,"dummy");

         Elem = CriarElemento( pLista, pValorDummy, 's', 8 );

         if( pCorr->pProx != NULL )
         {
            pCorr->pProx->pAnt = Elem;
         } /* if */

         Elem->pProx = pCorr->pProx;
         Elem->pAnt = pCorr->pAnt;

         pLista->numElem --;

         break;

      case LIS_ModoDeturpacaoTamNegativo:
         /* Faz tam = -1 */

         pCorr->tam = -1;

         break;

      case LIS_ModoDeturpacaoTamUm:
         /* Faz tam = 1 */

         pCorr->tam = 1;

         break;

      case LIS_ModoDeturpacaoConteudoLixo:
         /* Faz pValor apontar para lixo */

         pCorr->pValor = EspacoLixo;

         break;

      case LIS_ModoDeturpacaoConteudoApontaElem:
         /* Faz pValor apontar para elemento */

         pCorr->pValor = pCorr;

         break;

      case LIS_ModoDeturpacaoAntApontaCab:
         /* Faz pAnt do elemento corrente apontar para cabeça */

         pCorr->pAnt = ( LIS_tppElemLista ) pLista;

         break;

      case LIS_ModoDeturpacaoProxApontaCab:
         /* Faz pProx do elemento corrente apontar para cabeça */

         pCorr->pProx = ( LIS_tppElemLista ) pLista;

         break;

      default:
         
         TST_NotificarFalha( "Modo de deturpação não reconhecido" );

         break;

      } /* switch */
      
   } /* Fim função: LIS  &Deturpar lista */

#endif

/***************************************************************************
*
*  Função: LIS  &Liberar espaços inativos relativos ao módulo Lista
*  ****/

   int LIS_LiberarEspacosInativos ( void )
   {
      int numFalhas = 0;

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
               #ifdef _DEBUG
                  CNT_CONTAR( "MEM1" ) ;
               #endif
               TST_NotificarFalha( "Vazamento de espaço de memória detectado." );
               CED_ExcluirEspacoCorrente( );
               numFalhas++;
            } /* if */
            else
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "MEM2" ) ;
               #endif
               CED_AvancarProximoEspaco();
            } /* else */

         } /* if */
         else
         {
            #ifdef _DEBUG
               CNT_CONTAR( "MEM3" ) ;
            #endif
            CED_AvancarProximoEspaco();
         } /* else */

      } /* while */

      CED_TerminarIteradorEspacos();

      return numFalhas;

   } /* Fim função: LIS  -Liberar espaços inativos relativos ao módulo Lista */

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
                              , int tam
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
      
      CED_DefinirTipoEspaco( pValor , LIS_TipoEspacoEstrutura );
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

