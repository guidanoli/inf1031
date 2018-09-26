/***************************************************************************
*  $MCI Módulo de implementação: TVER Teste Vértice
*
*  Arquivo gerado:              TESTVER.c
*  Letras identificadoras:      TVER
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: ???
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores:   gui   Guilherme Dantas
*             cai   Caique Molina
*             nag   Nagib Suaid
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     0.5	  nag    29/09/18   INCOMPLETO
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
static const char OBTER_VALOR_CMD           [ ] = "=obtervalor"       ;
static const char INSERIR_ARESTA_CMD        [ ] = "=inseriraresta"    ;
static const char DESTRUIR_ARESTA_CMD       [ ] = "=destruiraresta"   ;



#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_VERTICE 10
#define DIM_VALOR 10

VER_tppVertice   vtVertices[ DIM_VT_VERTICE ] ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirValor( void * pValor ) ;

   static int ValidarInxVertice( int inxVERTICE , int Modo ) ;

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
*     =criarvertice                   inxVERTICE, stringdado
*	  =destruirvertice				  inxVERTICE, CondRetEsp
*	  =obtervalor					  inxVERTICE, ValorEsp, CondRetEsp
*	  =inseriraresta				  inxVERTICEPart, inxVERTICEDest, stringdado, CondRetEsp
*	  =destruiraresta				  inxVERTICE, stringdadoAre, CondRetEsp
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxVERTICE  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1  ;

      TST_tpCondRet CondRet ;

      char * pDado ;
	  char   StringDado[  DIM_VALOR ] ;

      int ValEsp = -1 ;

      int i ;

      int numElem = -1 ;


      /* Testar Criarvertice */

         if ( strcmp( ComandoTeste , CRIAR_VERTICE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ic" ,
                       &inxVERTICE, StringDado ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxVERTICE( inxVERTICE , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            vtVertices[ inxVERTICE ] =
                 VER_CriarVERTICE( DestruirValor, StringDado ) ;

            return TST_CompararPonteiroNulo( 1 , vtVertices[ inxVERTICE ] ,
               "Erro em ponteiro de novo VERTICE."  ) ;

         } /* fim ativa: Testar CriarVERTICE */

     

   } /* Fim função: TVER &Testar VERTICE */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TVER -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {

      free( pValor ) ;

   } /* Fim função: TVER -Destruir valor */


/***********************************************************************
*
*  $FC Função: TVER -Validar indice de VERTICE
*
***********************************************************************/

   int ValidarInxVERTICE( int inxVERTICE , int Modo )
   {

      if ( ( inxVERTICE <  0 )
        || ( inxVERTICE >= DIM_VT_VERTICE ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtVertices[ inxVERTICE ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtVertices[ inxVERTICE ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim função: TVER -Validar indice de VERTICE */

/********** Fim do módulo de implementação: TVER Teste VERTICE de símbolos **********/

