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
*     1.3     gui   02/10/2018  implementação da lista de origens e funções auxiliares
*     1.4     gui   03/10/2018  assertivas de entrada e saída
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#include "GRAFO.h"
#include "LISTA.H"
#include "VERTICE.H"
#include "PILHA.H"

#define GRF_TODOS_VERTICES 0
#define GRF_ORIGENS_APENAS 1

#define GRF_VERTICE_NAO_VISITADO 0
#define GRF_VERTICE_VISITADO 1

/***********************************************************************
*
*  $TC Tipo de dados: GRF Cabeça do grafo
*
*
***********************************************************************/

   typedef struct GRF_tagGrafo {

         VER_tppVertice pVertCorr ;
               /* Ponteiro para vértice corrente
                  É nulo para grafo vazio */

         LIS_tppLista pOrigensGrafo ;
               /* Ponteiro para cabeça da lista das origens */

         LIS_tppLista pVerticesGrafo ;
               /* Ponteiro para cabeça da lista dos vértices */

         PIL_tppPilha pPilhaReleitura ;
               /* Ponteiro para pilha de releitura */

         int (* ComparaValorAre ) ( void * pA, void * pB) ;
               /* Ponteiro para função de comparação de valores de aresta
                  Retorna 0 caso *pa == *pB, e diferente de 0 caso contrário */

         int (* ComparaValorVer ) ( void * pA, void * pB) ;
               /* Ponteiro para função de comparação de valores de vértice
                  Retorna 0 caso *pa == *pB, e diferente de 0 caso contrário */

         void (* CopiaValorAre ) ( void ** pA, void * pB) ;
               /* Ponteiro para função que copia valores de aresta
                  Copia o valor de pB para *pA */

         void (* CopiaValorVer ) ( void ** pA, void * pB) ;
               /* Ponteiro para função que copia valores de vértice
                  Copia o valor de pB para *pA */

         void (* ExcluirValorVer ) ( void * pDado ) ;
               /* Ponteiro para função que excluir o valor do vértice
                  Exclui o valor de *pDado de acordo com seu tipo
                  PODE SER NULO */

         void (* ExcluirValorAre ) ( void * pDado ) ;
               /* Ponteiro para função que excluir o valor da aresta
                  Exclui o valor de *pDado de acordo com seu tipo
                  PODE SER NULO */

         int ( *ConcatenaValorVer) ( char * pA, void * pB ) ;
               /* Ponteiro para função que concatena o valor de pB
                  no final da string pA
                  RETORNA:
                  >> 0 caso a concatenação ocorreu com sucesso
                  >> 1 caso *pA não tenha mais espaço */

         int numVertices ;
               /* Número de vértices */

         int numOrigens ;
               /* Número de origens */

   } GRF_tpGrafo ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirVertice ( void * pVertice );
   static int NumVertices ( GRF_tppGrafo pGrafo );

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: GRF  &Criar grafo
*  ****/

   GRF_tpCondRet GRF_CriarGrafo( int ( *ComparaValorAre ) ( void * pA, void * pB) ,
                                 int ( *ComparaValorVer ) ( void * pA, void * pB) ,
                                 void ( *CopiaValorAre ) ( void ** pA, void * pB) ,
                                 void ( *CopiaValorVer ) ( void ** pA, void * pB) ,
                                 void ( *ExcluirValorVer ) ( void * pDado ) ,
                                 void ( *ExcluirValorAre ) ( void * pDado ) ,
                                 int ( *ConcatenaValorVer) ( char * pA, void * pB ) ,
                                 GRF_tppGrafo * ppGrafoParam )
   {

      GRF_tppGrafo pNovoGrafo;
      LIS_tppLista pListaOrigem;
      LIS_tppLista pListaVertices;
      PIL_tppPilha pPilha = NULL;
      PIL_tpCondRet RetPil;

      *ppGrafoParam = NULL;

      if( ComparaValorAre     == NULL ||
          ComparaValorVer     == NULL ||
          CopiaValorAre       == NULL ||
          CopiaValorVer       == NULL ||
          ConcatenaValorVer   == NULL )
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

      RetPil = PIL_CriarPilha(&pPilha);

      if( RetPil != PIL_CondRetOK )
      {
         LIS_DestruirLista(pListaVertices);
         LIS_DestruirLista(pListaOrigem);
         free(pNovoGrafo);
         return GRF_CondRetFaltouMemoria;
      } /* if */

      pNovoGrafo->pVertCorr = NULL;
      pNovoGrafo->pOrigensGrafo = pListaOrigem;
      pNovoGrafo->pVerticesGrafo = pListaVertices;

      pNovoGrafo->pPilhaReleitura = pPilha;

      pNovoGrafo->ComparaValorAre = ComparaValorAre;
      pNovoGrafo->ComparaValorVer = ComparaValorVer;
      pNovoGrafo->CopiaValorAre = CopiaValorAre;
      pNovoGrafo->CopiaValorVer = CopiaValorVer;
      pNovoGrafo->ExcluirValorAre = ExcluirValorAre;
      pNovoGrafo->ExcluirValorVer = ExcluirValorVer;
      pNovoGrafo->ConcatenaValorVer = ConcatenaValorVer;

      pNovoGrafo->numVertices = 0;
      pNovoGrafo->numOrigens = 0;

      if( *ppGrafoParam != NULL )
      {
         GRF_DestruirGrafo( ppGrafoParam );
      } /* if */

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

      RetGrf = GRF_ProcurarVertice( pGrafo ,
                                    pValor ,
                                    GRF_TODOS_VERTICES ) ;
      /* Verificar que não há outro vértice com mesmo indentificador */

      if( RetGrf != GRF_CondRetVerticeNaoExiste &&
          RetGrf != GRF_CondRetGrafoVazio )
      {
         /* 
         Erros possíveis:  GRF_CondRetErroEstrutura
                           GRF_CondRetOK 
         OBS: GRF_CondRetGrafoNaoExiste já foi coberto em cima 
         */

         if( RetGrf == GRF_CondRetOK )
         {
            return GRF_CondRetVerticeExiste;
         } /* if */

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
         } /* if */
         else // RetVer == GRF_CondRetFuncaoNula
         {
            return GRF_CondRetFuncaoNula;
         } /* else */

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

      if( pGrafo->numVertices == 0 )
      {
         GRF_ToggleOrigem(pGrafo);
      } /* if */

      (pGrafo->numVertices)++;

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
         GRF_tpCondRet RetGrf;
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
                        
            if( RetLis2 == LIS_CondRetOK && pGrafo->numVertices > 1 )
            {
               pGrafo->pVertCorr = pVertice;
               RetGrf = GRF_ToggleOrigem( pGrafo );

               if( RetGrf != GRF_CondRetOK )
               {
                  return RetGrf;
               } /* if */

            } /* if */

         } /* if */
         else
         {
            return GRF_CondRetErroEstrutura;
         } /* else */

         RetLis = LIS_ExcluirElemento(pListaVer);

         if( RetLis != LIS_CondRetOK )
         {
            return GRF_CondRetErroEstrutura;
         } /* if */

         if( LIS_AvancarElementoCorrente(pListaOrig,0) != LIS_CondRetListaVazia )
         {
            VER_tppVertice pVerticeTemp = NULL;
            
            IrInicioLista(pListaOrig);
            pVerticeTemp = (VER_tppVertice) LIS_ObterValor(pListaOrig);

            if( pVerticeTemp == NULL )
            {
               return GRF_CondRetErroEstrutura;
            } /* if */

            pGrafo->pVertCorr = pVerticeTemp;

         } /* if */
         else
         {
            pGrafo->pVertCorr = NULL;

         } /* else */

         (pGrafo->numVertices)--;

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
            } /* if */

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
                                pGrafo->ComparaValorAre ,
                                pGrafo->CopiaValorAre ,
                                pGrafo->ExcluirValorAre) ;
      
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

   } /* Fim da função: GRF  &Inserir aresta */

