REM Copia apenas os arquivos importantes para a distruibuição na pasta DISTRIBUICAO

@echo off
if not exist "DISTRIBUICAO" mkdir DISTRIBUICAO
call LimpaDistribuicao.bat
xcopy /s SCRIPTS\* .\DISTRIBUICAO
copy ..\*.exe DISTRIBUICAO