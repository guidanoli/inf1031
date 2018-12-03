#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD Módulo de definição: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores:   avs   Arndt Von Staa
*             cai   Caique Molina
*             gui   Guilherme Dantas
*             nag   Nagib Suaid
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     6       gui   03/dez/2018 revisão da instrumentação
*     5       gui   29/nov/2018 início instrumentação
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa listas genéricas duplamente encadeadas.
*     Podem existir n listas em operação simultaneamente.
*     As listas possuem uma cabeça encapsulando o seu estado.
*
*     Cada lista é homogênea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que contém.
*
*     Os ponteiros para os dados são copiados para elementos da lista.
*        Não é copiado o valor apontado por estes ponteiros.
*
*     O controle da destruição do valor de um elemento a ser excluído
*        é realizado por uma função fornecida pelo usuário.
*
*     Cada lista referencia uma função que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A função de liberação dos valores contidos nos elementos deve
*        assegurar a liberação de todos os espaços referênciados pelo
*        valor contido em um elemento.
*        Esta função é chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso não seja necessário desalocar o valor referenciado pelo
*        elemento, o ponteiro para a função de liberação poderá ser NULL .
*        Caso o elemento da lista seja a única âncora do valor referenciado,
*        esta função deve promover a destruição (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
*
***********************************************************************/

   typedef enum {

         LIS_CondRetOK ,
               /* Concluiu corretamente */

         LIS_CondRetListaVazia ,
               /* A lista não contém elementos */

         LIS_CondRetFimLista ,
               /* Foi atingido o fim de lista */

         LIS_CondRetNaoAchou ,
               /* Não encontrou o valor procurado */

         LIS_CondRetFaltouMemoria ,
               /* Faltou memória ao tentar criar um elemento de lista */

#ifdef _DEBUG
         LIS_CondRetErroEstrutura ,
               /* Algum erro na estrutura ocorreu */

         LIS_CondRetErroParametro
               /* Função recebeu um parâmetro inválido */
#endif

   } LIS_tpCondRet ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Modos de deturpar
*
*
***********************************************************************/

#ifdef _DEBUG

   typedef enum {

         LIS_ModoDeturpacaoEliminaCorr = 1 ,
            /* Elimina o elemento corrente da lista */

         LIS_ModoDeturpacaoProxNULL = 2 ,
            /* Atribui NULL ao ponteiro para o próximo nó */

         LIS_ModoDeturpacaoAntNULL = 3 ,
            /* Atribui NULL ao ponteiro para o nó anterior */

         LIS_ModoDeturpacaoProxLixo = 4 ,
            /* Atribui lixo ao ponteiro para o próximo nó */

         LIS_ModoDeturpacaoAntLixo = 5 ,
            /* Atribui lixo ao ponteiro para o nó anterior */

         LIS_ModoDeturpacaoConteudoNULL = 6 ,
            /* Atribui NULL ao ponteiro para o conteúdo do nó */

         LIS_ModoDeturpacaoAlteraTipoNo = 7 ,
            /* Altera o tipo de estrutura apontado no nó */

         LIS_ModoDeturpacaoDesencadeiaNo = 8 ,
            /* Desencadeia nó sem liberá-lo com free */

         LIS_ModoDeturpacaoPontCorrNULL = 9 ,
            /* Atribui NULL ao ponteiro corrente */

         LIS_ModoDeturpacaoPontOrigNULL = 10 ,
            /* Atribui NULL ao ponteiro de origem */

         LIS_ModoDeturpacaoPontFimNULL = 11 ,
            /* Atribui NULL ao ponteiro de final */

         LIS_ModoDeturpacaoEliminaLista = 12 ,
            /* Elimina lista */

         LIS_ModoDeturpacaoCorrLixo = 13 ,
            /* Atribui lixo ao ponteiro para nó corrente */

         LIS_ModoDeturpacaoOrigLixo = 14 ,
            /* Atribui lixo ao ponteiro para nó origem */

         LIS_ModoDeturpacaoFinalLixo = 15 ,
            /* Atribui lixo ao ponteiro para nó final */

         LIS_ModoDeturpacaoNumElemNegativo = 16 ,
            /* Atribui valor negativo ao contador de elementos */

         LIS_ModoDeturpacaoCorrElemNovo = 17 ,
            /* Fazer ponteiro corrente apontar para novo elemento */

         LIS_ModoDeturpacaoCorrTipoErrado = 18 ,
            /* Fazer ponteiro corrente apontar para lista */

         LIS_ModoDeturpacaoOrigTipoErrado = 19 ,
            /* Fazer ponteiro origem apontar para lista */

         LIS_ModoDeturpacaoFinalTipoErrado = 20 ,
            /* Fazer ponteiro final apontar para lista */

         LIS_ModoDeturpacaoOrigElemNovo = 21 ,
            /* Fazer ponteiro origem apontar para novo elemento */

         LIS_ModoDeturpacaoElemCorrCabNULL = 22 ,
            /* Fazer pCab do elemento corrente NULL */

         LIS_ModoDeturpacaoDuplicarElem = 23 ,
            /* Duplica elemento de modo que se possa continuar
               a percorrer em ambos os sentidos por caminhos diferentes */

         LIS_ModoDeturpacaoTamNegativo = 24 ,
            /* Faz tam = -1 */

         LIS_ModoDeturpacaoTamUm = 25 ,
            /* Faz tam = 1 */

         LIS_ModoDeturpacaoConteudoLixo = 26 ,
            /* Faz pValor apontar para lixo */

         LIS_ModoDeturpacaoConteudoApontaElem = 27 ,
            /* Faz pValor apontar para elemento */

         LIS_ModoDeturpacaoAntApontaCab = 28 ,
            /* Faz pAnt do elemento corrente apontar para cabeça */

         LIS_ModoDeturpacaoProxApontaCab = 29 
            /* Faz pProx do elemento corrente apontar para cabeça */

   } LIS_tpModosDeturpacao ;

#endif

/***********************************************************************
*
*  $FC Função: LIS  &Criar lista
*
*  $ED Descrição da função
*     Cria uma lista genérica duplamente encadeada.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado à lista.
*
*  $EP Parâmetros
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro será utilizado pelas funções que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

   LIS_tppLista LIS_CriarLista( void   ( * ExcluirValor ) ( void * pDado )
#ifdef _DEBUG
                              , char TipoValor
#endif
      ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Destruir lista
*
*  $ED Descrição da função
*     Destrói a lista fornecida.
*     O parâmetro ponteiro para a lista não é modificado.
*     Se ocorrer algum erro durante a destruição, a lista resultará
*     estruturalmente incorreta.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  $FV Valor retornado
*     LIS_CondRetOK    - destruiu sem problemas
*
***********************************************************************/

   void LIS_DestruirLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Esvaziar lista
*
*  $ED Descrição da função
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a ser esvaziada
*
***********************************************************************/

   void LIS_EsvaziarLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Inserir elemento antes
*
*  $ED Descrição da função
*     Insere novo elemento antes do elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista onde deve ser inserido o elemento
*     pValor - ponteiro para o valor do novo elemento
*              Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetFaltouMemoria
*
*     Para _DEBUG ativo:
*     LIS_CondRetErroParametro
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor
#ifdef _DEBUG
                                          , char TipoValor
                                          , int tam
#endif
      ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Inserir elemento após
*
*  $ED Descrição da função
*     Insere novo elemento apás o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
*     Parâmetros
*        pLista - ponteiro para a lista onde deve ser inserido o elemento
*        pValor - ponteiro para o valor do novo elemento
*                 Pode ser NULL
*           
*
*  $FV Valor retornado
*     Valor retornado
*        LIS_CondRetOK
*        LIS_CondRetFaltouMemoria
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor
#ifdef _DEBUG
                                          , char TipoValor
                                          , int tam
#endif
      ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Excluir elemento
*
*  $ED Descrição da função
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento aa esquerda do corrente será o novo corrente.
*     Se não existir e existir o elemento à direita, este se tornará corrente.
*     Se este também não existir a lista tornou-se vazia.
*
*  $EP Parâmetros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetListaVazia
*
***********************************************************************/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Obter referência para o valor contido no elemento
*
*  $ED Descrição da função
*     Obtem a referência para o valor contido no elemento corrente da lista
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista de onde se quer o valor
*
*  $FV Valor retornado
*     não NULL - se o elemento corrente existe
*     NULL     - se a lista estiver vazia
*                Pode retornar NULL se o valor inserido no elemento for NULL.
*
***********************************************************************/

   void * LIS_ObterValor( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Ir para o elemento inicial
*
*  $ED Descrição da função
*     Torna corrente o primeiro elemento da lista.
*     Faz nada se a lista está vazia.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a manipular
*
***********************************************************************/

   void IrInicioLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Ir para o elemento final
*
*  $ED Descrição da função
*     Torna corrente o elemento final da lista.
*     Faz nada se a lista está vazia.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a manipular
*
***********************************************************************/

   void IrFinalLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Avançar elemento
*
*  $ED Descrição da função
*     Avança o elemento corrente numElem elementos na lista
*     Se numElem for positivo avança em direção ao final
*     Se numElem for negativo avança em direção ao início
*     numElem pode ser maior do que o númro de elementos existentes na
*               direção desejada
*     Se numElem for zero somente verifica se a lista está vazia
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista a ser manipulada
*     numElem - o número de elementos a andar
*
*  $FV Valor retornado
*     LIS_CondRetOK         - se numElem elementos tiverem sido andados
*     LIS_CondRetFimLista   - se encontrou o fim da lista antes de andar numElem
*                         elementos
*     LIS_CondRetListaVazia - se a lista está vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Procurar elemento contendo valor
*
*  $ED Descrição da função
*     Procura o elemento que referencia o valor dado.
*     A função compara ponteiro e não conteúdo apontado.
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista onde procura
*     pValor  - ponteiro para o valor procurado
*               Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK  - se encontrou.
*                      O elemento corrente é o primeiro elemento do
*                      elemento corrente inclusive para o fim da lista
*                      e que contém o ponteiro procurado
*
*     LIS_CondRetNaoAchou - se o ponteiro não foi encontrado
*                      O elemento corrente continua o mesmo
*     LIS_CondRetListaVazia   - se a lista estiver vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor        ) ;

/***********************************************************************
*
*  $FC Função: LIS  &Verificar uma lista
*
*  $ED Descrição da função
*     Função da interface de teste.
*     Verifica completamente uma determinada lista.
*     Também marca todos os espaços por ela ocupados.
*
*  $EP Parâmetros
*     pListaParam  - ponteiro para cabeça da lista a ser deturpada
*
*  $FV Valor retornado
*     Quantidade de falhas encontradas.
*
***********************************************************************/

#ifdef _DEBUG

   int LIS_VerificarLista( void * pListaParam ) ;

#endif

/***********************************************************************
*
*  $FC Função: LIS  &Deturpar lista
*
*  $ED Descrição da função
*     Função da interface de teste.
*     Corrompe elementos específicos da estrutura da lista.
*     Essa função destina-se a preparar os cenários de teste dos
*     casos de teste utilizados ao testar os verificadores estruturais
*     da lista.
*     Esta função não tem proteção contra erros de uso, consequentemente
*     poderá levar o programa a ser cancelado pelo sistema operacional.
*
*  $EP Parâmetros
*     pListaParam  - ponteiro para cabeça da lista a ser deturpada
*     ModoDeturpar - identifica como deve ser feita a deturpação
*                    LIS_tpModosDeturpacao identifica os modos de
*                    deturpação conhecidos
*
***********************************************************************/

#ifdef _DEBUG

   void LIS_Deturpar( void ** pListaParam ,
                      LIS_tpModosDeturpacao ModoDeturpar ) ;

#endif

/***********************************************************************
*
*  $FC Função: LIS  &Liberar espaços inativos relativos ao módulo Lista
*
*  $ED Descrição da função
*     Função da interface de teste.
*     Libera da memória todo espaço de memória inativo na LEA
*     que tenha como tipo de espaço de dados um dos seguintes:
*
*     - LIS_TipoEspacoElemento
*     - LIS_TipoEspacoCabeca
*     - LIS_TipoEspacoEstrutura
*
*  $AE Assertivas de Entrada:
*     Implicitamente é usada a LEA, componente do módulo
*     CESPDIN.H, importado apenas para _DEBUG.
*
*  $AS Assertivas de Saída:
*     Se houver outros espaços apontados por esta estrutura,
*     e não forem dos tipos citados, não serão tratadas.
*
***********************************************************************/

#ifdef _DEBUG

   int LIS_LiberarEspacosInativos ( void ) ;

#endif

#undef LISTA_EXT

/********** Fim do módulo de definição: LIS  Lista duplamente encadeada **********/

#else
#endif
