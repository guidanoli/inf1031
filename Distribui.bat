@echo off
REM Copia apenas os arquivos importantes para a distruibui��o na pasta DISTRIBUICAO

if not exist "DISTRIBUICAO" mkdir DISTRIBUICAO
call LimpaDistribuicao.bat
xcopy /s SCRIPTS\* .\DISTRIBUICAO
copy ..\*.exe DISTRIBUICAO