/***************************************************************************
*
*  Função: GRF  &Caminhar por grafo
*  ****/

   GRF_tpCondRet GRF_CaminharGrafo( GRF_tppGrafo pGrafo ,
                                    void * pValor,
                                    VER_tpSentCam Sentido )
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
      } /* if */

      if( pVerticeDestino == NULL )
      {
         return GRF_CondRetErroEstrutura;
      } /* if */

      pGrafo->pVertCorr = pVerticeDestino;
      return GRF_CondRetOK;

   } /* Fim da função: GRF  &Caminhar por grafo */

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

      RetGrf = GRF_ProcurarVertice(pGrafo, pValorVerOrig, GRF_TODOS_VERTICES);
      if ( RetGrf != GRF_CondRetOK )
      {
         return RetGrf;
      }/* if */

      pVerticeOrig = pGrafo->pVertCorr;

      RetGrf = GRF_ProcurarVertice(pGrafo, pValorVerDest, GRF_TODOS_VERTICES);
      if ( RetGrf != GRF_CondRetOK )
      {
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
      
      } /* switch */

   } /*Fim da função: GRF &Destruir aresta */

/***************************************************************************
*
*  Função: GRF  &Obter valor do vértice corrente
*  ****/

   GRF_tpCondRet GRF_ObterValor( GRF_tppGrafo pGrafo, void ** ppValor )
   {

      *ppValor = NULL;

      if( pGrafo == NULL )
      {
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

      *ppValor = VER_ObterValor(pGrafo->pVertCorr);

      if( *ppValor == NULL )
      {
         return GRF_CondRetErroEstrutura;
      } /* if */

      return GRF_CondRetOK;

   } /* Fim da função: GRF &Obter valor do vértice corrente */

/***************************************************************************
*
*  Função: GRF  &On/off origem no vértice corrente
*  ****/

   GRF_tpCondRet GRF_ToggleOrigem( GRF_tppGrafo pGrafo )
   {

      VER_tppVertice pCorr = NULL;
      LIS_tpCondRet RetLis;

      if( pGrafo == NULL )
      {
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

      RetLis = LIS_ProcurarValor( pGrafo->pVerticesGrafo , pGrafo->pVertCorr ) ;

      if( RetLis != LIS_CondRetOK )
      {
         return GRF_CondRetErroEstrutura;
      } /* if */

      RetLis = LIS_ProcurarValor( pGrafo->pOrigensGrafo , pGrafo->pVertCorr ) ;

      if( RetLis == LIS_CondRetOK )
      {

         if( pGrafo->numOrigens == 1 && pGrafo->numVertices >= 1 )
         {
            return GRF_CondRetUnicaOrigem;
         } /* if */

         (pGrafo->numOrigens)--;
         RetLis = LIS_ExcluirElemento( pGrafo->pOrigensGrafo ) ;
         return GRF_CondRetOK;

      } /* if */
      else
      {
         RetLis = LIS_InserirElementoApos( pGrafo->pOrigensGrafo , pGrafo->pVertCorr ) ;

         if( RetLis == LIS_CondRetFaltouMemoria)
         {
            return GRF_CondRetFaltouMemoria;
         } /* if */

         (pGrafo->numOrigens)++;

      } /* else */

      return GRF_CondRetOK;

   } /* Fim da função: GRF &On/off origem no vértice corrente */

/***************************************************************************
*
*  Função: GRF  &Procura vértice em grafo
*  ****/

   GRF_tpCondRet GRF_ProcurarVertice( GRF_tppGrafo pGrafo ,
										        void *pValor ,
                                      int Origem )
   {

      LIS_tppLista pVertices;
      LIS_tpCondRet RetLis;

      if( pGrafo == NULL )
      {
         return GRF_CondRetGrafoNaoExiste;
      } /* if */

      if( Origem == 1 )
      {
         pVertices = pGrafo->pOrigensGrafo;
      } /* if */
      else
      {
         pVertices = pGrafo->pVerticesGrafo;
      } /* else */

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
            } /* if */

            if( (*(pGrafo->ComparaValorVer))(pValorRecebido,pValor) == 0 )
            {
               pGrafo->pVertCorr = elem;
               return GRF_CondRetOK;
            } /* if */

            RetLis = LIS_AvancarElementoCorrente(pVertices,1);

         } /* while */

      } /* if */
      else
      {
         if( Origem == 1 )
         {

            /* Lista de origens vazia */

            if( pGrafo->pVerticesGrafo == NULL )
            {
               return GRF_CondRetErroEstrutura;
            } /* if */

            if( LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo,0) == LIS_CondRetListaVazia )
            {
               return GRF_CondRetGrafoVazio;
            } /* if */

            return GRF_CondRetErroEstrutura;

         } /* if */

         /* Lista de vértices vazia */

         return GRF_CondRetGrafoVazio;

      } /* else */

      return GRF_CondRetVerticeNaoExiste;

   } /* Fim da função: GRF  &Procurar vértice em grafo */

