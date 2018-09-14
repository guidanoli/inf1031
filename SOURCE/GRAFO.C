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
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define GRAFO_OWN
#include "GRAFO.h"
#undef GRAFO_OWN

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

   } GRF_tpGrafo ;


/***** Protótipos das funções encapuladas no módulo *****/

   //aqui

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: GRF  &Criar grafo
*  ****/

   GRF_tppGrafo GRF_CriarGrafo(
             void   ( * ExcluirValor ) ( void * pDado ) )
   {
      GRF_tppGrafo pNovoGrafo;
      LIS_tppLista pListaOrigem, pListaVertices;
      
      pNovoGrafo = (GRF_tppGrafo) malloc(sizeof(GRF_tpGrafo));
      
      if(pNovoGrafo == NULL)
      {
         return NULL;
      } /* if */

      pListaOrigem = LIS_CriarLista(ExcluirValor);
      pListaVertices = LIS_CriarLista(ExcluirValor);

      if(pListaOrigem == NULL || pListaVertices == NULL)
      {
         return NULL;
      } /* if */

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

/********** Fim do módulo de implementação: GRF  Grafo **********/