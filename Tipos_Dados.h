#ifndef TIPOS_DADOS_H_INCLUDED
#define TIPOS_DADOS_H_INCLUDED

#include "ListaGenerica.h"
#include "Utils.h"

#define SUCESSO   1
#define INSUCESSO 0
#define  NAO_LISTA "Lista Inexistente"
#define FICH_DEBUG "testes.txt"
#define TAMANHO_NOME 51
#define TAMANHO_TIPO 11

typedef struct
{
    char NOME_BDADOS[TAMANHO_NOME];
    char VERSAO_BDADOS[TAMANHO_NOME];
    ListaGenerica *LTabelas;
}BDadosCoupe;

typedef struct
{
    char NOME_TABELA[TAMANHO_NOME];
    ListaGenerica *LCampos;
    ListaGenerica *LRegistos;
}TABELA;

typedef struct
{
    char NOME_CAMPO[TAMANHO_NOME];
    char TIPO[10];
}CAMPO;

#define REGISTO ListaGenerica

void Destruir_Campo(CAMPO *c);
void Destruir_Tabela(TABELA *tab);
void Mostrar_Campo(CAMPO * campo);
void Gravar_Campo(CAMPO * campo, FILE *F);
void Gravar_Campo_Binario(CAMPO * campo, FILE *F);
void Mostrar_Campo_Simples(CAMPO * campo);
CAMPO *Criar_Campo (char * nome_campo, char * tipo);
int Comparar_Tabelas(TABELA *tab1, TABELA *tab2);
int Comparar_Campos(CAMPO *campo1, CAMPO *campo2);
void Destruir_Dado(char* dado);
void Destruir_Registo(REGISTO *r);
void Mostrar_Dado(char* dado);
CAMPO *Pesquisar_Campo(TABELA *T, char *nome_campo);
REGISTO * Criar_Registo(ListaGenerica * LISTA);
void Mostrar_Registo(REGISTO *r);
void Gravar_Dado(char * dado, FILE *F);
int Gravar_Tabela_TXT(TABELA *T,FILE *F);
void Gravar_Registo(REGISTO *r, FILE *F);





#endif // TIPOS_DADOS_H_INCLUDED
