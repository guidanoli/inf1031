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
*     1.1     gui   21/09/2018  definição das funções básicas
*
*  $ED Descrição do módulo
*     
*     WIP
*
***************************************************************************/

#include "LISTA.H"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um grafo */

typedef struct VER_tagVertice * VER_tppVertice;
typedef struct VER_tagAresta * VER_tppAresta;

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

         VER_CondRetVerticeNaoExiste ,
               /* O ponteiro para vértice é nulo */

         VER_CondRetArestaExiste ,
               /* Uma aresta com mesmo valor já existe */

         VER_CondRetArestaNaoExiste ,
               /* O ponteiro para a aresta é nulo */

         VER_CondRetErroEstrutura ,
               /* Erro na estrutura do vértice */    

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
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*     pValor        - ponteiro genérico para o valor do vértice procurado
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
             void   ( * ExcluirValor ) ( void * pDado ),
             void * Valor ) ;

/***********************************************************************
*
*  $FC Função: VER  &Destruir vértice
*
*  $ED Descrição da função
*     Destrói o vértice fornecido.
*
*  $EP Parâmetros
*     pVertice - ponteiro para o vértice
*
*  $FV Valor retornado
*     VER_CondRetOK                 - destruiu sem problemas
*     VER_CondRetVerticeNaoExiste   - ponteiro para vértice é nulo
*     VER_CondRetErroEstrutura      - algum erro na estrutura do vértice ocorreu
*
***********************************************************************/

   VER_tpCondRet VER_DestruirVertice( VER_tppVertice pVertice ) ;

/***********************************************************************
*
*  $FC Função: VER  &Obter referência para o valor contido no vértice
*
*  $ED Descrição da função
*     Obtem a referência para o valor contido no vértice
*
*  $EP Parâmetros
*     pVertice - ponteiro para o vértice cujo valor deseja-se obter
*
*  $FV Valor retornado
*     VER_CondRetOK                 - obteve sem problemas
*     VER_CondRetVerticeNaoExiste   - ponteiro para vértice é nulo
*     VER_CondRetErroEstrutura      - caso o valor seja nulo
                                      (Assertiva Estrutural)
*
***********************************************************************/

   VER_tpCondRet VER_ObterValor( VER_tppVertice pVertice ,
                                 void * pValor ) ;

/***********************************************************************
*
*  $FC Função: VER  &Inserir aresta
*
*  $ED Descrição da função
*
*     WIP
*
*  $EP Parâmetros
*     pVertice - ponteiro para vértice
*     pAresta  - ponteiro para aresta
*
*  $FV Valor retornado
*     VER_CondRetOK                 - inseriu sem problemas
*     VER_CondRetVerticeNaoExiste   - ponteiro para vértice é nulo
*     VER_CondRetErroEstrutura      - algum erro na estrutura do vértice ocorreu
*     VER_CondRetArestaExiste       - aresta já existe com o mesmo valor
*     VER_CondRetFaltouMemoria      - não foi possível alocar novas arestas
*
***********************************************************************/

   VER_tpCondRet VER_InserirAresta( VER_tppVertice pVertice ,
                                    void * pAresta ) ;


/***********************************************************************
*
*  $FC Função: VER  &Destruir aresta
*
*  $ED Descrição da função
*     Destrói uma aresta
*
*  $EP Parâmetros
*     pAresta  - ponteiro para aresta
*
*  $FV Valor retornado
*     VER_CondRetOK                 - destruiu sem problemas
*     VER_CondRetArestaNaoExiste    - o ponteiro para aresta é nulo
*     VER_CondRetErroEstrutura      - algum erro na estrutura do vértice ocorreu
*
***********************************************************************/

   VER_tpCondRet VER_DestruirAresta( VER_tppAresta pAresta ) ;

   // a implementar

/********** Fim do módulo de definição: VER  Vértice **********/