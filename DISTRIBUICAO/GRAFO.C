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
               /* Ponteiro para vértice corrente
                  É nulo para grafo vazio */

         LIS_tppLista pOrigensGrafo ;
               /* Ponteiro para cabeça da lista das origens */

         LIS_tppLista pVerticesGrafo ;
               /* Ponteiro para cabeça da lista dos vértices */

         int (* ComparaValorAre ) ( void * pA, void * pB);
               /* Ponteiro para função de comparação de valores de aresta
                  Retorna 0 caso *pa == *pB, e diferente de 0 caso contrário */

         int (* ComparaValorVer ) ( void * pA, void * pB);
               /* Ponteiro para função de comparação de valores de vértice
                  Retorna 0 caso *pa == *pB, e diferente de 0 caso contrário */

         void (* CopiaValorAre ) ( void ** pA, void * pB);
               /* Ponteiro para função que copia valores de aresta
                  Copia o valor de pb para *pA */

         void (* CopiaValorVer ) ( void ** pA, void * pB);
               /* Ponteiro para função que copia valores de vértice
                  Copia o valor de pb para *pA */

         void (* ExcluirValorVer ) ( void * pDado );
               /* Ponteiro para função que excluir o valor do vértice
                  Exclui o valor de *pDado de acordo com seu tipo
                  PODE SER NULO */

         void (* ExcluirValorAre ) ( void * pDado );
               /* Ponteiro para função que excluir o valor da aresta
                  Exclui o valor de *pDado de acordo com seu tipo
                  PODE SER NULO */

   } GRF_tpGrafo ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirVertice ( void * pVertice );

   static GRF_tpCondRet ProcurarVertice( GRF_tppGrafo pGrafo ,
										           void *pValor );

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: GRF  &Criar grafo
*  ****/

   GRF_tpCondRet GRF_CriarGrafo( int (* ComparaValorAre ) ( void * pA, void * pB) ,
                                 int (* ComparaValorVer ) ( void * pA, void * pB) ,
                                 void (* CopiaValorAre ) ( void ** pA, void * pB) ,
                                 void (* CopiaValorVer ) ( void ** pA, void * pB) ,
                                 void (* ExcluirValorVer ) ( void * pDado ) ,
                                 void (* ExcluirValorAre ) ( void * pDado ) ,
                                 GRF_tppGrafo * ppGrafoParam )
   {

      GRF_tppGrafo pNovoGrafo;
      LIS_tppLista pListaOrigem;
      LIS_tppLista pListaVertices;
      
      *ppGrafoParam = NULL;

      if( ComparaValorAre == NULL ||
          ComparaValorVer == NULL ||
          CopiaValorAre   == NULL ||
          CopiaValorVer   == NULL )
      {
         return GRF_CondRetFuncaoNula;
      } /* if */

      pNovoGrafo = (GRF_tppGrafo) malloc(sizeof(GRF_tpGrafo));
      
      if(pNovoGrafo == NULL)
      {
         return GRF_CondRetFaltouMemoria;
      } /* if */

      pListaOrigem = LIS_CriarLista(NULL);

      if(pListaOrigem == NULL)
      {
         free(pNovoGrafo);
         return GRF_CondRetFaltouMemoria;
      } /* if */

      pListaVertices = LIS_CriarLista(&DestruirVertice);

      if(pListaVertices == NULL)
      {
         LIS_DestruirLista(pListaOrigem);
         free(pNovoGrafo);
         return GRF_CondRetFaltouMemoria;
      } /* if */

      pNovoGrafo->pVertCorr = NULL;
      pNovoGrafo->pOrigensGrafo = pListaOrigem;
      pNovoGrafo->pVerticesGrafo = pListaVertices;

      pNovoGrafo->ComparaValorAre = ComparaValorAre;
      pNovoGrafo->ComparaValorVer = ComparaValorVer;
      pNovoGrafo->CopiaValorAre = CopiaValorAre;
      pNovoGrafo->CopiaValorVer = CopiaValorVer;
      pNovoGrafo->ExcluirValorAre = ExcluirValorAre;
      pNovoGrafo->ExcluirValorVer = ExcluirValorVer;

      if( *ppGrafoParam != NULL )
      {
         GRF_DestruirGrafo( ppGrafoParam );
      }

      *ppGrafoParam = pNovoGrafo;

      return GRF_CondRetOK;

   } /* Fim função: GRF  &Criar grafo */

