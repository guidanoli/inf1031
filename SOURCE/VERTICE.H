#if ! defined( VERTICE_ )
#define VERTICE_
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
*
*  $ED Descrição do módulo
*     
*     WIP
*
***************************************************************************/

#if defined( VERTICE_OWN )
   #define VERTICE_EXT
#else
   #define VERTICE_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um grafo */

typedef VER_tpVertice * VER_tppVertice;

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

         VER_CondRetOK ,
               /* Concluiu corretamente */

         VER_CondRetFaltouMemoria
               /* Faltou memória ao tentar criar um vértice */

   } VER_tpCondRet ;

/***********************************************************************
*
*  $FC Função: VER  &Criar vértice
*
*  $ED Descrição da função
*     Cria a estrutura de um vértice.
*     O tipo do valor armazenados não é espeficiado.
*
*  $EP Parâmetros
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado na estrutura.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para o vértice.
*     Este ponteiro será utilizado pelas funções que manipulem este vértice.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

   VER_tppVertice VER_CriarVertice(
             void   ( * ExcluirValor ) ( void * pDado ) ) ;

#undef VERTICE_EXT

/********** Fim do módulo de definição: VER  Vértice **********/

#else
#endif
