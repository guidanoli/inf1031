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
#define CMP_ARQUIVOS_CMD         "=cmparquivos"

#define DIM_NOME_ESTADO    30
#define DIM_ROTULO         30
#define TAMANHO_BUFFER_STR 500

#define RLEX_TRUE  1
#define RLEX_FALSE 0

#define SENTIDO_FRENTE  1
#define SENTIDO_TRAS    0

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

      RLEX_CondRetArquivosDiferentes ,
         /* Os arquivos comparados são diferentes */

      RLEX_CondRetErroArquivo ,
         /* Não foi possível abrir ou fechar um arquivo */

      RLEX_CondRetParametrosInvalidos ,
         /* Parâmetros não obedecem assertiva de entrada */

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

   int numElementos = 0 ;
   RLEX_tppEstado pOrigem = NULL ;
   GRF_tppGrafo pRec = NULL ;
   PIL_tppPilha pPilhaReleitura = NULL;

/***** Protótipos das funções encapuladas no módulo *****/

/***********************************************************************
*
*  Funções auxiliares do grafo
*
***********************************************************************/

   static int ComparaEstados ( void * pa , void * pb ) ;
   static void CopiaEstados ( void ** pa , void * pb ) ;
   static int ConcatenaEstados ( char * pa , void * pb ) ;
   static int ComparaRotulos ( void * pa , void * pb ) ;
   static int PercorreTransicao ( void * pa , void * pb ) ;
   static void CopiaStrings ( void ** pa , void * pb ) ;

/***********************************************************************
*
*  Funções auxiliares do reconhecedor léxico
*
***********************************************************************/

   static RLEX_tpCondRet IrOrigem( );

   //WIP
   static RLEX_tpCondRet ReconheceStr ( char Str[TAMANHO_BUFFER_STR] , char CaminhoSaida[TAMANHO_BUFFER_STR] ) ;

   //WIP
   static RLEX_tpCondRet ReconheceArq ( char CaminhoEntrada[TAMANHO_BUFFER_STR] , char CaminhoSaida[TAMANHO_BUFFER_STR] ) ;
   static RLEX_tpCondRet ReconheceChar ( char c ) ;
   static RLEX_tpCondRet ObterSubstring ( char * p , char * ant , int * col , int * linha , char * Str ) ;
   static RLEX_tpCondRet AtualizaLinha ( char * p , char * ant , int * linha ) ;
   static char * TraduzCaractere ( char c ) ;
   static int ValidarTipoEstado ( int Estado ) ;
   static void LiberaEstado ( void * pa ) ;
   static RLEX_tppEstado CriarEstado ( int idEstado , char nomeEstado[DIM_NOME_ESTADO] , RLEX_tpTipoEstado tipoEstado ) ;

