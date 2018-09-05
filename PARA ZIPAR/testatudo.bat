REM Roda os casos de teste do script "TesteArvore" por intermédio do arcabouço de teste automatizado

@echo off
TRAB1.exe /sTesteArvore.script >saida.log
start notepad "saida.log"