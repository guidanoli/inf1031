REM Copia apenas os arquivos importantes para a distruibuição na pasta DISTRIBUICAO

if not exist DISTRIBUICAO mkdir DISTRIBUICAO

copy TEXTO\*.txt DISTRIBUICAO
copy SOURCE\* DISTRIBUICAO
copy SCRIPTS\* DISTRIBUICAO
copy ..\*.exe DISTRIBUICAO