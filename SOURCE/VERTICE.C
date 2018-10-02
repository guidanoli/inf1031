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
*     1.1     gui   21/09/2018  implementação das funções básicas de vértices
*     1.2     gui   25/09/2018  implementação das funções básicas de arestas
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

      void ( * ExcluirValor ) ( void * pDado ) ;
               /* Ponteiro para a função de destruição do valor */

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

   static VER_tpCondRet DestruirArestaPorPonteiro(  VER_tppAresta pAresta );
   /* função prática para uso interno na rotina VER_DestruirVertice */

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: VER  &Criar vértice
*  ****/

   VER_tpCondRet VER_CriarVertice(  void   ( * ExcluirValor ) ( void * pDado ) ,
                                    void * pValor ,
                                    void (* CopiaValor ) ( void ** pA, void * pB) ,
                                    VER_tppVertice *ppVerticeParm )
   {

	   VER_tppVertice pNovoVertice;
      LIS_tppLista pListaSuc;
	   LIS_tppLista pListaAnt;

      if( CopiaValor == NULL )
      {
         return VER_CondRetFuncaoNula;
      } /* if */

      if( *ppVerticeParm != NULL )
      {
         VER_DestruirVertice(ppVerticeParm);
      } /* if */

      pNovoVertice = ( VER_tppVertice ) malloc( sizeof( VER_tpVertice ) );

      if( pNovoVertice == NULL )
      {
         return VER_CondRetFaltouMemoria;
      } /* if */

      pListaSuc = LIS_CriarLista(NULL);

      if( pListaSuc == NULL )
      {
         free(pNovoVertice);
         return VER_CondRetFaltouMemoria;
      } /* if */

      pListaAnt = LIS_CriarLista(NULL);

      if( pListaAnt == NULL )
      {
         free(pNovoVertice);
         LIS_DestruirLista(pListaAnt);
         return VER_CondRetFaltouMemoria;
      } /* if */

      pNovoVertice->ExcluirValor = ExcluirValor;
      pNovoVertice->pAnt = pListaAnt;
      pNovoVertice->pSuc = pListaSuc;

      pNovoVertice->Valor = NULL;
      (* CopiaValor )(&(pNovoVertice->Valor),pValor);

      *ppVerticeParm = pNovoVertice;

      return VER_CondRetOK;

	} /* Fim função: VER  &Criar vértice */

/***************************************************************************
*
*  Função: VER  &Destuir vértice
*  ****/

    VER_tpCondRet VER_DestruirVertice( VER_tppVertice * pVertice )
    {

       LIS_tppLista pListaSuc;
       LIS_tppLista pListaAnt;

       VER_tpCondRet RetVer;
       VER_tppAresta pArestaTemp;

       if( *pVertice == NULL )
       {
          return VER_CondRetVerticeNaoExiste;
       } /* if */

       pListaSuc = (*pVertice)->pSuc;

       if( pListaSuc == NULL )
       {
          return VER_CondRetErroEstrutura;
       } /* if */

       pListaAnt = (*pVertice)->pAnt;

       if( pListaAnt == NULL )
       {
          return VER_CondRetErroEstrutura;
       } /* if */

       if( LIS_AvancarElementoCorrente(pListaAnt,0) != LIS_CondRetListaVazia )
       {
          IrFinalLista( pListaAnt );

          while( LIS_AvancarElementoCorrente(pListaAnt,0) != LIS_CondRetListaVazia )
          {
             pArestaTemp = ( VER_tppAresta ) LIS_ObterValor( pListaAnt );
             RetVer = DestruirArestaPorPonteiro( pArestaTemp );

             if( RetVer != VER_CondRetOK )
             {
                return VER_CondRetErroEstrutura;
             } /* if */
          } /* while */

       } /* if */

       if( LIS_AvancarElementoCorrente(pListaSuc,0) != LIS_CondRetListaVazia )
       {
          IrFinalLista( pListaSuc );

          while( LIS_AvancarElementoCorrente(pListaSuc,0) != LIS_CondRetListaVazia )
          {
             pArestaTemp = ( VER_tppAresta ) LIS_ObterValor( pListaSuc );
             RetVer = DestruirArestaPorPonteiro( pArestaTemp );

             if( RetVer != VER_CondRetOK )
             {
                return VER_CondRetErroEstrutura;
             } /* if */
          } /* while */

       } /* if */

       LIS_DestruirLista( pListaAnt );
       LIS_DestruirLista( pListaSuc );

       if( (*pVertice)->ExcluirValor != NULL )
       {
         (*pVertice)->ExcluirValor((*pVertice)->Valor);
       } /* if */

       free(*pVertice);
       (*pVertice) = NULL;

       return VER_CondRetOK;

    } /* Fim função: VER  &Destruir vértice */

