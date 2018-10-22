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
*     0       gui   06/10/2018  Início do desenvolvimento
*     1       gui   08/10/2018  Criar, destruir, empilhar, desempilhar e vazia
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

#define PILHA_OWN
#include "PILHA.H"
#undef PILHA_OWN

#include "LISTA.H"

/***********************************************************************
*
*  $TC Tipo de dados: PIL Cabeça de Pilha
*
***********************************************************************/

   typedef struct PIL_tagPilha {

      LIS_tppLista pLista;
            /* ponteiro para cabeça de lista */

      int numElem;
            /* contador de elementos da lista */

   } PIL_tpPilha ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: PIL  &Criar pilha
*  ******/

   PIL_tpCondRet PIL_CriarPilha( PIL_tppPilha * ppPilhaParam )
   {

      PIL_tpPilha * pPilha = NULL;
      
      if( *ppPilhaParam != NULL )
      {
         PIL_tpCondRet Ret = PIL_DestruirPilha( ppPilhaParam );

         if( Ret == PIL_CondRetErroEstrutura )
         {
            return Ret;
         } /* if */

      } /* if */

      pPilha = ( PIL_tpPilha * ) malloc( sizeof( PIL_tpPilha ));

      if( pPilha == NULL )
      {
         return PIL_CondRetFaltouMemoria;
      } /* if */

      pPilha->numElem = 0;
      pPilha->pLista = LIS_CriarLista( NULL );

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

   PIL_tpCondRet PIL_DestruirPilha( PIL_tppPilha * ppPilhaParam )
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

   PIL_tpCondRet PIL_Empilhar( PIL_tppPilha pPilha ,
                               void * pValor )
   {

      LIS_tpCondRet RetLis;

      if( pPilha == NULL )
      {
         return PIL_CondRetPilhaNaoExiste;
      } /* if */

      if( pValor == NULL )
      {
         return PIL_CondRetValorFornecidoNulo;
      } /* if */

      if( pPilha->pLista == NULL )
      {
         return PIL_CondRetErroEstrutura;
      } /* if */
      
      RetLis = LIS_InserirElementoApos(pPilha->pLista,pValor);

      if( RetLis == LIS_CondRetFaltouMemoria )
      {
         return PIL_CondRetFaltouMemoria;
      } /* if */

      (pPilha->numElem)++;

      return PIL_CondRetOK;

   } /* Fim função: PIL  &Empilhar elemento na pilha */

/***************************************************************************
*
*  Função: PIL  &Desempilhar elemento na pilha
*  ******/

   void * PIL_Desempilhar( PIL_tppPilha pPilha )
   {
      void * pValorObtido = NULL;
      LIS_tpCondRet RetLis;

      if( pPilha == NULL )
      {
         return NULL;
      } /* if */

      if( pPilha->pLista == NULL )
      {
         return NULL;
      } /* if */

      if( LIS_AvancarElementoCorrente(pPilha->pLista,0) == LIS_CondRetListaVazia )
      {
         return NULL;
      } /* if */

      pValorObtido = LIS_ObterValor(pPilha->pLista);
      
      RetLis = LIS_ExcluirElemento(pPilha->pLista);

      (pPilha->numElem)--;

      return pValorObtido;

   } /* Fim função: PIL  &Desempilhar elemento na pilha */

/***************************************************************************
*
*  Função: PIL  &Pilha vazia
*  ******/

   PIL_tpCondRet PIL_PilhaVazia( PIL_tppPilha pPilha )
   {

      if( pPilha == NULL )
      {
         return PIL_CondRetPilhaNaoExiste;
      } /* if */

      if( pPilha->numElem == 0 )
      {
         return PIL_CondRetPilhaVazia;
      } /* if */
      else
      {
         return PIL_CondRetOK;
      } /* else */

   } /* Fim função: PIL  &Pilha vazia */

/********** Fim do módulo de implementação: PIL  Pilha genérica **********/