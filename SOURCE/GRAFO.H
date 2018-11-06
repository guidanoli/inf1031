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
*     Versão  Autor      Data     Observações
*     1       gui     11/09/2018  início do desenvolvimento
*     1.1     gui     21/09/2018  novo modelo de grafo dirigido
*     1.2     gui     25/09/2018  implementação das funções básicas de vértices e arestas
*     1.3     gui     02/10/2018  implementação da lista de origens e funções auxiliares
*     1.4   gui,cai   03/10/2018  assertivas de entrada e saída
*     1.5     gui     12/10/2018  exibir grafo
*     1.6     gui     27/10/2018  contadores de vértices e origens
*     1.7     gui     05/11/2018  restrições de aresta
*
*  $ED Descrição do módulo
*     
*     Este módulo implementa um conjunto simples de funções para criar e
*     explorar um grafo dirigido.
*     O grafo possui uma cabeça que contém uma referência para uma lista de vértices,
*     um lista de origens e um vértice corrente.
*     O nó corrente será nulo se e somente se o grafo estiver vazio.
*     
*     As funções específicas para o valor armazenado em arestas e vertices
*     ou "hotspots" são os seguintes:
*
*     ComparaValorAre   - Ponteiro para função de comparação de valores de aresta
*                         Retorna 0 caso forem iguais, e diferente de 0 caso contrário
*
*     ComparaValorVer   - Ponteiro para função de comparação de valores de vértice
*                         Retorna 0 caso forem iguais, e diferente de 0 caso contrário
*
*     CopiaValorAre     - Ponteiro para função que copia valores de aresta
*                         Copia o valor de pb para *pA
*
*     CopiaValorVer     - Ponteiro para função que copia valores de vértice
*                         Copia o valor de pb para *pA
*
*     ExcluirValorVer   - ponteiro para a função que processa a
*                         exclusão do valor referenciado pelo vértice
*                         Ver descrição do módulo.
*
*     ExcluirValorAre   - ponteiro para a função que processa a
*                         exclusão do valor referenciado pela aresta
*                         Ver descrição do módulo.
*
*     ConcatenaValorVer - Ponteiro para função que concatena o valor de pB
*                         no final da string pA
*                         RETORNA:
*                         >> 0 caso a concatenação ocorreu com sucesso
*                         >> 1 caso *pA não tenha mais espaço
*
*     PercorreAresta    - Ponteiro para função que define a prioridade de
*                         se percorrer uma determinada aresta. Quanto maior
*                         o inteiro retornado, maior a prioridade. Será per-
*                         corrida a aresta de maior prioridade dado um vértice
*                         e um sentido. Caso duas arestas tenham a mesma prioridade,
*                         será escolhida a primeiro a ser identificada.
*                         RECEBE:
*                         pA -- valor armazenado numa aresta
*                         pB -- entrada do usuário
*                         RETORNA:
*                         >> 0 caso a aresta não deve ser percorrida
*                         >> maior que 0, caso deve-se percorrê-la
*
*     Restricao         - Restrição de arestas que define a cardinalidade
*                         de arestas com mesmo valor para mesmo vértice
*                         de Partida e de Destino.
*                         VALORES POSSÍVEIS:
*                         >> VER_RestAreSemRestricao - Podem haver duas arestas
*                         com mesmo rótulo, no mesmo sentido entre os mesmos vértices.
*                         >> VER_RestAreSaidaUnica - Não podem haver duas arestas
*                         com mesmo rótulo, saindo do mesmo vértice.
*                         >> VER_RestAreEntradaUnica - Não podem haver duas arestas
*                         com mesmo rótulo, entrando no mesmo vértice.
*                         >> VER_RestAreSaidaEChegada - Não podem haver duas arestas
*                         com mesmo rótulo, saindo de um mesmo vértice, ou entrando
*                         no mesmo vértice.
*                         >> GRF_RestAreArestaUnica - Não podem haver duas arestas
*                         com mesmo rótulo, saindo de um mesmo vértice, e entrando
*                         no mesmo vértice.
*
***************************************************************************/

