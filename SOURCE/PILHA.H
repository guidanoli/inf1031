#if ! defined( PILHA_ )
#define PILHA_
/***************************************************************************
*
*  $MCD Módulo de definição: PIL  Pilha genérica
*
*  Arquivo gerado:              PILHA.H
*  Letras identificadoras:      PIL
*
*  Autores:   gui   Guilherme Dantas
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     0       gui   06/10/2018  Início do desenvolvimento
*     1       gui   08/10/2018  Criar, destruir, empilhar, desempilhar e vazia
*     2       gui   12/10/2018  Copiar
*
*  $ED Descrição do módulo
*     Implementa pilhas genéricas a partir do módulo lista,
*     desenvolvido por Arndt Von Staa.
*
*     Podem existir n pilhas em operação simultaneamente.
*     As pilhas possuem uma cabeça encapsulando o seu estado.
*
*     A pilha não possui restrição quanto ao tipo dos dados que armazena.
*     Cada elemento da pilha referencia o valor que contém.
*
*     Os ponteiros para os dados são copiados para elementos da pilha.
*        Não é copiado o valor apontado por estes ponteiros.
*
*     Os valores referenciados pelos elementos da pilha não são liberados.
*        Cabe ao módulo cliente fazer o housekeeping.
*
*     Caso uma pilha seja destruída antes de esvaziada, não será possível
*     ter acesso aos valores referenciados pelos elementos.
*        Cabe ao módulo cliente esvaziar a pilha, desempilhando elemento
*        por elemento, para então tratar de liberá-los ou manipulá-los
*        como queira, caso queira.
*
***************************************************************************/

#if defined( PILHA_OWN )
   #define PILHA_EXT
#else
   #define PILHA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma pilha */

   typedef struct PIL_tagPilha * PIL_tppPilha;

/***********************************************************************
*
*  $TC Tipo de dados: PIL Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da pilha
*
***********************************************************************/

   typedef enum {

         PIL_CondRetOK ,
               /* Concluiu corretamente */

         PIL_CondRetPilhaNaoExiste ,
               /* Ponteiro para pilha é nulo */

         PIL_CondRetValorFornecidoNulo ,
               /* Ponteiro para valor é nulo */

         PIL_CondRetPilhaVazia ,
               /* A pilha não possui nenhume elemento */

         PIL_CondRetErroEstrutura ,
               /* Há algum erro na estrutura interna da pilha */

         PIL_CondRetFaltouMemoria
               /* Faltou memória ao tentar criar um elemento de pilha */

   } PIL_tpCondRet ;


/***********************************************************************
*
*  $FC Função: PIL  &Criar pilha
*
*  $ED Descrição da função
*     Cria uma pilha genérica.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado à pilha.
*
*  $AE Assertivas de Entrada
*     O ponteiro não é nulo, e aponta para um ponteiro de pilha.
*     A função ExcluirValor deve estar de acordo com o seu propósito,
*     como descrito no módulo.
*
*  $AS Assertivas de Saída
*     Se já houver uma pilha armazenada por *ppPilhaParam, esta pilha
*     será destruída para ser substituída pela nova pilha, caso não
*     haja nenhum erro na estrutura interna da pilha.
*     Se houver memória o suficiente, a pilha terá uma lista interna
*     sem elementos, e com um contador indicando zero elementos.
*     A pilha então será armazenada no ponteiro referenciado pelo
*     ponteiro ppPilhaParam.
*     Caso contrário, nada será alocado e a condição de retorno
*     devido será retornado.
*
*  $EP Parâmetros
*     ppPilhaParam - endereço do ponteiro no módulo cliente que irá
*                    referenciar a pilha a ser criada.
*
*  $FV Valor retornado
*     PIL_CondRetOK
*     PIL_CondRetErroEstrutura
*     PIL_CondRetFaltouMemoria
*
***********************************************************************/

    PIL_tpCondRet PIL_CriarPilha( PIL_tppPilha * ppPilhaParam ) ;

/***********************************************************************
*
*  $FC Função: PIL  &Destruir pilha
*
*  $ED Descrição da função
*     Destrói a pilha fornecida.
*
*  $AE Assertivas de Entrada
*     O ponteiro *ppPilhaParam deve apontar para uma pilha ou ser NULO.
*     A pilha deve conter uma lista interna ou um ponteiro NULO
*     ( o que está incorreto, mas não prejudica a deleção da pilha ).
*
*  $AS Assertivas de Saída
*     Se a pilha existir, libera a memória ocupada por ela.
*     Se a pilha conter uma lista interna, ela é liberada também.
*     O ponteiro *ppPilhaParam é ANULADO.
*     Senão, a pilha não será destruída e a condição de retorno
*     devida será retornada.
*
*  $EP Parâmetros
*     ppPilhaParam - endereço do ponteiro no módulo cliente que
*                    referencia a pilha a ser destruída.
*
*  $FV Valor retornado
*     PIL_CondRetOK
*     PIL_CondRetPilhaNaoExiste
*
***********************************************************************/

   PIL_tpCondRet PIL_DestruirPilha( PIL_tppPilha * ppPilhaParam ) ;