/***********************************************************************
*
*  Funções auxiliares de arquivo
*
***********************************************************************/

   static RLEX_tpCondRet ComparaArq ( char ArqGerado[TAMANHO_BUFFER_STR] , char ArqEsperado[TAMANHO_BUFFER_STR] , char CharIgnora ) ;
   static RLEX_tpCondRet EscreveErro ( int coluna , int linha , char Path[TAMANHO_BUFFER_STR] );
   static RLEX_tpCondRet LimparArq ( char Path[TAMANHO_BUFFER_STR] ) ;
   static RLEX_tpCondRet EscreveArq ( char NomeEstado[DIM_NOME_ESTADO] , char LexemaReconhecido[TAMANHO_BUFFER_STR] ,
                                      int coluna , int linha ,  char Path[TAMANHO_BUFFER_STR] ) ;

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
*    =inserirestado             idEstado     nomeEstado     tipoEstado  RetEsperado
*    =destruirestado            idEstado     RetEsperado
*    =inserirtransicao          idEstadoPart idEstadoDest   Rotulo      RetEsperado
*    =removertransicao          idEstadoPart idEstadoDest   Rotulo      RetEsperado
*    =reconhecerstring          String       CaminhoSaida   CondRetEsp
*    =reconhecerarquivo         CaminhoArq   CaminhoSaida   CondRetEsp
*    =cmparquivos               CaminhoArq1  CaminhoArq2    CharIgnora  CondRetEsp
*
**************************************************************************************/

   TST_tpCondRet TST_EfetuarComando(char * ComandoTeste) {

      int numParamLidos = 0;

      RLEX_tpCondRet CondRetEsperada = RLEX_CondRetOK;
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

         CondRetObtida = GRF_CriarGrafo( GRF_RestAreSaidaUnica ,
                                         ComparaRotulos ,
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
         char CaminhoSaida[TAMANHO_BUFFER_STR] = "";
         RLEX_tpCondRet CondRetLexRetObtida, CondRetLexRetEsperada;

         numParamLidos = LER_LerParametros("ssi",String,CaminhoSaida,&CondRetLexRetEsperada);

         if( numParamLidos != 3 || strcmp(CaminhoSaida,"") == 0 )
         {
            return TST_CondRetParm;
         } /* if */

         CondRetLexRetObtida = ReconheceStr(String,CaminhoSaida);

         return TST_CompararInt(CondRetLexRetEsperada,CondRetLexRetObtida,"Retorno errado ao reconhecer string");

      } /* if */

      /* Comando =reconhecerarquivo */

      if( strcmp(ComandoTeste,RECONHECER_ARQUIVO_CMD) == 0 )
      {
         char CaminhoArq[TAMANHO_BUFFER_STR] = "";
         char CaminhoSaida[TAMANHO_BUFFER_STR] = "";
         RLEX_tpCondRet CondRetLexRetObtida, CondRetLexRetEsperada;

         numParamLidos = LER_LerParametros("ssi",CaminhoArq,CaminhoSaida,&CondRetLexRetEsperada);

         if( numParamLidos != 3 || strcmp(CaminhoSaida,"") == 0 || strcmp(CaminhoArq,"") == 0 )
         {
            return TST_CondRetParm;
         } /* if */

         CondRetLexRetObtida = ReconheceArq(CaminhoArq,CaminhoSaida);

         return TST_CompararInt(CondRetLexRetEsperada,CondRetLexRetObtida,"Retorno errado ao reconhecer arquivo");

      } /* if */

      /* Comando =cmparquivos */

      if( strcmp(ComandoTeste,CMP_ARQUIVOS_CMD) == 0 )
      {
         char Caminho1[TAMANHO_BUFFER_STR] = "";
         char Caminho2[TAMANHO_BUFFER_STR] = "";
         char CharIgnora;
         RLEX_tpCondRet CondRetLexRetObtida, CondRetLexRetEsperada;

         numParamLidos = LER_LerParametros("ssci",Caminho1,Caminho2,&CharIgnora,&CondRetLexRetEsperada);

         if( numParamLidos != 4 || strcmp(Caminho1,"") == 0 || strcmp(Caminho2,"") == 0 )
         {
            return TST_CondRetParm;
         } /* if */

         CondRetLexRetObtida = ComparaArq(Caminho1,Caminho2,CharIgnora);

         return TST_CompararInt(CondRetLexRetEsperada,CondRetLexRetObtida,"Retorno errado ao comparar arquivos");

      } /* if */

      return TST_CondRetNaoConhec;

   } /* Fim função: RLEX &Testar Reconhecedor Léxico */


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

      if( nomeEstado == NULL )
      {
         return NULL;
      } /* if */

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

   RLEX_tpCondRet ReconheceStr ( char Str[TAMANHO_BUFFER_STR] ,
                                 char CaminhoSaida[TAMANHO_BUFFER_STR] )
   {
      char *p = Str , *ant = Str;
      RLEX_tppEstado pEstadoCorr = NULL;
      int col = 0, linha = 0;

      char SmallStr[2] = "";

      GRF_tpCondRet  RetGrf;
      PIL_tpCondRet  RetPil;
      RLEX_tpCondRet RetRlex;

      /* Validando ponteiros */

      if( pRec == NULL )
      {
         return RLEX_CondRetLexRecNaoExiste;
      } /* if */

      if( Str == NULL || CaminhoSaida == NULL )
      {
         return RLEX_CondRetParametrosInvalidos;
      } /* if */

      /* Criando pilha -- não importa se a pilha está
         com erro de estrutura ou não, ela será destruída
         para uma nova ser criada */

      RetPil = PIL_CriarPilha(&pPilhaReleitura);

      if( RetPil == PIL_CondRetFaltouMemoria )
      {
         return RLEX_CondRetMemoria;
      } /* if */

      RetRlex = LimparArq(CaminhoSaida);

      if( RetRlex != RLEX_CondRetOK )
      {
         /* RLEX_CondRetErroArquivo */
         return RetRlex;
      } /* if */

      RetRlex = IrOrigem();

      if( RetRlex != RLEX_CondRetOK )
      {
         /*
         RLEX_CondRetLexRecNaoExiste
         RLEX_CondRetLexRecVazio
         RLEX_CondRetErroEstrutura
         */
         return RetRlex;
      } /* if */

      /* Laço principal */

      while( 1 )
      {

         /* Empilha na pilha de caminhamento o estado corrente */

         RetGrf = GRF_ObterValor( pRec , (void**) &pEstadoCorr );

         if( RetGrf != GRF_CondRetOK )
         {
            return RLEX_CondRetErroEstrutura;
         } /* else-if */

         if( pEstadoCorr == NULL )
         {
            return RLEX_CondRetErroEstrutura;
         } /* if */

         RetPil = PIL_Empilhar( pPilhaReleitura , pEstadoCorr );

         if( RetPil == PIL_CondRetFaltouMemoria )
         {
            return RLEX_CondRetMemoria;
         } /* if */
         else if( RetPil != PIL_CondRetOK )
         {
            return RLEX_CondRetErroEstrutura;
         } /* if */

         /* Caminha no grafo com o caractere corrente */

         RetRlex = ReconheceChar( *p );

         if( RetRlex == RLEX_CondRetOK )
         {
            /* Foi possível percorrer a transição */
            if( *p != '\0' )
            {
               p++;
            } /* if */
            else
            {
               break;
            } /* else */

         } /* if */
         else if( RetRlex == RLEX_CondRetTransicaoNaoExiste )
         {
            /* Não há a transição */
            while( pEstadoCorr->tipoEstado != RLEX_tppEstadoFinal 
                   && PIL_PilhaVazia(pPilhaReleitura) == PIL_CondRetOK )
            {
               pEstadoCorr = (RLEX_tppEstado) PIL_Desempilhar(pPilhaReleitura);

               if( pEstadoCorr == NULL )
               {
                  return RLEX_CondRetErroEstrutura;
               } /* if */

               if( p == ant )
               {
                  break;
               } /* if */
               else
               {
                  p--;
               } /* else */

            } /* while */

            if( pEstadoCorr->tipoEstado == RLEX_tppEstadoFinal )
            {
               char LexemaReconhecido[TAMANHO_BUFFER_STR] = "";
               int col_temp = col, linha_temp = linha;

               RetRlex = ObterSubstring(p,ant,&col_temp,&linha_temp,LexemaReconhecido);
               
               if( RetRlex != RLEX_CondRetOK )
               {
                  return RetRlex;
               } /* if */

               RetRlex = EscreveArq( pEstadoCorr->nomeEstado ,
                                     LexemaReconhecido ,
                                     col ,
                                     linha ,
                                     CaminhoSaida );

               if( RetRlex != RLEX_CondRetOK )
               {
                  return RetRlex;
               } /* if */

               col = col_temp;
               linha = linha_temp;

               ant = p;
               if( *ant == '\0' )
               {
                  break;
               } /* if */

               RetRlex = IrOrigem();

               if( RetRlex != RLEX_CondRetOK )
               {
                  return RetRlex;
               } /* if */

               RetPil = PIL_EsvaziarPilha( pPilhaReleitura );

               if( RetPil != PIL_CondRetOK )
               {
                  /*
                  PIL_CondRetPilhaNaoExiste
                  PIL_CondRetErroEstrutura
                  */
                  return RLEX_CondRetErroEstrutura;
               } /* if */

            } /* if */
            else if( PIL_PilhaVazia(pPilhaReleitura) == PIL_CondRetPilhaVazia )
            {
               RetRlex = EscreveErro(col,linha,CaminhoSaida);

               if( RetRlex != RLEX_CondRetOK )
               {
                  return RetRlex;
               } /* if */

               break;

            } /* else-if */

         } /* else-if */
         else
         {
            /*
            RLEX_CondRetLexRecNaoExiste
            RLEX_CondRetLexRecVazio
            RLEX_CondRetErroEstrutura
            */
            return RetRlex;
         } /* else */

      } /* while */

      PIL_DestruirPilha(&pPilhaReleitura);

      return RLEX_CondRetOK;

   } /* Fim função: RLEX -Reconhece String */