/* Limite da string de exibição de grafo */

#define GRF_STR_BUFFER_SIZE 500

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

         GRF_CondRetUnicaOrigem ,
               /* Só há uma origem e mais de um vértice */

         GRF_CondRetFuncaoNula ,
               /* O ponteiro para função é nulo */

         GRF_CondRetErroEstrutura ,
               /* Erro na estrutura do grafo */

         GRF_CondRetFaltouMemoria
               /* Faltou memória ao tentar criar um elemento do grafo */

   } GRF_tpCondRet ;

/***********************************************************************
*
*  $TC Tipo de dados: GRF Restrições de Arestas
*
*  $ED Descrição do tipo
*     Restrições no modelo de interconexões entre vértices quanto
*     à cardinalidade das arestas quanto ao seu sentido e valor.
*
***********************************************************************/

   typedef enum {

      GRF_RestAreSemRestricao ,
         /* Não há restrições */

      GRF_RestAreSaidaUnica ,
         /* De um estado sai no máximo uma aresta com mesmo valor */

      GRF_RestAreEntradaUnica ,
         /* De um estado chega no máximo uma aresta com mesmo valor */

      GRF_RestAreSaidaEChegada ,
         /* Não restringe que a aresta trate dos mesmos vértices
            É a conjunção das restrições de entrada e saída únicas */

      GRF_RestAreArestaUnica ,
         /* Considera que a aresta é única quando parte de um estado X,
            vai para outro estado Y (X pode ser igual a Y), e tem um 
            rótulo R. Esta tríade identifica a aresta. */

   } GRF_tpRestAre ;

/***********************************************************************
*
*  $FC Função: GRF  &Criar grafo
*
*  $ED Descrição da função
*     Cria a estrutura de um grafo sem vértices ou arestas.
*     O tipo dos valores armazenados não é espeficiado.
*
*  $AE Assertivas de entrada
*	  A função deverá receber um ponteiro para a função que compara o valor de duas
*	  arestas, um ponteiro para a função que compara o valor de dois vertices,
*     um ponteiro para a função que copia o valor do vértice do
*	  segundo parametro para o primeiro parametro, um ponteiro para a função que copia
*     o valor da aresta do segundo parametro para o primeiro parametro, um ponteiro para 
*     a função que exclui o valor de um vértice, um ponteiro para a função que exclui o valor
*     de uma aresta e um ponteiro que referencia o grafo, e a condição de restrição das arestas
*     do grafo, que, por padrão, será VER_RestAreSemRestricao.
*
*  $AS Assertivas de saída
*     Armazena todos os paramentros de função na cabeça do grafo, zera os contadores de vértice de origem,
*     aloca o struct de grafo e armazena o endereço para o grafo alocado no ponteiro ppGrafoParam, retornando
*     GRF_CondRetOK.
*
*  $EP Parâmetros
*     ComparaValorAre   - Ver descrição do módulo
*     ComparaValorVer   - Ver descrição do módulo
*     CopiaValorAre     - Ver descrição do módulo
*     CopiaValorVer     - Ver descrição do módulo
*     ExcluirValorVer   - Ver descrição do módulo
*     ExcluirValorAre   - Ver descrição do módulo
*     ConcatenaValorVer - Ver descrição do módulo
*     RestricaoArestas  - Ver descrição do módulo
*     ppGrafoParam      - Endereço para ponteiro de grafo que será criado
*                         Caso não for possível criar o grafo, *ppGrafoParam = NULL
*
*  $FV Valor retornado
*     GRF_CondRetOK              - criou grafo sem problemas
*     GRF_CondRetFuncaoNula      - ponteiro para alguma das funções é nulo
*     GRF_CondRetFaltouMemoria   - não foi possível alocar memória para grafo
*
***********************************************************************/

   GRF_tpCondRet GRF_CriarGrafo( GRF_tpRestAre Restricao ,
                                 int ( *ComparaValorAre ) ( void * pA, void * pB) ,
                                 int ( *ComparaValorVer ) ( void * pA, void * pB) ,
                                 void ( *CopiaValorAre ) ( void ** pA, void * pB) ,
                                 void ( *CopiaValorVer ) ( void ** pA, void * pB) ,
                                 void ( *ExcluirValorVer ) ( void * pDado ) ,
                                 void ( *ExcluirValorAre ) ( void * pDado ) ,
                                 int ( *ConcatenaValorVer) ( char * pA, void * pB ) ,
                                 int ( *PercorreAresta ) ( void * pA , void * pB ) ,
                                 GRF_tppGrafo * ppGrafoParam ) ;