/***************************************************************************
*
*  Função: GRF  &Exibir grafo
*  ****/

   GRF_tpCondRet GRF_ExibirGrafo( GRF_tppGrafo pGrafo ,
                                  void * pValorOrigem ,
                                  char * StringSaida )
   {

      GRF_tpCondRet RetGrf;
      VER_tpCondRet RetVer;
      LIS_tpCondRet RetLis;
      PIL_tpCondRet RetPil;
      void * pValor = NULL;

      LIS_tppLista pVertices = NULL;
      VER_tppVertice pVerticeTemp = NULL,
                     pVerticeCorr = NULL;
      PIL_tppPilha pPilha = NULL;

      if( StringSaida == NULL || pValorOrigem == NULL )
      {
         return GRF_CondRetValorFornecidoNulo;
      } /* if */

      strcpy_s( StringSaida , GRF_STR_BUFFER_SIZE , "" );

      if( pGrafo == NULL )
      {
         return GRF_CondRetGrafoNaoExiste;
      } /* if */

      pVertices = pGrafo->pVerticesGrafo;

      if( pVertices == NULL )
      {
         return GRF_CondRetErroEstrutura;
      } /* if */

      RetGrf = GRF_ProcurarVertice( pGrafo , pValorOrigem , GRF_ORIGENS_APENAS );

      if( RetGrf != GRF_CondRetOK )
      {
         return RetGrf;
      } /* if */

      /* A partir daqui sabemos que o grafo e a origem existem e o ponteiro de 
         vértice corrente está apontando para a origem de valor pValorOrigem */

      /* Agora os ponteiros de aresta corrente de todos os vértices apontarão
         para a aresta raiz (a primeira a ser inserida), ou serão nulos, caso
         o vértice não possua aresta */

      if( LIS_AvancarElementoCorrente(pVertices,0) != LIS_CondRetListaVazia )
      {

         RetLis = LIS_CondRetOK;
         IrInicioLista(pVertices);

         while( RetLis == LIS_CondRetOK )
         {
            VER_tppVertice pVerticeTemp = (VER_tppVertice) LIS_ObterValor(pVertices);
            
            if( pVerticeTemp == NULL )
            {
               return GRF_CondRetErroEstrutura;
            } /* if */

            RetVer = VER_IrInicioArestaCorrente( pVerticeTemp , VER_SentCamFrente );

            if( RetVer == VER_CondRetErroEstrutura )
            {
               return GRF_CondRetErroEstrutura;
            } /* if */

            RetVer = VER_IrInicioArestaCorrente( pVerticeTemp , VER_SentCamTras );

            if( RetVer == VER_CondRetErroEstrutura )
            {
               return GRF_CondRetErroEstrutura;
            } /* if */

            VER_MudarFlag( pVerticeTemp , GRF_VERTICE_NAO_VISITADO );
            RetLis = LIS_AvancarElementoCorrente(pVertices,1);

         } /* while */

      } /* if */
      else
      {
         return GRF_CondRetErroEstrutura;
      } /* else */

      /* Agora todas as listas de aresta dos vértices do grafo possuem
         seus ponteiros correntes apontando para o elemento raiz ou NULOS*/

      /* Lembrando que o ponteiro corrente da cabeça do grafo aponta
         ainda pro vértice origem */
      
      if( pGrafo->pPilhaReleitura == NULL )
      {
         return GRF_CondRetErroEstrutura;
      } /* if */

      while( PIL_PilhaVazia( pGrafo->pPilhaReleitura ) != PIL_CondRetPilhaVazia )
      {
         /* Os valores são descartados nesse caso */
         PIL_Desempilhar( pGrafo->pPilhaReleitura );
         
      } /* while */

      /* Loop de caminhamento */
      while( 1 )
      {

         int FlagRecebida = -1;
         pVerticeCorr = pGrafo->pVertCorr;
         pPilha = pGrafo->pPilhaReleitura;

         if( pVerticeCorr == NULL ||
             pPilha == NULL )
         {
            strcpy_s( StringSaida , 2 , "" );
            return GRF_CondRetErroEstrutura;
         } /* if */

         if( VER_ObterFlag( pVerticeCorr , &FlagRecebida ) != VER_CondRetOK )
         {
            strcpy_s( StringSaida , 2 , "" );
            return GRF_CondRetErroEstrutura;
         } /* if */

         if( FlagRecebida == GRF_VERTICE_VISITADO )
         {
            /* Vértice corrente visitado */

            RetVer = VER_ComparaFlagsVizinhos( pVerticeCorr ,
                                               GRF_VERTICE_VISITADO ,
                                               VER_SentCamFrente );

            if( RetVer == VER_CondRetListaVazia ||
                RetVer == VER_CondRetOK )
            {
               /* Acabaram as arestas ou não há arestas */

               RetPil = PIL_PilhaVazia( pPilha );

               if( RetPil == PIL_CondRetPilhaVazia )
               {
                  /* Pilha de releitura vazia */
                  break;
               } /* if */
               else
               {
                  /* Pilha de releitura não-vazia */
                  pGrafo->pVertCorr = (VER_tppVertice) PIL_Desempilhar( pPilha );
               } /* else */

            } /* if */
            else
            {
               /* Há arestas a serem visitadas ainda */
               PIL_Empilhar( pPilha , pVerticeCorr );
               pVerticeTemp = pVerticeCorr;
               RetVer = VER_ObterArestaCorrente( pVerticeCorr ,
                                                 &(pGrafo->pVertCorr) ,
                                                 VER_SentCamFrente );
               if( RetVer != VER_CondRetOK )
               {
                  strcpy_s( StringSaida , 2 , "" );
                  return GRF_CondRetErroEstrutura;;
               } /* if */
               RetVer = VER_AvancarArestaCorrente( pVerticeTemp , VER_SentCamFrente, 1 );
            } /* else */

         } /* if */
         else
         {
            int RetInt;
            /* Vértice corrente não visitado */
            pValor = VER_ObterValor( pVerticeCorr );
            RetInt = (*(pGrafo->ConcatenaValorVer))( StringSaida , pValor );

            if( RetInt == 1 )
            {
               strcpy_s( StringSaida , 2 , "" );
               return GRF_CondRetFaltouMemoria;
            } /* if */

            VER_MudarFlag( pVerticeCorr , GRF_VERTICE_VISITADO );
            RetVer = VER_AvancarArestaCorrente( pVerticeCorr , VER_SentCamFrente , 0 );

            if( RetVer == VER_CondRetErroEstrutura )
            {
               strcpy_s( StringSaida , 2 , "" );
               return GRF_CondRetErroEstrutura;
            } /* if */
            else if( RetVer != VER_CondRetArestaNaoExiste )
            {
               /* Vértice corrente possui arestas */
               PIL_Empilhar( pPilha , pVerticeCorr );
               pVerticeTemp = pVerticeCorr;
               RetVer = VER_ObterArestaCorrente( pVerticeCorr ,
                                                 &(pGrafo->pVertCorr) ,
                                                 VER_SentCamFrente );
               if( RetVer != VER_CondRetOK )
               {
                  strcpy_s( StringSaida , 2 , "" );
                  return GRF_CondRetErroEstrutura;;
               } /* if */

               RetVer = VER_AvancarArestaCorrente( pVerticeTemp , VER_SentCamFrente, 1 );

            } /* else if */
         } /* else */

      } /* while */

      return GRF_CondRetOK;

   } /* Fim da função: GRF  &Exibir grafo */

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: GRF  -Destruir vértice
*
*  $ED Descrição da função
*     Destrói um vértice recebendo um ponteiro genérico, e arestas
*     conectadas a ele.
*
*  $AE Assertivas de entrada
*     A função recebe um ponteiro que aponta para uma struct VER_tppVertice
*     ou um ponteiro NULO.
*
*  $AS Assertivas de saída
*     A função torna o ponteiro NULO.
*     Se o ponteiro fornecido não for nulo, exclui quaisquer arestas
*     que estavam conectadas a este vértice, exclui o valor
*     armazenado no vértice e nas arestas, e o próprio vértice em si.
*     Senão, nada será feito.
*
*  $EP Parâmetros
*     pVertice - ponteiro genérico que aponta para o vértice
*
***********************************************************************/

   void DestruirVertice ( void * pVertice )
   {
      VER_DestruirVertice( (VER_tppVertice *) &pVertice );
   } /* Fim da função: GRF  -Destruir Vértice */ 

