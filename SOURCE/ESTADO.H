/***************************************************************************
*
*  $MCD Módulo de implementação: VER Vértice
*
*  Arquivo gerado:              VERTICE.h
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
*     2       gui   17/09/2018  funções básicas do módulo
*
*  $ED Descrição do módulo
*     
*     WIP
*
***************************************************************************/

#include "VERTICE.H"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um grafo */

typedef EST_tpEstado * EST_tppEstado;

/***********************************************************************
*
*  $TC Tipo de dados: VER Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do vértice
*
***********************************************************************/

   typedef enum {

         EST_CondRetOK ,
               /* Concluiu corretamente */

         EST_CondRetErroEstrutura ,
               /* Erro na estrutura do estado */    

         EST_CondRetFaltouMemoria
               /* Faltou memória ao tentar criar um estado */

   } EST_tpCondRet ;

/***********************************************************************
*
*  $FC Função: EST  &Criar estado
*
*  $ED Descrição da função
*     Cria a estrutura de um estado.
*     O tipo do valor armazenados não é espeficiado.
*
*  $EP Parâmetros
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo estado
*                     Ver descrição do módulo.
*     pValor        - ponteiro genérico para o valor do estado procurado
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para o estado.
*     Este ponteiro será utilizado pelas funções que manipulem este estado.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

   EST_tppEstado EST_CriarEstado(
             void   ( * ExcluirValor ) ( void * pDado ),
             void * Valor,
             char tipo ) ;

/***********************************************************************
*
*  $FC Função: EST  &Destruir estado
*
*  $ED Descrição da função
*     Destrói o estado fornecido.
*     O parâmetro ponteiro para o estado não é modificado.
*     Se ocorrer algum erro durante a destruição, o estado resultará
*     estruturalmente incorreto.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  $EP Parâmetros
*     pEstado - ponteiro para o estado
*
***********************************************************************/

   void EST_DestruirEstado( EST_tppEstado pEstado ) ;

/***********************************************************************
*
*  $FC Função: EST  &Obter referência para o valor contido no vértice
*
*  $ED Descrição da função
*     Obtem a referência para o valor contido no vértice
*
*  $EP Parâmetros
*     pVertice - ponteiro para o vértice cujo valor deseja-se obter
*
*  $FV Valor retornado
*     não NULL - se o vértice existe
*     NULL     - se o ponteiro para o vértice for nulo
*                Pode retornar NULL se o valor inserido no vértice for NULL.
*
***********************************************************************/

   void * VER_ObterValor( VER_tppVertice pVertice ) ;

/********** Fim do módulo de definição: VER  Vértice **********/