/***********************************************************************
*
*  $FC Função: PIL  &Empilhar elemento na pilha
*
*  $ED Descrição da função
*     Empilha o valor fornecido no topo da pilha.
*
*  $AE Assertivas de Entrada
*     Recebe um ponteiro para uma pilha ou NULO, e um ponteiro
*     para o valor a ser empilhado.
*
*  $AS Assertivas de Saída
*     Caso a pilha exista, haja memória, não tenha erro na
*     estrutura interna, e o valor não for nulo, o elemento
*     será empilhado no topo da pilha.
*     Caso contrário, será retornada a condição de retorno
*     aquequada, e o elemento não será empilhado.
*
*  $EP Parâmetros
*     pPilha -       ponteiro para pilha a ser manipulada.
*     pValor -       ponteiro para valor a ser inserido no topo da pilha.
*
*  $FV Valor retornado
*     PIL_CondRetOK
*     PIL_CondRetPilhaNaoExiste
*     PIL_CondRetValorFornecidoNulo
*     PIL_CondRetErroEstrutura
*     PIL_CondRetFaltouMemoria
*
***********************************************************************/

   PIL_tpCondRet PIL_Empilhar( PIL_tppPilha pPilha ,
                               void * pValor ) ;

/***********************************************************************
*
*  $FC Função: PIL  &Desempilhar elemento na pilha
*
*  $ED Descrição da função
*     Caso a pilha não estiver nula, retira o elemento do topo da
*     pilha e retorna valor armazenado nele.
*
*  $AE Assertivas de Entrada
*     Recebe um ponteiro que aponta para uma pilha ou NULO.
*
*  $AS Assertivas de Saída
*     Caso a pilha exista, não tenha erro na estrutura interna, e não
*     estava vazia antes de executada a função, tem o elemento do topo
*     removido e seu valor retornado pela função.
*     Caso contrário, a função retorna NULO e a pilha não é alterada.
*     O topo da pilha agora é o último elemento a ser inserido antes
*     do antigo topo da pilha, ou nenhum, caso a pilha tinha apenas
*     um elemento.
*
*  $EP Parâmetros
*     pPilha -       ponteiro para pilha a ser manipulada.
*
*  $FV Valor retornado
*     O valor armazenado no topo da pilha.
*     OU NULO, caso a pilha estiver vazia.
*
***********************************************************************/

   void * PIL_Desempilhar( PIL_tppPilha pPilha ) ;

/***********************************************************************
*
*  $FC Função: PIL  &Pilha vazia
*
*  $ED Descrição da função
*     Averigua se pilha está vazia ou não.
*
*  $AE Assertivas de Entrada
*     Recebe um ponteiro que aponta para uma pilha ou NULO.
*
*  $AS Assertivas de Saída
*     Retorna a condição de retorno correspondente ao estado da pilha.
*     Não altera a estrutura interna.
*
*  $EP Parâmetros
*     pPilha -       ponteiro para pilha a ser analisada.
*
*  $FV Valor retornado
*     PIL_CondRetOK              - a pilha não está vazia
*     PIL_CondRetPilhaNaoExiste  - a pilha não existe
*     PIL_CondRetPilhaVazia      - a pilha está vazia
*
***********************************************************************/

   PIL_tpCondRet PIL_PilhaVazia( PIL_tppPilha pPilha ) ;

/***********************************************************************
*
*  $FC Função: PIL  &Copiar pilha
*
*  $ED Descrição da função
*     Copia os elementos de uma pilha para outra
*
*  $AE Assertivas de Entrada
*     Recebe o endereço para ponteiro que aponta para a pilha que
*     será copiada, e o endereço de ponteiro que aponta para a
*     a pilha que receberá os elementos da pilha fonte.
*
*  $AS Assertivas de Saída
*     Se a pilha fonte existir, não tiver erros de estrutura,
*     e não faltar memória, a pilha será copiada para o destino,
*     sem alterar a estrutura da pilha fonte.
*     Caso contrário, pode-se resultar em pilha com erro
*     de estrutura. A função retornará a condição de retorno
*     apropriada para o estado das pilhas.
*
*  $EP Parâmetros
*     pFonte   - endereço de ponteiro para pilha a ser copiada.
*     pDestino - endereço de ponteiro para pilha nova
*
*  $FV Valor retornado
*     PIL_CondRetOK                 - copiou com sucesso
*     PIL_CondRetPilhaNaoExiste     - ponteiro para pilha não existe
*     PIL_CondRetValorFornecidoNulo - algum dos endereços não existe
*     PIL_CondRetErroEstrutura      - há erros na estrutura interna da pilha
*     PIL_CondRetFaltouMemoria
*
***********************************************************************/

   PIL_tpCondRet PIL_CopiarPilha( PIL_tppPilha * pFonte ,
                                  PIL_tppPilha * pDestino ) ;

#undef PILHA_EXT

/********** Fim do módulo de definição: PIL  Pilha genérica **********/

#else
#endif
