#include "BDadosCoupe.h"

#include "menus.h"
#define ficheiro_binario "BD.dat"
#define ficheiro_excel "BD.csv"
BDadosCoupe *BD;

void iniciarPrograma()
{

    BD=Ler_nome_versao_BD_bin(ficheiro_binario);
    if (!BD)
        menuCriar_BDados();
    else
        Importar_BDados_Ficheiro_Binario(BD,ficheiro_binario);
}


void menuCriar_BDados()
{

    char nome[TAMANHO_NOME];
    char versao[TAMANHO_NOME];
    printf("\nEscreva o nome da base de dados: ");
    scanf("%s", nome);
    printf("\nEscreva a versao da base de dados: ");
    scanf("%s", versao);
    BD = Criar_BDados(nome,versao);
}

void menuCriar_Tabela()
{
    char nomeBD[TAMANHO_NOME];
    char nomeTabela[TAMANHO_NOME];
    printf("\nEscreva o nome da Tabela: ");
    scanf("%s", nomeTabela);
    Criar_Tabela(BD, nomeTabela);
}
void menuAdd_Campo_Tabela(TABELA *T)
{

    char nomeCampo[TAMANHO_NOME];
    char tipoCampo[TAMANHO_TIPO];
    printf("\nEscreva o nome do Campo: ");
    scanf("%s", nomeCampo);
    printf("\nEscreva o tipo do Campo: ");
    scanf("%s", tipoCampo);
    Add_Campo_Tabela(T, &nomeCampo, &tipoCampo);

}
void menuAdd_Valores_Tabela(TABELA *T)
{


    char dados[1000];
    MostrarLG(T->LCampos, Mostrar_Campo_Simples);

    printf("\n Exemplo: Pedro;123;555-111 \n");
    lerString("Insira os dados:", dados);
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
int menuPrincipal()
{
    int opcaoSair = 0, opcao;
    iniciarPrograma();
    do
    {
        system("cls");
        printf(" _________________________________________________________________________\n");
        printf("|                            MENU PRINCIPAL                               |\n");
        printf("|_________________________________________________________________________|\n");
        printf("\n\t1 - Ver Tabelas existentes\n");
        printf("\t2 - Criar tabela\n");
        printf("\t3 - Importar CSV(Ficheiro Excel)\n");
        printf("\t4 - Exportar Bases de Dados em CSV\n");
        printf("\t5 - Guardar dados\n");
        printf("\t6 - Mostrar infomacao sobre memoria \n");
        printf("\t7 - Sair\n");
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
            menuCriar_Tabela();
            break;
        case 3:
            system("cls");
            if (Importar_BDados_Excel(BD, ficheiro_excel) == 1 )
                printf("\n\n\t\t\tDados importados satisfatoriamente!!");
            else
                printf("\n\n\t\t\tErro ao importar os dados!!");
            teclaParaContinuar();
            break;
        case 4:
            system("cls");
            if (Exportar_BDados_Excel(BD, ficheiro_excel) == 1 )
                printf("\n\n\t\t\tDados exportados satisfatoriamente!!");
            else
                printf("\n\n\t\t\tErro ao exportar os dados!!");
            teclaParaContinuar();
            break;
        case 5:
            system("cls");
            if (Exportar_BDados_Ficheiro_Binario(BD, ficheiro_binario) == 1 )
                printf("\n\n\t\t\tDados guardados satisfatoriamente!!");
            else
                printf("\n\n\t\t\tErro ao guardar os dados!!");
            teclaParaContinuar();
            break;
        case 6:
            system("cls");
            printf("\n tamanho BD: %ld bytes", Memoria_BDados(BD));
            printf("\n tamanho despedicado BD: %ld bytes", Memoria_Desperdicada_BDados(BD));
            teclaParaContinuar();
            break;
        case 7:
            system("cls");
            opcaoSair=1;
             if (Exportar_BDados_Ficheiro_Binario(BD, ficheiro_binario) == 1 )
                printf("\n\n\t\t\tDados guardados satisfatoriamente!!");
            else
                printf("\n\n\t\t\tErro ao guardar os dados!!");

            printf("\n\n\n\t\tObrigado por usar a nossa aplicao!");
            teclaParaContinuar();
            break;
        default:
            system("cls");
            printf("\n\tERRO! Introduza uma opcao valida\n\n");
            teclaParaContinuar();
            break;
        }
    }
    while (!opcaoSair);
    Destruir_BDados(BD);
    return 0;
}

