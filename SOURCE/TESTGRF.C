/***************************************************************************
*  $MCI Módulo de implementação: TGRF Teste Grafo
*
*  Arquivo gerado:              TESTGRF.c
*  Letras identificadoras:      TGRF
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
*     0       avs    30/09/18   Modificamos a implementação de TESTLIS.C
*                               de Arndt Von Staa.
*     1.0     gui    30/09/18   Início da implementação do módulo
*     2.0     gui    01/10/18   Opera com três grafos com todas as funções
*     2.1     gui    27/10/18   Funções p/ obter número de vértices e origens
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "GRAFO.H"

#define CRIAR_GRAFO_CMD          "=criargrafo"
#define DESTRUIR_GRAFO_CMD       "=destruirgrafo"
#define INSERIR_VERTICE_CMD      "=inserirvertice"
#define REMOVER_VERTICE_CMD      "=removervertice"
#define INSERIR_ARESTA_CMD       "=inseriraresta"
#define REMOVER_ARESTA_CMD       "=removeraresta"
#define CAMINHAR_GRAFO_CMD       "=caminhargrafo"
#define OBTER_VALOR_CMD          "=obtervalor"
#define TOGGLE_ORIGEM_CMD        "=toggleorigem"
#define PROCURAR_VERTICE_CMD     "=procurarvertice"
#define EXIBIR_GRAFO_CMD         "=exibirgrafo"
#define NUM_VERT_CMD             "=obternumvert"
#define NUM_ORIG_CMD             "=obternumorig"

#define TST_GRF_TRUE 1
#define TST_GRF_FALSE 0

#define DIM_VT_GRAFO 3
#define DIM_STRINGS 10
#define DIM_STRING_EXIBICAO 500

/***** Variáveis globais do módulo *****/

   GRF_tppGrafo pGrafo[DIM_VT_GRAFO] = {NULL,NULL,NULL} ;