/***********************************************************************
*
*  $FC Função: GRF  -Número de vértices
*
*  $ED Descrição da função
*     Obtem a quantidade de vértices do grafo
*
*  $AE Assertivas de entrada
*     Recebe um ponteiro para grafo ou NULO.
*
*  $AS Assertivas de saída
*     A função não modifica a estrutura do grafo.
*     O vértice corrente é o último a ser inserido.
*     Caso o grafo não exista ou tiver algum erro de
*     estrutura, a condição de retorono adequada será retornada.
*
*  $EP Parâmetros
*     pGrafo   - ponteiro para grafo
*
*  $FV Valor retornado
*     Quantidade de vértices no grafo fornecido.
*     Caso o grafo for vazio, ou for inexistente, ou a lista de
*     vértices não existir (erro de estrutura), retornará 0.
*
***********************************************************************/

   int NumVertices ( GRF_tppGrafo pGrafo )
   {
      int num = 0;
      LIS_tpCondRet RetLis;
      LIS_tppLista pVertices;

      if( pGrafo == NULL )
      {
         return num;
      } /* if */

      pVertices = pGrafo->pVerticesGrafo;

      if( pVertices == NULL )
      {
         return num;
      } /* if */

      if( LIS_AvancarElementoCorrente(pVertices,0) != LIS_CondRetListaVazia )
      {
         RetLis = LIS_CondRetOK;
         IrInicioLista(pVertices);

         while( RetLis == LIS_CondRetOK )
         {
            num++;
            RetLis = LIS_AvancarElementoCorrente(pVertices,1);
         } /* while */

      } /* if */

      return num;

   } /* Fim da função: GRF  -Número de vértices */

/********** Fim do módulo de implementação: GRF  Grafo **********/
