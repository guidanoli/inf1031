/***************************************************************************
*  $MCI Módulo de implementação: ARE  Aresta
*
*  Arquivo gerado:              ARESTA.c
*  Letras identificadoras:      ARE
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

#include "ARESTA.h"

/***********************************************************************
*
*  $TC Tipo de dados: ARE Aresta
*
*
***********************************************************************/

   typedef struct ARE_tagAresta {

          void * Valor;
               /* Ponteiro genérico para o valor armazenado na aresta */

          VER_tppVertice pVertice;
               /* Ponteiro para o vértice para o qual a aresta aponta */

          void ( * ExcluirValor ) ( void * pDado ) ;
               /* Ponteiro para a função de destruição do valor contido em um elemento */

   } ARE_tpAresta ;

/***** Protótipos das funções encapuladas no módulo *****/

/*****  Código das funções exportadas pelo módulo  *****/

/*****  Código das funções encapsuladas no módulo  *****/

/********** Fim do módulo de implementação: ARE  Aresta **********/