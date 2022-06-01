#ifndef TIPOS_DADOS_H_INCLUDED
#define TIPOS_DADOS_H_INCLUDED

#include "ListaGenerica.h"
#include "utils.h"

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
} BDadosCoupe;

typedef struct
{
    char NOME_TABELA[TAMANHO_NOME];
    ListaGenerica *LCampos;
    ListaGenerica *LRegistos;
} TABELA;

typedef struct
{
    char NOME_CAMPO[TAMANHO_NOME];
    char TIPO[10];
} CAMPO;

#define REGISTO ListaGenerica

void Destruir_Campo(void *c);
void Destruir_Tabela(void *tab);
void Mostrar_Campo(CAMPO * campo);
void Mostrar_Campo_Simples(CAMPO * campo);
CAMPO *Criar_Campo (char * nome_campo, char * tipo);

int Comparar_Tabelas(void *tab1, void *tab2);
int Comparar_Campos(CAMPO *campo1, CAMPO *campo2);
int Compara_Dado(char * dado1, char * dado2);
int Compara_Registo(REGISTO * reg1, REGISTO * reg2);


void Destruir_Dado(void* dado);
void Destruir_Registo(void *r);
void Mostrar_Dado(char* dado);
CAMPO *Pesquisar_Campo(TABELA *T, char *nome_campo);
REGISTO * Criar_Registo(ListaGenerica * LISTA);
void Mostrar_Registo(REGISTO *r);

void Gravar_Dado(char * dado, FILE *F);
void Gravar_Registo(REGISTO *r, FILE *F);
void Gravar_Campo(CAMPO * campo, FILE *F);
int Gravar_Tabela_TXT(TABELA *T,FILE *F);

void Gravar_Dado_Binario(char * dado, FILE *F);
void Gravar_Registo_Binario(REGISTO *r, FILE *F);
void Gravar_Campo_Binario(CAMPO * campo, FILE *F);
int Gravar_Tabela_Binario(TABELA *T,FILE *F);
void  Ler_Valores_Tabela(FILE *F, TABELA *T);

TABELA *Ler_Nome_Tabela(BDadosCoupe *BD,FILE *F);

int Ler_Tabela_Binario(TABELA *T,FILE *F);
void Ler_Campo_Binario(CAMPO * campo, FILE *F);

long Obter_Tamanho_Memoria_Tabela(void *T);
long Obter_Tamanho_Memoria_Campo(void *C);
long Obter_Tamanho_Memoria_Registo(void *R);
long Obter_Tamanho_Memoria_Dado(void *D);
long Obter_Tamanho_Desperdicado_Memoria_Campo(void *C);
long Obter_Tamanho_Desperdicado_Memoria_Tabela(void *T);






#endif // TIPOS_DADOS_H_INCLUDED
