/***************************************************************************
*  $MCI Módulo de implementação: VER Vértice
*
*  Arquivo gerado:              VERTICE.c
*  Letras identificadoras:      VER
*
*  Curso: INF 1301 Programação Modular
*  Orientador: Flavio Bevilacqua
*  Autores:   gui   Guilherme Dantas
*             cai   Caique Molina
*             nag   Nagib Suaid
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       gui   17/09/2018  início do desenvolvimento
*     1.1     gui   21/09/2018  implementação das funções básicas
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#include "VERTICE.h"

/***********************************************************************
*
*  $TC Tipo de dados: VER Aresta
*
*
***********************************************************************/

	typedef struct VER_tagAresta{

		void * Valor ;
			/* Ponteiro genérico para o valor armazenado na aresta */

		VER_tppVertice pPart;
			/* Ponteiro para vértice de origem da aresta */

		VER_tppVertice pDest;
			/* Ponteiro para vértice de destino da aresta*/

	} VER_tpAresta;

/***********************************************************************
*
*  $TC Tipo de dados: VER Vértice
*
*
***********************************************************************/

   typedef struct VER_tagVertice {

          void * Valor ;
               /* Ponteiro genérico para o valor armazenado no vértice */

          LIS_tppLista pAnt;
               /* Ponteiro para a cabeça da lista de arestas que apontam para o vértice (antecessores) */

          LIS_tppLista pSuc;
               /* Ponteiro para a cabeça da lista de arestas que partem do vértice (sucessores) */

          void ( * ExcluirValor ) ( void * pDado ) ;
               /* Ponteiro para a função de destruição do valor */

   } VER_tpVertice ;

/***** Protótipos das funções encapuladas no módulo *****/

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: VER  &Criar vértice
*  ****/

    VER_tppVertice VER_CriarVertice(  void   ( * ExcluirValor ) ( void * pDado ),
                                      void * pValor ) {

	VER_tppVertice pNovoVertice;
   LIS_tppLista pListaSuc;
	LIS_tppLista pListaAnt;

   pNovoVertice = ( VER_tppVertice ) malloc( sizeof( VER_tpVertice ) );

   if( pNovoVertice == NULL )
   {
      return NULL;
   } /* if */

   pListaSuc = LIS_CriarLista(NULL);

   if( pListaSuc == NULL )
   {
      free(pNovoVertice);
      return NULL;
   } /* if */

   pListaAnt = LIS_CriarLista(NULL);

   if( pListaAnt == NULL )
   {
      free(pNovoVertice);
      LIS_DestruirLista(pListaAnt);
      return NULL;
   } /* if */

   pNovoVertice->ExcluirValor = ExcluirValor;
   pNovoVertice->pAnt = pListaAnt;
   pNovoVertice->pSuc = pListaSuc;
   pNovoVertice->Valor = pValor;

   return pNovoVertice;

	} /* Fim função: VER  &Criar vértice */

/***************************************************************************
*
*  Função: VER  &Destuir vértice
*  ****/

    VER_tpCondRet VER_DestruirVertice( VER_tppVertice pVertice )
    {

       LIS_tppLista pListaSuc;
       LIS_tppLista pListaAnt;

       VER_tpCondRet RetVer;
       VER_tppAresta pArestaTemp;

       if( pVertice == NULL )
       {
          return VER_CondRetVerticeNaoExiste;
       } /* if */

       pListaSuc = pVertice->pSuc;

       if( pListaSuc == NULL )
       {
          return VER_CondRetErroEstrutura;
       } /* if */

       pListaAnt = pVertice->pAnt;

       if( pListaAnt == NULL )
       {
          return VER_CondRetErroEstrutura;
       } /* if */

       IrFinalLista( pListaAnt );

       while( LIS_AvancarElementoCorrente(pListaAnt,0) != LIS_CondRetListaVazia )
       {
          pArestaTemp = ( VER_tppAresta ) LIS_ObterValor( pListaAnt );
          RetVer = VER_DestruirAresta( pArestaTemp );

          if( RetVer != VER_CondRetOK )
          {
             return VER_CondRetErroEstrutura;
          } /* if */
       } /* while */

       IrFinalLista( pListaSuc );

       while( LIS_AvancarElementoCorrente(pListaSuc,0) != LIS_CondRetListaVazia )
       {
          pArestaTemp = ( VER_tppAresta ) LIS_ObterValor( pListaSuc );
          RetVer = VER_DestruirAresta( pArestaTemp );

          if( RetVer != VER_CondRetOK )
          {
             return VER_CondRetErroEstrutura;
          } /* if */
       } /* while */

       LIS_DestruirLista( pListaAnt );
       LIS_DestruirLista( pListaSuc );

       if( pVertice->ExcluirValor != NULL )
       {
         pVertice->ExcluirValor(pVertice->Valor);
       } /* if */

       free(pVertice);

       return VER_CondRetOK;

    } /* Fim função: VER  &Destruir vértice */

/***************************************************************************
*
*  Função: VER  &Destruir aresta
*  ****/

   VER_tpCondRet VER_DestruirAresta( VER_tppAresta pAresta )
   {

      LIS_tpCondRet RetLis;

      LIS_tppLista pListaDestino, pListaPartida;
      VER_tppVertice pDestino, pPartida;

      if( pAresta == NULL )
      {
         return VER_CondRetArestaNaoExiste;
      } /* if */

      pDestino = pAresta->pDest;
      pPartida = pAresta->pPart;

      if( pDestino == NULL || pPartida == NULL )
      {
         return VER_CondRetErroEstrutura;
      } /* if */

      pListaDestino = pDestino->pAnt;
      pListaPartida = pPartida->pSuc;

      if( pListaDestino == NULL || pListaPartida == NULL )
      {
         return VER_CondRetErroEstrutura;
      } /* if */

      /*
      -----------------------------------
         Tratando do vértice de destino
      -----------------------------------
      */
   
      RetLis = LIS_ProcurarValor(pListaDestino,pAresta);

      if( RetLis != LIS_CondRetOK )
      {
         return VER_CondRetErroEstrutura;
      } /* if */

      LIS_ExcluirElemento(pListaDestino);

      /*
      -----------------------------------
         Tratando do vértice de partida
      -----------------------------------
      */

      RetLis = LIS_ProcurarValor(pListaPartida,pAresta);

      if( RetLis != LIS_CondRetOK )
      {
         return VER_CondRetErroEstrutura;
      } /* if */

      LIS_ExcluirElemento(pListaPartida);

      /* Libera a aresta */

      free(pAresta);
      return VER_CondRetOK;

   } /* Fim função: VER  &Destruir Aresta */

/***************************************************************************
*
*  Função: VER  &Obter valor do vértice
*  ****/

   VER_tpCondRet VER_ObterValor( VER_tppVertice pVertice ,
                                 void * pValor )
   {

      if( pVertice == NULL )
      {
         return VER_CondRetVerticeNaoExiste;
      } /* if */

      (*pValor) = pVertice->Valor;

      if( *pValor == NULL )
      {
         return VER_CondRetErroEstrutura;
      } /* if */

      return VER_CondRetOK;

   } /* Fim função: VER  &Obter valor do vértice */

/*****  Código das funções encapsuladas no módulo  *****/

/********** Fim do módulo de implementação: VER  Vértice **********/