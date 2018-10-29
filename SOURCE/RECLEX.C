/***************************************************************************
*  $MCI Módulo de implementação: RLEX Reconhecedor Léxico
*
*  Arquivo gerado:              RECLEX.c
*  Letras identificadoras:      RLEX
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores:   avs   Arndt Von Staa
*             gui   Guilherme Dantas
*             cai   Caique Molina
*             nag   Nagib Suaid
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     0       gui   19/10/2018  Início do desenvolvimento (baseado em TSTGRF.c)
*     0.1     gui   26/10/2018  criar e destruir rec.lex.
*     0.2     gui   26/10/2018  inserir e remover estado
*     0.3     gui   26/10/2018  inserir e remover transições
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "GRAFO.H"
#include    "PILHA.H"

#define CRIAR_RLEX_CMD           "=criarlexrec"
#define DESTRUIR_RLEX_CMD        "=destruirlexrec"
#define INSERIR_ESTADO_CMD       "=inserirestado"
#define REMOVER_ESTADO_CMD       "=removerestado"
#define INSERIR_TRANSICAO_CMD    "=inserirtransicao"
#define REMOVER_TRANSICAO_CMD    "=removertransicao"
#define RECONHECER_STRING_CMD    "=reconhecerstring"
#define RECONHECER_ARQUIVO_CMD   "=reconhecerarquivo"

#define DIM_NOME_ESTADO    30
#define DIM_ROTULO         30
#define TAMANHO_BUFFER_STR 500

#define RLEX_TRUE  1
#define RLEX_FALSE 0

/* Ponteiro para estado */

   typedef struct tagEstado * RLEX_tppEstado;

/***********************************************************************
*
*  $TC Tipo de dados: RLEX Condição de retorno do módulo de Rec.Lex.
*
*
***********************************************************************/

   typedef enum {

      RLEX_CondRetOK,
         /* Ok! */

      RLEX_CondRetLexRecNaoExiste ,
         /* O reconhecedor léxico não existe */

      RLEX_CondRetLexRecVazio ,
         /* O reconhecedor léxico está vazio */

      RLEX_CondRetTransicaoNaoExiste ,
         /* Não há transição pela qual se pode percorrer */

      RLEX_CondRetValorFornecidoNulo ,
         /* Valor fornecido nulo */

      RLEX_CondRetErroArquivo ,
         /* Não foi possível abrir ou fechar um arquivo */

      RLEX_CondRetErroEstrutura ,
         /* Há um erro na estrutura do reconhecedor léxico */

      RLEX_CondRetMemoria
         /* Faltou memória para alocar espaço de dados dinamicamente */

   } RLEX_tpCondRet;

/***********************************************************************
*
*  $TC Tipo de dados: RLEX Tipo de Estado
*
*
***********************************************************************/

   typedef enum {

      RLEX_tppEstadoFinal = 0 ,
         /* Estado final */

      RLEX_tppEstadoIntermediario = 1 
         /* Estado intermediário */

   } RLEX_tpTipoEstado;

/***********************************************************************
*
*  $TC Tipo de dados: RLEX Estado
*
*
***********************************************************************/

   typedef struct tagEstado {

      int idEstado;
         /* Número identificador do estado */

      char nomeEstado[DIM_NOME_ESTADO];
         /* Nome do estado */

      RLEX_tpTipoEstado tipoEstado;
         /* Tipo do Estado
            Ver definição da enumeração RLEX_tpTipoEstado */

   } RLEX_tpEstado ;

/***** Variáveis globais do módulo *****/

   int numElementos = 0;
   RLEX_tppEstado pOrigem = NULL;
   GRF_tppGrafo pRec = NULL ;
   PIL_tppPilha pPilhaReleitura = NULL ;

