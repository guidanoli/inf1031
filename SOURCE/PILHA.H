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
*     1       gui   06/10/2018  Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa pilhas genéricas a partir do módulo lista,
*     desenvolvido por Arndt Von Staa.
*
*     Podem existir n pilhas em operação simultaneamente.
*     As pilhas possuem uma cabeça encapsulando o seu estado.
*
*     Cada pilha é homogênea quanto ao tipo dos dados que armazena.
*     Cada elemento da pilha referencia o valor que contém.
*
*     Os ponteiros para os dados são copiados para elementos da pilha.
*        Não é copiado o valor apontado por estes ponteiros.
*
*     O controle da destruição do valor de um elemento a ser excluído
*        é realizado por uma função fornecida pelo usuário.
*
*     Cada pilha referencia uma função que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A função de liberação dos valores contidos nos elementos deve
*        assegurar a liberação de todos os espaços referênciados pelo
*        valor contido em um elemento.
*        Esta função é chamada antes de se desalocar um elemento
*        de uma pilha.
*        Caso não seja necessário desalocar o valor referenciado pelo
*        elemento, o ponteiro para a função de liberação poderá ser NULL .
*        Caso o elemento da pilha seja a única âncora do valor referenciado,
*        esta função deve promover a destruição (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma pilha */

   typedef struct PIL_tagElemPilha * PIL_tppElemPilha;

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
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*     PIL_CondRetOK
*     PIL_CondRetErroEstrutura
*     PIL_CondRetFaltouMemoria
*
***********************************************************************/

    PIL_tpCondRet PIL_CriarPilha( PIL_tppElemPilha * ppPilhaParam ,
                                  void ( * ExcluirValor ) ( void * pDado ) ) ;

/***********************************************************************
*
*  $FC Função: PIL  &Destruir pilha
*
*  $ED Descrição da função
*     Destrói a pilha fornecida.
*     O parâmetro ponteiro para a pilha é ANULADO, caso
*     não haja algum erro de estrutura interna.
*
*  $AE Assertivas de Entrada
*     O ponteiro *ppPilhaParam deve apontar para uma pilha ou ser NULO.
*     A pilha deve conter uma lista interna ou um ponteiro NULO
*     ( o que está incorreto, mas não prejudica a deleção da pilha ).
*
*  $AS Assertivas de Saída
*     Se a pilha existir, libera a memória ocupada por ela.
*     Se a pilha conter uma lista interna, ela é liberada também.
*     O ponteiro agora é NULO.
*     Senão, a pilha não será destruída e a condição de retorno
*     devida será retornada.
*
*  $FV Valor retornado
*     PIL_CondRetOK
*     PIL_CondRetPilhaNaoExiste
*     PIL_CondRetErroEstrutura
*     PIL_CondRetFaltouMemoria
*
***********************************************************************/

   PIL_tpCondRet PIL_DestruirPilha( PIL_tppElemPilha * ppPilhaParam ) ;

/***********************************************************************
*
*  $FC Função: PIL  &Empilhar elemento na pilha
*
*  $ED Descrição da função
*
*  $AE Assertivas de Entrada
*
*  $AS Assertivas de Saída
*
*  $FV Valor retornado
*     PIL_CondRetOK
*     PIL_CondRetPilhaNaoExiste
*     PIL_CondRetValorFornecidoNulo
*     PIL_CondRetErroEstrutura
*     PIL_CondRetFaltouMemoria
*
***********************************************************************/

   PIL_tpCondRet PIL_Empilhar( PIL_tppElemPilha pPilhaParam ,
                               void * pValor ) ;


/********** Fim do módulo de definição: PIL  Pilha genérica **********/
