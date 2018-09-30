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

#define TST_GRF_TRUE 1
#define TST_GRF_FALSE 0

#define DIM_VT_GRAFO 10
#define DIM_STRINGS 10

GRF_tppGrafo vtGrafos[ DIM_VT_GRAFO ] ;

/***** Protótipos das funções encapuladas no módulo *****/

   static int ValidarIndexGrafo( int indexGrafo ) ;
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
*    =criargrafo                indexGrafo CondRetEsperada
*    =destruirgrafo             indexGrafo CondRetEsperada

***********************************************************************/

   TST_tpCondRet TST_EfetuarComando(char * ComandoTeste) {

      int indexGrafo = -1,
          numParamLidos = -1;

      GRF_tpCondRet CondRetEsperada = GRF_CondRetFaltouMemoria;
      GRF_tpCondRet CondRetObtida   = GRF_CondRetOK;

      TST_tpCondRet CondRetTST = TST_CondRetOK;

      char pDado[DIM_STRINGS] = "";
      char *pRecebido;
      char StringDado[DIM_STRINGS] = "!";
      char StringEsperado[DIM_STRINGS] = "!";

      /* Testar criargrafo */

      if( strcmp(ComandoTeste,CRIAR_GRAFO_CMD) == 0 )
      {

         numParamLidos = LER_LerParametros("ii",&indexGrafo,&CondRetEsperada);

         if( numParamLidos != 2 ||
             !ValidarIndexGrafo(indexGrafo) )
         {
            return TST_CondRetParm;
         } /* if */

         CondRetObtida = GRF_CriarGrafo(  ComparaStrings ,
                                          ComparaStrings,
                                          CopiaStrings,
                                          CopiaStrings,
                                          &vtGrafos[indexGrafo] );

         return TST_CompararInt(CondRetEsperada,CondRetObtida,"Retorno errado ao criar grafo");

      } /* if */

      if( strcmp(ComandoTeste,DESTRUIR_GRAFO_CMD) == 0 )
      {

         numParamLidos = LER_LerParametros("ii",&indexGrafo,&CondRetEsperada);

         if( numParamLidos != 2 ||
             !ValidarIndexGrafo(indexGrafo) )
         {
            return TST_CondRetParm;
         } /* if */

         CondRetObtida = GRF_DestruirGrafo( &vtGrafos[indexGrafo] );

         return TST_CompararInt(CondRetEsperada,CondRetObtida,"Retorno errado ao destruir grafo");

      }

      return TST_CondRetNaoConhec;

   } /* Fim função: TVER &Testar VERTICE */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TGRF -Validar indice de Grafo
*
***********************************************************************/

   int ValidarIndexGrafo( int indexGrafo )
   {

      if ( ( indexGrafo <  0 )
        || ( indexGrafo >= DIM_VT_GRAFO ))
      {
         return TST_GRF_FALSE ;
      } /* if */
         
      return TST_GRF_TRUE ;

   } /* Fim função: TGRF -Validar indice de Grafo */


 /***********************************************************************
*
*  $FC Função: TVER -Compara Strings
*
***********************************************************************/

   int ComparaStrings (void *pa, void *pb)
   {

      return strcmp( (char*)pa, (char*)pb );

   } /* Fim função: TGRF -Compara Strings */

 /***********************************************************************
*
*  $FC Função: TVER -Copia Strings
*
***********************************************************************/

   void CopiaStrings (void **pa, void *pb)
   {

      *pa = (char *) malloc(sizeof(char)*DIM_STRINGS);
      strcpy_s( (char*)(*pa), DIM_STRINGS, (char*)pb );

   } /* Fim função: TGRF -Copia Strings */

/********** Fim do módulo de implementação: TGRF Teste Grafo **********/