/***********************************************************************
*
*  $FC Função: RLEX -Reconhece Arquivo
*
***********************************************************************/

   RLEX_tpCondRet ReconheceArq ( char CaminhoEntrada[TAMANHO_BUFFER_STR] ,
                                 char CaminhoSaida[TAMANHO_BUFFER_STR] )
   {
      
      //TO-DO
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

      sprintf_s(Str,2,"%c",c);
      RetGrf = GRF_CaminharGrafo( pRec , Str , SENTIDO_FRENTE );

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

      if( pa == NULL || pb == NULL )
      {
         return 0;
      } /* if */

      if( strcmp((char *)pb,"") == 0 )
      {
         return 0;
      } /* if */

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

/***********************************************************************
*
*  $FC Função: RLEX -Limpa arquivo
*
***********************************************************************/

   static RLEX_tpCondRet LimparArq ( char Path[TAMANHO_BUFFER_STR] )
   {
      FILE *f = NULL;

      if( Path == NULL )
      {
         return RLEX_CondRetParametrosInvalidos;
      } /* if */

      if( fopen_s(&f,Path,"w") != 0 )
      {
         return RLEX_CondRetErroArquivo;
      } /* if */
      
      if( fclose(f) != 0 )
      {
         return RLEX_CondRetErroArquivo;
      } /* if */

      return RLEX_CondRetOK;
   } /* Fim função: RLEX -Limpa arquivo */

/***********************************************************************
*
*  $FC Função: RLEX -Escreve em arquivo
*
***********************************************************************/

   static RLEX_tpCondRet EscreveArq ( char NomeEstado[DIM_NOME_ESTADO] ,
                                      char LexemaReconhecido[TAMANHO_BUFFER_STR] ,
                                      int coluna ,
                                      int linha , 
                                      char Path[TAMANHO_BUFFER_STR] )
   {
      FILE *f = NULL;

      char Mensagens[][30] = {"O lexema \"","\" presente na linha "," coluna "," foi reconhecido como ",".\n"};
      char linha_str[10] = "", coluna_str[10] = "";

      if( NomeEstado == NULL ||
          LexemaReconhecido == NULL ||
          Path == NULL ||
          coluna < 0 ||
          linha < 0 )
      {
         return RLEX_CondRetParametrosInvalidos;
      } /* if */

      if( fopen_s(&f,Path,"a") != 0 )
      {
         return RLEX_CondRetErroArquivo;
      } /* if */
      
      sprintf_s(linha_str,10,"%d",linha);
      sprintf_s(coluna_str,10,"%d",coluna);

      fwrite(Mensagens[0],sizeof(char),strlen(Mensagens[0]),f);             // O lexema "
      fwrite(LexemaReconhecido,sizeof(char),strlen(LexemaReconhecido),f);   // <LexemaReconhecido>
      fwrite(Mensagens[1],sizeof(char),strlen(Mensagens[1]),f);             // " presente na linha
      fwrite(linha_str,sizeof(char),strlen(linha_str),f);                   // <linha_str>
      fwrite(Mensagens[2],sizeof(char),strlen(Mensagens[2]),f);             //  coluna
      fwrite(coluna_str,sizeof(char),strlen(coluna_str),f);                 // <coluna_str>
      fwrite(Mensagens[3],sizeof(char),strlen(Mensagens[3]),f);             //  foi reconhecido como 
      fwrite(NomeEstado,sizeof(char),strlen(NomeEstado),f);                 // <NomeEstado>
      fwrite(Mensagens[4],sizeof(char),strlen(Mensagens[4]),f);             // .\n

      if( fclose(f) != 0 )
      {
         return RLEX_CondRetErroArquivo;
      } /* if */

      return RLEX_CondRetOK;
   } /* Fim função: RLEX -Escreve em arquivo */

/***********************************************************************
*
*  $FC Função: RLEX -Obter sub-string
*
***********************************************************************/

   RLEX_tpCondRet ObterSubstring ( char * p , char * ant , int * col , int * linha , char Str[TAMANHO_BUFFER_STR] ) 
   {
      char Buffer[TAMANHO_BUFFER_STR] = "";
      char SmallStr[2] = "";

      if( p == NULL || ant == NULL || col == NULL || Str == NULL )
      {
         return RLEX_CondRetParametrosInvalidos;
      } /* if */

      while( p > ant )
      {
         if( *ant == '\n' )
         {
            (*linha)++;
         } /* if */

         sprintf_s(SmallStr,2,"%c",*ant);

         if( strcat_s(Buffer,TAMANHO_BUFFER_STR,SmallStr) != 0 )
         {
            return RLEX_CondRetMemoria;
         } /* if */

         ant++;
         (*col)++;

      } /* while */

      strcpy_s(Str,TAMANHO_BUFFER_STR,Buffer);
      return RLEX_CondRetOK;

   } /* Fim função: RLEX -Obter sub-string */

/***********************************************************************
*
*  $FC Função: RLEX -Escrever erro
*
***********************************************************************/

   static RLEX_tpCondRet EscreveErro ( int coluna ,
                                       int linha ,
                                       char Path[TAMANHO_BUFFER_STR] )
   {
      FILE *f = NULL;

      char Mensagens[][50] = {"Erro de reconhecimento na linha "," e coluna ",".\n"};
      char linha_str[10] = "", coluna_str[10] = "";

      if( Path == NULL ||
          coluna < 0 ||
          linha < 0 )
      {
         return RLEX_CondRetParametrosInvalidos;
      } /* if */

      if( fopen_s(&f,Path,"a") != 0 )
      {
         return RLEX_CondRetErroArquivo;
      } /* if */
      
      sprintf_s(linha_str,10,"%d",linha);
      sprintf_s(coluna_str,10,"%d",coluna);

      fwrite(Mensagens[0],sizeof(char),strlen(Mensagens[0]),f);             // Erro de reconhecimento na linha 
      fwrite(linha_str,sizeof(char),strlen(linha_str),f);                   // <linha_str>
      fwrite(Mensagens[1],sizeof(char),strlen(Mensagens[1]),f);             //  e coluna
      fwrite(coluna_str,sizeof(char),strlen(coluna_str),f);                 // <coluna_str>
      fwrite(Mensagens[2],sizeof(char),strlen(Mensagens[2]),f);             // .\n

      if( fclose(f) != 0 )
      {
         return RLEX_CondRetErroArquivo;
      } /* if */

      return RLEX_CondRetOK;
   } /* Fim função: RLEX -Escrever erro */

/***********************************************************************
*
*  $FC Função: RLEX -Compara arquivos
*
***********************************************************************/

   RLEX_tpCondRet ComparaArq ( char ArqGerado[TAMANHO_BUFFER_STR] ,
                               char ArqEsperado[TAMANHO_BUFFER_STR] ,
                               char CharIgnora )
   {
      FILE *f1 = NULL, *f2 = NULL;
      char c1, c2;
      int flag_iguais = RLEX_TRUE;
      
      if( ArqGerado == NULL ||
          ArqEsperado == NULL )
      {
         return RLEX_CondRetParametrosInvalidos;
      } /* if */

      if( fopen_s(&f1,ArqGerado,"r") != 0 )
      {
         return RLEX_CondRetErroArquivo;
      } /* if */

      if( fopen_s(&f2,ArqEsperado,"r") != 0 )
      {
         return RLEX_CondRetErroArquivo;
      } /* if */

      while( RLEX_TRUE )
      {
         c1 = fgetc(f1);
         c2 = fgetc(f2);

         if( feof(f1) || feof(f2) )
         {
            if( feof(f1) && feof(f2) )
            {
               break;
            } /* if */

            /* Um dos arquivos acabou, mas não os dois */
            flag_iguais = RLEX_FALSE;
            break;
         } /* if */

         if( c1 != c2 && c2 != CharIgnora )
         {
            flag_iguais = RLEX_FALSE;
            break;
         } /* if */

      } /* if */

      if( fclose(f1) != 0 )
      {
         return RLEX_CondRetErroArquivo;
      } /* if */

      if( fclose(f2) != 0 )
      {
         return RLEX_CondRetErroArquivo;
      } /* if */
      
      if( flag_iguais )
      {
         return RLEX_CondRetOK;
      } /* else */
      else
      {
         return RLEX_CondRetArquivosDiferentes;
      } /* else */

   } /* Fim função: RLEX -Compara arquivos */

/********** Fim do módulo de implementação: RLEX Reconhecedor Léxico **********/

