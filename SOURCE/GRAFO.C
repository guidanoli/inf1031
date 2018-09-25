/***************************************************************************
*  $MCI Módulo de implementação: GRF Grafo Dirigido
*
*  Arquivo gerado:              GRAFO.c
*  Letras identificadoras:      GRF
*
*  Curso: INF 1301 Programação Modular
*  Orientador: Flavio Bevilacqua
*  Autores:   gui   Guilherme Dantas
*             cai   Caique Molina
*             nag   Nagib Suaid
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       gui   11/09/2018  início do desenvolvimento
*     1.1     gui   21/09/2018  novo modelo de grafo dirigido
*     1.2     gui   25/09/2018  implementação das funções básicas de vértices e arestas
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#include "GRAFO.h"

/***********************************************************************
*
*  $TC Tipo de dados: GRF Cabeça do grafo
*
*
***********************************************************************/

   typedef struct GRF_tagGrafo {

         VER_tppVertice pVertCorr;
               /* Ponteiro para vértice corrente */

         LIS_tppLista pOrigensGrafo ;
               /* Ponteiro para cabeça da lista das origens */

         LIS_tppLista pVerticesGrafo ;
               /* Ponteiro para cabeça da lista dos vértices */

   } GRF_tpGrafo ;

/***** Protótipos das funções encapuladas no módulo *****/

   void DestruirVertice ( void * pVertice );

   GRF_tpCondRet ProcurarVertice( GRF_tppGrafo pGrafo ,
                                  void *pValor );

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: GRF  &Criar grafo
*  ****/

   GRF_tppGrafo GRF_CriarGrafo()
   {

      GRF_tppGrafo pNovoGrafo;
      LIS_tppLista pListaOrigem;
      LIS_tppLista pListaVertices;
      
      pNovoGrafo = (GRF_tppGrafo) malloc(sizeof(GRF_tpGrafo));
      
      if(pNovoGrafo == NULL)
      {
         return NULL;
      } /* if */

      pListaOrigem = LIS_CriarLista(NULL);

      if(pListaOrigem == NULL)
      {
         free(pNovoGrafo);
         return NULL;
      } /* if */

      pListaVertices = LIS_CriarLista(&DestruirVertice);

      if(pListaVertices == NULL)
      {
         LIS_DestruirLista(pListaOrigem);
         free(pNovoGrafo);
         return NULL;
      } /* if */

      pNovoGrafo->pVertCorr = NULL;
      pNovoGrafo->pOrigensGrafo = pListaOrigem;
      pNovoGrafo->pVerticesGrafo = pListaVertices;

      return pNovoGrafo;

   } /* Fim função: GRF  &Criar grafo */

/***************************************************************************
*
*  Função: GRF  &Destruir grafo
*  ****/

   GRF_tpCondRet GRF_DestruirGrafo( GRF_tppGrafo pGrafo )
   {

      if(pGrafo == NULL)
      {
         return GRF_CondRetGrafoNaoExiste;
      } /* if */

      LIS_DestruirLista(pGrafo->pOrigensGrafo);
      LIS_DestruirLista(pGrafo->pVerticesGrafo);

      free(pGrafo);

      return GRF_CondRetOK;

   } /* Fim função: GRF  &Destruir grafo */

/***************************************************************************
*
*  Função: GRF  &Inserir vértice
*  ****/

   GRF_tpCondRet GRF_InserirVertice( GRF_tppGrafo pGrafo ,
                                     void * pValor ,
                                     void (* ExcluirValor) ( void * pDado ) )
   {

      LIS_tpCondRet RetLis;
      GRF_tpCondRet RetGrf;

      VER_tppVertice pNovoVertice;
      LIS_tppLista pVertices;

      if( pGrafo == NULL )
      {
         return GRF_CondRetGrafoNaoExiste;
      } /* if */

      pVertices = pGrafo->pVerticesGrafo;
      /* Facilitar o acesso à lista de Vértices */

      if( pVertices == NULL )
      {
         return GRF_CondRetErroEstrutura;
      } /* if */

      RetGrf = ProcurarVertice(pGrafo,pValor);
      /* Verificar que não há outro vértice com mesmo indentificador */

      if( RetGrf != GRF_CondRetVerticeNaoExiste )
      {
         return RetGrf;
      } /* if */

      pNovoVertice = VER_CriarVertice(ExcluirValor,pValor);
      /* Cria uma novo vértice com a regra de exclusão padrão do grafo e o valor fornecido */

      if( pNovoVertice == NULL )
      {
         return GRF_CondRetFaltouMemoria;
      } /* if */

      RetLis = LIS_InserirElementoApos(pVertices,pNovoVertice);
      /* Insere a vértice no final da lista dos vértices do grafo */

      if( RetLis == LIS_CondRetFaltouMemoria )
      {
         free(pNovoVertice);
         return GRF_CondRetFaltouMemoria;
      } /* if */

      return GRF_CondRetOK;

   } /* Fim função: GRF  &Inserir vértice */

