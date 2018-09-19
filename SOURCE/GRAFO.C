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

         LIS_tppLista pOrigensGrafo ;
               /* Ponteiro para cabeça da lista das origens */

         LIS_tppLista pVerticesGrafo ;
               /* Ponteiro para cabeça da lista dos vértices */

          void ( * ExcluirValor ) ( void * pDado ) ;
               /* Ponteiro para a função de destruição do valor contido em um elemento */

   } GRF_tpGrafo ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirListaGrafo( void * pLista );

   GRF_tpCondRet ProcurarVertice( GRF_tppGrafo pGrafo ,
                                  void *pValor );

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: GRF  &Criar grafo
*  ****/

   GRF_tppGrafo GRF_CriarGrafo(
             void   ( * ExcluirValor ) ( void * pDado ) )
   {

      GRF_tppGrafo pNovoGrafo;
      LIS_tppLista pListaOrigem;
      LIS_tppLista pListaVertices;
      
      pNovoGrafo = (GRF_tppGrafo) malloc(sizeof(GRF_tpGrafo));
      
      if(pNovoGrafo == NULL)
      {
         return NULL;
      } /* if */

      /* Origem e Vértices são LISTAS, portanto recebem a função DestruirListaGrafo */
      pListaOrigem = LIS_CriarLista(DestruirListaGrafo);

      if(pListaOrigem == NULL)
      {
         return NULL;
      } /* if */

      pListaVertices = LIS_CriarLista(DestruirListaGrafo);

      if(pListaVertices == NULL)
      {
         return NULL;
      } /* if */

      /* Contudo, o conteúdo do grafo não é espeficado, e deve ser tratado por ExcluirValor*/
      pNovoGrafo->ExcluirValor = ExcluirValor;
      pNovoGrafo->pOrigensGrafo = pListaOrigem;
      pNovoGrafo->pVerticesGrafo = pListaVertices;

      return pNovoGrafo;

   } /* Fim função: GRF  &Criar grafo */

/***************************************************************************
*
*  Função: GRF  &Destruir grafo
*  ****/

   void GRF_DestruirGrafo( GRF_tppGrafo pGrafo )
   {

      if(pGrafo == NULL)
      {
         return;
      } /* if */

      LIS_DestruirLista(pGrafo->pOrigensGrafo);
      LIS_DestruirLista(pGrafo->pVerticesGrafo);

      free(pGrafo);

   } /* Fim função: GRF  &Destruir grafo */

/***************************************************************************
*
*  Função: GRF  &Inserir vértice
*  ****/

   GRF_tpCondRet GRF_InserirVertice( GRF_tppGrafo pGrafo ,
                                     void * pValor )
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

      pNovoVertice = VER_CriarVertice(pGrafo->ExcluirValor,pValor);
      /* Cria uma novo vértice com a regra de exclusão padrão do grafo */

      if( pNovoVertice == NULL )
      {
         return GRF_CondRetFaltouMemoria;
      } /* if */

      RetLis = LIS_InserirElementoApos(pVertices,pNovoVertice);
      /* Insere a vértice no final da lista dos vértices do grafo */

      if( RetLis == LIS_CondRetFaltouMemoria )
      {
         return GRF_CondRetFaltouMemoria;
      } /* if */

      pAresta = ARE_CriarAresta(
      /* Cria uma a lista para as arestas do novo vértice */

      if( pListaAresta == NULL )
      {
         return GRF_CondRetFaltouMemoria;
      } /* if */

      VER_InserirAresta(pNovoVertice,pListaAresta);
      /* Associa a lista de arestas criado ao struct de vértice */

      return GRF_CondRetOK;

   } /* Fim função: GRF  &Inserir vértice */

/***************************************************************************
*
*  Função: GRF  &Inserir aresta
*  ****/

   

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: GRF  -Destruir lista do grafo
*
*  $ED Descrição da função
*     Destrói a lista interna de uma estrutura de grafo, seja de
*     Origem, Aresta, Vértices ou Vértice. É a função padrão a ser
*     chamada para destruir uma lista interna de um grafo.
*
*  $EP Parâmetros
*     pLista  - ponteiro genérico, mas que deve ser do tipo LIS_tppLista
*               para que a função LIS_DestruirLista seja devidamente
*               chamada.
*
***********************************************************************/

   void DestruirListaGrafo( void * pLista )
   {

      LIS_DestruirLista( (LIS_tppLista) pLista );

   } /* Fim função: GRF  -Destruir lista do grafo */

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

      VER_tppVertice pVertices;

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
         /* Verifica se algum dos vértices possui o indentificador Index */
         LIS_tppLista vert;
         GRF_tpVertice *elem;
         vert = (LIS_tppLista) LIS_ObterValor(pVertices);

         if( vert == NULL )
         {
            return GRF_CondRetErroEstrutura;
         } /* if */

         IrInicioLista(vert);
         elem = (GRF_tpVertice *) LIS_ObterValor(vert);

         if( elem == NULL )
         {
            return GRF_CondRetErroEstrutura;
         } /* if */

         if( elem->Index == Index )
         {
            return GRF_CondRetVerticeExiste;
         }

      } /* while */

      return GRF_CondRetVerticeNaoExiste;

   } /* Fim da função: GRF  -Procurar vértice em grafo */

/********** Fim do módulo de implementação: GRF  Grafo **********/