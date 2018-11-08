REM Copia apenas os arquivos importantes para a distruibuição na pasta DISTRIBUICAO

if not exist DISTRIBUICAO mkdir DISTRIBUICAO
call LimpaDistribuicao.bat
copy TEXTO\*.txt DISTRIBUICAO
copy SOURCE\* DISTRIBUICAO
xcopy /s SCRIPTS\* .\DISTRIBUICAO
copy SCRIPTS\* DISTRIBUICAO
copy ..\*.exe DISTRIBUICAO