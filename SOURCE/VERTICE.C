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
*  $TC Tipo de dados: VER Vértice
*
*
***********************************************************************/

   typedef struct VER_tagVertice {

          void * Valor ;
               /* Ponteiro genérico para o valor armazenado no vértice */

          LIS_tppLista pArestaVertice;
               /* Ponteiro para a cabeça da lista de arestas do vértice */

          void ( * ExcluirValor ) ( void * pDado ) ;
               /* Ponteiro para a função de destruição do valor contido em um elemento */

   } VER_tpVertice ;

/***** Protótipos das funções encapuladas no módulo *****/

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: VER  &Criar vértice
*  ****/

   // a fazer ainda


/*****  Código das funções encapsuladas no módulo  *****/

/********** Fim do módulo de implementação: VER  Vértice **********/