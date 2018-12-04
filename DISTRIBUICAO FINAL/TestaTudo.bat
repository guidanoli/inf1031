TRAB4-1.EXE /s"TesteVerificaListaSemDeturpacoes.script" >SaidaTesteListaSemDeturp.log
TRAB4-1.EXE /s"TesteVerificaLista.script" >SaidaTesteListaComDeturp.log
TRAB4-2.EXE /s"TesteLista.script" >SaidaTesteListaRelease.log
start notepad "ContadoresListaComDeturp.count"
start notepad "ContadoresListaSemDeturp.count"