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

   static int ValidarIndexPilha( int indexPilha ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: TPIL &Testar pilha
*
*  $ED Descrição da função
*     Podem ser criadas até 10 pilhas, identificadas pelos índices 0 a 9 (inclusive)
*
*     Comandos disponíveis:
*    =criarpilha                indexPilha, CondRetEsp
*    =destruirvertice			  indexPilha, CondRetEsp
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando(char * ComandoTeste) {

      int indexPilha = -1;
      int numLidos = -1;

      PIL_tpCondRet CondRetEsp = PIL_CondRetFaltouMemoria;
      TST_tpCondRet CondRetTST = TST_CondRetOK;
      PIL_tpCondRet CondRetPIL = PIL_CondRetOK;

      int IntDado = -1;
      int IntEsperado = -1;

      /* Testar criarpilha */

      if (strcmp(ComandoTeste, CRIAR_PILHA_CMD) == 0) {

         numLidos = LER_LerParametros("ii", &indexPilha, &CondRetEsp);

         if ((numLidos != 2) ||
            (!ValidarIndexPilha(indexPilha))) {
            return TST_CondRetParm;
         } /* if */

         CondRetPIL = PIL_CriarPilha(&vtPilhas[indexPilha],NULL);

         return TST_CompararInt(CondRetEsp,CondRetPIL,"Retorno errado ao criar pilha");

      } /* fim ativa: Testar criarpilha */

      /* Testar destruirpilha */

      if (strcmp(ComandoTeste, DESTRUIR_PILHA_CMD) == 0) {
         numLidos = LER_LerParametros("ii", &indexPilha, &CondRetEsp);

         if ((numLidos != 2) ||
            (!ValidarIndexPilha(indexPilha))) {
            return TST_CondRetParm;
         } /* if */

         CondRetPIL = PIL_DestruirPilha(&vtPilhas[indexPilha]);

         return TST_CompararInt(CondRetEsp,CondRetPIL,"Retorno errado ao destruir pilha");

      } /*fim ativa: Testar destruirpilha*/

      return TST_CondRetNaoConhec;

   } /* Fim função: TPIL &Testar pilha */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TPIL -Validar índice de pilha
*
***********************************************************************/

   int ValidarIndexPilha( int indexPilha )
   {

      if ( ( indexPilha <  0 )
        || ( indexPilha >= DIM_VT_PILHA ))
      {
         return TST_PIL_FALSE ;
      } /* if */
         
      return TST_PIL_TRUE ;

   } /* Fim função: TPIL -Validar indice de pilha */

/********** Fim do módulo de implementação: TPIL Teste pilha com inteiros **********/

