/***************************************************************************
*
*  $MCD Módulo de definição: GRF  Grafo
*
*  Arquivo gerado:              GRAFO.h
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
*     1.1     gui   14/09/2018  funções de acesso básicas
*
*  $ED Descrição do módulo
*     
*     WIP
*
***************************************************************************/

#include "LISTA.H"
#include "VERTICE.H"
#include "ARESTA.H"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um grafo */

typedef struct GRF_tagGrafo * GRF_tppGrafo ;

/***********************************************************************
*
*  $TC Tipo de dados: GRF Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do grafo
*
***********************************************************************/

   typedef enum {

         GRF_CondRetOK ,
               /* Concluiu corretamente */

         GRF_CondRetGrafoNaoExiste ,
               /* Grafo inexistente */

         GRF_CondRetVerticeExiste ,
               /* Vértice com dado valor existente */

         GRF_CondRetVerticeNaoExiste ,
               /* Vértice com dado valor não existe*/

         GRF_CondRetErroEstrutura ,
               /* Erro na estrutura do grafo */

         GRF_CondRetFaltouMemoria
               /* Faltou memória ao tentar criar um elemento do grafo */

   } GRF_tpCondRet ;

/***********************************************************************
*
*  $FC Função: GRF  &Criar grafo
*
*  $ED Descrição da função
*     Cria a estrutura de um grafo sem vértices ou arestas.
*     O tipo dos valores armazenados não é espeficiado.
*
*  $EP Parâmetros
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para o grafo.
*     Este ponteiro será utilizado pelas funções que manipulem este grafo.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

   GRF_tppGrafo GRF_CriarGrafo(
             void   ( * ExcluirValor ) ( void * pDado ) ) ;

/***********************************************************************
*
*  $FC Função: GRF  &Destruir grafo
*
*  $ED Descrição da função
*     Destrói o grafo fornecido.
*     Se ocorrer algum erro durante a destruição, a grafo resultará
*     estruturalmente incorreto.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  $EP Parâmetros
*     pGrafo - ponteiro para o grafo
*
***********************************************************************/

   void GRF_DestruirGrafo( GRF_tppGrafo pGrafo ) ;


/***********************************************************************
*
*  $FC Função: GRF  &Inserir vértice
*
*  $ED Descrição da função
*     Insere um novo vértice ao grafo fornecido.
*     Considera que não haverá mais de um vértice com o mesmo
*     valor no mesmo grafo.
*
*  $EP Parâmetros
*     pGrafo - ponteiro para o grafo
*     pValor - valores do novo vértice
*
*  $FV Valor retornado
*     GRF_CondRetOK              - inseriu sem problemas
*     GRF_CondRetGrafoNaoExiste  - o ponteiro para o grafo é nulo
*     GRF_CondRetVerticeExiste   - já existe um vértice no grafo tal valor
*     GRF_CondRetErroEstrutura   - algum erro na estrutura do grafo ocorreu 
*     GRF_CondRetFaltouMemoria   - não foi possível alocar um novo vértice
*
***********************************************************************/

   GRF_tpCondRet GRF_InserirVertice( GRF_tppGrafo pGrafo ,
                                     void * pValor );
   
/***********************************************************************
*
*  $FC Função: GRF  &Inserir aresta
*
*  $ED Descrição da função
*
*     WIP
*
*  $EP Parâmetros
*     pGrafo - ponteiro para o grafo
*     pValorA e pValorB - valores dos vértices
*     ValorAresta - valor da arestas
*
*  $FV Valor retornado
*     GRF_CondRetOK                 - inseriu sem problemas
*     GRF_CondRetGrafoNaoExiste     - ponteiro para grafo é nulo
*     GRF_CondRetErroEstrutura      - algum erro na estrutura do grafo ocorreu
*     GRF_CondRetVerticeNaoExiste   - algum dos valores fornecidos não pertence
*                                     a nenhum dos vértices esperados
*     GRF_CondRetFaltouMemoria      - não foi possível alocar novas arestas
*
***********************************************************************/

   GRF_tpCondRet GRF_InserirAresta( GRF_tppGrafo pGrafo ,
                                    void * pValorA,
                                    void * pValorB,
                                    void * ValorAresta);

/********** Fim do módulo de definição: GRF  Grafo **********/