/***************************************************************************
*
*  Função: GRF  &Destruir grafo
*  ****/

   GRF_tpCondRet GRF_DestruirGrafo( GRF_tppGrafo * ppGrafoParam )
   {

      if(*ppGrafoParam == NULL)
      {
         return GRF_CondRetGrafoNaoExiste;
      } /* if */

      LIS_DestruirLista((*ppGrafoParam)->pOrigensGrafo);
      LIS_DestruirLista((*ppGrafoParam)->pVerticesGrafo);

      free(*ppGrafoParam);
      *ppGrafoParam = NULL;

      return GRF_CondRetOK;

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
      VER_tpCondRet RetVer;

      VER_tppVertice pNovoVertice = NULL;
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

      RetGrf = ProcurarVertice( pGrafo ,
                                pValor ) ;
      /* Verificar que não há outro vértice com mesmo indentificador */

      if( RetGrf != GRF_CondRetVerticeNaoExiste )
      {
         /* 
         Erros possíveis:  GRF_CondRetErroEstrutura
                           GRF_CondRetVerticeExiste 
         OBS: GRF_CondRetGrafoNaoExiste já foi coberto em cima 
         */

         return RetGrf;
      } /* if */

      RetVer = VER_CriarVertice( pGrafo->ExcluirValorVer ,
                                 pValor ,
                                 pGrafo->CopiaValorVer ,
                                 &pNovoVertice ) ;
      /* Cria uma novo vértice com a regra de exclusão e
         comparação padrões do grafo e o valor fornecido */

      if( RetVer != VER_CondRetOK )
      {
         /* 
         Erros possíveis:  VER_CondRetFaltouMemoria
                           GRF_CondRetFuncaoNula 
         OBS: GRF_CondRetGrafoNaoExiste já foi coberto em cima 
         */

         if( RetVer == VER_CondRetFaltouMemoria )
         {
            return GRF_CondRetFaltouMemoria;
         }
         else // RetVer == GRF_CondRetFuncaoNula
         {
            return GRF_CondRetFuncaoNula;
         }

      } /* if */

      RetLis = LIS_InserirElementoApos( pVertices ,
                                        pNovoVertice )  ;
      /* Insere a vértice na lista dos vértices do grafo */

      if( RetLis == LIS_CondRetFaltouMemoria )
      {
         VER_DestruirVertice(&pNovoVertice);
         return GRF_CondRetFaltouMemoria;
      } /* if */

      pGrafo->pVertCorr = pNovoVertice;
      /* Ponteiro para vértice corrente aponta para o novo vértice */

      return GRF_CondRetOK;

   } /* Fim função: GRF  &Inserir vértice */

