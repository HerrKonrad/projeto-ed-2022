#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED
#include "BDadosCoupe.h"

void iniciarPrograma();
void menuCriar_BDados();
void menuCriar_Tabela();
void menuAdd_Campo_Tabela();
void menuAdd_Valores_Tabela(TABELA *T);
void menuPesquisar_Tabela();
int menuPrincipal();
TABELA * menuSelecionarTabela();
int menuTabelas();
void menuApagarValoresTabela(TABELA *T);
void menuProcurarValoresTabela(TABELA *T);
void menuUpdateTabela(T);


#endif // MENUS_H_INCLUDED
