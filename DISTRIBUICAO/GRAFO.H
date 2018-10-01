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

         GRF_CondRetArestaExiste ,
               /* Aresta com mesmo valor, origem e destino já existe */

         GRF_CondRetArestaNaoExiste ,
               /* Aresta inexistente */

         GRF_CondRetFuncaoNula ,
               /* O ponteiro para função é nulo */

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
*     ComparaValorAre   - Ponteiro para função de comparação de valores de aresta
*                         Retorna 0 caso *pa == *pB, e diferente de 0 caso contrário
*     ComparaValorVer   - Ponteiro para função de comparação de valores de vértice
*                         Retorna 0 caso *pa == *pB, e diferente de 0 caso contrário
*     CopiaValorAre     - Ponteiro para função que copia valores de aresta
*                         Copia o valor de pb para *pA
*     CopiaValorVer     - Ponteiro para função que copia valores de vértice
*                         Copia o valor de pb para *pA
*     ppGrafoParam      - Endereço para ponteiro de grafo que será criado
*                         Caso não for possível criar o grafo, *ppGrafoParam = NULL
*
*  $FV Valor retornado
*     GRF_CondRetOK              - criou grafo sem problemas
*     GRF_CondRetFuncaoNula        - ponteiro para alguma das funções é nulo
*     GRF_CondRetFaltouMemoria   - não foi possível alocar memória para grafo
*
***********************************************************************/

   GRF_tpCondRet GRF_CriarGrafo( int (* ComparaValorAre ) ( void * pA, void * pB) ,
                                 int (* ComparaValorVer ) ( void * pA, void * pB) ,
                                 void (* CopiaValorAre ) ( void ** pA, void * pB) ,
                                 void (* CopiaValorVer ) ( void ** pA, void * pB) ,
                                 void (* ExcluirValorVer ) ( void * pDado ) ,
                                 void (* ExcluirValorAre ) ( void * pDado ) ,
                                 GRF_tppGrafo * ppGrafoParam ) ;

/***********************************************************************
*
*  $FC Função: GRF  &Destruir grafo
*
*  $ED Descrição da função
*     Destrói o grafo fornecido.
*
*  $EP Parâmetros
*     ppGrafoParam - endereço do ponteiro para o grafo a ser destruido
*
*  $FV Valor retornado
*     GRF_CondRetOK              - destruiu sem problemas
*     GRF_CondRetGrafoNaoExiste  - o ponteiro para o grafo é nulo
*
***********************************************************************/

   GRF_tpCondRet GRF_DestruirGrafo( GRF_tppGrafo * ppGrafoParam ) ;


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
*     GRF_CondRetFuncaoNula        - o ponteiro para função de cópia é nula
*     GRF_CondRetErroEstrutura   - algum erro na estrutura do grafo ocorreu 
*     GRF_CondRetFaltouMemoria   - não foi possível alocar um novo vértice
*
***********************************************************************/

   GRF_tpCondRet GRF_InserirVertice( GRF_tppGrafo pGrafo ,
                                     void * pValor ) ;
   
/***********************************************************************
*
*  $FC Função: GRF  &Remover vértice
*
*  $ED Descrição da função
*     Remove um vértice ao grafo fornecido.
*     Se não há tal vértice no grafo, nada será feito.
*
*  $EP Parâmetros
*     pGrafo - ponteiro para o grafo
*     pValor - valores do novo vértice 
*
*  $FV Valor retornado
*     GRF_CondRetOK                 - removeu sem problemas
*     GRF_CondRetGrafoNaoExiste     - o ponteiro para grafo é nulo
*     GRF_CondRetGrafoVazio         - o grafo não possui vértices
*     GRF_CondRetValorFornecidoNulo - o ponteiro para valor é nulo
*     GRF_CondRetErroEstrutura
*     GRF_CondRetVerticeNaoExiste   - não foi encontrado tal vértice
*
***********************************************************************/

   GRF_tpCondRet GRF_RemoverVertice( GRF_tppGrafo pGrafo ,
                                     void * pValor ) ;

