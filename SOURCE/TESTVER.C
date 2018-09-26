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
*     1       nag    29/09/18   Criar e Destruir
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
static const char INSERIR_ARESTA_CMD        [ ] = "=inseriraresta"    ;
static const char DESTRUIR_ARESTA_CMD       [ ] = "=destruiraresta"   ;

#define TST_VER_TRUE  1
#define TST_VER_FALSE 0

#define DIM_VT_VERTICE 10
#define DIM_VALOR_VERTICE 10

VER_tppVertice   vtVertices[ DIM_VT_VERTICE ] ;

/***** Protótipos das funções encapuladas no módulo *****/

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
	  char   StringDado[  DIM_VALOR_VERTICE ] ;

      int ValEsp = -1 ;

      int i ;

      int numElem = -1 ;


      /* Testar criarvertice */

         if ( strcmp( ComandoTeste , CRIAR_VERTICE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ic" ,
                       &inxVERTICE, StringDado ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxVERTICE( inxVERTICE )))
            {
               return TST_CondRetParm ;
            } /* if */

			pDado = ( char * ) malloc( strlen( StringDado ) + 1 ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

			 strcpy( pDado , StringDado ) ;

            vtVertices[ inxVERTICE ] =
                 VER_CriarVertice( NULL, pDado ) ;

            return TST_CompararPonteiroNulo( 1 , vtVertices[ inxVERTICE ] ,
               "Erro em ponteiro de novo VERTICE."  ) ;

         } /* fim ativa: Testar criarvertice */

      /* Testar destruirvertice */

		 if (strcmp( ComandoTeste, DESTRUIR_VERTICE_CMD) == 0)
		 {
			 numLidos = LER_LerParametros("ii",
						&inxVERTICE, &CondRetEsp);

			 if ( ( numLidos != 2 )
              || ( ! ValidarInxVERTICE( inxVERTICE ))){
				  return TST_CondRetParm ;
			 }/* if */
			 
			 CondRet = VER_DestruirVertice(vtVertices[ inxVERTICE ]);

			  vtVertices[ inxVERTICE ] = NULL ;

			 return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao destruir vertice.") ;

		 }/*fim ativa: Testar destruirvertice*/
     

   } /* Fim função: TVER &Testar VERTICE */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TVER -Validar indice de VERTICE
*
***********************************************************************/

   int ValidarInxVERTICE( int inxVERTICE )
   {

      if ( ( inxVERTICE <  0 )
        || ( inxVERTICE >= DIM_VT_VERTICE ))
      {
         return TST_VER_FALSE ;
      } /* if */
         
      return TST_VER_TRUE ;

   } /* Fim função: TVER -Validar indice de VERTICE */

/********** Fim do módulo de implementação: TVER Teste VERTICE de símbolos **********/

