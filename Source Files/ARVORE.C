/***************************************************************************
*  $MCI Módulo de implementação: Módulo árvore
*
*  Arquivo gerado:              ARVORE.C
*  Letras identificadoras:      ARV
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: avs - Arndt von Staa
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       3.00   avs   28/02/2003 Uniformização da interface das funções e
*                               de todas as condições de retorno.
*       2.00   avs   03/08/2002 Eliminação de código duplicado, reestruturação
*       1.00   avs   15/08/2001 Início do desenvolvimento
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>

#define ARVORE_OWN
#include "ARVORE.H"
#undef ARVORE_OWN

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor do nó da árvore
*
*
*  $ED Descrição do tipo
*     Descreve a organização do nó
*
***********************************************************************/

   typedef struct tgNoArvore {

         struct tgNoArvore * pNoPai ;
               /* Ponteiro para pai
               *
               *$EED Assertivas estruturais
               *   É NULL sse o nó é raiz
               *   Se não for raiz, um de pNoEsq ou pNoDir de pNoPai do nó
               *   corrente apontam para o nó corrente */

         struct tgNoArvore * pNoEsq ;
               /* Ponteiro para filho à esquerda
               *
               *$EED Assertivas estruturais
               *   se pNoEsq do nó X != NULL então pNoPai de pNoEsq aponta para o nó X */

         struct tgNoArvore * pNoDir ;
               /* Ponteiro para filho à direita
               *
               *$EED Assertivas estruturais
               *   se pNoDir do nó X != NULL então pNoPai de pNoDir aponta para o nó X */

         char Valor ;
               /* Valor do nó */

		 ARV_tpModoVisita ModoVisita ;
		       /* Modo de visita do nó */

   } tpNoArvore ;

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor da cabeça de uma árvore
*
*
*  $ED Descrição do tipo
*     A cabe‡a da árvore é o ponto de acesso para uma determinada árvore.
*     Por intermédio da referência para o nó corrente e do ponteiro
*     pai pode-se navegar a árvore sem necessitar de uma pilha.
*     Pode-se, inclusive, operar com a árvore em forma de co-rotina.
*
***********************************************************************/

   typedef struct tgArvore {

         tpNoArvore * pNoRaiz ;
               /* Ponteiro para a raiz da árvore */

         tpNoArvore * pNoCorr ;
               /* Ponteiro para o nó corrente da árvore */

   } tpArvore ;

/*****  Dados encapsulados no módulo  *****/