int menuTabelas()
{
    TABELA *T = NULL;
    int opcaoSair = 0;
    int opcao;

    system("cls");
    printf(" _________________________________________________________________________\n");
    printf("|                              MENU TABELAS                               |\n");
    printf("|_________________________________________________________________________|\n");
    T = menuSelecionarTabela();
    if (!T)
    {
        teclaParaContinuar();
        menuTabelas();
    }
        system("cls");
        printf("___________________________________________________________________________");
        printf("\n\n\t1 - Criar tabela\n");
        printf("\t2 - Ver tabela\n");
        printf("\t3 - Apagar tabela\n");
        printf("\t4 - Apagar todo o conteudo da tabela\n");
        printf("\t5 - Procurar valores na tabela\n");
        printf("\t6 - Apagar dados da tabela sob condição\n");
        printf("\t7 - Atualizar Valores\n");
        printf("\t8 - Inserir Dados a tabela\n");
        printf("\t9 - Inserir Campos a tabela\n");
        printf("\t10 - Exportar Tabela Para Excel\n");

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
            Mostrar_Todos_Registos(T);
            teclaParaContinuar();
            break;
        case 3:
            system("cls");
            DROP_TABLE(BD, T->NOME_TABELA);
            opcaoSair = 1;
            break;
        case 4:
            system("cls");
            DELETE_TABLE_DATA(T);
            break;
        case 5:
            system("cls");
            menuProcurarValoresTabela(T);
            break;
        case 6:
            system("cls");
            menuApagarValoresTabela(T);
            break;
        case 7:
            system("cls");
            menuUpdateTabela(T);
            break;
        case 8:
            system("cls");
            menuAdd_Valores_Tabela(T);
            break;
        case 9:
            system("cls");
            menuAdd_Campo_Tabela(T);
            break;
        case 10:
            system("cls");
            Exportar_Tabela_BDados_Excel(BD, T->NOME_TABELA, ficheiro_excel);
            break;
        case 0:
            system("cls");
            opcaoSair = 1;
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

TABELA * menuSelecionarTabela()
{
    int erro=0;
    char nome[TAMANHO_NOME];
    Mostrar_BDados(BD);
    printf("\n___________________________________________________________________________\n");
    lerString("\nEscolha uma das tabelas: ", nome);
    TABELA *T = Pesquisar_Tabela(BD, nome);

    if(T)
        return T;
    else
    {
        printf("\n\n\ttabela nao encontrada!!");
        teclaParaContinuar();

    }




}

void menuProcurarValoresTabela(TABELA *T)
{

    char palavra[5];
    char nome_campo[TAMANHO_NOME];
    char valor[100];
    int qtd_mostrada = 0;
    int opcao;
    lerString("Digite o nome do campo: ", nome_campo);
    lerString("Digite o valor que deseja comparar: ", valor);
    printf("\n____________________________________________________________________");
    printf("\n\n\t1 - Mostrar apenas os iguais ao valor\n");
    printf("\t2 - Mostrar os maiores alfabeticamente ao valor\n");
    printf("\t3 - Mostrar os menores alfabeticamente ao valor\n");
    printf("\t4 - Mostrar os maiores numericamente ao valor\n");
    printf("\t5 - Mostrar os menores numericamente ao valor\n");
    printf("\t6 - Mostrar os que contem o a palavra (ou caracter) do valor\n");
    printf("\n____________________________________________________________________\n");
    opcao = lerInteiro("Digite a opcao que deseja mostrar:");
    switch(opcao)
    {
    case 1:
        system("cls");
        qtd_mostrada = SELECT(BD, T->NOME_TABELA, Condicao_Igual, nome_campo, valor );
        printf("\n___________________________________________________________________________\n");
        printf("Quantidade de linhas mostradas: %d", qtd_mostrada);
        teclaParaContinuar();
        break;

    case 2:
        system("cls");
        qtd_mostrada = SELECT(BD, T->NOME_TABELA, Condicao_Maior, nome_campo, valor );
        printf("\n___________________________________________________________________________\n");
        printf("Quantidade de linhas mostradas: %d", qtd_mostrada);
        teclaParaContinuar();
        break;
    case 3:
        system("cls");
        qtd_mostrada =SELECT(BD, T->NOME_TABELA, Condicao_Menor, nome_campo, valor );
        printf("\n___________________________________________________________________________\n");
        printf("Quantidade de linhas mostradas: %d", qtd_mostrada);
        teclaParaContinuar();
        break;
    case 4:
        system("cls");
        qtd_mostrada =SELECT(BD, T->NOME_TABELA, Condicao_Maior_Numericamente, nome_campo, valor );
        printf("\n___________________________________________________________________________\n");
        printf("Quantidade de linhas mostradas: %d", qtd_mostrada);
        teclaParaContinuar();
        break;
    case 5:
        system("cls");
        qtd_mostrada =SELECT(BD, T->NOME_TABELA, Condicao_Menor_Numericamente, nome_campo, valor );
        printf("\n___________________________________________________________________________\n");
        printf("Quantidade de linhas mostradas: %d", qtd_mostrada);
        teclaParaContinuar();
        break;
    case 6:
        system("cls");
        qtd_mostrada =SELECT(BD, T->NOME_TABELA, Condicao_Contem_Palavra, nome_campo, valor );
        printf("\n___________________________________________________________________________\n");
        printf("Quantidade de linhas mostradas: %d", qtd_mostrada);
        teclaParaContinuar();
        break;

    }
}

void menuApagarValoresTabela(TABELA *T)
{

    char palavra[5];
    char nome_campo[TAMANHO_NOME];
    char valor[100];
    int qtd_mostrada = 0;
    int opcao;
    lerString("Digite o nome do campo: ", nome_campo);
    lerString("Digite o valor que deseja comparar: ", valor);
    printf("\n____________________________________________________________________");
    printf("\n\n\t1 - Apagar apenas os iguais ao valor\n");
    printf("\t2 - Apagar os maiores alfabeticamente ao valor\n");
    printf("\t3 - Apagar os menores alfabeticamente ao valor\n");
    printf("\t4 - Apagar os maiores numericamente ao valor\n");
    printf("\t5 - Apagar os menores numericamente ao valor\n");
    printf("\t6 - Apagar os que contem o a palavra (ou caracter) do valor\n");
    printf("\n____________________________________________________________________\n");
    opcao = lerInteiro("Digite a opcao que deseja apagar:");

    switch(opcao)
    {
    case 1:
        system("cls");
        qtd_mostrada = DELETE(BD, T->NOME_TABELA, Condicao_Igual, nome_campo, valor );
        printf("\n___________________________________________________________________________\n");
        printf("Quantidade de linhas apagadas: %d", qtd_mostrada);
        teclaParaContinuar();
        break;
    case 2:
        system("cls");
        qtd_mostrada = DELETE(BD, T->NOME_TABELA, Condicao_Maior, nome_campo, valor );
        printf("\n___________________________________________________________________________\n");
        printf("Quantidade de linhas apagadas: %d", qtd_mostrada);
        teclaParaContinuar();
        break;
    case 3:
        system("cls");
        qtd_mostrada =DELETE(BD, T->NOME_TABELA, Condicao_Menor, nome_campo, valor );
        printf("\n___________________________________________________________________________\n");
        printf("Quantidade de linhas apagadas: %d", qtd_mostrada);
        teclaParaContinuar();
        break;
    case 4:
        system("cls");
        qtd_mostrada =DELETE(BD, T->NOME_TABELA, Condicao_Maior_Numericamente, nome_campo, valor );
        printf("\n___________________________________________________________________________\n");
        printf("Quantidade de linhas apagadas: %d", qtd_mostrada);
        teclaParaContinuar();
        break;
    case 5:
        system("cls");
        qtd_mostrada =DELETE(BD, T->NOME_TABELA, Condicao_Menor, nome_campo, valor );
        printf("\n___________________________________________________________________________\n");
        printf("Quantidade de linhas apagadas: %d", qtd_mostrada);
        teclaParaContinuar();
        break;
    case 6:
        system("cls");
        qtd_mostrada =DELETE(BD, T->NOME_TABELA, Condicao_Contem_Palavra, nome_campo, valor );
        printf("\n___________________________________________________________________________\n");
        printf("Quantidade de linhas apagadas: %d", qtd_mostrada);
        teclaParaContinuar();
        break;

    }
}
void menuUpdateTabela(TABELA *T)
{


    char nome_campo_comparar[TAMANHO_NOME];
    char valor_comparar[100];
    char nome_campo_update[TAMANHO_NOME];
    char * valor_update = (char*) malloc(sizeof(char) * 100);
    int qtd_mostrada = 0;
    int opcao;
    lerString("Digite o nome do campo para comparar: ", nome_campo_comparar);
    lerString("Digite o valor que deseja comparar: ", valor_comparar);
    lerString("Digite o nome do campo para atualizar: ", nome_campo_update);
    lerString("Digite o valor que deseja atualizar: ", valor_update);
    printf("\n____________________________________________________________________");
    printf("\n\n\t1 - Editar apenas os iguais ao valor\n");
    printf("\t2 - Editar os maiores alfabeticamente ao valor\n");
    printf("\t3 - Editar os menores alfabeticamente ao valor\n");
    printf("\t4 - Editar os maiores numericamente ao valor\n");
    printf("\t5 - Editar os menores numericamente ao valor\n");
    printf("\t6 - Editar os que contem o a palavra (ou caracter) do valor\n");
    printf("\n____________________________________________________________________\n");
    opcao = lerInteiro("Digite a opcao que deseja atualizar:");
    switch(opcao)
    {
    case 1:
        system("cls");
        qtd_mostrada = UPDATE(BD, T->NOME_TABELA, Condicao_Igual,
                              nome_campo_comparar, valor_comparar, nome_campo_update, valor_update);
        printf("\n___________________________________________________________________________\n");
        printf("Quantidade de linhas mostradas: %d", qtd_mostrada);
        teclaParaContinuar();
        break;

    case 2:
        system("cls");
        qtd_mostrada = UPDATE(BD, T->NOME_TABELA, Condicao_Maior,
                              nome_campo_comparar, valor_comparar, nome_campo_update, valor_update);
        printf("\n___________________________________________________________________________\n");
        printf("Quantidade de linhas mostradas: %d", qtd_mostrada);
        teclaParaContinuar();
        break;
    case 3:
        system("cls");
        qtd_mostrada = UPDATE(BD, T->NOME_TABELA, Condicao_Menor,
                              nome_campo_comparar, valor_comparar, nome_campo_update, valor_update);
        printf("\n___________________________________________________________________________\n");
        printf("Quantidade de linhas mostradas: %d", qtd_mostrada);
        teclaParaContinuar();
        break;
    case 4:
        system("cls");
        qtd_mostrada = UPDATE(BD, T->NOME_TABELA, Condicao_Maior_Numericamente,
                              nome_campo_comparar, valor_comparar, nome_campo_update, valor_update);
        printf("\n___________________________________________________________________________\n");
        printf("Quantidade de linhas mostradas: %d", qtd_mostrada);
        teclaParaContinuar();
        break;
    case 5:
        system("cls");
        qtd_mostrada = UPDATE(BD, T->NOME_TABELA, Condicao_Menor_Numericamente,
                              nome_campo_comparar, valor_comparar, nome_campo_update, valor_update);
        printf("\n___________________________________________________________________________\n");
        printf("Quantidade de linhas mostradas: %d", qtd_mostrada);
        teclaParaContinuar();
        break;
    case 6:
        system("cls");
        qtd_mostrada = UPDATE(BD, T->NOME_TABELA, Condicao_Contem_Palavra,
                              nome_campo_comparar, valor_comparar, nome_campo_update, valor_update);
        printf("\n___________________________________________________________________________\n");
        printf("Quantidade de linhas mostradas: %d", qtd_mostrada);
        teclaParaContinuar();
        break;
    }

}