/***************************************************************************
*
*  Função: VER  &Destruir aresta
*  ****/

   VER_tpCondRet VER_DestruirAresta( VER_tppVertice pVerPartida,
                                     VER_tppVertice pVerDestino,
                                     void * pValor,
                                     int (* ComparaValor) ( void * pA, void * pB))
   {

      LIS_tpCondRet RetLis;
      VER_tppAresta pAresta;
      LIS_tppLista pListaDestino, pListaPartida;
      VER_tppVertice pDestino, pPartida;

      if( pVerPartida == NULL || pVerDestino == NULL )
      {
         return VER_CondRetVerticeNaoExiste;
      } /* if */

      if( ComparaValor == NULL )
      {
         return VER_CondRetFuncaoNula;
      } /* if */

      if( LIS_AvancarElementoCorrente(pVerPartida->pSuc,0) != LIS_CondRetListaVazia )
      {

         IrInicioLista(pVerPartida->pSuc);
         RetLis = LIS_CondRetOK;

         while( RetLis == LIS_CondRetOK )
         {
            VER_tppAresta pArestaTemp = (VER_tppAresta) LIS_ObterValor(pVerPartida->pSuc);

            if( pArestaTemp == NULL )
            {
               return VER_CondRetArestaNaoExiste;
            } /* if */

            if( (* ComparaValor)(pArestaTemp->Valor,pValor) == 0 )
            {
               if( pArestaTemp->pPart != pVerPartida )
               {
                  return VER_CondRetErroEstrutura;
               } /* if */

               if( pArestaTemp->pDest == pVerDestino )
               {
                  pAresta = pArestaTemp;
                  break;
               } /* if */

            } /* if */

            RetLis = LIS_AvancarElementoCorrente(pVerPartida->pSuc,1);

         } /* while */
      } /* if */
      else
      {
         return VER_CondRetArestaNaoExiste;
      } /* else */
      
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

      if( LIS_AvancarElementoCorrente(pListaDestino,0) != LIS_CondRetListaVazia )
      {
         IrInicioLista(pListaDestino);
      } /* if */
   
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

      if( LIS_AvancarElementoCorrente(pListaPartida,0) != LIS_CondRetListaVazia )
      {
         IrInicioLista(pListaPartida);
      } /* if */

      RetLis = LIS_ProcurarValor(pListaPartida,pAresta);

      if( RetLis != LIS_CondRetOK )
      {
         return VER_CondRetErroEstrutura;
      } /* if */

      LIS_ExcluirElemento(pListaPartida);

      /* Libera a aresta */

      if ((pAresta->ExcluirValor) != NULL){
         (pAresta->ExcluirValor)(pAresta->Valor);
      }/* if */

      free(pAresta);
      return VER_CondRetOK;

   } /* Fim função: VER  &Destruir Aresta */

/***************************************************************************
*
*  Função: VER  &Obter valor do vértice
*  ****/

   void * VER_ObterValor( VER_tppVertice pVertice )
   {

      if( pVertice == NULL )
      {
         return NULL;
      } /* if */

      return pVertice->Valor;

   } /* Fim função: VER  &Obter valor do vértice */

/***************************************************************************
*
*  Função: VER  &Criar aresta
*  ****/

   VER_tpCondRet VER_CriarAresta(   VER_tppVertice pPartida ,
                                    VER_tppVertice pDestino ,
                                    void * pValorAresta ,
                                    int (* ComparaValor) ( void * pA, void * pB),
                                    void (* CopiaValor ) ( void ** pA, void * pB),
                                    void (* ExcluirValor) ( void * p))
   {

      LIS_tpCondRet RetLis;

      VER_tppAresta pNovaAresta;

      if( CopiaValor == NULL || ComparaValor == NULL )
      {
         return VER_CondRetFuncaoNula;
      } /* if */

      if( pPartida == NULL || pDestino == NULL )
      {
         return VER_CondRetVerticeNaoExiste;
      } /* if */

      if( pValorAresta == NULL   || pPartida->pSuc == NULL || pDestino->pAnt == NULL ||
          pPartida->pAnt == NULL || pDestino->pSuc == NULL )
      {
         return VER_CondRetErroEstrutura;
      } /* if */

      if( pValorAresta == NULL )
      {
         return VER_CondRetValorFornecidoNulo;
      } /* if */

      if( LIS_AvancarElementoCorrente(pPartida->pSuc,0) != LIS_CondRetListaVazia )
      {

         IrInicioLista(pPartida->pSuc);
         RetLis = LIS_CondRetOK;

         while( RetLis == LIS_CondRetOK )
         {
            VER_tppAresta pArestaTemp = (VER_tppAresta) LIS_ObterValor(pPartida->pSuc);

            if( pArestaTemp == NULL )
            {
               return VER_CondRetErroEstrutura;
            } /* if */

            if( pArestaTemp->Valor == NULL )
            {
               return VER_CondRetErroEstrutura;
            } /* if */

            if( ((*ComparaValor)(pArestaTemp->Valor,pValorAresta) == 0) &&
                pArestaTemp->pDest == pDestino &&
                pArestaTemp->pPart == pPartida )
            {
               return VER_CondRetArestaExiste;
            } /* if */

            RetLis = LIS_AvancarElementoCorrente(pPartida->pSuc,1);

         } /* while */

      } /* if */

      pNovaAresta = (VER_tppAresta) malloc(sizeof(VER_tpAresta));

      if( pNovaAresta == NULL )
      {
         return VER_CondRetFaltouMemoria;
      } /* if */

      pNovaAresta->pDest = pDestino;
      pNovaAresta->pPart = pPartida;
      pNovaAresta->ExcluirValor = ExcluirValor;

      /* Torna Valor de pAresta nulo por precaução */
      pNovaAresta->Valor = NULL;

      /* Copia o valor de pValorAresta para pValor da aresta pNovaAresta */
      (*CopiaValor)(&(pNovaAresta->Valor),pValorAresta);

      RetLis = LIS_InserirElementoApos(pDestino->pAnt,pNovaAresta);

      if( RetLis == LIS_CondRetFaltouMemoria )
      {
         free(pNovaAresta);
         return VER_CondRetFaltouMemoria;
      } /* if */

      RetLis = LIS_InserirElementoApos(pPartida->pSuc,pNovaAresta);

      if( RetLis == LIS_CondRetFaltouMemoria )
      {
         LIS_ExcluirElemento(pDestino->pAnt);
         free(pNovaAresta);
         return VER_CondRetFaltouMemoria;
      } /* if */

      return VER_CondRetOK;

   } /* Fim função: VER  &Criar Aresta */