/***** Protótipos das funções encapuladas no módulo *****/

   static tpNoArvore * CriarNo( char ValorParm ) ;

   static ARV_tpCondRet CriarNoRaiz( tpArvore * pArvore , char ValorParm ) ;

   static void DestroiArvore( tpNoArvore * pNo ) ;

   static ARV_tpCondRet ObterModoNoCorr( tpArvore * pArvore , ARV_tpModoVisita * ModoParm ) ;

   static ARV_tpCondRet MarcarVisitado( tpArvore * pArvore , ARV_tpModoVisita Modo ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: ARV Criar árvore
*  ****/

   ARV_tpCondRet ARV_CriarArvore( void ** ppArvoreParm )
   {
	  
	  tpArvore *pNovaArvore;
	  
      if ( *ppArvoreParm != NULL )
      {
         ARV_DestruirArvore( ppArvoreParm ) ;
      } /* if */

      pNovaArvore = ( tpArvore * ) malloc( sizeof( tpArvore )) ;
      if ( pNovaArvore == NULL )
      {
         return ARV_CondRetFaltouMemoria ;
      } /* if */

      pNovaArvore->pNoRaiz = NULL ;
      pNovaArvore->pNoCorr = NULL ;
	  *ppArvoreParm = pNovaArvore;

      return ARV_CondRetOK ;

   } /* Fim função: ARV Criar árvore */

/***************************************************************************
*
*  Função: ARV Destruir árvore
*  ****/

   void ARV_DestruirArvore( void ** ppArvoreParm )
   {

      tpArvore * pArvore ;

      pArvore = ( tpArvore * )( * ppArvoreParm ) ;
      if ( pArvore != NULL )
      {
         if ( pArvore->pNoRaiz != NULL )
         {
            DestroiArvore( pArvore->pNoRaiz ) ;
         } /* if */
         free( pArvore ) ;
         *ppArvoreParm = NULL ;
      } /* if */

   } /* Fim função: ARV Destruir árvore */

/***************************************************************************
*
*  Função: ARV Exibe a árvore
*  ****/

   void ARV_ExibirArvore( void * pArvoreParm )
   {
      
      /* variáveis auxiliares */

      int NoEsq, NoDir, NoDirNulo;
      char valor;
      ARV_tpCondRet retorno;
      ARV_tpModoVisita modo = ARV_ModoNulo;
      tpArvore *pArvore;
      
      /* Tratar de árvore inexistente */

      if(pArvoreParm == NULL)
      {
         printf("Arvore inexistente\n");
         return;
      } /* if */

      pArvore = ( tpArvore * ) ( pArvoreParm );

      /* Tratar de árvore vazia */

      if(pArvore->pNoRaiz == NULL)
      {
         printf("Arvore vazia\n");
         return;
      } /* if */

      /* A partir daqui ignoramos as seguntes condições de retorno:
         ARV_CondRetArvoreNaoExiste
         ARV_CondRetArvoreVazia
      */

      /* Retornar ponteiro corrente para raiz */

      pArvore->pNoCorr = pArvore->pNoRaiz;

      /* Testa se o nó raiz é folha ou não */

      if(ARV_IrNoEsquerda(pArvore) == ARV_CondRetOK)
      {
         ARV_IrPai(pArvore);
      } /* if */
      else if(ARV_IrNoDireita(pArvore) == ARV_CondRetOK)
      {
         ARV_IrPai(pArvore);
      } /* else if */
      else
      {
         /* Se o nó raiz for folha, rodar caso elementar */

         ARV_ObterValorCorr(pArvore,&valor);
         printf("( %c )",valor);
         return;
      } /* else */

      printf("(");

      /* No algoritmo desta função, é dado um modo de visita a um nó
         para rastrear o caminhamento feito na árvore:
         
         ARV_ModoNulo - todos os nós incialmente são nulos
         ARV_ModoDePai - quando o pai do nó é acessado
         ARV_ModoParaEsq - quando o nó esquerdo é acessado
         ARV_ModoParaDir - quando o nó direito é acessado

         O algoritmo cessará quando o nó raiz tiver modo ARV_ModoDePai */

      while(pArvore->pNoRaiz->ModoVisita != ARV_ModoDePai)
      {

         /* flags: caso nenhum dos nós filhos puderam ser acessados, portanto,
            inexistentes, o nó corrente é uma folha */

         NoDir = 0;
         NoEsq = 0;

         /* Apontar para o nó mais a esquerda */

         while(ARV_IrNoEsquerda(pArvore) == ARV_CondRetOK)
         {
            ARV_IrPai(pArvore);
            ARV_ObterValorCorr(pArvore,&valor);
            printf(" %c (",valor);
            MarcarVisitado(pArvore,ARV_ModoParaEsq);
            ARV_IrNoEsquerda(pArvore);
            NoEsq = 1;
         } /* while */

         /* Caso não haja nó a esquerda, ir para direita uma vez */

         if(ARV_IrNoDireita(pArvore) == ARV_CondRetOK)
         {
            ARV_IrPai(pArvore);
            ARV_ObterValorCorr(pArvore,&valor);
            printf(" %c",valor);
            MarcarVisitado(pArvore,ARV_ModoParaDir);
            ARV_IrNoDireita(pArvore);
            NoDir = 1;
         } /* if */

         /* Caso não houver nem nó à esquerda nem à direita, ou seja,
            for folha, retornar até o nó mais próximo ainda não visitado */

         if(!NoDir && !NoEsq)
         {

            /* O nó corrente passa a ser o nó pai enquanto a folha tiver modo de
               visita igual a ARV_ModoParaDir (vai para o pai uma vez ao menos) */
            
            do
            {
               if(ARV_IrPai(pArvore) == ARV_CondRetOK)
               {
                  ObterModoNoCorr(pArvore,&modo);
                  if(modo == ARV_ModoParaDir)
                  {
                     /* O nó corrente é o último dos irmãos */

                     ARV_IrNoDireita(pArvore);
                     ObterModoNoCorr(pArvore,&modo);
                     if(modo == ARV_ModoNulo)
                     {                        
                        ARV_ObterValorCorr(pArvore,&valor);
                        printf(" %c )",valor);
                        
                     }
                     MarcarVisitado(pArvore,ARV_ModoDePai);
                     ARV_IrPai(pArvore);
                     ObterModoNoCorr(pArvore,&modo);
                  } /* if */
                  else  /* são desconsiderados os modos de visita ARV_ModoDePai e ARV_ModoNulo
                           pois é ilógico este nó corrente ter sido acessado sem que
                           seu pai (que existe, como ARV_IrPai() = ARV_CondRetOK) tenha
                           sido percorrido (portanto não é ARV_ModoNulo) ou declarado como
                           inteiramente explorado (portanto não é ARV_ModoDePai). Portanto,
                           só resta ser ARV_ModoParaEsq */
                  {
                     /* O nó corrente é o primeiro filho */

                     ARV_IrNoEsquerda(pArvore);
                     ObterModoNoCorr(pArvore,&modo);
                     if(modo == ARV_ModoNulo)
                     {                        
                        ARV_ObterValorCorr(pArvore,&valor);
                        printf(" %c )",valor);
                        
                     }
                     MarcarVisitado(pArvore,ARV_ModoDePai);
                     ARV_IrPai(pArvore);
                     ObterModoNoCorr(pArvore,&modo);
                  } /* else */
               } /* if */
               else
               {

                  /* Caso o nó corrente seja o nó raiz */

                  /* Neste bloco já assumimos que ou todos os filhos à
                     esquerda do nó raiz foram explorados ou ele não
                     possui nós filhos, e, portanto, é folha */

                  /* Portanto, testamos se há um filho à direita
                     inexplorado. */

                  if(ARV_IrNoDireita(pArvore) == ARV_CondRetOK)
                  {
                     /* Se sim, alteramos o modo do nó raiz para ARV_ModoParaDir
                        e o filho à direita se torna o nó corrente */
                     ObterModoNoCorr(pArvore,&modo);
                     ARV_IrPai(pArvore);
                     if(modo == ARV_ModoNulo)
                     {
                        MarcarVisitado(pArvore,ARV_ModoParaDir);
                        ARV_IrNoDireita(pArvore);
                        ObterModoNoCorr(pArvore,&modo); /* modo = ARV_ModoNulo */
                     }
                     else
                     {
                        MarcarVisitado(pArvore,ARV_ModoDePai);
                        ObterModoNoCorr(pArvore,&modo); /* modo = ARV_ModoDePai */
                     }
                     break;
                  } /* if */
                  else
                  {
                     /* Se não houver filhos à direita, declaramos fim do caminhamento */

                     ARV_IrPai(pArvore);
                     MarcarVisitado(pArvore,ARV_ModoDePai);
                     printf(" )");
                     break;   
                  }  /* else */           
               } /* else */

            }while(modo == ARV_ModoParaDir); /* do-while */

            /* Caso a folha seja o nó a esquerda do seu pai */

            if(modo == ARV_ModoParaEsq)
            {

               NoDirNulo = 0;
               
               /* Enquanto não houver um nó a direita cujo modo de visita
                  seja ARV_tpModoNulo, ou seja, que não foi explorado ainda*/

               while(!NoDirNulo)
               {
                  if(ARV_IrNoDireita(pArvore) == ARV_CondRetOK)
                  {
                     ObterModoNoCorr(pArvore,&modo);
                     if(modo == ARV_ModoNulo)
                     {
                        NoDirNulo = 1; /* Achado o nó não explorado ainda, sairemos deste loop */

                        /* Caso o nó corrente seja a raiz e tiver um filho à direita, ARV_IrPai() vai falhar
                           mas o algoritmo continuará funcionando, pois ele irá retornar ao nó raiz quando
                           a àrvore à sua direita for completamente explorado */

                        ARV_IrPai(pArvore);
                        MarcarVisitado(pArvore,ARV_ModoParaDir);
                        ARV_IrNoDireita(pArvore);
                        break;

                     } /* if */
                     else if(modo == ARV_ModoDePai)
                     {
                        ARV_IrPai(pArvore);
                        MarcarVisitado(pArvore,ARV_ModoDePai);
                        if(ARV_IrPai(pArvore) == ARV_CondRetNohEhRaiz)
                        {
                           break;
                        }
                     }
                  } /* if */
                  else if(ARV_IrPai(pArvore) == ARV_CondRetOK)
                  {
                     retorno = ObterModoNoCorr(pArvore,&modo);
                     if(modo == ARV_ModoParaDir)
                     {
                        ARV_IrNoDireita(pArvore);
                        MarcarVisitado(pArvore,ARV_ModoDePai);
                        ARV_IrPai(pArvore);
                     } /* if */
                     else
                     {
                        ARV_IrNoEsquerda(pArvore);
                        MarcarVisitado(pArvore,ARV_ModoDePai);
                        ARV_IrPai(pArvore);
                     } /* else */
                  } /* else-if */
                  else
                  {
                     MarcarVisitado(pArvore,ARV_ModoDePai);
                     break;
                  } /* else */
               } /* while */
            } /* if */
         } /* if */

      } /* while */

   } /* Fim função: ARV Exibe a árvore */

/***************************************************************************
*
*  Função: ARV Adicionar filho à esquerda
*  ****/

   ARV_tpCondRet ARV_InserirEsquerda( void * pArvoreParm , char ValorParm )
   {

      tpArvore *pArvore;

      ARV_tpCondRet CondRet ;

      tpNoArvore * pCorr ;
      tpNoArvore * pNo ;

      if(pArvoreParm == NULL)
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      pArvore = (tpArvore *) (pArvoreParm);

      /* Tratar vazio, esquerda */

         CondRet = CriarNoRaiz( pArvore, ValorParm ) ;
         if ( CondRet != ARV_CondRetNaoCriouRaiz )
         {
            return CondRet ;
         } /* if */

      /* Criar nó à esquerda de folha */

         pCorr = pArvore->pNoCorr ;
         if ( pCorr == NULL )
         {
            return ARV_CondRetErroEstrutura ;
         } /* if */
               
         if ( pCorr->pNoEsq == NULL )
         {
            pNo = CriarNo( ValorParm ) ;
            if ( pNo == NULL )
            {
               return ARV_CondRetFaltouMemoria ;
            } /* if */
            pNo->pNoPai      = pCorr ;
            pCorr->pNoEsq    = pNo ;
            pArvore->pNoCorr = pNo ;

            return ARV_CondRetOK ;
         } /* if */

      /* Tratar não folha à esquerda */

         return ARV_CondRetNaoEhFolha ;

   } /* Fim função: ARV Adicionar filho à esquerda */

/***************************************************************************
*
*  Função: ARV Adicionar filho à direita
*  ****/

   ARV_tpCondRet ARV_InserirDireita( void * pArvoreParm , char ValorParm )
   {

      tpArvore *pArvore;

      ARV_tpCondRet CondRet ;

      tpNoArvore * pCorr ;
      tpNoArvore * pNo ;

      if(pArvoreParm == NULL)
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      pArvore = (tpArvore *) (pArvoreParm);

      /* Tratar vazio, direita */

         CondRet = CriarNoRaiz( pArvore, ValorParm ) ;
         if ( CondRet != ARV_CondRetNaoCriouRaiz )
         {
            return CondRet ;
         } /* if */

      /* Criar nó à direita de folha */

         pCorr = pArvore->pNoCorr ;
         if ( pCorr == NULL )
         {
            return ARV_CondRetErroEstrutura ;
         } /* if */
               
         if ( pCorr->pNoDir == NULL )
         {
            pNo = CriarNo( ValorParm ) ;
            if ( pNo == NULL )
            {
               return ARV_CondRetFaltouMemoria ;
            } /* if */
            pNo->pNoPai      = pCorr ;
            pCorr->pNoDir    = pNo ;
            pArvore->pNoCorr = pNo ;

            return ARV_CondRetOK ;
         } /* if */

      /* Tratar não folha à direita */

         return ARV_CondRetNaoEhFolha ;

   } /* Fim função: ARV Adicionar filho à direita */

/***************************************************************************
*
*  Função: ARV Ir para nó pai
*  ****/

   ARV_tpCondRet ARV_IrPai( void * pArvoreParm )
   {

      tpArvore *pArvore;

      if ( pArvoreParm == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      pArvore = ( tpArvore * ) ( pArvoreParm );

      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoPai != NULL )
      {
         pArvore->pNoCorr = pArvore->pNoCorr->pNoPai ;
         return ARV_CondRetOK ;
      } /* if */

      return ARV_CondRetNohEhRaiz ;
      

   } /* Fim função: ARV Ir para nó pai */

/***************************************************************************
*
*  Função: ARV Ir para nó à esquerda
*  ****/

   ARV_tpCondRet ARV_IrNoEsquerda( void * pArvoreParm )
   {

      tpArvore *pArvore;

      if ( pArvoreParm == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      pArvore = ( tpArvore * ) ( pArvoreParm );

      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoEsq == NULL )
      {
         return ARV_CondRetNaoPossuiFilho ;
      } /* if */

      pArvore->pNoCorr = pArvore->pNoCorr->pNoEsq ;
      return ARV_CondRetOK ;

   } /* Fim função: ARV Ir para nó à esquerda */

/***************************************************************************
*
*  Função: ARV Ir para nó à direita
*  ****/

   ARV_tpCondRet ARV_IrNoDireita( void * pArvoreParm )
   {

      tpArvore *pArvore;

      if ( pArvoreParm == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      pArvore = ( tpArvore * ) ( pArvoreParm );

      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoDir == NULL )
      {
         return ARV_CondRetNaoPossuiFilho ;
      } /* if */

      pArvore->pNoCorr = pArvore->pNoCorr->pNoDir ;
      return ARV_CondRetOK ;

   } /* Fim função: ARV Ir para nó à direita */

/***************************************************************************
*
*  Função: ARV Obter valor corrente
*  ****/

   ARV_tpCondRet ARV_ObterValorCorr( void * pArvoreParm , char * ValorParm )
   {

      tpArvore *pArvore;

      if ( pArvoreParm == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      pArvore = ( tpArvore * ) ( pArvoreParm );

      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      * ValorParm = pArvore->pNoCorr->Valor ;
      return ARV_CondRetOK ;

   } /* Fim função: ARV Obter valor corrente */


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: ARV Altera o ModoVisita do nó corrente
*
*  $ED Descrição da função
*     Altera o modo de visita do nó corrente da árvore corrente,
*     caso haja árvore, e que não esteja vazia.
*
*  $EP Parâmetros
*     $P ValorParm - novo modo do nó corrente.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*
***********************************************************************/

   ARV_tpCondRet MarcarVisitado( tpArvore * pArvore , ARV_tpModoVisita Modo )
   {
	   
      if(pArvore == NULL)
      {
         return ARV_CondRetArvoreNaoExiste;
	  } /* if */
	  if(pArvore->pNoCorr == NULL)
      {
         return ARV_CondRetArvoreVazia;
	  } /* if */

	  pArvore->pNoCorr->ModoVisita = Modo;
	  return ARV_CondRetOK;

   } /* Fim função: ARV Altera o ModoVisita do nó corrente */

/***********************************************************************
*
*  $FC Função: ARV Obter modo de visita do nó corrente
*
*  $EP Parâmetros
*     $P ModoParm - é o valor que receberá o modo de visita do
*                   nó corrente
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*
***********************************************************************/

   ARV_tpCondRet ObterModoNoCorr( tpArvore * pArvore , ARV_tpModoVisita * ModoParm )
   {

      if(pArvore == NULL)
      {
         return ARV_CondRetArvoreNaoExiste;
	  } /* if */
	  if(pArvore->pNoCorr == NULL)
      {
         return ARV_CondRetArvoreVazia;
	  } /* if */

      *ModoParm = pArvore->pNoCorr->ModoVisita;
      return ARV_CondRetOK;

   } /* Fim função: ARV Recebe modo de visita do nó corrente */

/***********************************************************************
*
*  $FC Função: ARV Criar nó da árvore
*
*  $FV Valor retornado
*     Ponteiro para o nó criado.
*     Será NULL caso a memória tenha se esgotado.
*     Os ponteiros do nó criado estarão nulos e o valor é igual ao do
*     parâmetro.
*
***********************************************************************/

   tpNoArvore * CriarNo( char ValorParm )
   {

      tpNoArvore * pNo ;

      pNo = ( tpNoArvore * ) malloc( sizeof( tpNoArvore )) ;
      if ( pNo == NULL )
      {
         return NULL ;
      } /* if */

      pNo->pNoPai = NULL ;
      pNo->pNoEsq = NULL ;
      pNo->pNoDir = NULL ;
      pNo->Valor  = ValorParm ;
	  pNo->ModoVisita = ARV_ModoNulo;
      return pNo ;

   } /* Fim função: ARV Criar nó da árvore */


/***********************************************************************
*
*  $FC Função: ARV Criar nó raiz da árvore
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetFaltouMemoria
*     ARV_CondRetNaoCriouRaiz
*
***********************************************************************/

   ARV_tpCondRet CriarNoRaiz( tpArvore * pArvore , char ValorParm )
   {

      tpNoArvore * pNo ;

      if ( pArvore->pNoRaiz == NULL )
      {
         pNo = CriarNo( ValorParm ) ;
         if ( pNo == NULL )
         {
            return ARV_CondRetFaltouMemoria ;
         } /* if */

         pArvore->pNoRaiz = pNo ;
         pArvore->pNoCorr = pNo ;

         return ARV_CondRetOK ;
      } /* if */

      return ARV_CondRetNaoCriouRaiz ;

   } /* Fim função: ARV Criar nó raiz da árvore */


/***********************************************************************
*
*  $FC Função: ARV Destruir a estrutura da árvore
*
*  $EAE Assertivas de entradas esperadas
*     pNoArvore != NULL
*
***********************************************************************/

   void DestroiArvore( tpNoArvore * pNo )
   {

      if ( pNo->pNoEsq != NULL )
      {
         DestroiArvore( pNo->pNoEsq ) ;
      } /* if */

      if ( pNo->pNoDir != NULL )
      {
         DestroiArvore( pNo->pNoDir ) ;
      } /* if */

      free( pNo ) ;

   } /* Fim função: ARV Destruir a estrutura da árvore */

/********** Fim do módulo de implementação: Módulo árvore **********/

