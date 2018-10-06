/***************************************************************************
*  $MCI Módulo de implementação: TPIL Teste pilha com inteiros
*
*  Arquivo gerado:              TESTPIL.C
*  Letras identificadoras:      TPIL
*
*  Autores:   gui    Guilherme Dantas
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     0       gui   06/10/2018  Início do desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "PILHA.H"

#define CRIAR_PILHA_CMD          "=criarpilha"
#define DESTRUIR_PILHA_CMD       "=destruirpilha"

#define TST_PIL_TRUE  1
#define TST_PIL_FALSE 0

#define DIM_VT_PILHA 10

PIL_tppElemPilha vtPilhas[ DIM_VT_PILHA ] = { NULL, NULL, NULL, NULL, NULL,
                                              NULL, NULL, NULL, NULL, NULL };

/***** Protótipos das funções encapuladas no módulo *****/

   static int ValidarIndexVertice( int indexVertice ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: TPIL &Testar pilha
*
*  $ED Descrição da função
*     Podem ser criadas até 10 pilhas, identificadas pelos índices 0 a 9 (inclusive)
*
*     Comandos disponíveis:
*
*     //TEMP
*    =criarvertice              inxVERTICE, StringEsperado, CondRetEsp
*	  =destruirvertice			  inxVERTICE, CondRetEsp
*	  =obtervalor					  inxVERTICE, ValorEsp
*	  =criararesta				     inxVERTICEPart, inxVERTICEDest, StringEsperado, CondRetEsp
*	  =destruiraresta				  inxVERTICEPart, inxVERTICEDest, StringEsperadoAre, CondRetEsp
*    =percorreraresta           inxVERTIVEPart, StringEsperadoAre, Sentido, StringEsperadoVerDestino, ConsRetEsp
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando(char * ComandoTeste) {

      int inxVERTICE = -1;
      int numLidos = -1;

      PIL_tpCondRet CondRetEsp = PIL_CondRetFaltouMemoria;
      TST_tpCondRet CondRetTST = TST_CondRetOK;
      PIL_tpCondRet CondRetPIL = PIL_CondRetOK;

      int IntDado = -1;
      int IntEsperado = -1;

      /* Testar criarpilha */

      if (strcmp(ComandoTeste, CRIAR_PILHA_CMD) == 0) {

         numLidos = LER_LerParametros("ii", &inxVERTICE, &CondRetEsp);

         if ((numLidos != 2) ||
            (!ValidarIndexVertice(inxVERTICE))) {
            return TST_CondRetParm;
         } /* if */

         CondRetPIL = PIL_CriarPilha(&vtPilhas[inxVERTICE],NULL);

          return TST_CompararInt(CondRetEsp,CondRetPIL,"Retorno errado ao criar pilha");

      } /* fim ativa: Testar criarpilha */

      /* Testar destruirpilha */

      if (strcmp(ComandoTeste, DESTRUIR_PILHA_CMD) == 0) {
         numLidos = LER_LerParametros("i", &inxVERTICE);

         if ((numLidos != 1) ||
            (!ValidarIndexVertice(inxVERTICE))) {
            return TST_CondRetParm;
         } /* if */

         PIL_DestruirPilha(&vtPilhas[inxVERTICE]);

        return TST_CondRetOK;

      } /*fim ativa: Testar destruirpilha*/

      return TST_CondRetNaoConhec;

   } /* Fim função: TPIL &Testar pilha */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TPIL -Validar índice de pilha
*
***********************************************************************/

   int ValidarIndexVertice( int indexVertice )
   {

      if ( ( indexVertice <  0 )
        || ( indexVertice >= DIM_VT_PILHA ))
      {
         return TST_PIL_FALSE ;
      } /* if */
         
      return TST_PIL_TRUE ;

   } /* Fim função: TPIL -Validar indice de VERTICE */

/********** Fim do módulo de implementação: TVER Teste VERTICE de símbolos **********/