/***************************************************************************
*
*  Função: GRF  &Remover vértice
*  ****/

      GRF_tpCondRet GRF_RemoverVertice( GRF_tppGrafo pGrafo ,
                                        void * pValor )
      {

         LIS_tppLista pListaVer, pListaOrig;
         LIS_tpCondRet RetLis = LIS_CondRetNaoAchou,
                       RetLis2 = LIS_CondRetNaoAchou;
         VER_tppVertice pVertice = NULL;

         if( pValor == NULL )
         {
            return GRF_CondRetValorFornecidoNulo;
         } /* if */

         if( pGrafo == NULL )
         {
            return GRF_CondRetGrafoNaoExiste;
         } /* if */

         pListaVer = pGrafo->pVerticesGrafo;
         pListaOrig = pGrafo->pOrigensGrafo;

         if( pListaVer == NULL || pListaOrig == NULL )
         {
            return GRF_CondRetErroEstrutura;
         } /* if */

         if ( LIS_AvancarElementoCorrente(pListaVer,0) != LIS_CondRetListaVazia )
         {
            IrInicioLista(pListaVer);
            RetLis = LIS_CondRetOK;

            while( RetLis == LIS_CondRetOK )
            {
               VER_tppVertice pVerticeTemp = (VER_tppVertice) LIS_ObterValor(pListaVer);
               void * pValorTemp = NULL;

               if( pVerticeTemp == NULL )
               {
                  return GRF_CondRetErroEstrutura;
               } /* if */

               pValorTemp = VER_ObterValor(pVerticeTemp);

               if( pValorTemp == NULL )
               {
                  return GRF_CondRetErroEstrutura;
               } /* if */

               if( (*(pGrafo->ComparaValorVer))(pValorTemp,pValor) == 0 )
               {
                  pVertice = pVerticeTemp;
                  break;
               } /* if */

               RetLis = LIS_AvancarElementoCorrente(pListaVer,1);

            } /* while */

         } /* if */
         else
         {
            return GRF_CondRetGrafoVazio;
         } /* else */

         if( pVertice == NULL )
         {
            return GRF_CondRetVerticeNaoExiste;
         } /* if */

         if ( LIS_AvancarElementoCorrente(pListaOrig,0) != LIS_CondRetListaVazia )
         {
            IrInicioLista(pListaOrig);
            RetLis2 = LIS_ProcurarValor(pListaOrig,pVertice);          
         } /* if */
         
         RetLis = LIS_ExcluirElemento(pListaVer);

         if( RetLis != LIS_CondRetOK )
         {
            return GRF_CondRetErroEstrutura;
         } /* if */
         
         if( RetLis2 == LIS_CondRetOK )
         {
            RetLis = LIS_ExcluirElemento(pListaOrig);
            if( RetLis != LIS_CondRetOK )
            {
               return GRF_CondRetErroEstrutura;
            } /* if */
         } /* if */

         return GRF_CondRetOK;

      } /* Fim função: GRF  &Remover vértice */

/***************************************************************************
*
*  Função: GRF  &Inserir aresta
*  ****/

   GRF_tpCondRet GRF_InserirAresta( GRF_tppGrafo pGrafo ,
                                    void * pValorPartida,
                                    void * pValorDestino,
                                    void * ValorAresta )
   {
      
      VER_tppVertice vA = NULL, vB = NULL;
      LIS_tppLista pVertices;
      VER_tpCondRet RetVer;
      LIS_tpCondRet RetLis;

      if( ValorAresta == NULL )
      {
         return GRF_CondRetValorFornecidoNulo;
      } /* if */

      if( pGrafo == NULL )
      {
         return GRF_CondRetGrafoNaoExiste;
      } /* if */

      pVertices = pGrafo->pVerticesGrafo;

      if( pVertices == NULL )
      {
         return GRF_CondRetErroEstrutura;
      } /* if */

      if( LIS_AvancarElementoCorrente(pVertices,0) != LIS_CondRetListaVazia )
      {

         RetLis = LIS_CondRetOK;
         IrInicioLista(pVertices);

         while( RetLis == LIS_CondRetOK )
         {
            VER_tppVertice pVertCorr = (VER_tppVertice) LIS_ObterValor(pVertices);
            void *pValorCorr = NULL;

            pValorCorr = VER_ObterValor(pVertCorr);

            if( pValorCorr == NULL )
            {
               return GRF_CondRetErroEstrutura;
            } /* if */

            if( (*(pGrafo->ComparaValorVer))(pValorCorr,pValorPartida) == 0 )
            {
               vA = pVertCorr;
            } /* if */
            
            if( (*(pGrafo->ComparaValorVer))(pValorCorr,pValorDestino) == 0 )
            {
               vB = pVertCorr;
            } /* else if */

            RetLis = LIS_AvancarElementoCorrente(pVertices,1);

         } /* while */

      } /* if */

      if( vB == NULL || vA == NULL )
      {
         return GRF_CondRetVerticeNaoExiste;
      } /* if */

      RetVer = VER_CriarAresta( vA ,
                                vB ,
                                ValorAresta ,
                                pGrafo->ComparaValorVer ,
                                pGrafo->CopiaValorVer ) ;
      
      switch( RetVer )
      {
      case VER_CondRetVerticeNaoExiste:
         return GRF_CondRetVerticeNaoExiste;

      case VER_CondRetArestaExiste:
         return GRF_CondRetArestaExiste;

      case VER_CondRetErroEstrutura:
         return GRF_CondRetErroEstrutura;

      case VER_CondRetFaltouMemoria:
         return GRF_CondRetFaltouMemoria;

      case VER_CondRetFuncaoNula:
         return GRF_CondRetFuncaoNula;

      default:
         return GRF_CondRetOK;

      } /* switch */

   } /* Fim da função: GRF  Inserir aresta */

