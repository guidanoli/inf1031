/***************************************************************************
*
*  $MCD Módulo de definição: GRF  Grafo Dirigido
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
*     1.1     gui   21/09/2018  novo modelo de grafo dirigido
*     1.2     gui   25/09/2018  implementação das funções básicas de vértices e arestas
*
*  $ED Descrição do módulo
*     
*     WIP
*
***************************************************************************/

#include "LISTA.H"
#include "VERTICE.H"

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

         GRF_CondRetGrafoVazio ,
               /* Grafo vazio */

         GRF_CondRetVerticeExiste ,
               /* Vértice com dado valor existente */

         GRF_CondRetVerticeNaoExiste ,
               /* Vértice com dado valor não existe*/

         GRF_CondRetValorFornecidoNulo ,
               /* Valor fornecido é nulo */

         GRF_CondRetArestaNaoExiste ,
               /* Aresta inexistente */

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
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para o grafo.
*     Este ponteiro será utilizado pelas funções que manipulem este grafo.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

   GRF_tppGrafo GRF_CriarGrafo() ;

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
*  $FV Valor retornado
*     GRF_CondRetOK              - destruiu sem problemas
*     GRF_CondRetGrafoNaoExiste  - o ponteiro para o grafo é nulo
*
***********************************************************************/

   GRF_tpCondRet GRF_DestruirGrafo( GRF_tppGrafo pGrafo ) ;


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
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo vértice
*                     a ser excluído.
*                     Ver descrição do módulo.  
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
                                     void * pValor ,
                                     void (* CopiaValor ) ( void ** pA, void * pB) ,
                                     void (* ExcluirValor) ( void * pDado ) ) ;
   
/***********************************************************************
*
*  $FC Função: GRF  &Inserir aresta
*
*  $ED Descrição da função
*     Insere uma aresta com valor fornecido ValorAresta que sai do
*     vértice A e vai para o vértice B.
*
*  $EP Parâmetros
*     pGrafo - ponteiro para o grafo
*     pValorA e pValorB - valores dos vértices
*     ValorAresta - valor da arestas
*     ComparaValor - ponteiro para função que compara valores do
*                    tipo de pValorA e pValorB.
*                    Retorno da função:
*                    >>> 0 caso pValorA == pValorB
*                    >>> diferente de 0 caso contrário
*     CopiaValor   - ponteiro para função que copia o valor de
*                    pB para *pA. Essencial para estruturas de dados
*                    que trabalham com ponteiros, como string e structs.
*                    O espaço referenciado por pA é inicialmente nulo
*                    e deve ser inicalmente alocado dinamicamente
*                    com o tipo de estrutura de dados apropriado.
*                    >>> void
*
*  $FV Valor retornado
*     GRF_CondRetOK                 - inseriu sem problemas
*     GRF_CondRetGrafoNaoExiste     - ponteiro para grafo é nulo
*     GRF_CondRetErroEstrutura      - algum erro na estrutura do grafo ocorreu
*     GRF_CondRetVerticeNaoExiste   - um dos valores fornecidos não existem
*     GRF_CondRetFaltouMemoria      - não foi possível alocar espaço na memória
*
***********************************************************************/

   GRF_tpCondRet GRF_InserirAresta( GRF_tppGrafo pGrafo ,
                                    void * pValorA,
                                    void * pValorB,
                                    void * ValorAresta,
                                    int (* ComparaValor) ( void * pA, void * pB),
                                    void (* CopiaValor) (void ** pA, void * pB)) ;

/***********************************************************************
*
*  $FC Função: GRF  &Caminhar
*
*  $ED Descrição da função
*     Caminha por um grafo em um determinado sentido
*
*  $EP Parâmetros
*     pGrafo - ponteiro para o grafo
*     pValor - valor da aresta que deseja-se caminhar
*
*  $FV Valor retornado
*     GRF_CondRetOK                 - caminhou sem problemas
*     GRF_CondRetGrafoNaoExiste
*     GRF_CondRetErroEstrutura
*     GRF_CondRetGrafoVazio         - não há vertices no grafo
*     GRF_CondRetValorFornecidoNulo - pValor é nulo
*     GRF_CondRetArestaNaoExiste    - não foi encontrada a aresta com
*                                     o valor pValor
*
***********************************************************************/

   GRF_tpCondRet GRF_Caminhar( GRF_tppGrafo pGrafo ,
                               void * pValor,
                               int Sentido ) ;

/********** Fim do módulo de definição: GRF  Grafo **********/