/***********************************************************************
*
*  $FC Função: GRF  &Destruir grafo
*
*  $ED Descrição da função
*     Destrói o grafo fornecido.
*
*  $AE Assertivas de entrada
*	  A função recebe um endereço de ponteiro existente que aponta
*    para um grafo ou é NULO.
*
*  $AS Assertivas de saída
*	  Caso o grafo exista, destrói as listas de origem e de vértices,
*    e libera o grafo fornecido. Anula o valor de *ppGrafoParam e
*    retorna GRF_CondRetOK. Caso o grafo não exista, retorna
*    GRF_CondRetGrafoNaoExiste.
*
*  $EP Parâmetros
*     ppGrafoParam - endereço do ponteiro para o grafo a ser destruido.
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
*  $AE Assertivas de entrada
*     Recebe um ponteiro para grafo ou NULO.
*     Recebe um ponteiro para o valor a ser armazenado no
*     vértice, não podendo ser nulo, e do tipo padrão
*     de estrutura de dados para vértices do grafo fornecido.
*
*  $AS Assertivas de saída
*     Se o ponteiro para grafo não for nulo, nem tiver algum
*     erro de estrutura, nem ter função interna nula, nem o valor
*     fornecido for nulo, nem existir outro vértice com o mesmo valor,
*     e houver espaço para ser alocado na memória, então a função
*     insere um vértice na lista de vértices do grafo e retorna GRF_CondRetOK .
*     Caso contrário, a função retornará a condição de retorno
*     apropriada para o erro e o vértice não será inserido.
*     Se o grafo antes da execução da função for vazio, este
*     vértice será inserido também na lista de origens.
*     O valor armazenado no vértice inserido será pValor,
*     e serão alocadas duas listas na estrutura do vértice:
*     lista de sucessores (das arestas que saem do vértice) e
*     lista de antecessores (das arestas que apontam para o vértice).
*     Além disso, a função de exclusão referenciada no vértice
*     será a mesma referenciada pela cabeça do grafo em ExcluiValorVer.
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
*  $AE Assertivas de entrada
*     Recebe um ponteiro para grafo ou NULO.
*     Recebe um ponteiro para o valor armazenado no
*     vértice a ser removido, que deve apontar para
*     uma estrutura de dado do tipo padrão de vértice do grafo.
*
*  $AS Assertivas de saída
*     Se o ponteiro para grafo não for nulo, nem tiver algum
*     erro de estrutura, nem o valor fornecido for nulo,
*     nem algum dos vértices forem inválidos, nem o vértice
*     for a única origem de um grafo com mais de um vértice,
*     nem faltar memória, nem o grafo for vazio,
*     a função remove o vértice do grafo, excluindo além do
*     próprio vértice, todas as arestas conectadas a ele,
*     elementos de listas dos vértices que estas arestas conectem
*     que referenciem estas arestas, e, caso este vértice for uma origem,
*     o elemento que aponta pro vértice da lista de origem.
*     A função retorna GRF_CondRetOK se foi removido o vértice sem
*     problemas, e a condição de retorno apropriada caso contrário.
*     Caso o vértice tenha sido removido com sucesso, o vértice corrente
*     é nulo (caso o grafo tenha ficado vazio) ou aponta para a primeira
*     origem definida.
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
*     GRF_CondRetUnicaOrigem        - o grafo possui mais de um vértice
*                                     e uma única origem
*     GRF_CondRetFaltouMemoria
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
*  $AE Assertivas de entrada
*     Recebe um ponteiro para grafo ou NULO.
*     Recebe dois ponteiros para estruturas de dados correspondente
*     ao tipo padrão de vértice do grafo fornecido,
*     que correspondem ao valor do vértice de partida, de origem,
*     e mais outro ponteiro do valor de aresta, que aponta para uma
*     estrutura de dados do tipo padrão de aresta do grafo.
*
*  $AS Assertivas de saída
*     Se o grafo não for nulo, os valores foram de tipos válidos
*     e não-nulos, não houver já uma aresta com os mesmos parâmetros, os
*     vértices com os valores existirem, não faltar memória,
*     as funções internas forem válidas, a função inserirá no grafo
*     a aresta saindo do vértice referenciado por pValorPartida para
*     o vértice referenciado por  pValorDestino, armazenando nesta
*     nova aresta o valor apontado por ValorAresta.
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
*     GRF_CondRetFuncaoNula         - algum dos ponteiros para função é nulo
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
*  $AE Assertivas de entrada
*     Recebe um ponteiro para grafo ou NULO.
*     Recebe dois ponteiros para estruturas de dados correspondente
*     ao tipo padrão de vértice do grafo fornecido,
*     que correspondem ao valor do vértice de partida, de origem,
*     e mais outro ponteiro do valor de aresta, que aponta para uma
*     estrutura de dados do tipo padrão de aresta do grafo.
*
*  $AS Assertivas de saída
*     Se o grafo, a aresta e os vértices existirem, as funções
*     internas não forem nulas, e não houver erro de estrutura,
*     a função removerá a aresta do grafo, liberando o valor armazenado
*     na aresta, e removendo o elemento que referencia a aresta
*     presente na lista de arestas dos vértices que a aresta
*     conecta, e retorna GRF_CondRetOK. Caso contrário,
*     retornará a condição de retorno condizente com o erro
*     e não será alterada a estrutura do grafo.
*
*  $EP Parâmetros
*     pGrafo            - ponteiro para o grafo
*     pValorVerOrig     - valor do vértice de partida
*     pValorVerDest     - valor do vértice de destino
*     pValorAre         - valor da aresta a ser inserida
*
*  $FV Valor retornado
*     GRF_CondRetOK                 - inseriu sem problemas
*     GRF_CondRetGrafoNaoExiste     - ponteiro para grafo é nulo
*     GRF_CondRetGrafoVazio         -
*     GRF_CondRetValorFornecidoNulo - valor da aresta ou de vértice nulo
*     GRF_CondRetFuncaoNula         - função de comparação nula
*     GRF_CondRetArestaNaoExiste    - não foi encontrada tal aresta
*     GRF_CondRetVerticeNaoExiste   - algum dos valores vértices fornecidos não existe
*     GRF_CondRetErroEstrutura      - algum erro na estrutura do grafo ocorreu
*
***********************************************************************/

   GRF_tpCondRet GRF_RemoverAresta( GRF_tppGrafo pGrafo,
                                    void * pValorVerOrig,
                                    void * pValorVerDest,
                                    void * pValorAre) ;