/***********************************************************************
*
*  $FC Função: GRF  &Inserir aresta
*
*  $ED Descrição da função
*     Insere uma aresta com valor fornecido ValorAresta que sai do
*     vértice *pValorPartida e vai para o vértice *pValorDestino.
*
*  $EP Parâmetros
*     pGrafo            - ponteiro para o grafo
*     pValorPartida     - valor do vértice de partida
*     pValorDestino     - valor do vértice de destino
*     ValorAresta       - valor da aresta a ser inserida
*
*  $FV Valor retornado
*     GRF_CondRetOK                 - inseriu sem problemas
*     GRF_CondRetGrafoNaoExiste     - ponteiro para grafo é nulo
*     GRF_CondRetValorFornecidoNulo - valor da aresta nulo
*     GRF_CondRetArestaExiste       - já existe uma aresta com mesma origem,
*                                     destino e valor no grafo
*     GRF_CondRetErroEstrutura      - algum erro na estrutura do grafo ocorreu
*     GRF_CondRetVerticeNaoExiste   - algum dos valores vértices fornecidos não existe
*     GRF_CondRetFaltouMemoria      - não foi possível alocar espaço na memória
*
***********************************************************************/

   GRF_tpCondRet GRF_InserirAresta( GRF_tppGrafo pGrafo ,
                                    void * pValorPartida,
                                    void * pValorDestino,
                                    void * ValorAresta ) ;

/***********************************************************************
*
*  $FC Função: GRF  &Remover aresta
*
*  $ED Descrição da função
*     Remove uma aresta com valor fornecido ValorAresta que sai do
*     vértice *pValorPartida e vai para o vértice *pValorDestino.
*
*  $EP Parâmetros
*     pGrafo            - ponteiro para o grafo
*     pValorPartida     - valor do vértice de partida
*     pValorDestino     - valor do vértice de destino
*     ValorAresta       - valor da aresta a ser inserida
*
*  $FV Valor retornado
*     GRF_CondRetOK                 - inseriu sem problemas
*     GRF_CondRetGrafoNaoExiste     - ponteiro para grafo é nulo
*     GRF_CondRetGrafoVazio
*     GRF_CondRetValorFornecidoNulo - valor da aresta ou de vértice nulo
*     GRF_CondRetFuncaoNula         - função de comparação nula
*     GRF_CondRetArestaNaoExiste    - não foi encontrada tal aresta
*     GRF_CondRetVerticeNaoExiste   - algum dos valores vértices fornecidos não existe
*     GRF_CondRetErroEstrutura      - algum erro na estrutura do grafo ocorreu
*     GRF_CondRetFaltouMemoria      - não foi possível alocar espaço na memória
*
***********************************************************************/

   GRF_tpCondRet GRF_RemoverAresta( GRF_tppGrafo pGrafo,
                                    void* pValorVerOrig,
                                    void* pValorVerDest,
                                    void* pValorAre) ;

/***********************************************************************
*
*  $FC Função: GRF  &Caminhar por grafo
*
*  $ED Descrição da função
*     Caminha do vértice corrente por uma aresta em um determinado sentido.
*     Se nestas variáveis existir mais de uma aresta, será caminhada aquela
*     que foi inserida primeiro no grafo.
*
*  $EP Parâmetros
*     pGrafo  - ponteiro para o grafo
*     pValor  - valor da aresta que deseja-se caminhar
*     Sentido - sentido do caminhamento
*               >> 1 para frente
*               >> 0 para trás
*
*  $FV Valor retornado
*     GRF_CondRetOK                 - caminhou sem problemas
*     GRF_CondRetGrafoNaoExiste
*     GRF_CondRetErroEstrutura
*     GRF_CondRetGrafoVazio         - não há vertices no grafo
*     GRF_CondRetValorFornecidoNulo - pValor é nulo
*     GRF_CondRetFuncaoNula         - função ComparaValorAre é nula
*     GRF_CondRetArestaNaoExiste    - não foi encontrada a aresta com
*                                     o valor pValor
*
***********************************************************************/

   GRF_tpCondRet GRF_CaminharGrafo( GRF_tppGrafo pGrafo ,
                                    void * pValor,
                                    int Sentido ) ;

/********** Fim do módulo de definição: GRF  Grafo **********/