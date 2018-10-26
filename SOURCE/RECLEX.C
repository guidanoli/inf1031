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
*     0.1     gui   26/10/2018  criar e destruir rec.lex., inserir e remover estado
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "GRAFO.H"

#define CRIAR_RLEX_CMD           "=criarlexrec"
#define DESTRUIR_RLEX_CMD        "=destruirlexrec"
#define INSERIR_ESTADO_CMD       "=inserirestado"
#define REMOVER_ESTADO_CMD       "=removerestado"
#define INSERIR_TRANSICAO_CMD    "=inserirtransicao"
#define REMOVER_TRANSICAO_CMD    "=removertransicao"
#define RECONHECER_STRING_CMD    "=reconhecerstring"
#define RECONHECER_ARQUIVO_CMD   "=reconhecerarquivo"

#define DIM_NOME_ESTADO    30
#define DIM_ROTULO         10
#define TAMANHO_BUFFER_STR 500

/* Ponteiro para estado */

   typedef struct tagEstado * RLEX_tpEstado;

/***********************************************************************
*
*  $TC Tipo de dados: RLEX Tipo de Estado
*
*
***********************************************************************/

   typedef enum {

      RLEX_tpEstadoFinal = 0 ,
         /* Estado final */

      RLEX_tpEstadoIntermediario = 1
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

   } RLEX_tagEstado ;

/***** Variáveis globais do módulo *****/

   GRF_tppGrafo pRec = NULL ;

/***** Protótipos das funções encapuladas no módulo *****/

   static RLEX_tpEstado CriarEstado ( int idEstado ,
                                      char nomeEstado[DIM_NOME_ESTADO] , 
                                      RLEX_tpTipoEstado tipoEstado );

   static void LiberaEstado ( void * pa );

   static int ValidarTipoEstado ( int Estado );

   static int ComparaEstados ( void * pa , void * pb );
   static void CopiaEstados ( void ** pa , void * pb );
   static int ConcatenaEstados ( char * pa , void * pb );
   static int ComparaStrings ( void * pa , void * pb ) ;
   static void CopiaStrings ( void ** pa , void * pb ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
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
*    =inserirestado             idEstado     nomeEstado     tipoEstado  RetEsperado
*    =destruirestado            idEstado     RetEsperado
*     //a ser implementado VVVV
*    =inserirtransicao          idEstadoPart idEstadoDest   Rotulo      RetEsperado
*    =removertransicao          idEstadoPart Rotulo         RetEsperado
*    =reconhecerString          String       RetEsperado
*    =reconhecerArquivo         CaminhoArq   RetEsperado
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando(char * ComandoTeste) {

      int numParamLidos = 0;

      GRF_tpCondRet CondRetEsperada = GRF_CondRetOK;
      GRF_tpCondRet CondRetObtida = GRF_CondRetFaltouMemoria;

      /* Comando =criarlexrec */

      if( strcmp(ComandoTeste,CRIAR_RLEX_CMD) == 0 )
      {
         numParamLidos = LER_LerParametros("i",&CondRetEsperada);

         if( numParamLidos != 1 )
         {
            return TST_CondRetParm;
         } /* if */

         CondRetObtida = GRF_CriarGrafo( ComparaStrings ,
                                  ComparaEstados ,
                                  CopiaStrings ,
                                  CopiaEstados ,
                                  LiberaEstado ,
                                  NULL ,
                                  ConcatenaEstados ,
                                  &pRec ) ;

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

         return TST_CompararInt(CondRetEsperada,CondRetObtida,"Retorno errado ao destruir reconhecedor lexico");

      } /* if */

      /* Comando =inserirestado */

      if( strcmp(ComandoTeste,INSERIR_ESTADO_CMD) == 0 )
      {
         int idEstado = -1;
         char nomeEstado[DIM_NOME_ESTADO] = "";
         int tipoEstado = -1;

         RLEX_tpEstado pEstado = NULL;

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

         return TST_CompararInt(CondRetEsperada,CondRetObtida,"Retorno errado ao inserir estado");

      } /* if */

      if( strcmp(ComandoTeste,REMOVER_ESTADO_CMD) == 0 )
      {
         int idEstado = -1;
         RLEX_tpEstado pEstado = NULL;

         numParamLidos = LER_LerParametros("ii",&idEstado,&CondRetEsperada);

         if( numParamLidos != 2 )
         {
            return TST_CondRetParm;
         } /* if */

         pEstado = CriarEstado( idEstado , "" , RLEX_tpEstadoFinal );
         /* A função ComparaEstados compara apenas os ids, portanto os
            outros campos são fantasiosos e não serão levados em conta */

         CondRetObtida = GRF_RemoverVertice( pRec , pEstado );

         LiberaEstado( pEstado );

         return TST_CompararInt(CondRetEsperada,CondRetObtida,"Retorno errado ao remover estado");

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
      RLEX_tpEstado pEstA = (RLEX_tpEstado) pa;
      RLEX_tpEstado pEstB = (RLEX_tpEstado) pb;

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
      RLEX_tpEstado pEstA = (RLEX_tpEstado) malloc( sizeof(RLEX_tagEstado) );
      RLEX_tpEstado pEstB = (RLEX_tpEstado) pb;

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
      RLEX_tpEstado pEstB = (RLEX_tpEstado) pb;

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
      free(pa);

   } /* Fim função: RLEX -Libera Estado */

/***********************************************************************
*
*  $FC Função: RLEX -Compara Strings
*
***********************************************************************/

   int ComparaStrings (void *pa, void *pb)
   {

      return strcmp( (char*)pa, (char*)pb );

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

   RLEX_tpEstado CriarEstado ( int idEstado ,
                               char nomeEstado[DIM_NOME_ESTADO] , 
                               RLEX_tpTipoEstado tipoEstado )
   {

      RLEX_tpEstado pEstado = NULL;

      pEstado = (RLEX_tpEstado) malloc( sizeof(RLEX_tagEstado) );

      if( pEstado == NULL )
      {
         return NULL;
      } /* if */

      pEstado->idEstado = idEstado;
      strcpy_s(pEstado->nomeEstado,DIM_NOME_ESTADO,nomeEstado);
      pEstado->tipoEstado = tipoEstado;

      return pEstado;

   } /* Fim função: RLEX -Criar Estado */

/********** Fim do módulo de implementação: RLEX Reconhecedor Léxico **********/

