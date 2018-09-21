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

		VER_tpVertice * pPart;
			/* Ponteiro para vértice de origem da aresta */

		VER_tpVertice * pDest;
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

    VER_tppVertice VER_CriarVertice(
             void   ( * ExcluirValor ) ( void * pDado ),
             void * Valor ) {

	void* ptListaSuc;
	void* ptListaAnt;

	}


/*****  Código das funções encapsuladas no módulo  *****/

	void destroiAresta(VER_tpAresta*);

/********** Fim do módulo de implementação: VER  Vértice **********/