/***********************************************************************
*
*  $FC Função: GRF  &Caminhar por grafo
*
*  $ED Descrição da função
*     Caminha do vértice corrente por uma aresta em um determinado sentido.
*     Se nestas variáveis existir mais de uma aresta, será caminhada aquela
*     que foi inserida primeiro no grafo.
*
*  $AE Assertivas de entrada
*     Recebe um ponteiro para grafo ou NULO,
*     um ponteiro do valor de aresta, que aponta para uma
*     estrutura de dados do tipo padrão de aresta do grafo,
*     e um inteiro que indica o sentido do caminhamento
*     (0 para trás e 1 para frente).
*
*  $AS Assertivas de saída
*     Se o grafo e a aresta existirem, e o vértice corrente
*     do grafo tiver a aresta no sentido indicado,
*     o novo vértice corrente será o vértice do outro
*     lado da aresta, e retornará GRF_CondRetOK.
*     Caso contrário, a função não realiza nada, e 
*     retorna a condição de retorno apropriada.
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

/***********************************************************************
*
*  $FC Função: GRF  &Obter valor do vértice corrente
*
*  $ED Descrição da função
*     Retorna o valor armazenado no vértice corrente.
*
*  $AE Assertivas de entrada
*     Recebe um ponteiro para um grafo ou NULO e o endereço de um ponteiro
*     existente.
*
*  $AS Assertivas de saída
*     Se o grafo existir, atribui o valor do vértice corrente do grafo à
*     variável *ppValor, retornando GRF_CondRetOK. Caso contrário,
*     *ppValor será NULO, e a função retornará a condição de retorno
*     condizente com o erro.
*
*  $EP Parâmetros
*     pGrafo  - ponteiro para o grafo
*     ppValor - endereço para ponteiro para valor
*
*  $FV Valor retornado
*     GRF_CondRetOK
*     GRF_CondRetErroEstrutura
*     GRF_CondRetGrafoVazio
*     GRF_CondRetGrafoNaoExiste
*
***********************************************************************/

   GRF_tpCondRet GRF_ObterValor( GRF_tppGrafo pGrafo, void ** ppValor ) ;
         
