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


static const char CRIAR_VERTICE_CMD         [ ] = "=criarvertice"     ;
static const char DESTRUIR_VERTICE_CMD      [ ] = "=destruirvertice"  ;
static const char OBTER_VALOR_VERTICE_CMD   [ ] = "=obtervalor"       ;
static const char CRIAR_ARESTA_CMD        [ ] = "=criararesta"      ;
static const char DESTRUIR_ARESTA_CMD       [ ] = "=destruiraresta"   ;
static const char PERCORRER_ARESTA_CMD      [ ] = "=percorreraresta"  ;

#define TST_VER_TRUE  1
#define TST_VER_FALSE 0

#define DIM_VT_VERTICE 10
#define DIM_VALOR_VERTICE 10

VER_tppVertice vtVertices[ DIM_VT_VERTICE ] ;

/***** Protótipos das funções encapuladas no módulo *****/

   static int ValidarIndexVertice( int indexVertice ) ;

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
*    =criarvertice              inxVERTICE, stringdado, CondRetEsp
*	  =destruirvertice			  inxVERTICE, CondRetEsp
*	  =obtervalor					  inxVERTICE, ValorEsp, CondRetEsp
*	  =criararesta				     inxVERTICEPart, inxVERTICEDest, stringdado, CondRetEsp
*	  =destruiraresta				  inxVERTICE, stringdadoAre, CondRetEsp
*    =percorreraresta           inxVERTIVEPart, stringdado, inxVERTICEDest, Sentido, ConsRetEsp
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando(char * ComandoTeste) {

      int inxVERTICE = -1,
         inxVERTICE2 = -1,
         numLidos = -1,
         sentido = -1,
         CondRetEsp = -1;

      TST_tpCondRet CondRetTST = TST_CondRetOK;
      VER_tpCondRet CondRetVER = VER_CondRetOK;

      char * pDado;
      char StringDado[DIM_VALOR_VERTICE];
      char StringEsperado[DIM_VALOR_VERTICE];

      int ValEsp = -1;
      int numElem = -1;

      /* Testar criarvertice */

      if (strcmp(ComandoTeste, CRIAR_VERTICE_CMD) == 0) {

         numLidos = LER_LerParametros("isi", &
            inxVERTICE, StringDado, &CondRetEsp);

         if ((numLidos != 3) ||
            (!ValidarIndexVertice(inxVERTICE))) {
            return TST_CondRetParm;
         } /* if */

         pDado = (char * ) malloc(DIM_VALOR_VERTICE);
         if (pDado == NULL) {
            return TST_CondRetMemoria;
         } /* if */

         strcpy_s(pDado, DIM_VALOR_VERTICE, StringDado);

         CondRetVER = VER_CriarVertice(NULL, pDado, &vtVertices[inxVERTICE]);

          if (CondRetVER != CondRetEsp)
            return TST_CondRetErro;

         return TST_CondRetOK;

      } /* fim ativa: Testar criarvertice */

      /* Testar destruirvertice */

      if (strcmp(ComandoTeste, DESTRUIR_VERTICE_CMD) == 0) {
         numLidos = LER_LerParametros("ii", &
            inxVERTICE, & CondRetEsp);

         if ((numLidos != 2) ||
            (!ValidarIndexVertice(inxVERTICE))) {
            return TST_CondRetParm;
         } /* if */

         CondRetVER = VER_DestruirVertice(vtVertices[inxVERTICE]);

         vtVertices[inxVERTICE] = NULL;

        if (CondRetVER != CondRetEsp)
            return TST_CondRetErro;

         return TST_CondRetOK;

      } /*fim ativa: Testar destruirvertice*/

      /* Testar obtervalor*/
      if (strcmp(ComandoTeste, OBTER_VALOR_VERTICE_CMD) == 0) {

         numLidos = LER_LerParametros("isi", &
            inxVERTICE, StringEsperado, & CondRetEsp);

         if ((numLidos != 3) ||
            (!ValidarIndexVertice(inxVERTICE))) {
            return TST_CondRetParm;
         } /* if */

         pDado = (char * ) malloc(DIM_VALOR_VERTICE);
         if (pDado == NULL) {
            return TST_CondRetMemoria;
         } /* if */

         strcpy_s(pDado, DIM_VALOR_VERTICE, StringEsperado);

         CondRetVER = VER_ObterValor(vtVertices[inxVERTICE], StringDado);

         if ((CondRetVER != CondRetEsp) || (strcmp(pDado, StringDado) != 0)) {
            return TST_CondRetErro;
         } /* if */

         return TST_CondRetOK;

      } /* fim ativa: Testar obtervalor */

      /* Testar criararesta*/
      if (strcmp(ComandoTeste, CRIAR_ARESTA_CMD) == 0) {

         numLidos = LER_LerParametros("iisi", &
            inxVERTICE, & inxVERTICE2, StringDado, & CondRetEsp);

         if ((numLidos != 3) ||
            (!ValidarIndexVertice(inxVERTICE)) ||
            (!ValidarIndexVertice(inxVERTICE2))) {
            return TST_CondRetParm;
         } /* if */

         pDado = (char * ) malloc(DIM_VALOR_VERTICE);
         if (pDado == NULL) {
            return TST_CondRetMemoria;
         } /* if */

         strcpy_s(pDado, DIM_VALOR_VERTICE, StringEsperado);

         CondRetVER = VER_CriarAresta(vtVertices[inxVERTICE],
            vtVertices[inxVERTICE2],
            pDado);

         if (CondRetVER != CondRetEsp)
            return TST_CondRetErro;

         return TST_CondRetOK;

      } /* fim ativa: Testar criararesta*/

      /* Testar destruiraresta*/
      if (strcmp(ComandoTeste, DESTRUIR_ARESTA_CMD) == 0) {
         numLidos = LER_LerParametros("isi", &
            inxVERTICE, StringDado, & CondRetEsp);

         if ((numLidos != 3) ||
            (!ValidarIndexVertice(inxVERTICE))) {
            return TST_CondRetParm;
         } /* if */

         pDado = (char * ) malloc(DIM_VALOR_VERTICE);
         if (pDado == NULL) {
            return TST_CondRetMemoria;
         } /* if */

         strcpy_s(pDado, DIM_VALOR_VERTICE, StringEsperado);

         CondRetVER = VER_DestruirAresta(vtVertices[inxVERTICE], pDado, ComparaStrings);

         if (CondRetVER != CondRetEsp)
            return TST_CondRetErro;

         return TST_CondRetOK;

      } /* fim ativa: Testar destruiraresta*/

      /* Testar percorreraresta*/
      if (strcmp(ComandoTeste, PERCORRER_ARESTA_CMD) == 0) {

          numLidos = LER_LerParametros("isiii", &
            inxVERTICE, StringDado, inxVERTICE2, &sentido, & CondRetEsp);

           if ((numLidos != 5) ||
            (!ValidarIndexVertice(inxVERTICE))||
            (!ValidarIndexVertice(inxVERTICE2))||
            (sentido!=0 && sentido!=1)) {
            return TST_CondRetParm;
         } /* if */

         pDado = (char * ) malloc(DIM_VALOR_VERTICE);
         if (pDado == NULL) {
            return TST_CondRetMemoria;
         } /* if */

         strcpy_s(pDado, DIM_VALOR_VERTICE, StringDado);

         CondRetVER = VER_PercorrerAresta(vtVertices[inxVERTICE], pDado, vtVertices[inxVERTICE2], ComparaStrings, sentido);

         if (CondRetVER != CondRetEsp)
            return TST_CondRetErro;

         return TST_CondRetOK;

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

   int ComparaStrings (void* pa, void*pb)
   {

      return strcmp((char*)pa, (char*)pb);

   } /* Fim função: TVER -Compara Strings */

/********** Fim do módulo de implementação: TVER Teste VERTICE de símbolos **********/

