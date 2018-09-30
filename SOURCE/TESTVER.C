/***************************************************************************
*  $MCI Módulo de implementação: TVER Teste Vértice
*
*  Arquivo gerado:              TESTVER.c
*  Letras identificadoras:      TVER
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
*     0       avs    26/09/18   Modificamos a implementação de TESTLIS.C
*                               de Arndt Von Staa.
*     1       nag    26/09/18   Teste de todas funções menos 
*                               destruiraresta e percorreraresta.
*     2       nag    28/09/18   Implementação de todas as funções de acesso.
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "VERTICE.H"


#define CRIAR_VERTICE_CMD        "=criarvertice"
#define DESTRUIR_VERTICE_CMD     "=destruirvertice"
#define OBTER_VALOR_VERTICE_CMD  "=obtervalor"
#define CRIAR_ARESTA_CMD         "=criararesta"
#define DESTRUIR_ARESTA_CMD      "=destruiraresta"
#define PERCORRER_ARESTA_CMD     "=percorreraresta"

#define TST_VER_TRUE  1
#define TST_VER_FALSE 0

#define DIM_VT_VERTICE 10
#define DIM_VALOR_VERTICE 10

VER_tppVertice vtVertices[ DIM_VT_VERTICE ] ;

/***** Protótipos das funções encapuladas no módulo *****/

   static int ValidarIndexVertice( int indexVertice ) ;
   static int ComparaStrings (void *pa, void*pb) ;
   static void CopiaStrings (void **pa, void *pb) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: TVER &Testar vértice