/***************************************************************************
*
*  Função: GRF  &Caminhar por grafo
*  ****/

   GRF_tpCondRet GRF_CaminharGrafo( GRF_tppGrafo pGrafo ,
                                    void * pValor,
                                    int Sentido )
   {

      VER_tpCondRet RetVer;
      VER_tppVertice pVerticeDestino = NULL;

      if( pGrafo == NULL )
      {
         return GRF_CondRetGrafoNaoExiste;
      } /* if */

      if( pGrafo->pOrigensGrafo == NULL || pGrafo->pVerticesGrafo == NULL )
      {
         return GRF_CondRetErroEstrutura;
      } /* if */

      if( LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo,0)
          == LIS_CondRetListaVazia )
      {
         return GRF_CondRetGrafoVazio;
      } /* if */

      if( pGrafo->pVertCorr == NULL )
      {
         /* Uma incoerência do grafo, pois certificou-se acima que o grafo
            não é vazio, portanto, o ponteiro pVertCorr não poderia ser nulo */
         return GRF_CondRetErroEstrutura;
      } /* if */

      RetVer = VER_PercorrerAresta( pGrafo->pVertCorr,
                                    pValor,
                                    &pVerticeDestino,
                                    pGrafo->ComparaValorAre,
                                    Sentido );

      if( RetVer != VER_CondRetOK)
      {
         switch( RetVer )
         {
         case VER_CondRetValorFornecidoNulo:
            /* Optou-se por deixar avaliar se
               pValor é nulo apenas aqui por
               elegância de código.
            */
            return GRF_CondRetValorFornecidoNulo;

         case VER_CondRetArestaNaoExiste:
            return GRF_CondRetArestaNaoExiste;

         case VER_CondRetFuncaoNula:
            /* Optou-se por deixar avaliar se
               a função é nula apenas aqui por
               elegância de código.
            */
            return GRF_CondRetFuncaoNula;

         default:
            /* Aqui caem os retornos:
               VER_CondRetErroEstrutura
               VER_CondRetVerticeNaoExiste
            */
            return GRF_CondRetErroEstrutura;
         } /* switch */
      }

      if( pVerticeDestino == NULL )
      {
         return GRF_CondRetErroEstrutura;
      }

      pGrafo->pVertCorr = pVerticeDestino;
      return GRF_CondRetOK;

   } /* Fim da função: GRF  Caminhar por grafo */

   /***************************************************************************
*
*  Função: GRF  &Destruir aresta
*  ****/

   GRF_tpCondRet GRF_RemoverAresta( GRF_tppGrafo pGrafo,
                                    void* pValorVerOrig,
                                    void* pValorVerDest,
                                    void* pValorAre)
   {
      
      VER_tppVertice pVerticeOrig;
      VER_tppVertice pVerticeDest;
      VER_tpCondRet RetVer;
      GRF_tpCondRet RetGrf;

      if ( pValorAre == NULL || pValorVerOrig == NULL || pValorVerDest == NULL )
      {
         return GRF_CondRetValorFornecidoNulo;
      } /* if */

      if (pGrafo == NULL){
         return GRF_CondRetGrafoNaoExiste;
      } /* if */

      if ( (LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo,0) == LIS_CondRetListaVazia) ^ (pGrafo->pVertCorr == NULL) )
      {
         /* OBS: OPERADOR XOR --> True quando FV ou VF, False quando VV ou FF */
         return GRF_CondRetErroEstrutura;

      } /* if */

      if ( (LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo,0) == LIS_CondRetListaVazia) && (pGrafo->pVertCorr == NULL) )
      {
         /* OPERADOR AND */
         return GRF_CondRetGrafoVazio;
      } /* if */

      RetGrf = ProcurarVertice(pGrafo, pValorVerOrig);
      if ( RetGrf != GRF_CondRetVerticeExiste){
         return RetGrf;
      }/* if */

      pVerticeOrig = pGrafo->pVertCorr;

      RetGrf = ProcurarVertice(pGrafo, pValorVerDest);
      if ( RetGrf != GRF_CondRetVerticeExiste){
         return RetGrf;
      }/* if */

      pVerticeDest = pGrafo->pVertCorr;
      
      RetVer = VER_DestruirAresta(pVerticeOrig, pVerticeDest, pValorAre, pGrafo->ComparaValorAre);

      switch( RetVer )
      {

      case VER_CondRetArestaNaoExiste:
         return GRF_CondRetArestaNaoExiste;

      case VER_CondRetErroEstrutura:
         return GRF_CondRetErroEstrutura;

      case VER_CondRetVerticeNaoExiste:
         return GRF_CondRetVerticeNaoExiste;

      case VER_CondRetFuncaoNula:
         return GRF_CondRetFuncaoNula;

      case VER_CondRetOK:
         return GRF_CondRetOK;

      default:
         return GRF_CondRetErroEstrutura;
      
      } /* if */

   }/*Fim da função: GRF Destruir aresta*/

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
      VER_DestruirVertice( (VER_tppVertice *) &pVertice );
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
      LIS_tpCondRet RetLis;

      if( pGrafo == NULL )
      {
         return GRF_CondRetGrafoNaoExiste;
      } /* if */

      pVertices = pGrafo->pVerticesGrafo;

      if( pVertices == NULL )
      {
         return GRF_CondRetErroEstrutura;
      } /* if */

      if( LIS_AvancarElementoCorrente(pVertices,0) != LIS_CondRetListaVazia )
      {

         RetLis = LIS_CondRetOK;
         IrInicioLista(pVertices);

         while( RetLis == LIS_CondRetOK )
         {
            /* Verifica se algum dos vértices possui o indentificador pValor */

            VER_tppVertice elem = NULL;
            void * pValorRecebido = NULL;

            elem = (VER_tppVertice) LIS_ObterValor(pVertices);

            if( elem == NULL )
            {
               return GRF_CondRetErroEstrutura;
            } /* if */

            pValorRecebido = VER_ObterValor(elem);

            if( pValorRecebido == NULL )
            {
               return GRF_CondRetErroEstrutura;
            }

            if( (*(pGrafo->ComparaValorVer))(pValorRecebido,pValor) == 0 )
            {
               pGrafo->pVertCorr = elem;
               return GRF_CondRetVerticeExiste;
            } /* if */

            RetLis = LIS_AvancarElementoCorrente(pVertices,1);

         } /* while */

      } /* if */

      return GRF_CondRetVerticeNaoExiste;

   } /* Fim da função: GRF  -Procurar vértice em grafo */

/********** Fim do módulo de implementação: GRF  Grafo **********/