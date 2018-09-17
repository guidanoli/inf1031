/***************************************************************************
*
*  $MCD Módulo de implementação: ARE  Aresta
*
*  Arquivo gerado:              ARESTA.h
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
*  $ED Descrição do módulo
*     
*     WIP
*
***************************************************************************/

#include "VERTICE.H"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma aresta */

typedef struct ARE_tagAresta * ARE_tppAresta;

/***********************************************************************
*
*  $TC Tipo de dados: ARE Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da aresta
*
***********************************************************************/

   typedef enum {

         ARE_CondRetOK ,
               /* Concluiu corretamente */

         ARE_CondRetFaltouMemoria
               /* Faltou memória ao tentar criar uma aresta */

   } ARE_tpCondRet ;

/***********************************************************************
*
*  $FC Função: ARE  &Criar aresta
*
*  $ED Descrição da função
*     Cria a estrutura de uma aresta.
*     O tipo do valor armazenados não é espeficiado.
*
*  $EP Parâmetros
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pela aresta.
*                     Ver descrição do módulo.
*     pValor        - ponteiro genérico para o valor da aresta procurado
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a aresta.
*     Este ponteiro será utilizado pelas funções que manipulem este vértice.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

   ARE_tppAresta ARE_CriarAresta(
             void   ( * ExcluirValor ) ( void * pDado ),
             void * Valor ) ;

/***********************************************************************
*
*  $FC Função: ARE  &Destruir aresta
*
*  $ED Descrição da função
*     Destrói a aresta fornecida.
*     Se ocorrer algum erro durante a destruição, a aresta resultará
*     estruturalmente incorreto.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  $EP Parâmetros
*     pAresta - ponteiro para a aresta
*
***********************************************************************/

   void ARE_DestruirAresta( ARE_tppAresta pAresta ) ;

/***********************************************************************
*
*  $FC Função: ARE  &Obter referência para o valor contido na aresta
*
*  $ED Descrição da função
*     Obtem a referência para o valor contido na aresta
*
*  $EP Parâmetros
*     pAresta - ponteiro para a aresta cujo valor deseja-se obter
*
*  $FV Valor retornado
*     não NULL - se a aresta existe
*     NULL     - se o ponteiro para a aresta for nulo
*                Pode retornar NULL se o valor inserido na aresta for NULL.
*
***********************************************************************/

   void * ARE_ObterValor( ARE_tppAresta pAresta ) ;

/********** Fim do módulo de definição: ARE  Aresta **********/