/***** Protótipos das funções encapuladas no módulo *****/

   static int ComparaEstados ( void * pa , void * pb ) ;
   static void CopiaEstados ( void ** pa , void * pb ) ;
   static int ConcatenaEstados ( char * pa , void * pb ) ;
   static int ComparaRotulos ( void * pa , void * pb ) ;
   static int PercorreTransicao ( void * pa , void * pb ) ;
   static void CopiaStrings ( void ** pa , void * pb ) ;
   static RLEX_tpCondRet IrOrigem( );

   //WIP
   static RLEX_tpCondRet ReconheceStr ( char * Str ,
                                        char StrSaida[TAMANHO_BUFFER_STR] ) ;

   //WIP
   static RLEX_tpCondRet ReconheceArq ( char * Path ,
                                        char StrSaida[TAMANHO_BUFFER_STR] ) ;
   
   //WIP
   static RLEX_tpCondRet ReconheceChar ( char c ) ;

   static char * TraduzCaractere ( char c ) ;
   static int ValidarTipoEstado ( int Estado ) ;
   static void LiberaEstado ( void * pa ) ;
   static RLEX_tppEstado CriarEstado ( int idEstado ,
                                      char nomeEstado[DIM_NOME_ESTADO] , 
                                      RLEX_tpTipoEstado tipoEstado ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/**************************************************************************************
*
*  $FC Função: RLEX &Reconhecer comandos
*
*  $ED Descrição da função
*     Podem ser criadas até 10 grafos, identificadas pelos índices 0 a 9 (inclusive)
*
*     Comandos disponíveis:
*
*    =criarlexrec               RetEsperado
*    =destruirlexrec            RetEsperado
*    =inserirestado             idEstado     nomeEstado        tipoEstado  RetEsperado
*    =destruirestado            idEstado     RetEsperado
*    =inserirtransicao          idEstadoPart idEstadoDest      Rotulo      RetEsperado
*    =removertransicao          idEstadoPart idEstadoDest      Rotulo      RetEsperado
*     //a ser implementado VVVV
*    =reconhecerstring          String       LexemasEsperados
*    =reconhecerarquivo         CaminhoArq   RetEsperado
*
**************************************************************************************/

   TST_tpCondRet TST_EfetuarComando(char * ComandoTeste) {

      int numParamLidos = 0;

      GRF_tpCondRet CondRetEsperada = GRF_CondRetOK;
      GRF_tpCondRet CondRetObtida = GRF_CondRetFaltouMemoria;
      PIL_tpCondRet RetPil = PIL_CondRetFaltouMemoria;
      RLEX_tpCondRet RetRLex = RLEX_CondRetErroEstrutura;

      /* Comando =criarlexrec */

      if( strcmp(ComandoTeste,CRIAR_RLEX_CMD) == 0 )
      {
         numParamLidos = LER_LerParametros("i",&CondRetEsperada);

         if( numParamLidos != 1 )
         {
            return TST_CondRetParm;
         } /* if */

         CondRetObtida = GRF_CriarGrafo( ComparaRotulos ,
                                         ComparaEstados ,
                                         CopiaStrings ,
                                         CopiaEstados ,
                                         LiberaEstado ,
                                         NULL ,
                                         ConcatenaEstados ,
                                         PercorreTransicao ,
                                         &pRec ) ;

         if( CondRetObtida == GRF_CondRetOK )
         {
            numElementos = 0;
            RetPil = PIL_CriarPilha(&pPilhaReleitura);

            if( RetPil != PIL_CondRetOK )
            {
               GRF_DestruirGrafo(&pRec);
               return TST_CondRetMemoria;
            } /* if */

         } /* if */

         return TST_CompararInt(CondRetEsperada,CondRetObtida,"Retorno errado ao criar reconhecedor lexico");

      } /* if */
      
      /* Comando =destruirlexrec */

      if( strcmp(ComandoTeste,DESTRUIR_RLEX_CMD) == 0 )
      {
         numParamLidos = LER_LerParametros("i",&CondRetEsperada);

         if( numParamLidos != 1 )
         {
            return TST_CondRetParm;
         } /* if */

         CondRetObtida = GRF_DestruirGrafo( &pRec );

         if( CondRetObtida == GRF_CondRetOK )
         {
            numElementos = 0;
            PIL_DestruirPilha(&pPilhaReleitura);
         } /* if */

         return TST_CompararInt(CondRetEsperada,CondRetObtida,"Retorno errado ao destruir reconhecedor lexico");

      } /* if */

      /* Comando =inserirestado */

      if( strcmp(ComandoTeste,INSERIR_ESTADO_CMD) == 0 )
      {
         int idEstado = -1;
         char nomeEstado[DIM_NOME_ESTADO] = "";
         int tipoEstado = -1;

         RLEX_tppEstado pEstado = NULL;

         numParamLidos = LER_LerParametros("isii",&idEstado,nomeEstado,&tipoEstado,&CondRetEsperada);

         if( numParamLidos != 4 || !ValidarTipoEstado(tipoEstado) )
         {
            return TST_CondRetParm;
         } /* if */

         pEstado = CriarEstado( idEstado , nomeEstado , (RLEX_tpTipoEstado) tipoEstado );

         if( pEstado == NULL )
         {
            return TST_CondRetMemoria;
         } /* if */

         CondRetObtida = GRF_InserirVertice( pRec , pEstado );

         if( CondRetObtida != GRF_CondRetOK )
         {
            LiberaEstado( pEstado );
         } /* if */
         else
         {
            if( numElementos == 0 )
            {
               pOrigem = pEstado;
            } /* if */

            numElementos = GRF_ObterNumVertices(pRec);
         } /* else */

         return TST_CompararInt(CondRetEsperada,CondRetObtida,"Retorno errado ao inserir estado");

      } /* if */

      /* Comando =removerestado */

      if( strcmp(ComandoTeste,REMOVER_ESTADO_CMD) == 0 )
      {
         int idEstado = -1;
         RLEX_tppEstado pEstado = NULL;

         numParamLidos = LER_LerParametros("ii",&idEstado,&CondRetEsperada);

         if( numParamLidos != 2 )
         {
            return TST_CondRetParm;
         } /* if */

         pEstado = CriarEstado( idEstado , "" , RLEX_tppEstadoFinal );
         /* A função ComparaEstados compara apenas os ids, portanto os
            outros campos são fantasiosos e não serão levados em conta */

         if( pEstado == NULL )
         {
            return TST_CondRetMemoria;
         } /* if */

         CondRetObtida = GRF_RemoverVertice( pRec , pEstado );

         LiberaEstado( pEstado );
         numElementos = GRF_ObterNumVertices(pRec);

         if( numElementos == 0 )
         {
            pOrigem = NULL;
         } /* if */

         return TST_CompararInt(CondRetEsperada,CondRetObtida,"Retorno errado ao remover estado");

      } /* if */

      /* Comando =inserirtransicao */

      if( strcmp(ComandoTeste,INSERIR_TRANSICAO_CMD) == 0 )
      {
         int idEstadoPartida = -1 , idEstadoDestino = -1;
         RLEX_tppEstado pEstadoPartida = NULL , pEstadoDestino = NULL;

         char Rotulo[DIM_ROTULO] = "";

         numParamLidos = LER_LerParametros("iisi",&idEstadoPartida,&idEstadoDestino,Rotulo,&CondRetEsperada);

         if( numParamLidos != 4 || strcmp(Rotulo,"") == 0 )
         {
            return TST_CondRetParm;
         } /* if */

         pEstadoPartida = CriarEstado( idEstadoPartida , "" , RLEX_tppEstadoFinal );
         pEstadoDestino = CriarEstado( idEstadoDestino , "" , RLEX_tppEstadoFinal );

         if( pEstadoPartida == NULL || pEstadoDestino == NULL )
         {
            LiberaEstado( pEstadoPartida );
            LiberaEstado( pEstadoDestino );
            return TST_CondRetMemoria;
         } /* if */

         CondRetObtida = GRF_InserirAresta( pRec , pEstadoPartida , pEstadoDestino , Rotulo );

         LiberaEstado( pEstadoPartida );
         LiberaEstado( pEstadoDestino );

         return TST_CompararInt(CondRetEsperada,CondRetObtida,"Retorno errado ao inserir transicao");

      } /* if */

      /* Comando =removertransicao */

      if( strcmp(ComandoTeste,REMOVER_TRANSICAO_CMD) == 0 )
      {
         int idEstadoPartida = -1 , idEstadoDestino = -1;
         RLEX_tppEstado pEstadoPartida = NULL , pEstadoDestino = NULL;

         char Rotulo[DIM_ROTULO] = "";

         numParamLidos = LER_LerParametros("iisi",&idEstadoPartida,&idEstadoDestino,Rotulo,&CondRetEsperada);

         if( numParamLidos != 4 || strcmp(Rotulo,"") == 0 )
         {
            return TST_CondRetParm;
         } /* if */

         pEstadoPartida = CriarEstado( idEstadoPartida , "" , RLEX_tppEstadoFinal );
         pEstadoDestino = CriarEstado( idEstadoDestino , "" , RLEX_tppEstadoFinal );

         if( pEstadoPartida == NULL || pEstadoDestino == NULL )
         {
            LiberaEstado( pEstadoPartida );
            LiberaEstado( pEstadoDestino );
            return TST_CondRetMemoria;
         } /* if */

         CondRetObtida = GRF_RemoverAresta( pRec , pEstadoPartida , pEstadoDestino , Rotulo );

         LiberaEstado( pEstadoPartida );
         LiberaEstado( pEstadoDestino );

         return TST_CompararInt(CondRetEsperada,CondRetObtida,"Retorno errado ao remover transicao");

      } /* if */

      /* Comando =reconhecerstring */

      if( strcmp(ComandoTeste,RECONHECER_STRING_CMD) == 0 )
      {
         char String[TAMANHO_BUFFER_STR] = "";
         char LexemasEsperados[TAMANHO_BUFFER_STR] = "";
         char LexemasObtidos[TAMANHO_BUFFER_STR] = "";

         numParamLidos = LER_LerParametros("ssi",String,LexemasEsperados);

         if( numParamLidos != 2 )
         {
            return TST_CondRetParm;
         } /* if */

         RetRLex = ReconheceStr(String,LexemasObtidos);

         if( RetRLex != RLEX_CondRetOK )
         {
            return TST_CondRetErro;
         } /* if */

         return TST_CompararString(LexemasEsperados,LexemasObtidos,"Lexemas esperados nao correspondem aos obtidos em string");

      } /* if */

      /* Comando =reconhecerarquivo */

      if( strcmp(ComandoTeste,RECONHECER_ARQUIVO_CMD) == 0 )
      {
         char Caminho[TAMANHO_BUFFER_STR] = "";
         char LexemasEsperados[TAMANHO_BUFFER_STR] = "";
         char LexemasObtidos[TAMANHO_BUFFER_STR] = "";

         numParamLidos = LER_LerParametros("ss",Caminho,LexemasEsperados);

         if( numParamLidos != 2 )
         {
            return TST_CondRetParm;
         } /* if */

         RetRLex = ReconheceArq(Caminho,LexemasObtidos);

         if( RetRLex != RLEX_CondRetOK )
         {
            return TST_CondRetErro;
         } /* if */

         return TST_CompararString(LexemasEsperados,LexemasObtidos,"Lexemas esperados nao correspondem aos obtidos em arquivo");

      } /* if */

      return TST_CondRetNaoConhec;

   } /* Fim função: RLEX &Testar Grafo */


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: RLEX -Compara Estados
*
***********************************************************************/

   int ComparaEstados ( void *pa, void *pb )
   {
      RLEX_tppEstado pEstA = (RLEX_tppEstado) pa;
      RLEX_tppEstado pEstB = (RLEX_tppEstado) pb;

      if( pEstA == NULL || pEstB == NULL )
      {
         return -1;
      } /* if */

      return !(pEstA->idEstado == pEstB->idEstado) ;

   } /* Fim função: RLEX -Compara Estados */

/***********************************************************************
*
*  $FC Função: RLEX -Copia Estados
*
***********************************************************************/

   void CopiaEstados ( void ** pa , void * pb )
   {
      RLEX_tppEstado pEstA = (RLEX_tppEstado) malloc( sizeof(RLEX_tpEstado) );
      RLEX_tppEstado pEstB = (RLEX_tppEstado) pb;

      if( pEstA == NULL || pEstB == NULL )
      {
         return;
      } /* if */

      pEstA->idEstado = pEstB->idEstado;
      strcpy_s(pEstA->nomeEstado,DIM_NOME_ESTADO,pEstB->nomeEstado);
      pEstA->tipoEstado = pEstB->tipoEstado;

      *pa = pEstA;

   } /* Fim função: RLEX -Copia Estados */

/***********************************************************************
*
*  $FC Função: RLEX -Concatena nome de estados
*
***********************************************************************/

   int ConcatenaEstados ( char * pa , void * pb )
   {
      RLEX_tppEstado pEstB = (RLEX_tppEstado) pb;

      if( pEstB == NULL )
      {
         return 0;
      } /* if */

      return strcat_s( pa , TAMANHO_BUFFER_STR , pEstB->nomeEstado );

   } /* Fim função: RLEX -Concatena nome de estados */

/***********************************************************************
*
*  $FC Função: RLEX -Libera Estado
*
***********************************************************************/

   void LiberaEstado ( void * pa )
   {
      if( pa != NULL )
      {
         free(pa);
      } /* if */

   } /* Fim função: RLEX -Libera Estado */

/***********************************************************************
*
*  $FC Função: RLEX -Compara Rotulos
*
***********************************************************************/

   int ComparaRotulos (void *pa, void *pb)
   {
      return strcmp((char *)pa,(char *)pb);
   } /* Fim função: RLEX -Compara Strings */

 /***********************************************************************
*
*  $FC Função: RLEX -Copia Strings
*
***********************************************************************/

   void CopiaStrings (void **pa, void *pb)
   {

      *pa = (char *) malloc(sizeof(char)*DIM_ROTULO);
      strcpy_s( (char*)(*pa), DIM_ROTULO, (char*)pb );

   } /* Fim função: RLEX -Copia Strings */

/***********************************************************************
*
*  $FC Função: RLEX -Validar tipo de estado
*
***********************************************************************/

   int ValidarTipoEstado ( int Estado )
   {
      if( Estado < 0 || Estado > 1 )
      {
         return 0;
      } /* if */

      return 1;

   } /* Fim função: RLEX -Validar tipo de estado */

/***********************************************************************
*
*  $FC Função: RLEX -Criar Estado
*
***********************************************************************/

   RLEX_tppEstado CriarEstado ( int idEstado ,
                               char nomeEstado[DIM_NOME_ESTADO] , 
                               RLEX_tpTipoEstado tipoEstado )
   {

      RLEX_tppEstado pEstado = NULL;

      pEstado = (RLEX_tppEstado) malloc( sizeof(RLEX_tpEstado) );

      if( pEstado == NULL )
      {
         return NULL;
      } /* if */

      pEstado->idEstado = idEstado;
      strcpy_s(pEstado->nomeEstado,DIM_NOME_ESTADO,nomeEstado);
      pEstado->tipoEstado = tipoEstado;

      return pEstado;

   } /* Fim função: RLEX -Criar Estado */

/***********************************************************************
*
*  $FC Função: RLEX -Traduz caractere para Rótulo correspondente
*
***********************************************************************/

   char * TraduzCaractere ( char c )
   {

      if( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') )
      {
         return "\\l";
      } /* if */

      if( c >= '0' && c <= '9' )
      {
         return "\\d";
      } /* if */

      if( c == ' ' || c == '\t' || c == '\n' || c == '\r' )
      {
         return "\\b";
      } /* if */

      return "\\o";

   } /* Fim função: RLEX -Traduz caractere para Rótulo correspondente */

/***********************************************************************
*
*  $FC Função: RLEX -Reconhece String
*
***********************************************************************/

   RLEX_tpCondRet ReconheceStr ( char * Str , char StrSaida[TAMANHO_BUFFER_STR] )
   {
      char Buffer[TAMANHO_BUFFER_STR] = "";
      char * p = Str, * b = Str;
      RLEX_tpCondRet Ret;
      PIL_tpCondRet RetPil;
      GRF_tpCondRet RetGrf;
      RLEX_tppEstado pEstadoCorr = NULL;

      PIL_tppPilha pPilhaCaminhamento = NULL;

      if( StrSaida == NULL || Str == NULL )
      {
         return RLEX_CondRetValorFornecidoNulo;
      } /* if */

      strcpy_s(StrSaida,TAMANHO_BUFFER_STR,"");

      Ret = IrOrigem();

      if( Ret != RLEX_CondRetOK )
      {
         return Ret;
      } /* if */

      RetPil = PIL_CriarPilha(&pPilhaCaminhamento);

      if( RetPil != PIL_CondRetOK )
      {
         return RLEX_CondRetMemoria;
      } /* if */

      while ( 1 )
      {

         if( PIL_PilhaVazia( pPilhaReleitura ) != PIL_CondRetOK )
         {

         } /* if */

         RetGrf = GRF_ObterValor( pRec , (void **) &pEstadoCorr );
         RetPil = PIL_Empilhar( pPilhaCaminhamento , pEstadoCorr );

         if( RetGrf != GRF_CondRetOK || RetPil != PIL_CondRetOK )
         {
            return RLEX_CondRetErroEstrutura;
         } /* if */

         if( *p == '\0' )
         {
            Ret = ReconheceChar('\f');
         } /* if */
         else
         {
            Ret = ReconheceChar(*p);
         } /* else */

         if( Ret == RLEX_CondRetTransicaoNaoExiste )
         {
            /* "Se o estado não for terminal, precisa-se retroceder sobre o caminho percorrido,
               até que se chegue ou a um estado final ou ao estado inicial." */

            while( PIL_PilhaVazia( pPilhaCaminhamento ) == PIL_CondRetOK )
            {

               /* "Os caracteres do fluxo percorridos nesse trajeto inverso devem ser empilhados
                  na pilha de releitura." */

               pEstadoCorr = (RLEX_tppEstado) PIL_Desempilhar( pPilhaCaminhamento );
               RetPil = PIL_Empilhar( pPilhaReleitura, p );

               if( RetPil == PIL_CondRetFaltouMemoria )
               {
                  return RLEX_CondRetMemoria;
               } /* if */
               else if( RetPil != PIL_CondRetOK )
               {
                  return RLEX_CondRetErroEstrutura;
               } /* else if */

               if( pEstadoCorr == NULL )
               {
                  return RLEX_CondRetErroEstrutura;
               } /* if */

               if( pEstadoCorr->tipoEstado == RLEX_tppEstadoFinal )
               {
                  break;
               } /* if */

            } /* while */

            if( PIL_PilhaVazia( pPilhaCaminhamento ) == PIL_CondRetPilhaVazia )
            {
               /* "Caso, ao retroceder, tenha-se chegado ao estado inicial, encontrou-se um erro 
                  de dados de entrada, mais especificamente, o caractere no topo da pilha de releitura
                  não leva a um estado final. Neste caso elimina-se o caractere no topo da pilha, emite-se
                  uma mensagem de erro e reinicia-se o reconhecimento." */

               char topo[2];

               if( strcpy_s(topo,2,(char *)PIL_Desempilhar( pPilhaReleitura )) != 0 )
               {
                  return RLEX_CondRetErroEstrutura;
               } /* if */

               if( strcat_s( StrSaida , TAMANHO_BUFFER_STR , "Erro, " ) != 0 )
               {
                  return RLEX_CondRetMemoria;
               } /* if */

            } /* if */
            else
            {
               /* "Caso, ao retroceder, tenha-se chegado a um estado final, esse corresponderá ao
                  lexema encontrado." */

               if( strcat_s( StrSaida , TAMANHO_BUFFER_STR , pEstadoCorr->nomeEstado ) != 0 )
               {
                  return RLEX_CondRetMemoria;
               } /* if */

               if( strcat_s( StrSaida , TAMANHO_BUFFER_STR , ", " ) != 0 )
               {
                  return RLEX_CondRetMemoria;
               } /* if */

               RetPil = PIL_DestruirPilha( &pPilhaCaminhamento );
               
               if( RetPil != PIL_CondRetOK )
               {
                  return RLEX_CondRetErroEstrutura;
               } /* if */

               RetPil = PIL_CriarPilha( &pPilhaCaminhamento );

               if( RetPil == PIL_CondRetFaltouMemoria )
               {
                  return RLEX_CondRetMemoria;
               } /* if */
               else if( RetPil == PIL_CondRetErroEstrutura )
               {
                  return RLEX_CondRetErroEstrutura;
               } /* else-if */

               Ret = IrOrigem();

               if( Ret != RLEX_CondRetOK )
               {
                  return Ret;
               } /* if */

            } /* else */

         } /* if */
         else if( Ret == RLEX_CondRetOK )
         {
            p++;
         } /* if */
         else
         {
            return Ret;
         } /* if */

      } /* while */

      strcpy_s(StrSaida,TAMANHO_BUFFER_STR,Buffer);
      return RLEX_CondRetOK;

   } /* Fim função: RLEX -Reconhece String */

/***********************************************************************
*
*  $FC Função: RLEX -Reconhece Arquivo
*
***********************************************************************/

   RLEX_tpCondRet ReconheceArq ( char * Path , char StrSaida[TAMANHO_BUFFER_STR] )
   {
      char Buffer[TAMANHO_BUFFER_STR] = "";
      FILE *f;
      RLEX_tpCondRet Ret;

      if( fopen_s(&f,Path,"rb") != 0 || f == NULL )
      {
         /* Não foi possível abrir o arquivo */
         strcpy_s(StrSaida,TAMANHO_BUFFER_STR,"");
         return RLEX_CondRetErroArquivo;
      } /* if */

      do
      {
         
         fread(Buffer,sizeof(char),1,f);

         /* Caso o arquivo tenha chegado ao final */
         if( feof(f) )
            break;

         Ret = ReconheceChar(Buffer[0]);

         if( Ret != RLEX_CondRetOK )
         {
            strcpy_s(StrSaida,TAMANHO_BUFFER_STR,"");
            return Ret;
         } /* if */

         //WIP
         //Tratar da condição de retorno

      } while( 1 ); /* do-while */

      if( fclose(f) != 0 )
      {
         /* Não foi possível fechar o arquivo */
         strcpy_s(StrSaida,TAMANHO_BUFFER_STR,"");
         return RLEX_CondRetErroArquivo;
      } /* if */

      strcpy_s(StrSaida,TAMANHO_BUFFER_STR,Buffer);
      return RLEX_CondRetOK;

   } /* Fim função: RLEX -Reconhece Arquivo */

/***********************************************************************
*
*  $FC Função: RLEX -Reconhece Caractere
*
***********************************************************************/

   RLEX_tpCondRet ReconheceChar ( char c )
   {

      GRF_tpCondRet RetGrf;
      char Str[2] = "";

      if( pRec == NULL )
      {
         return RLEX_CondRetLexRecNaoExiste;
      } /* if */

      if( pPilhaReleitura == NULL )
      {
         return RLEX_CondRetErroEstrutura;
      } /* if */

      sprintf_s(Str,2,"%c",c);
      RetGrf = GRF_CaminharGrafo( pRec , Str , 1 );

      if( RetGrf == GRF_CondRetArestaNaoExiste )
      {
         return RLEX_CondRetTransicaoNaoExiste;
      } /* if */

      switch( RetGrf )
      {
      case GRF_CondRetOK:
         return RLEX_CondRetOK;

      case GRF_CondRetArestaNaoExiste:
         return RLEX_CondRetTransicaoNaoExiste;

      case GRF_CondRetGrafoVazio:
         return RLEX_CondRetLexRecVazio;

      default:
         /*
         GRF_CondRetGrafoNaoExiste
         GRF_CondRetValorFornecidoNulo
         GRF_CondRetErroEstrutura
         GRF_CondRetFuncaoNula
         */
         return RLEX_CondRetErroEstrutura;
      } /* switch */

   } /* Fim função: RLEX -Reconhece Caractere */

/***********************************************************************
*
*  $FC Função: RLEX -Percorre Transicao
*
***********************************************************************/

   int PercorreTransicao ( void * pa , void * pb )
   {

      int i;
      int j = 0;
      int pa_size = strlen((char*)pa);

      char el[DIM_ROTULO] = "";

      if( strcmp((char *)pa,"\\o") == 0 )
      {
         /* Rótulo engloba outros
            >> prioridade 1 */
         return 1;
      } /* if */

      for ( i = 0 ; i < pa_size ; i++ )
      {
         char c[2] = "";
         sprintf_s(c,2,"%c",*((char *)pa+i));

         if( c[0] == ' ' && i != j )
         {
            if( strlen(el) == 1 )
            {
               if( strcmp((char *)pb,el) == 0 )
               {
                  /* Rótulo possui caractere
                     >> prioridade 3 */
                  return 3;
               } /* if */
            } /* if */
            else
            {
               if( strcmp(TraduzCaractere(*((char *)pb)),el) == 0 )
               {
                  /* Rótulo possui conjunto que engloba caractere 
                     >> prioridade 2 */
                  return 2;
               } /* if */
            }

            strcpy_s(el,DIM_ROTULO,"");
            j = i + 1;
         } /* if */
         else
         {
            strcat_s(el,DIM_ROTULO,c);
         } /* else */

         if( i == pa_size - 1 )
         {
            if( strlen(el) == 1 )
            {
               if( strcmp((char *)pb,el) == 0 )
               {
                  /* Rótulo possui caractere
                     >> prioridade 3 */
                  return 3;
               } /* if */
            } /* if */
            else
            {
               if( strcmp(TraduzCaractere(*((char *)pb)),el) == 0 )
               {
                  /* Rótulo possui conjunto que engloba caractere 
                     >> prioridade 2 */
                  return 2;
               } /* if */
            }
         }

      } /* for */

      /* Rótulo não representa transição "percorrível"
         >> prioridade 0 */
      return 0;

   } /* Fim função: RLEX -Percorre Transicao */

/***********************************************************************
*
*  $FC Função: RLEX -Ir à origem do reconhecedor léxico
*
***********************************************************************/

   RLEX_tpCondRet IrOrigem( )
   {
      GRF_tpCondRet RetGrf;

      RetGrf = GRF_ProcurarVertice( pRec , pOrigem , RLEX_TRUE );

      switch( RetGrf )
      {

      case GRF_CondRetOK:
         return RLEX_CondRetOK;

      case GRF_CondRetGrafoNaoExiste:
         return RLEX_CondRetLexRecNaoExiste;

      case GRF_CondRetGrafoVazio:
         return RLEX_CondRetLexRecVazio;

      default:
         /*
         GRF_CondRetErroEstrutura
         GRF_CondRetVerticeNaoExiste - pOrigem não aponta para origem
         */
         return RLEX_CondRetErroEstrutura;

      } /* switch */

   } /* Fim função: RLEX -Ir à origem do reconhecedor léxico */

/********** Fim do módulo de implementação: RLEX Reconhecedor Léxico **********/