/***********************************************************************
*
*  $FC Função: GRF  &On/off origem no vértice corrente
*
*  $ED Descrição da função
*     Se o vértice corrente é origem, o faz não-origem mais.
*     Se o vértice corrente não é origem, o torna origem.
*
*  $AE Assertivas de entrada
*     Recebe um ponteiro para um grafo ou NULO.
*
*  $AS Assertivas de saída
*     Se o grafo existir e não for vazio, torna o vértice
*     corrente em origem. Se o grafo tiver mais de uma
*     origem e o vértice corrente for origem, o tornará
*     não-origem. Em ambos os casos, retorna GRF_CondRetOK.
*     Caso contrário, a função retornará a condição de retorno
*     condizente com o erro.
*
*  $EP Parâmetros
*     pGrafo  - ponteiro para o grafo
*
*  $FV Valor retornado
*     GRF_CondRetOK
*     GRF_CondRetGrafoNaoExiste
*     GRF_CondRetGrafoVazio
*     GRF_CondRetUnicaOrigem
*     GRF_CondRetErroEstrutura
*     GRF_CondRetFaltouMemoria
*
***********************************************************************/

   GRF_tpCondRet GRF_ToggleOrigem( GRF_tppGrafo pGrafo ) ;     

/***********************************************************************
*
*  $FC Função: GRF  -Procurar vértice em grafo
*
*  $ED Descrição da função
*     Procura no grafo um vértice com dado valor fornecido,
*     tornando-o vértice corrente, caso exista. Pode-se restringir
*     o domínio dos vértices procurados para origens somente.
*
*  $AE Assertivas de entrada
*     Recebe um ponteiro para um grafo ou NULO, um ponteiro
*     para o valor do vértice a ser procurado - que deve
*     apontar para uma estrutura de dados do tipo padrão
*     de vértice do grafo fornecido - e um booleano caso
*     deseja-se procurar o vértice dentre todos os vértices
*     ou somente entre origens.
*
*  $AS Assertivas de saída
*     Se o grafo existir e não for vazio, e houver um vértice/origem
*     no grafo com o mesmo valor, o ponteiro de vértice corrente do grafo
*     agora apontará para o vértice com valor pValor e a função
*     retornará GRF_CondRetOK. Caso contrário, o vértice corrente
*     não mudará e a função retornará a condição de retorno
*     apropriada para o erro.
*
*  $EP Parâmetros
*     pGrafo  - ponteiro para o grafo
*     pValor  - ponteiro genérico para o valor do vértice procurado
*     Origem  - booleano
*               >> 0 - procura dentre todos os vértices
*               >> 1 - procura dentre as origens
*
*  $FV Valor retornado
*     GRF_CondRetOK                 - o vértice foi encontrado
*     GRF_CondRetGrafoNaoExiste     - o ponteiro para o grafo é nulo
*     GRF_CondRetGrafoVazio
*     GRF_CondRetErroEstrutura      - algum erro na estrutura ocorreu
*     GRF_CondRetVerticeNaoExiste   - o vertice com o valor dado não existe
*
***********************************************************************/

   GRF_tpCondRet GRF_ProcurarVertice( GRF_tppGrafo pGrafo ,
										        void *pValor ,
                                      int Origem ) ;