/***************************************************************************
*
*  Função: VER  &Percorrer Aresta
*  ****/

   VER_tpCondRet VER_PercorrerAresta( VER_tppVertice pVerPartida,
                                      void * pValor,
                                      VER_tppVertice * pVerDestino,
                                      int (* ComparaValor) ( void * pA, void * pB),
                                      int Sentido )
   {
    
      LIS_tppLista listaAresta;

      if( ComparaValor == NULL )
      {
         return VER_CondRetFuncaoNula;
      } /* if */

      if( pVerPartida == NULL )
      {
         return VER_CondRetVerticeNaoExiste;
      } /* if */

      if( pValor == NULL )
      {
         return VER_CondRetValorFornecidoNulo;
      } /* if */

      if( pVerPartida->pSuc == NULL || pVerPartida->pAnt == NULL )
      {
         return VER_CondRetErroEstrutura;
      } /* if */

      if( Sentido == 1 )
      {
         listaAresta = pVerPartida->pSuc;
      } /* if */
      else
      {
         listaAresta = pVerPartida->pAnt;
      } /* else */

      if( LIS_AvancarElementoCorrente(listaAresta,0) != LIS_CondRetListaVazia )
      {

         LIS_tpCondRet Ret = LIS_CondRetOK;
         IrInicioLista( listaAresta );

         while( Ret == LIS_CondRetOK )
         {
            VER_tppAresta pArestaTemp = (VER_tppAresta) LIS_ObterValor(listaAresta);
            int retorno = (* ComparaValor) (pArestaTemp->Valor,pValor);

            if( retorno == 0 )
            {
               if( Sentido == 1 )
               {
                  *pVerDestino = pArestaTemp->pDest;
               } /* if */
               else
               {
                  *pVerDestino = pArestaTemp->pPart;
               } /* else */

               return VER_CondRetOK;
            } /* if */

            Ret = LIS_AvancarElementoCorrente(listaAresta,1);

         } /* while */

      }

      return VER_CondRetArestaNaoExiste;

   } /* Fim função: VER  &Percorrer Aresta */

/*****  Código das funções encapsuladas no módulo  *****/

   VER_tpCondRet DestruirArestaPorPonteiro(  VER_tppAresta pAresta )
   {

      LIS_tpCondRet RetLis;
      LIS_tppLista pListaDestino, pListaPartida;
      VER_tppVertice pDestino, pPartida;

      if( pAresta == NULL )
      {
         return VER_CondRetValorFornecidoNulo;
      }

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
   
      if( LIS_AvancarElementoCorrente(pListaDestino,0) != LIS_CondRetListaVazia )
         IrInicioLista(pListaDestino);

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

      if( LIS_AvancarElementoCorrente(pListaPartida,0) != LIS_CondRetListaVazia )
         IrInicioLista(pListaPartida);

      RetLis = LIS_ProcurarValor(pListaPartida,pAresta);

      if( RetLis != LIS_CondRetOK )
      {
         return VER_CondRetErroEstrutura;
      } /* if */

      LIS_ExcluirElemento(pListaPartida);

      /*
      ----------------------
         Libera a aresta
      ----------------------
      */

      if ((pAresta->ExcluirValor) != NULL){
         (pAresta->ExcluirValor)(pAresta->Valor);
      }/* if */

      free(pAresta);
      return VER_CondRetOK;

   } /* Fim função: VER  &Destruir Aresta */

/********** Fim do módulo de implementação: VER  Vértice **********/