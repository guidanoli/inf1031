@echo off

:read-exec-path

set /p exec=Nome do executavel: 

if not exist %exec% (
	@echo on
	echo Este executavel nao existe!
	@echo off
	goto read-exec-path
)

:read-script-path

set /p var=Nome do script: 

if not exist %var% (
	@echo on
	echo Este script nao existe!
	@echo off
	goto read-script-path
)

%exec% /s%var% >saida.log

start notepad "saida.log"

:fim