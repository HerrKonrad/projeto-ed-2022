#include "BDadosCoupe.h"
#define TAMANHO_NOME 50
#include "menus.h"
#define ficheiro_binario "BD.dat"
#define ficheiro_excel "BD.csv"




// SELECT tabela

// DELETE tabela

// UPDATE tabela

// Exportar Excel

// Importar excel

// Apagar Tabela (DROP TABELA)

// apagar conteudo tabela (DELETE TABLE DATA)

void iniciarPrograma()
{

    BD = Ler_nome_versao_BD_bin(ficheiro_binario);
    if (!BD)
        menuCriar_BDados();
    else
        Importar_BDados_Ficheiro_Binario(BD,ficheiro_binario);
}


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
    Criar_Tabela(BD, nomeTabela);
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


    char *dados[1000];
    lerString("Insira os dados;", dados);
    // verifica se é valido
    // ...
    if(dados)
    Add_Valores_Tabela(T, dados);
}

void menuPesquisar_Tabela()
{

    char tabela[TAMANHO_NOME];
    lerString("\nQual tabela deseja procurar?:", tabela);
    TABELA *T = Pesquisar_Tabela(BD, tabela);
    if (T == NULL)
    {

        printf("\n\nA tabela %s não existe!!", tabela);

    }
    else
    {

        Mostrar_Tabela(tabela);
        Mostrar_Todos_Registos(tabela);


    }
}
int menuPrincipal(){
    int opcaoInvalida, opcao;
    do
    {
        system("cls");
        printf(" _________________________________________________________________________\n");
        printf("|                            MENU PRINCIPAL                               |\n");
        printf("|_________________________________________________________________________|\n");
        printf("\n\t1 - Tabelas\n");
        printf("\t2 - Importar CSV(Ficheiro Excel)\n");
        printf("\t3 - Exportar Bases de Dados em CSV\n");
        printf("\t4 - Guardar dados\n");
        printf("\t5 - Sair\n");
        printf("\nDigite o numero relativo ao menu a que pretende aceder: ");
        scanf("%d", &opcao);
        printf("\n");
        switch (opcao)
        {
        case 1:
            system("cls");
            menuTabelas();
            break;
        case 2:
            system("cls");

            break;
        case 3:
            system("cls");

            break;
        case 4:
            system("cls");
            printf("\n\n\t\t\tDados guardados satisfatoriamente!!");
            Exportar_BDados_Ficheiro_Binario(BD, ficheiro_binario);
            teclaParaContinuar();
            break;
        case 5:
            system("cls");
            printf("\n\n\n\t\tObrigado por usar a nossa aplicao!");
            Exportar_BDados_Ficheiro_Binario(BD, ficheiro_binario);
            teclaParaContinuar();
            system("exit");
            break;

        default:
            system("cls");
            printf("\n\tERRO! Introduza uma opcao valida\n\n");
            teclaParaContinuar();
            break;
        }
        fseek(stdin, 2, 0);
    } while (opcaoInvalida);
    return 0;
}

int menuTabelas(){
    TABELA *T;
    int opcao;
        system("cls");
        printf(" _________________________________________________________________________\n");
        printf("|                              MENU TABELAS                               |\n");
        printf("|_________________________________________________________________________|\n");
        T = menuSelecionarTabela();
        if (!T){
            teclaParaContinuar();
            menuTabelas();
        }
        printf("___________________________________________________________________________");
        printf("\n\n\t1 - Criar tabela\n");
        printf("\t2 - Ver tabela\n");
        printf("\t3 - Apagar tabela\n");
        printf("\t4 - Apagar todo o conteudo da tabela\n");
        printf("\t5 - Procurar valores na tabela\n");
        printf("\t6 - Apagar dados da tabela sob condição\n");
        printf("\t7 - Atualizar Valores\n");
        printf("\t8 - Inserir Dados a tabela\n");
        printf("\t9 - Exportar Tabela Para Excel\n");
        printf("\t0 - Voltar\n");
        printf("\nDigite o numero relativo ao menu a que pretende aceder: ");
        scanf("%d", &opcao);
        printf("\n");
        switch (opcao)
        {
        case 1:
            system("cls");
            menuCriar_Tabela();
            break;
        case 2:
            system("cls");

            break;
        case 3:
            system("cls");
            DROP_TABLE(BD, T);
            break;
        case 4:
            system("cls");
            DELETE_TABLE_DATA(T);
            break;
        case 5:
            system("cls");
            // menuProcurarValoresTabela();
            break;
        case 6:
            system("cls");

            break;
        case 7:
            system("cls");

            break;
        case 8:
            system("cls");
            menuAdd_Valores_Tabela(T);
            break;
        case 9:
            system("cls");
            Exportar_Tabela_BDados_Excel(BD, T->NOME_TABELA, ficheiro_excel);
            break;
        case 0:
            system("cls");
            menuPrincipal();
            break;

        default:
            system("cls");
            printf("\n\tERRO! Introduza uma opcao valida\n\n");
            teclaParaContinuar();
            break;
        }
        fseek(stdin, 2, 0);
    return 0;
}

TABELA * menuSelecionarTabela(){
    int erro=0;
    char nome[TAMANHO_NOME];
    Mostrar_BDados(BD);
    lerString("\nEscolha uma das tabelas", nome);
    TABELA *T = Pesquisar_Tabela(BD, nome);

    if(T)
        return T;
    else
        printf("\n\n\t\t tabela nao encontrada");



}
/*
void menuProcurarValoresTabela(TABELA *T){

    char palavra[5];
    char nome[TAMANHO_NOME];
    char valor[150];
    lerString("O valor que deseja procurar contem palavra?(S/N): ", palavra);
    SELECT(BD, T->NOME_TABELA, contemPalavra(palavra), nome, valor );

}
*/
