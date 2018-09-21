/***************************************************************************
*  $MCI Módulo de implementação: GRF Grafo
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
*     1.1     gui   14/09/2018  funções de acesso básicas
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#include "GRAFO.h"

#define TAM_INDEX_ARESTA 3

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
         return NULL;
      } /* if */

      pListaVertices = LIS_CriarLista(&DestruirVertice);

      if(pListaVertices == NULL)
      {
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
      LIS_tppLista pAresta;

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

   // a implementar

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
   }

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
         }

      } /* while */

      return GRF_CondRetVerticeNaoExiste;

   } /* Fim da função: GRF  -Procurar vértice em grafo */

/********** Fim do módulo de implementação: GRF  Grafo **********/