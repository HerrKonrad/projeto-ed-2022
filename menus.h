#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED
//#include "menus.c"
#define TAMANHO_NOME 50
#include "BDadosCoupe.h"

BDadosCoupe *BD = NULL;

void iniciarPrograma();
void menuCriar_BDados();
void menuCriar_Tabela();
void menuAdd_Campo_Tabela();
void menuAdd_Valores_Tabela(TABELA *T);
void menuPesquisar_Tabela();
int menuPrincipal();
TABELA * menuSelecionarTabela();
int menuTabelas();



#endif // MENUS_H_INCLUDED