*
*  $ED Descrição da função
*     Podem ser criadas até 10 vértices, identificadas pelos índices 0 a 9 (inclusive)
*
*     Comandos disponíveis:
*
*    =criarvertice              inxVERTICE, StringEsperado, CondRetEsp
*	  =destruirvertice			  inxVERTICE, CondRetEsp
*	  =obtervalor					  inxVERTICE, ValorEsp
*	  =criararesta				     inxVERTICEPart, inxVERTICEDest, StringEsperado, CondRetEsp
*	  =destruiraresta				  inxVERTICE, StringEsperadoAre, CondRetEsp
*    =percorreraresta           inxVERTIVEPart, StringEsperado, inxVERTICEDest, Sentido, ConsRetEsp
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando(char * ComandoTeste) {

      int inxVERTICE = -1,
         inxVERTICE2 = -1,
         numLidos = -1,
         sentido = -1;

      VER_tpCondRet CondRetEsp = VER_CondRetFaltouMemoria;
      TST_tpCondRet CondRetTST = TST_CondRetOK;
      VER_tpCondRet CondRetVER = VER_CondRetOK;

      char pDado[DIM_VALOR_VERTICE] = "";
      char *pRecebido;
      char StringDado[DIM_VALOR_VERTICE] = "";
      char StringEsperado[DIM_VALOR_VERTICE] = "!";

      int ValEsp = -1;
      int numElem = -1;

      /* Testar criarvertice */

      if (strcmp(ComandoTeste, CRIAR_VERTICE_CMD) == 0) {

         numLidos = LER_LerParametros("isi", &inxVERTICE, StringEsperado, &CondRetEsp);

         if ((numLidos != 3) ||
            (!ValidarIndexVertice(inxVERTICE))) {
            return TST_CondRetParm;
         } /* if */

         strcpy_s(pDado, DIM_VALOR_VERTICE, StringEsperado);

         CondRetVER = VER_CriarVertice(NULL, pDado, CopiaStrings, &vtVertices[inxVERTICE]);

          return TST_CompararInt(CondRetEsp,CondRetVER,"Retorno errado ao criar vertice");

      } /* fim ativa: Testar criarvertice */

      /* Testar destruirvertice */

      if (strcmp(ComandoTeste, DESTRUIR_VERTICE_CMD) == 0) {
         numLidos = LER_LerParametros("ii", &inxVERTICE, &CondRetEsp);

         if ((numLidos != 2) ||
            (!ValidarIndexVertice(inxVERTICE))) {
            return TST_CondRetParm;
         } /* if */

         CondRetVER = VER_DestruirVertice(&vtVertices[inxVERTICE]);

         vtVertices[inxVERTICE] = NULL;

        return TST_CompararInt(CondRetEsp,CondRetVER,"Retorno errado ao destruir vertice");

      } /*fim ativa: Testar destruirvertice*/

      /* Testar obtervalor*/
      if (strcmp(ComandoTeste, OBTER_VALOR_VERTICE_CMD) == 0) {

         numLidos = LER_LerParametros("is", &inxVERTICE, StringDado);

         if ((numLidos != 2) ||
            (!ValidarIndexVertice(inxVERTICE))) {
            return TST_CondRetParm;
         } /* if */

         strcpy_s(pDado, DIM_VALOR_VERTICE, StringDado);

         pRecebido = (char *) VER_ObterValor(vtVertices[inxVERTICE]);

         if(pRecebido != NULL)
         {
            strcpy(StringEsperado,pRecebido);
         }

         return TST_CompararString(pDado,StringEsperado,"Valor obtido nao corresponde ao esperado");

      } /* fim ativa: Testar obtervalor */

      /* Testar criararesta*/
      if (strcmp(ComandoTeste, CRIAR_ARESTA_CMD) == 0) {

         numLidos = LER_LerParametros("iisi", &inxVERTICE, &inxVERTICE2, StringEsperado, &CondRetEsp);

         if ((numLidos != 4) ||
            (!ValidarIndexVertice(inxVERTICE)) ||
            (!ValidarIndexVertice(inxVERTICE2))) {
            return TST_CondRetParm;
         } /* if */

         strcpy_s(pDado, DIM_VALOR_VERTICE, StringEsperado);

         CondRetVER = VER_CriarAresta( vtVertices[inxVERTICE] ,
                                       vtVertices[inxVERTICE2] ,
                                       pDado ,
                                       ComparaStrings ,
                                       CopiaStrings ) ;

         return TST_CompararInt(CondRetEsp,CondRetVER,"Retorno errado ao criar aresta");

      } /* fim ativa: Testar criararesta*/

      /* Testar destruiraresta*/
      if (strcmp(ComandoTeste, DESTRUIR_ARESTA_CMD) == 0) {
         numLidos = LER_LerParametros("isi", &inxVERTICE, StringEsperado, &CondRetEsp);

         if ((numLidos != 3) ||
            (!ValidarIndexVertice(inxVERTICE))) {
            return TST_CondRetParm;
         } /* if */

         strcpy_s(pDado, DIM_VALOR_VERTICE, StringEsperado);

         CondRetVER = VER_DestruirAresta(vtVertices[inxVERTICE], pDado, ComparaStrings);

         return TST_CompararInt(CondRetEsp,CondRetVER,"Retorno errado ao destruir aresta");

      } /* fim ativa: Testar destruiraresta*/

      /* Testar percorreraresta*/
      if (strcmp(ComandoTeste, PERCORRER_ARESTA_CMD) == 0) {

          numLidos = LER_LerParametros("isiii", &inxVERTICE, StringEsperado, &inxVERTICE2, &sentido, &CondRetEsp);

           if ((numLidos != 5) ||
            (!ValidarIndexVertice(inxVERTICE))||
            (!ValidarIndexVertice(inxVERTICE2))||
            (sentido!=0 && sentido!=1)) {
            return TST_CondRetParm;
         } /* if */

         strcpy_s(pDado, DIM_VALOR_VERTICE, StringEsperado);

         CondRetVER = VER_PercorrerAresta(vtVertices[inxVERTICE], pDado, &vtVertices[inxVERTICE2], ComparaStrings, sentido);

         return TST_CompararInt(CondRetEsp,CondRetVER,"Retorno errado ao percorrer aresta");

      }/* fim ative: Testar percorreraresta*/


      return TST_CondRetNaoConhec;

   } /* Fim função: TVER &Testar VERTICE */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TVER -Validar indice de VERTICE
*
***********************************************************************/

   int ValidarIndexVertice( int indexVertice )
   {

      if ( ( indexVertice <  0 )
        || ( indexVertice >= DIM_VT_VERTICE ))
      {
         return TST_VER_FALSE ;
      } /* if */
         
      return TST_VER_TRUE ;

   } /* Fim função: TVER -Validar indice de VERTICE */


 /***********************************************************************
*
*  $FC Função: TVER -Compara Strings
*
***********************************************************************/

   int ComparaStrings (void *pa, void *pb)
   {

      return strcmp( (char*)pa, (char*)pb );

   } /* Fim função: TVER -Compara Strings */

 /***********************************************************************
*
*  $FC Função: TVER -Copia Strings
*
***********************************************************************/

   void CopiaStrings (void **pa, void *pb)
   {

      *pa = (char *) malloc(sizeof(char)*DIM_VALOR_VERTICE);
      strcpy_s( (char*)(*pa), DIM_VALOR_VERTICE, (char*)pb );

   } /* Fim função: TVER -Copia Strings */

/********** Fim do módulo de implementação: TVER Teste VERTICE de símbolos **********/

