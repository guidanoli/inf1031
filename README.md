# Grupo de Programação Modular (INF1031)
**Alunos: Caique, Guilherme e Nagib**

Este repositório contém apenas os arquivos .c, .h e .lib.
Para trabalhar no Visual Studio 2010 com estes arqvuiso, basta arrastá-los para o seu projeto no VS. Não esquecer de configurar o seu projeto para que não utilize pre-compiled headers (cabeçalhos pré-compilados) nem dependa de DLLs.

## Scripts

Na pasta **_SCRIPTS_**, edite o arquivo de nome **_TesteArvore.script_**, mas não altere o nome. Para testar o script, rode o batch **__Distruibui.bat__** e dentro da pasta **DISTRIBUICAO**, rode o batch **__Testa.bat__** e a saída estará salva como **__saida.txt__**.

## Relatórios

Sempre que fizer alguma alteração relevante no programa, dê commit e sinalize no arquivo "RELATORIO-SeuNome.txt" a tarefa que você realizou no seguinte formato:

`Data - Horas Trabalhadas - Tipo de Tarefa - Descrição da Tarefa Realizada`

Os tipos de tarefa são:
* estudar
* especificar os módulos
* especificar as funções
* revisar especificações
* projetar
* revisar projetos
* codificar módulo
* revisar código do módulo
* redigir script de teste
* revisar script de teste
* realizar os testes
* diagnosticar e corrigir os problemas encontrados

## Diretório de distribuição

Primeiramente, certifique-se que esta pasta esteja na pasta do seu projeto do Visual Basic. Assim:

`[...]\Visual Studio 2010\Projects\MeuProjeto\Debug\progmod`

A localização do repositório na sua máquina é fundamental para que o arquivo batch consiga copiar o executável automaticamente. Para gerar o diretório de distribuição, rode o batch _**Distribui.bat**_ para copiar apenas os arquivos importantes para a pasta **_DISTRIBUICAO_**.

_Att,
Guilherme_