/***********************************************************************
*
*  $FC Função: GRF  -Exibir grafo
*
*  $ED Descrição da função
*     Exibe grafo, caminhando a partir de uma origem, pelas arestas
*     mais "antigas" primeiro.
*
*  $AE Assertivas de entrada
*     Recebe um ponteiro que aponta para grafo, um ponteiro para
*     o valor armazenado no vértice origem, e uma string de
*     saída aonde será armazenada a exibição.
*     É recomendável que a string passada tenha tamanho
*     igual à constante GRF_STR_BUFFER_SIZE, para poucos vértices.
*
*  $AS Assertivas de saída
*     Se nenhum dos ponteiros for nulo, a string de saída tiver
*     capacidade para armazenar toda a exibição, e a estrutura
*     do grafo não apresentar erros, a função armazenará corretamente
*     a exibição do grafo na string de saída.
*     Se nenhum dos ponteiros for nulo, a string é esvaziada mesmo que
*     no meio da execução da função haja algum problema.
*     Se os parâmetros e a estrutura interna estiverem íntegros, a
*     pilha de releitura será esvaziada antes do caminhamento.
*
*  $EP Parâmetros
*     pGrafo       - ponteiro para o grafo
*     pValorOrigem - valor da origem
*     StringSaida  - string de saída referenciada
*
*  $FV Valor retornado
*     GRF_CondRetOK
*     GRF_CondRetGrafoNaoExiste
*     GRF_CondRetGrafoVazio
*     GRF_CondRetVerticeNaoExiste
*     GRF_CondRetValorFornecidoNulo
*     GRF_CondRetErroEstrutura
*     GRF_CondRetFaltouMemoria
*
***********************************************************************/

   GRF_tpCondRet GRF_ExibirGrafo( GRF_tppGrafo pGrafo ,
                                  void * pValorOrigem ,
                                  char * StringSaida ) ;

/***********************************************************************
*
*  $FC Função: GRF  -Obter o número de vértices
*
*  $AE Assertivas de entrada
*     Recebe um ponteiro que aponta para grafo ou NULO.
*
*  $AS Assertivas de saída
*     Se o grafo existir, e não houver erro de estrutura, a função
*     retornará o número de vértices no grafo.
*     Caso contrário, será retornado -1.
*     A função não altera a estrutura interna do grafo.
*
*  $EP Parâmetros
*     pGrafo       - ponteiro para o grafo
*
*  $FV Valor retornado
*     Número de vértices ou -1 ( para grafo inexistente ou com erros
*     na estrutura internaa ).
*
***********************************************************************/

   int GRF_ObterNumVertices( GRF_tppGrafo pGrafo );

/***********************************************************************
*
*  $FC Função: GRF  -Obter o número de vértices
*
*  $AE Assertivas de entrada
*     Recebe um ponteiro que aponta para grafo ou NULO.
*
*  $AS Assertivas de saída
*     Se o grafo existir, e não houver erro de estrutura, a função
*     retornará o número de origens no grafo.
*     Caso contrário, será retornado -1.
*     A função não altera a estrutura interna do grafo.
*
*  $EP Parâmetros
*     pGrafo       - ponteiro para o grafo
*
*  $FV Valor retornado
*     Número de origens ou -1 ( para grafo inexistente ou com erros
*     na estrutura internaa ).
*
***********************************************************************/

   int GRF_ObterNumOrigens( GRF_tppGrafo pGrafo );

/********** Fim do módulo de definição: GRF  Grafo **********/
