#include "BDadosCoupe.h"
#define TAMANHO_NOME 50
#include "menus.h"
BDadosCoupe *BD;

// SELECT tabela

// DELETE tabela

// UPDATE tabela

// Exportar Excel

// Importar excel

// Apagar Tabela (DROP TABELA)

// apagar conteudo tabela (DELETE TABLE DATA)



void menuCriar_BDados(){

    char nome[TAMANHO_NOME];
    char versao[TAMANHO_NOME];
    printf("\nEscreva o nome da base de dados: ");
    scanf("%s", &nome);
    printf("\nEscreva a versao da base de dados: ");
    scanf("%s", &versao);
    BD = Criar_BDados(nome,versao);
}

void menuCriar_Tabela(){

    char *nomeBD[TAMANHO_NOME];
    char *nomeTabela[TAMANHO_NOME];
    printf("\nEscreva o nome da Base de dados: ");
    scanf("%s", &nomeBD);
    printf("\nEscreva o nome da Tabela: ");
    scanf("%s", &nomeTabela);
    Criar_Tabela(nomeBD, nomeTabela);
}
void menuAdd_Campo_Tabela(TABELA *T){

    char *nomeCampo[TAMANHO_NOME];
    char *tipoCampo[10];
    printf("\nEscreva o nome do Campo: ");
    scanf("%s", &nomeCampo);
    printf("\nEscreva o tipo do Campo: ");
    scanf("%s", &tipoCampo);
    Add_Campo_Tabela(T, nomeCampo, tipoCampo);

}
void menuAdd_Valores_Tabela(TABELA *T){
    char *dados[300];
    lerString("Insira os dados;", dados);
    // verifica se é valido
    // ...
    if(dados)
    Add_Valores_Tabela(T, dados);
}
