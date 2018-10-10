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
*     1       gui   08/10/2018  Criar, destruir, empilhar, desempilhar e vazia
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
#define EMPILHAR_CMD             "=empilhar"
#define DESEMPILHAR_CMD          "=desempilhar"
#define VAZIA_CMD                "=vazia"

#define TST_PIL_TRUE  1
#define TST_PIL_FALSE 0

#define TST_VALOR_NULO -1234
#define TST_VALOR_ERRO -1235

#define DIM_VT_PILHA 3

PIL_tppPilha vtPilhas[ DIM_VT_PILHA ] = { NULL, NULL, NULL };

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
*    =empilhar                  indexPilha, IntDado
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando(char * ComandoTeste) {

      int indexPilha = -1;
      int numLidos = -1;

      PIL_tpCondRet CondRetEsp = PIL_CondRetFaltouMemoria;
      TST_tpCondRet CondRetTST = TST_CondRetOK;
      PIL_tpCondRet CondRetPIL = PIL_CondRetOK;

      int IntDado = TST_VALOR_ERRO;
      int IntEsperado = TST_VALOR_ERRO;
      int * pInt = NULL;

      /* Testar criarpilha */

      if (strcmp(ComandoTeste, CRIAR_PILHA_CMD) == 0)
      {
         numLidos = LER_LerParametros("ii", &indexPilha, &CondRetEsp);

         if ((numLidos != 2) ||
            (!ValidarIndexPilha(indexPilha))) {
            return TST_CondRetParm;
         } /* if */

         CondRetPIL = PIL_CriarPilha(&vtPilhas[indexPilha]);

         return TST_CompararInt(CondRetEsp,CondRetPIL,"Retorno errado ao criar pilha");

      } /* fim ativa: Testar criarpilha */

      /* Testar destruirpilha */

      if (strcmp(ComandoTeste, DESTRUIR_PILHA_CMD) == 0)
      {
         numLidos = LER_LerParametros("ii", &indexPilha, &CondRetEsp);

         if ((numLidos != 2) ||
            (!ValidarIndexPilha(indexPilha))) {
            return TST_CondRetParm;
         } /* if */

         CondRetPIL = PIL_DestruirPilha(&vtPilhas[indexPilha]);

         return TST_CompararInt(CondRetEsp,CondRetPIL,"Retorno errado ao destruir pilha");

      } /*fim ativa: Testar destruirpilha*/

      /* Testar empilhar */

      if (strcmp(ComandoTeste, EMPILHAR_CMD) == 0)
      {
         numLidos = LER_LerParametros("iii", &indexPilha, &IntDado, &CondRetEsp);

         if ((numLidos != 3) ||
            (!ValidarIndexPilha(indexPilha))) {
            return TST_CondRetParm;
         } /* if */

         if( IntDado == TST_VALOR_NULO )
         {
            CondRetPIL = PIL_Empilhar(vtPilhas[indexPilha],NULL);
         } /* if */
         else
         {

            pInt = ( int * ) malloc( sizeof(int) );

            if( pInt == NULL )
            {
               return TST_CondRetMemoria;
            } /* if */

            *pInt = IntDado;

            CondRetPIL = PIL_Empilhar(vtPilhas[indexPilha],pInt);
         } /* else */
         
         return TST_CompararInt(CondRetEsp,CondRetPIL,"Retorno errado ao empilhar");

      } /*fim ativa: Testar empilhar*/

      /* Testar desempilhar */

      if (strcmp(ComandoTeste, DESEMPILHAR_CMD) == 0)
      {
         numLidos = LER_LerParametros("ii", &indexPilha, &IntEsperado); 

         if ((numLidos != 2) ||
            (!ValidarIndexPilha(indexPilha))) {
            return TST_CondRetParm;
         } /* if */

         pInt = (int *) PIL_Desempilhar(vtPilhas[indexPilha]);

         if( pInt != NULL )
         {
            IntDado = *pInt;
         } /* if */

         return TST_CompararInt(IntEsperado,IntDado,"Valor obtido diverge do esperado");
         
      } /*fim ativa: Testar desempilhar*/

      /* Testar vazia */

      if (strcmp(ComandoTeste, VAZIA_CMD) == 0)
      {
         numLidos = LER_LerParametros("ii", &indexPilha, &CondRetEsp); 

         if ((numLidos != 2) ||
            (!ValidarIndexPilha(indexPilha))) {
            return TST_CondRetParm;
         } /* if */

         CondRetPIL = PIL_PilhaVazia(vtPilhas[indexPilha]);

         return TST_CompararInt(CondRetEsp,CondRetPIL,"Retorno errado ao checar se pilha eh vazia");

      } /*fim ativa: Testar vazia*/

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

