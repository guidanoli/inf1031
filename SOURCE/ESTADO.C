/***************************************************************************
*  $MCI Módulo de implementação: EST Estado
*
*  Arquivo gerado:              ESTADO.c
*  Letras identificadoras:      EST
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

#define ESTADO_OWN
#include "ESTADO.h"
#undef ESTADO_OWN

/***********************************************************************
*
*  $TC Tipo de dados: EST Estado
*
*
***********************************************************************/

   typedef struct EST_tagEstado {

          VER_tppVertice Valor ;
               /* Ponteiro para a estrutura Vértice */

          char tipo;
               /* Flag indicando o tipo do Estado */

   } EST_tpEstado ;

/***** Protótipos das funções encapuladas no módulo *****/

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: VER  &Criar vértice
*  ****/

   // a fazer ainda


/*****  Código das funções encapsuladas no módulo  *****/

/********** Fim do módulo de implementação: VER  Vértice **********/