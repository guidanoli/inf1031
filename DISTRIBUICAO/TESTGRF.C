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

#define TST_GRF_TRUE 1
#define TST_GRF_FALSE 0

#define DIM_VT_GRAFO 3
#define DIM_STRINGS 10

/***** Variáveis globais do módulo *****/

   GRF_tppGrafo pGrafo[DIM_VT_GRAFO] = {NULL,NULL,NULL} ;

/***** Protótipos das funções encapuladas no módulo *****/

   static int ValidaIndiceGrafo ( int indice ) ;
   static int ComparaStrings ( void *pa , void*pb ) ;
   static void CopiaStrings ( void **pa , void *pb ) ;

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
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando(char * ComandoTeste) {

      int indiceGrafo = -1 ,
          numParamLidos = -1 ,
          sentido = -1 ;

      GRF_tpCondRet CondRetEsperada = GRF_CondRetFaltouMemoria;
      GRF_tpCondRet CondRetObtida   = GRF_CondRetOK;

      TST_tpCondRet CondRetTST = TST_CondRetOK;

      char ValorDado[DIM_STRINGS] = "";
      char ValorDado2[DIM_STRINGS] = "";
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

      }

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
         }

         CondRetObtida = GRF_CaminharGrafo( pGrafo[indiceGrafo] ,
                                            ValorDado ,
                                            sentido ) ;

         return TST_CompararInt(CondRetEsperada,CondRetObtida,"Retorno errado ao caminhar por grafo");

      }
      
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

      }


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

