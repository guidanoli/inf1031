REM Copia apenas os arquivos importantes para a distruibuição na pasta DISTRIBUICAO

if not exist DISTRIBUICAO mkdir DISTRIBUICAO

copy RELATORIO*.txt DISTRIBUICAO
copy SOURCE\* DISTRIBUICAO
copy LEIAME.txt DISTRIBUICAO
copy ..\*.exe DISTRIBUICAO
copy SCRIPTS\* DISTRIBUICAO