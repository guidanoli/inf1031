REM Copia apenas os arquivos importantes para a distruibuição na pasta DISTRIBUICAO

if not exist DISTRIBUICAO mkdir DISTRIBUICAO
call LimpaDistribuicao.bat
copy SCRIPTS\* DISTRIBUICAO
copy ..\*.exe DISTRIBUICAO