/***** Protótipos das funções encapuladas no módulo *****/

   static int ValidaIndiceGrafo ( int indice ) ;
   static int ComparaStrings ( void * pa , void * pb ) ;
   static void CopiaStrings ( void ** pa , void * pb ) ;
   static int ConcatenaStrings ( char * pA , void * pB ) ;
   static int PercorreAresta ( void * pA , void * pB ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: TGRF &Testar GRAFO
*
*  $ED Descrição da função
*     Podem ser criadas até 10 grafos, identificadas pelos índices 0 a 9 (inclusive)
*
*     Comandos disponíveis:
*
*    =criargrafo                indexGrafo CondRetEsperada
*    =destruirgrafo             indexGrafo CondRetEsperada
*    =inserirvertice            indexGrafo ValorVertice CondRetEsperada
*    =removervertice            indexGrafo ValorVertice CondRetEsperada
*    =inseriraresta             indexGrafo ValorVerOrigem ValorVerDestino ValorAresta CondRetEsperada
*    =removeraresta             indexGrafo ValorVerOrigem ValorVerDestino ValorAresta CondRetEsperada
*    =caminhargrafo             indexGrafo ValorAresta Sentido CondRetEsperada
*    =obtervalor                indexGrafo ValorEsperado CondRetEsperada
*    =toggleorigem              indexGrafo CondRetEsperada
*    =procurarvertice           indexGrafo ValorVertice OrigemBool CondRetEsperada
*    =exibirgrafo               indexGrafo ValorOrigem StringEsperada CondRetEsperada
*    =obternumvert              indexGrafo ValorEsperado
*    =obternumorig              indexGrafo ValorEsperado
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando(char * ComandoTeste) {

      int indiceGrafo = -1 ,
          numParamLidos = -1 ,
          sentido = -1 ;

      GRF_tpCondRet CondRetEsperada = GRF_CondRetFaltouMemoria;
      GRF_tpCondRet CondRetObtida   = GRF_CondRetOK;
      TST_tpCondRet CondRetTST = TST_CondRetOK;

      char *pValorObtido = NULL;
      char StringEsperada[GRF_STR_BUFFER_SIZE] = "";
      char StringObtida[GRF_STR_BUFFER_SIZE] = "";
      char ValorDado[DIM_STRINGS] = "";
      char ValorDado2[DIM_STRINGS] = "!";
      char ValorDado3[DIM_STRINGS] = "";

      /* Testar criargrafo */

      if( strcmp(ComandoTeste,CRIAR_GRAFO_CMD) == 0 )
      {

         numParamLidos = LER_LerParametros("ii",&indiceGrafo,&CondRetEsperada);

         if( numParamLidos != 2 || !ValidaIndiceGrafo(indiceGrafo) )
         {
            return TST_CondRetParm;
         } /* if */

         CondRetObtida = GRF_CriarGrafo(  ComparaStrings ,
                                          ComparaStrings ,
                                          CopiaStrings ,
                                          CopiaStrings ,
                                          NULL ,
                                          NULL ,
                                          ConcatenaStrings ,
                                          PercorreAresta ,
                                          &(pGrafo[indiceGrafo]) );

         return TST_CompararInt(CondRetEsperada,CondRetObtida,"Retorno errado ao criar grafo");

      } /* if */

      /* Testar destruirgrafo */

      if( strcmp(ComandoTeste,DESTRUIR_GRAFO_CMD) == 0 )
      {

         numParamLidos = LER_LerParametros("ii",&indiceGrafo,&CondRetEsperada);

         if( numParamLidos != 2 || !ValidaIndiceGrafo(indiceGrafo) )
         {
            return TST_CondRetParm;
         } /* if */

         CondRetObtida = GRF_DestruirGrafo( &(pGrafo[indiceGrafo]) );

         return TST_CompararInt(CondRetEsperada,CondRetObtida,"Retorno errado ao destruir grafo");

      } /* if */

      /* Testar inserirvertice */

      if( strcmp(ComandoTeste,INSERIR_VERTICE_CMD) == 0 )
      {

         numParamLidos = LER_LerParametros("isi",&indiceGrafo,ValorDado,&CondRetEsperada);

         if( numParamLidos != 3 || !ValidaIndiceGrafo(indiceGrafo) )
         {
            return TST_CondRetParm;
         } /* if */

         CondRetObtida = GRF_InserirVertice( pGrafo[indiceGrafo] , ValorDado );

         return TST_CompararInt(CondRetEsperada,CondRetObtida,"Retorno errado ao inserir vertice");

      } /* if */

      /* Testar inseriraresta */

      if( strcmp(ComandoTeste,INSERIR_ARESTA_CMD) == 0 )
      {

         numParamLidos = LER_LerParametros("isssi",&indiceGrafo,ValorDado,ValorDado2,ValorDado3,&CondRetEsperada);

         if( numParamLidos != 5 || !ValidaIndiceGrafo(indiceGrafo) )
         {
            return TST_CondRetParm;
         } /* if */

         CondRetObtida = GRF_InserirAresta( pGrafo[indiceGrafo] ,
                                            ValorDado ,
                                            ValorDado2 ,
                                            ValorDado3 ) ;

         return TST_CompararInt(CondRetEsperada,CondRetObtida,"Retorno errado ao inserir aresta");

      } /* if */

      /* Testar removeraresta */

      if( strcmp(ComandoTeste,REMOVER_ARESTA_CMD) == 0 )
      {

         numParamLidos = LER_LerParametros("isssi",&indiceGrafo,ValorDado,ValorDado2,ValorDado3,&CondRetEsperada);

         if( numParamLidos != 5 || !ValidaIndiceGrafo(indiceGrafo) )
         {
            return TST_CondRetParm;
         } /* if */

         CondRetObtida = GRF_RemoverAresta( pGrafo[indiceGrafo] ,
                                            ValorDado ,
                                            ValorDado2 ,
                                            ValorDado3 ) ;

         return TST_CompararInt(CondRetEsperada,CondRetObtida,"Retorno errado ao remover aresta");

      } /* if */

      /* Testar caminhargrafo */

      if( strcmp(ComandoTeste,CAMINHAR_GRAFO_CMD) == 0 )
      {

         numParamLidos = LER_LerParametros("isii",&indiceGrafo,ValorDado,&sentido,&CondRetEsperada);

         if( numParamLidos != 4 ||
             !ValidaIndiceGrafo(indiceGrafo) ||
             sentido < 0 || sentido > 1 )
         {
            return TST_CondRetParm;
         } /* if */

         CondRetObtida = GRF_CaminharGrafo( pGrafo[indiceGrafo] ,
                                            ValorDado ,
                                            sentido ) ;

         return TST_CompararInt(CondRetEsperada,CondRetObtida,"Retorno errado ao caminhar por grafo");

      } /* if */
      
      /* Testar removervertice */

      if( strcmp(ComandoTeste,REMOVER_VERTICE_CMD) == 0 )
      {

         numParamLidos = LER_LerParametros("isi",&indiceGrafo,ValorDado,&CondRetEsperada);

         if( numParamLidos != 3 || !ValidaIndiceGrafo(indiceGrafo) )
         {
            return TST_CondRetParm;
         } /* if */

         CondRetObtida = GRF_RemoverVertice( pGrafo[indiceGrafo] , ValorDado );

         return TST_CompararInt(CondRetEsperada,CondRetObtida,"Retorno errado ao remover vertice");

      } /* if */

      /* Testar obtervalor */

      if( strcmp(ComandoTeste,OBTER_VALOR_CMD) == 0 )
      {

         numParamLidos = LER_LerParametros("isi",&indiceGrafo,ValorDado,&CondRetEsperada);

         if( numParamLidos != 3 || !ValidaIndiceGrafo(indiceGrafo) )
         {
            return TST_CondRetParm;
         } /* if */

         CondRetObtida = GRF_ObterValor( pGrafo[indiceGrafo] , (void**) &pValorObtido );

         CondRetTST = TST_CompararInt(CondRetEsperada,CondRetObtida,"Retorno errado ao obter valor de vertice");

         if( CondRetTST != TST_CondRetOK )
         {
            return CondRetTST;
         } /* if */

         if( pValorObtido != NULL )
         {
            strcpy_s(ValorDado2,DIM_STRINGS,pValorObtido);
         } /* if */

         return TST_CompararString(ValorDado,ValorDado2,"Valor obtido nao corresponde ao esperado");

      } /* if */
      
      /* Testar toggleorigem */

      if( strcmp(ComandoTeste,TOGGLE_ORIGEM_CMD) == 0 )
      {

         numParamLidos = LER_LerParametros("ii",&indiceGrafo,&CondRetEsperada);

         if( numParamLidos != 2 || !ValidaIndiceGrafo(indiceGrafo) )
         {
            return TST_CondRetParm;
         } /* if */

         CondRetObtida = GRF_ToggleOrigem( pGrafo[indiceGrafo] );

         return TST_CompararInt(CondRetEsperada,CondRetObtida,"Retorno errado ao tornar vertice origem");

      } /* if */

      /* Testar procurarvertice */

      if( strcmp(ComandoTeste,PROCURAR_VERTICE_CMD) == 0 )
      {

         int boolOrigem;

         numParamLidos = LER_LerParametros("isii",&indiceGrafo,ValorDado,&boolOrigem,&CondRetEsperada);

         if( numParamLidos != 4 || !ValidaIndiceGrafo(indiceGrafo) )
         {
            return TST_CondRetParm;
         } /* if */

         CondRetObtida = GRF_ProcurarVertice( pGrafo[indiceGrafo] , ValorDado , boolOrigem );

         return TST_CompararInt(CondRetEsperada,CondRetObtida,"Retorno errado ao procurar vertice");

      } /* if */

      /* Testar exibirgrafo */

      if( strcmp(ComandoTeste,EXIBIR_GRAFO_CMD) == 0 )
      {

         numParamLidos = LER_LerParametros("issi",&indiceGrafo,ValorDado,StringEsperada,&CondRetEsperada);

         if( numParamLidos != 4 || !ValidaIndiceGrafo(indiceGrafo) )
         {
            return TST_CondRetParm;
         } /* if */

         CondRetObtida = GRF_ExibirGrafo( pGrafo[indiceGrafo] , ValorDado , StringObtida );

         CondRetTST = TST_CompararInt(CondRetEsperada,CondRetObtida,"Retorno errado ao exibir grafo");

         if( CondRetTST != TST_CondRetOK )
         {
            return CondRetTST;
         } /* if */

         return TST_CompararString(StringEsperada,StringObtida,"Exibicao esperada nao confere com obtida");

      } /* if */

      /* Testar obternumvert */

      if( strcmp(ComandoTeste,NUM_VERT_CMD) == 0 )
      {
         int ValorEsperado, ValorObtido;

         numParamLidos = LER_LerParametros("ii",&indiceGrafo,&ValorEsperado);

         if( numParamLidos != 2 || !ValidaIndiceGrafo(indiceGrafo) )
         {
            return TST_CondRetParm;
         } /* if */

         ValorObtido = GRF_ObterNumVertices( pGrafo[indiceGrafo] );

         return TST_CompararInt(ValorEsperado,ValorObtido,"Numero de vertices esperado nao corresponde ao obtido");

      } /* if */

      /* Testar obternumorig */

      if( strcmp(ComandoTeste,NUM_ORIG_CMD) == 0 )
      {
         int ValorEsperado, ValorObtido;

         numParamLidos = LER_LerParametros("ii",&indiceGrafo,&ValorEsperado);

         if( numParamLidos != 2 || !ValidaIndiceGrafo(indiceGrafo) )
         {
            return TST_CondRetParm;
         } /* if */

         ValorObtido = GRF_ObterNumOrigens( pGrafo[indiceGrafo] );

         return TST_CompararInt(ValorEsperado,ValorObtido,"Numero de origens esperado nao corresponde ao obtido");

      } /* if */

      return TST_CondRetNaoConhec;

   } /* Fim função: TGRF &Testar Grafo */


/*****  Código das funções encapsuladas no módulo  *****/

 /***********************************************************************
*
*  $FC Função: TGRF -Compara Strings
*
***********************************************************************/

   int ComparaStrings (void *pa, void *pb)
   {

      return strcmp( (char*)pa, (char*)pb );

   } /* Fim função: TGRF -Compara Strings */

 /***********************************************************************
*
*  $FC Função: TGRF -Copia Strings
*
***********************************************************************/

   void CopiaStrings (void **pa, void *pb)
   {

      *pa = (char *) malloc(sizeof(char)*DIM_STRINGS);
      strcpy_s( (char*)(*pa), DIM_STRINGS, (char*)pb );

   } /* Fim função: TGRF -Copia Strings */

/***********************************************************************
*
*  $FC Função: TGRF -Concatena Strings
*
***********************************************************************/

   int ConcatenaStrings ( char * pA, void * pB )
   {
      return strcat_s( pA , DIM_STRING_EXIBICAO, (char *) pB );
   } /* Fim função: TGRF -Concatena Strings */

/***********************************************************************
*
*  $FC Função: TGRF -Percorre aresta
*
***********************************************************************/

   int PercorreAresta ( void * pA , void * pB )
   {
      return !ComparaStrings(pA,pB);
   } /* Fim função: TGRF -Percorre aresta */

 /***********************************************************************
*
*  $FC Função: TGRF -Valida índice de grafo
*
***********************************************************************/

   int ValidaIndiceGrafo (int indice)
   {
      if( indice < 0 || indice >= DIM_VT_GRAFO )
      {
         return TST_GRF_FALSE;
      } /* if */

      return TST_GRF_TRUE;

   } /* Fim função: TGRF -Valida índice de grafo */

/********** Fim do módulo de implementação: TGRF Teste Grafo **********/

