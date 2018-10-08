/***************************************************************************
*
*  $MCI Módulo de implementação: PIL  Pilha genérica
*
*  Arquivo gerado:              PILHA.C
*  Letras identificadoras:      PIL
*
*  Autores:   gui   Guilherme Dantas
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       gui   06/10/2018  Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa o conceito de pilha a partir do módulo lista,
*     desenvolvido por Arndt Von Staa.
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#include "PILHA.H"
#include "LISTA.H"

/***********************************************************************
*
*  $TC Tipo de dados: PIL Cabeça de Pilha
*
***********************************************************************/

   typedef struct PIL_tagElemPilha {

      LIS_tppLista pLista;
            /* ponteiro para cabeça de lista */

      int numElem;
            /* contador de elementos da lista */

   } PIL_tpElemPilha ;

/***** Protótipos das funções encapuladas no módulo *****/

   //aqui os protótipos com static

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: PIL  &Criar pilha
*  ******/

   PIL_tpCondRet PIL_CriarPilha( PIL_tppElemPilha * ppPilhaParam ,
                                  void ( * ExcluirValor ) ( void * pDado ) )
   {

      PIL_tpElemPilha * pPilha = NULL;
      
      if( *ppPilhaParam != NULL )
      {
         PIL_tpCondRet Ret = PIL_DestruirPilha( ppPilhaParam );

         if( Ret == PIL_CondRetErroEstrutura )
         {
            return Ret;
         } /* if */

      } /* if */

      pPilha = ( PIL_tpElemPilha * ) malloc( sizeof( PIL_tpElemPilha ));
      if( pPilha == NULL )
      {
         return PIL_CondRetFaltouMemoria;
      } /* if */

      pPilha->numElem = 0;
      pPilha->pLista = LIS_CriarLista( ExcluirValor );

      if( pPilha->pLista == NULL )
      {
         free(pPilha);
         return PIL_CondRetFaltouMemoria;
      } /* if */
      
      *ppPilhaParam = pPilha;

      return PIL_CondRetOK;

   } /* Fim função: PIL  &Criar pilha */

/***************************************************************************
*
*  Função: PIL  &Destruir pilha
*  ******/

   PIL_tpCondRet PIL_DestruirPilha( PIL_tppElemPilha * ppPilhaParam )
   {

      if( *ppPilhaParam == NULL )
      {
         return PIL_CondRetPilhaNaoExiste;
      } /* if */

      if( (*ppPilhaParam)->pLista == NULL )
      {
         return PIL_CondRetErroEstrutura;
      } /* if */

      LIS_DestruirLista( (*ppPilhaParam)->pLista );

      free( *ppPilhaParam );

      *ppPilhaParam = NULL;

      return PIL_CondRetOK;

   } /* Fim função: PIL  &Destruir pilha */

/***************************************************************************
*
*  Função: PIL  &Empilhar elemento na pilha
*  ******/

   PIL_tpCondRet PIL_Empilhar( PIL_tppElemPilha pPilhaParam ,
                               void * pValor )
   {

      LIS_tpCondRet RetLis;

      if( pPilhaParam == NULL )
      {
         return PIL_CondRetPilhaNaoExiste;
      } /* if */

      if( pValor == NULL )
      {
         return PIL_CondRetValorFornecidoNulo;
      } /* if */

      if( pPilhaParam->pLista == NULL )
      {
         return PIL_CondRetErroEstrutura;
      } /* if */
      
      RetLis = LIS_InserirElementoApos(pPilhaParam->pLista,pValor);

      if( RetLis == LIS_CondRetFaltouMemoria )
      {
         return PIL_CondRetFaltouMemoria;
      } /* if */

      (pPilhaParam->numElem)++;

      return PIL_CondRetOK;

   } /* Fim função: PIL  &Empilhar elemento na pilha */

/********** Fim do módulo de implementação: PIL  Pilha genérica **********/