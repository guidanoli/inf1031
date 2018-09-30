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
#define INSERIR_ARESTA_CMD       "=inseriraresta"
#define CAMINHAR_GRAFO_CMD       "=caminhargrafo"

#define TST_GRF_TRUE 1
#define TST_GRF_FALSE 0

#define DIM_VT_GRAFO 10
#define DIM_STRINGS 10

GRF_tppGrafo pGrafo = NULL ;

/***** Protótipos das funções encapuladas no módulo *****/

   static int ComparaStrings (void *pa, void*pb) ;
   static void CopiaStrings (void **pa, void *pb) ;

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
*    =criargrafo                CondRetEsperada
*    =destruirgrafo             CondRetEsperada
*    =inserirvertice            ValorVertice CondRetEsperada
*    =inseriraresta             ValorVerOrigem ValorVerDestino ValorAresta CondRetEsperada
*    =caminhargrafo             ValorAresta Sentido CondRetEsperada
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando(char * ComandoTeste) {

      int numParamLidos = -1,
          sentido = -1;

      GRF_tpCondRet CondRetEsperada = GRF_CondRetFaltouMemoria;
      GRF_tpCondRet CondRetObtida   = GRF_CondRetOK;

      TST_tpCondRet CondRetTST = TST_CondRetOK;

      char ValorDado[DIM_STRINGS] = "";
      char ValorDado2[DIM_STRINGS] = "";
      char ValorDado3[DIM_STRINGS] = "";

      /* Testar criargrafo */

      if( strcmp(ComandoTeste,CRIAR_GRAFO_CMD) == 0 )
      {

         numParamLidos = LER_LerParametros("i",&CondRetEsperada);

         if( numParamLidos != 1 )
         {
            return TST_CondRetParm;
         } /* if */

         CondRetObtida = GRF_CriarGrafo(  ComparaStrings ,
                                          ComparaStrings ,
                                          CopiaStrings ,
                                          CopiaStrings ,
                                          NULL ,
                                          NULL ,
                                          &pGrafo );

         return TST_CompararInt(CondRetEsperada,CondRetObtida,"Retorno errado ao criar grafo");

      } /* if */

      /* Testar destruirgrafo */

      if( strcmp(ComandoTeste,DESTRUIR_GRAFO_CMD) == 0 )
      {

         numParamLidos = LER_LerParametros("i",&CondRetEsperada);

         if( numParamLidos != 1 )
         {
            return TST_CondRetParm;
         } /* if */

         CondRetObtida = GRF_DestruirGrafo( &pGrafo );

         return TST_CompararInt(CondRetEsperada,CondRetObtida,"Retorno errado ao destruir grafo");

      }

      /* Testar inserirvertice */

      if( strcmp(ComandoTeste,INSERIR_VERTICE_CMD) == 0 )
      {

         numParamLidos = LER_LerParametros("si",ValorDado,&CondRetEsperada);

         if( numParamLidos != 2 )
         {
            return TST_CondRetParm;
         } /* if */

         CondRetObtida = GRF_InserirVertice( pGrafo , ValorDado );

         return TST_CompararInt(CondRetEsperada,CondRetObtida,"Retorno errado ao inserir vertice");

      } /* if */

      /* Testar inseriraresta */

      if( strcmp(ComandoTeste,INSERIR_ARESTA_CMD) == 0 )
      {

         numParamLidos = LER_LerParametros("sssi",ValorDado,ValorDado2,ValorDado3,&CondRetEsperada);

         if( numParamLidos != 4 )
         {
            return TST_CondRetParm;
         } /* if */

         CondRetObtida = GRF_InserirAresta( pGrafo ,
                                            ValorDado ,
                                            ValorDado2 ,
                                            ValorDado3 ) ;

         return TST_CompararInt(CondRetEsperada,CondRetObtida,"Retorno errado ao inserir aresta");

      } /* if */

      /* Testar caminhargrafo */

      if( strcmp(ComandoTeste,CAMINHAR_GRAFO_CMD) == 0 )
      {

         numParamLidos = LER_LerParametros("sii",ValorDado,&sentido,&CondRetEsperada);

         if( numParamLidos != 3 ||
             sentido < 0 || sentido > 1 )
         {
            return TST_CondRetParm;
         }

         CondRetObtida = GRF_CaminharGrafo( pGrafo ,
                                            ValorDado ,
                                            sentido ) ;

         return TST_CompararInt(CondRetEsperada,CondRetObtida,"Retorno errado ao caminhar por grafo");

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

/********** Fim do módulo de implementação: TGRF Teste Grafo **********/

