REM Roda os casos de teste do script "TesteArvore" por interm�dio do arcabou�o de teste automatizado

@echo off
PROGMOD.exe /sTesteArvore.script >saida.log
start notepad "saida.log"