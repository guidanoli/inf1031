REM Roda os casos de teste do script "TesteArvore" por interm�dio do arcabou�o de teste automatizado

@echo off
TRAB1.exe /sTesteArvore.script >saida.log
start notepad "saida.log"