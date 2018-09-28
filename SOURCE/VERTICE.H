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

         VER_CondRetValorFornecidoNulo ,
               /* O valor fornecido é nulo */

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
*     ppVerticeParm - endereço do ponteiro para vértice a ser criado
*
*  $FV Valor retornado
*     VER_CondRetOK
*     VER_CondRetFaltouMemoria
*
***********************************************************************/

   VER_tpCondRet VER_CriarVertice(  void   ( * ExcluirValor ) ( void * pDado ),
                                    void * pValor, VER_tppVertice *ppVerticeParm ) ;

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
*     Faz o ponteiro pValor apontar para o valor armazenado no vértice
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
*     pPartida - ponteiro para vértice de partida da aresta
*     pDestino - ponteiro para vértice de destino da aresta
*     pAresta  - ponteiro para valor da aresta
*
*  $FV Valor retornado
*     VER_CondRetOK                 - inseriu sem problemas
*     VER_CondRetVerticeNaoExiste   - ponteiro para vértice é nulo
*     VER_CondRetArestaExiste       - há uma aresta com mesmo valor saindo de
*                                      pPartida e indo para pDestino
*     VER_CondRetErroEstrutura      - algum erro na estrutura do vértice ocorreu
*     VER_CondRetFaltouMemoria      - não foi possível alocar novas arestas
*
***********************************************************************/

   VER_tpCondRet VER_CriarAresta( VER_tppVertice pPartida ,
                                    VER_tppVertice pDestino ,
                                    void * pValorAresta ) ;


/***********************************************************************
*
*  $FC Função: VER  &Destruir aresta
*
*  $ED Descrição da função
*     Destrói uma aresta
*
*  $EP Parâmetros
*     pVertice  - ponteiro para vértice
*     pValor    - ponteiro para valor armazenado na aresta
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
*
***********************************************************************/

   VER_tpCondRet VER_DestruirAresta( VER_tppVertice pVertice,
                                     void * pValor,
                                     int (* ComparaValor) ( void * pA, void * pB)) ;

/***********************************************************************
*
*  $FC Função: VER  &Percorrer aresta
*
*  $ED Descrição da função
*     Percorre uma aresta partindo do vértice de partida fornecido
*     segundo um valor também fornecido, e armazena no ponteiro pDestino
*     o endereço do vértice de destino
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
*
***********************************************************************/

   VER_tpCondRet VER_PercorrerAresta( VER_tppVertice pVerPartida,
                                      void * pValor,
                                      VER_tppVertice pVerDestino,
                                      int (* ComparaValor) ( void * pA, void * pB),
                                      int Sentido ) ;

/********** Fim do módulo de definição: VER  Vértice **********/