/***************************************************************************
*
*  Função: GRF  &Inserir aresta
*  ****/

   GRF_tpCondRet GRF_InserirAresta( GRF_tppGrafo pGrafo ,
                                    void * pValorA,
                                    void * pValorB,
                                    void * ValorAresta,
                                    int (* ComparaValor) ( void * pA, void * pB) )
   {
      
      VER_tppVertice vA = NULL, vB = NULL;
      LIS_tppLista pVertices;
      VER_tpCondRet RetVer;

      if( pGrafo == NULL )
      {
         return GRF_CondRetGrafoNaoExiste;
      } /* if */

      pVertices = pGrafo->pVerticesGrafo;

      if( pVertices == NULL || ValorAresta == NULL )
      {
         return GRF_CondRetErroEstrutura;
      } /* if */

      IrInicioLista(pVertices);
      while( LIS_AvancarElementoCorrente(pVertices,1) != LIS_CondRetOK )
      {
         VER_tppVertice pVertCorr = (VER_tppVertice) LIS_ObterValor(pVertices);
         void *pValorCorr;

         RetVer = VER_ObterValor(pVertCorr,pValorCorr);
         switch(RetVer)
         {
         case VER_CondRetVerticeNaoExiste:
            return GRF_CondRetVerticeNaoExiste;

         case VER_CondRetErroEstrutura:
            return GRF_CondRetErroEstrutura;
         } /* switch */

         if( pValorCorr == NULL )
         {
            return GRF_CondRetErroEstrutura;
         } /* if */

         if( ComparaValor(pValorCorr,pValorA) == 0 )
         {
            vA = pVertCorr;
         } /* if */
         else if( ComparaValor(pValorCorr,pValorB) == 0 )
         {
            vB = pVertCorr;
         } /* else if */

      } /* while */

      if( vB == NULL || vA == NULL )
      {
         return GRF_CondRetVerticeNaoExiste;
      } /* if */

      RetVer = VER_InserirAresta(vA,vB,ValorAresta);
      
      switch( RetVer )
      {
      case VER_CondRetVerticeNaoExiste:
         return GRF_CondRetVerticeNaoExiste;

      case VER_CondRetErroEstrutura:
         return GRF_CondRetErroEstrutura;

      case VER_CondRetFaltouMemoria:
         return GRF_CondRetFaltouMemoria;
      } /* switch */

      return GRF_CondRetOK;

   } /* Fim da função: GRF  Inserir aresta */

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: GRF  -Destruir Vértice
*
*  $ED Descrição da função
*     Destrói um vértice
*
*  $EP Parâmetros
*     pVertice - ponteiro para vértice
*
***********************************************************************/

   void DestruirVertice ( void * pVertice )
   {
      VER_DestruirVertice( (VER_tppVertice) pVertice );
   } /* Fim da função: GRF  -Destruir Vértice */

/***********************************************************************
*
*  $FC Função: GRF  -Procurar vértice em grafo
*
*  $ED Descrição da função
*     Procura na lista de vértices de um grafo um vértice com dado valor
*     fornecido.
*
*  $EP Parâmetros
*     pGrafo  - ponteiro para o grafo
*     pValor  - ponteiro genérico para o valor do vértice procurado
*
*  $FV Valor retornado
*     GRF_CondRetGrafoNaoExiste     - o ponteiro para o grafo é nulo
*     GRF_CondRetErroEstrutura      - algum erro na estrutura ocorreu
*     GRF_CondRetVerticeExiste      - o vertice com o valor dado existe
*     GRF_CondRetVerticeNaoExiste   - o vertice com o valor dado não existe
*
***********************************************************************/

   GRF_tpCondRet ProcurarVertice( GRF_tppGrafo pGrafo ,
                                  void *pValor )
   {

      LIS_tppLista pVertices;

      if( pGrafo == NULL )
      {
         return GRF_CondRetGrafoNaoExiste;
      } /* if */

      pVertices = pGrafo->pVerticesGrafo;

      if( pVertices == NULL )
      {
         return GRF_CondRetErroEstrutura;
      } /* if */

      IrInicioLista(pVertices);
      while(LIS_AvancarElementoCorrente(pVertices,1) != LIS_CondRetFimLista)
      {
         /* Verifica se algum dos vértices possui o indentificador pValor */

         VER_tppVertice elem;
         void * pValorRecebido;

         elem = (VER_tppVertice) LIS_ObterValor(pVertices);

         if( elem == NULL )
         {
            return GRF_CondRetErroEstrutura;
         } /* if */

         VER_ObterValor(elem,pValorRecebido);

         if( pValorRecebido == pValor )
         {
            return GRF_CondRetVerticeExiste;
         } /* if */

      } /* while */

      return GRF_CondRetVerticeNaoExiste;

   } /* Fim da função: GRF  -Procurar vértice em grafo */

/********** Fim do módulo de implementação: GRF  Grafo **********/