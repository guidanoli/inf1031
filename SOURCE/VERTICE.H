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
*     1.2     gui   25/09/2018  implementação das funções básicas de arestas
*     1.3  cai,nag  03/10/2018  assertivas de entrada e saída
*
*  $ED Descrição do módulo
*     
*     Este módulo implementa vértices e arestas genéricos.
*     Vértices possuem:
*        - ponteiro genérico que pode apontar para qualquer estrutura (void *)
*        - uma lista de arestas que partem do vértice (ponteiros VER_tppAresta)
*        - uma lista de arestas que chegam no vértice (ponteiros VER_tppAresta)
*        - um ponteiro para função que exclui o valor genérico
*
*      A função de liberação dos valores contidos no vértice e aresta deve
*        assegurar a liberação de todos os espaços referênciados pelo
*        ponteiro pValor.
*        Esta função é chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso não seja necessário desalocar o valor referenciado pelo
*        elemento, o ponteiro para a função de liberação poderá ser NULL .
*        Caso o elemento da lista seja a única âncora do valor referenciado,
*        esta função deve promover a destruição (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/

#include "LISTA.H"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um grafo */

/* ponteiro para estrutura de vértice */
typedef struct VER_tagVertice * VER_tppVertice;

/* ponteiro para estrutura de aresta */
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

         VER_CondRetValorFornecidoNulo ,
               /* O valor fornecido é nulo */

         VER_CondRetFuncaoNula ,
               /* O ponteiro para função é nulo */

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
*  $AE Assertivas de entrada
*     pValor é um ponteiro para o valor a ser armazenado no vértice.
*     ExcluirValor é uma função que exclui o tipo de dado referenciado
*     por pValor, CopiaValor é uma função que faz o ponteiro referenciado 
*     pelo primeiro argumento apontar para uma cópia do valor referenciado
*     pelo segundo argumento. ppVerticeParm deve ser NULL ou referenciar um
*     vértice existente.
*
*  $AS Assertivas de saída
*     Se ppVerticeParm não apontava para um vértice com erro de estrutura, ele
*     passa a referenciar um vértice, cujo valor é uma cópia daquele referenciado
*     por pValor. As listas de sucessores e antecessores desse novo vértice são
*     necessáriamente vazias.
*
*  $EP Parâmetros
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*     pValor        - ponteiro genérico para o valor do vértice procurado
*     CopiaValor   -  ponteiro para função que copia o valor de
*                     pB para *pA. Essencial para estruturas de dados
*                     que trabalham com ponteiros, como string.
*                     O espaço referenciado por *pA é inicialmente nulo
*                     e a função deve alocado dinamicamente este ponteiro
*                     com o tipo de estrutura de dados apropriado.
*     ppVerticeParm - endereço do ponteiro para vértice a ser criado
*
*  $FV Valor retornado
*     VER_CondRetOK
*     VER_CondRetFaltouMemoria
*     VER_CondRetFuncaoNula      - ponteiro para função CopiaValor é nulo
*     VER_CondRetErroEstrutura
*     VER_CondRetValorFornecidoNulo
*
***********************************************************************/

   VER_tpCondRet VER_CriarVertice(  void ( * ExcluirValor ) ( void * pDado ) ,
                                    void * pValor ,
                                    void (* CopiaValor ) ( void ** pA, void * pB) ,
                                    VER_tppVertice *ppVerticeParm ) ;

/***********************************************************************
*
*  $FC Função: VER  &Destruir vértice
*
*  $ED Descrição da função
*     Destrói o vértice fornecido.
*
*  $AE Assertivas de entrada
*     A função recebe um ponteiro para um vértice existente ou NULL.
*
*  $AS Assertivas de saída
*     Se o parâmetro aponta para um vértice sem erros de estrutura,
*     ele passa a ser NULL e o vértice para o qual ele apontava é
*     destruido junto com suas listas e todas as arestas que a referenciavam.
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

   VER_tpCondRet VER_DestruirVertice( VER_tppVertice *  pVertice ) ;

/***********************************************************************
*
*  $FC Função: VER  &Obter referência para o valor contido no vértice
*
*  $ED Descrição da função
*     Retorna pVertice->pValor.
*     Esta função não altera o vértice ou sua estrutura interna.
*
*  $AE Assertivas de entrada
*     A função recebe um ponteiro para um vértice existente ou NULL.
*
*  $AS Assertivas de saída
*     Se o vértice referenciado pelo parâmetro existe e não possui erros
*     de estrutura, a função retorna uma referência ao valor deste vértice.
*     Se o vértice referenciado não existe a função retorna NULL
*
*  $EP Parâmetros
*     pVertice - ponteiro para o vértice cujo valor deseja-se obter
*
*  $FV Valor retornado
*     Retorna o valor armazenado em vértice.
*     Se o vértice não existir ou se o valor for nulo,
*     será retornado NULL.
*
***********************************************************************/

   void * VER_ObterValor( VER_tppVertice pVertice ) ;

/***********************************************************************
*
*  $FC Função: VER  &Criar aresta
*
*  $ED Descrição da função
*     Cria uma aresta que sai do vértice pPartida e vai para
*     pDestino, com o valor pValorAresta. Recebe também
*     ponteiro para funções que tratam do tipo de dados
*     apontado por pValorAresta.
*
*  $AE Assertivas de entrada
*     Os ponteiros pPartida e pDestino são nulos ou apontam
*     para vértices existentes.
*     A função ComparaValor recebe duas referências a valores do
*     mesmo tipo referenciado por pValorAresta, retorna 0 se os valores 
*     referenciados forem iguais e um valor diferente de 0 caso contrario.
*     ExcluirValor é uma função que exclui o tipo de dado referenciado
*     por pValor, e todos os dados referenciados por ele.
*     CopiaValor é uma função que faz o ponteiro referenciado 
*     pelo primeiro argumento apontar para uma cópia do valor referenciado
*     pelo segundo argumento.
*
*  $AS Assertivas de saída
*     Se tanto pPartida quanto pDestino apontam para vértices válidos,
*     pValorAresta é diferente de NULL e as funções CopiaValor e ComparaValor
*     são válidas, é criada uma aresta cujo valor é uma cópia do referenciado
*     por pValorAresta. Esta nova aresta referencia os dois vértices passados.
*     São criados elementos na lista de sucessores do vértice de partida e na
*     lista de antecessores do vértice destino que referenciam a nova aresta criada.
*
*  $EP Parâmetros
*     pPartida -      ponteiro para vértice de partida da aresta
*     pDestino -      ponteiro para vértice de destino da aresta
*     pAresta  -      ponteiro para valor da aresta
*     ComparaValor -  ponteiro para função que compara valores do
*                     tipo de pValorA e pValorB.
*                     Retorno da função:
*                     >>> 0 caso pValorA == pValorB
*                     >>> diferente de 0 caso contrário
*     CopiaValor   -  ponteiro para função que copia o valor de
*                     pB para *pA. Essencial para estruturas de dados
*                     que trabalham com ponteiros, como string.
*                     O espaço referenciado por *pA é inicialmente nulo
*                     e a função deve alocado dinamicamente este ponteiro
*                     com o tipo de estrutura de dados apropriado.
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*     VER_CondRetOK                 - criou sem problemas
*     VER_CondRetVerticeNaoExiste   - ponteiro para vértice é nulo
*     VER_CondRetArestaExiste       - há uma aresta com mesmo valor saindo de
*                                     pPartida e indo para pDestino.
*                                     (Assertiva Estrutural)
*     VER_CondRetValorFornecidoNulo - pValorAresta é nulo
*     VER_CondRetErroEstrutura      - há algum erro na estrutura do vértice
*     VER_CondRetFaltouMemoria      - não foi possível alocar uma nova aresta
*     VER_CondRetFuncaoNula         - ponteiro para função CopiaValor ou
*                                     para função ComparaValor é nulo
*
***********************************************************************/

   VER_tpCondRet VER_CriarAresta(   VER_tppVertice pPartida ,
                                    VER_tppVertice pDestino ,
                                    void * pValorAresta ,
                                    int (* ComparaValor) ( void * pA, void * pB),
                                    void (* CopiaValor ) ( void ** pA, void * pB),
                                    void (* ExcluirValor) ( void* p)) ;


/***********************************************************************
*
*  $FC Função: VER  &Destruir aresta
*
*  $ED Descrição da função
*     Destrói uma aresta dado valor de aresta e ponteiros dos vértices
*     de destino e partida.
*
*  $AE Assertivas de entrada
*     Os ponteiros pPartida e pDestino são nulos ou apontam
*     para vértices existentes.
*     A função ComparaValor recebe duas referências a valores do
*     mesmo tipo referenciado por pValorAresta, retorna 0 se os valores 
*     referenciados forem iguais e um valor diferente de 0 caso contrario.
*
*  $AS Assertivas de saída
*     Se tanto pPartida quanto pDestino apontam para vértices válidos
*     e existir uma aresta cujo valor é igual ao valor referenciado por
*     pValor, parte do vértice referenciado por pPartida e chega no vértice
*     referenciado por pDestino, esta aresta será excluída, junto o seu valor
*     e todos os elementos de lista que a referenciavam.
*
*  $EP Parâmetros
*     pVerPartida  - ponteiro para vértice de partida da aresta
*     pVerDestino  - ponteiro para vértice de origem da aresta
*     pValor       - ponteiro para valor armazenado na aresta
*     ComparaValor - ponteiro para função que compara valores do
*                    tipo de pValorA e pValorB.
*                    Retorno da função:
*                    >>> 0 caso pValorA == pValorB
*                    >>> diferente de 0 caso contrário
*
*  $FV Valor retornado
*     VER_CondRetOK                 - destruiu sem problemas
*     VER_CondRetArestaNaoExiste    - o ponteiro para aresta é nulo
*     VER_CondRetErroEstrutura      - algum erro na estrutura do vértice ocorreu
*     VER_CondRetVerticeNaoExiste   - o vértice de partida da aresta não existe
*     VER_CondRetFuncaoNula         - ponteiro para função ComparaValor é nulo
*
***********************************************************************/

   VER_tpCondRet VER_DestruirAresta( VER_tppVertice pVerPartida,
                                     VER_tppVertice pVerDestino,
                                     void * pValor,
                                     int (* ComparaValor) ( void * pA, void * pB) ) ;

/***********************************************************************
*
*  $FC Função: VER  &Percorrer aresta
*
*  $ED Descrição da função
*     Percorre uma aresta partindo do vértice de partida fornecido
*     segundo um valor também fornecido, e armazena no ponteiro pDestino
*     o endereço do vértice de destino
*
*  $AE Assertivas de entrada
*	  A função deve receber um ponteiro do vértice de partida,
*	  o valor da aresta, um ponteiro que referencia o vertice destino,
*     que também pode ser nulo, um ponteiro para a função que
*     compara o valor de duas arestas e o sentido que irá andar
*     ( 0 para trás ou 1 para frente).
*  
*  $AS Assertivas de saída
*     Caso o ponteiro para vértice, valor e função não for nulo,
*     o Sentido for 0 ou 1, a função deverá alterar o ponteiro do vértice destino *pVerDestino
*     com o valor do Vértice destino caso o sentido seja 1, ou com o valor
*     do vértice de partida caso o valor seja 0 e retornar VER_CondRetOK.
*	   Caso contrário, deverá retornar a condição de retorno de acordo com o erro obtido.
*
*  $EP Parâmetros
*     pVerPartida  - ponteiro para o vértice de partida
*     pValor       - valor da aresta que deseja-se percorrer
*     pVerDestino  - ponteiro para o vértice de destino
*     ComparaValor - ponteiro para função que compara valores do
*                    tipo de pValorA e pValorB.
*                    Retorno da função:
*                    >>> 0 caso pValorA == pValorB
*                    >>> diferente de 0 caso contrário
*     Sentido      - 0 pra trás, 1 para frente
*
*  $FV Valor retornado
*     VER_CondRetOK                 - destruiu sem problemas
*     VER_CondRetValorFornecidoNulo - foi fornecido um valor nulo
*     VER_CondRetVerticeNaoExiste   - ponteiro para vértice é nulo
*     VER_CondRetArestaNaoExiste    - o ponteiro para aresta é nulo
*     VER_CondRetErroEstrutura      - algum erro na estrutura do vértice ocorreu
*     VER_CondRetFuncaoNula         - ponteiro para função ComparaValor é nulo
*
***********************************************************************/

   VER_tpCondRet VER_PercorrerAresta( VER_tppVertice pVerPartida,
                                      void * pValor,
                                      VER_tppVertice * pVerDestino,
                                      int (* ComparaValor) ( void * pA, void * pB),
                                      int Sentido ) ;

/********** Fim do módulo de definição: VER  Vértice **********/
