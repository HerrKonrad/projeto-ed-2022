
#include "BDadosCoupe.h"

/** \brief Criar_BDados: A) Criar a Base de dados
 *
 * \param nome_bd char* : Nome da Base de Dados
 * \param versao char*  : Versão da Base de Dados
 * \return BDadosCoupe* : Ponteiro para a Base de Dados Criada
 *
 */
BDadosCoupe *Criar_BDados(char *nome_bd, char *versao)
{
    BDadosCoupe *BD = (BDadosCoupe *)malloc(sizeof(BDadosCoupe));
    strcpy(BD->NOME_BDADOS, nome_bd);
    strcpy(BD->VERSAO_BDADOS, versao);
    BD->LTabelas = CriarLG();
    return BD;
}

/** \brief B) Criar uma Tabela na Base de Dados,
 * a tabela deve ser inserida à lista de tabelas da BD
 *
 * \param BD BDadosCoupe* : Ponteiro para a Base de Dados
 * \param nome_tabela char* : Nome da tabela a Criar
 * \return TABELA*        : Retorna a Tabela Criada
 * \author                : CS, FM & JL
 */
TABELA *Criar_Tabela(BDadosCoupe *BD, char *nome_tabela)
{
    TABELA *T = (TABELA *)malloc(sizeof(TABELA));
    strcpy(T->NOME_TABELA, nome_tabela);
    T->LCampos = CriarLG();
    T->LRegistos = CriarLG();

    AddLG(BD->LTabelas, T);
    return T;
}
/** \brief C)  Adicionar um campo a uma tabela.
 *
 * \param T TABELA* : Ponteiro para a tabela
 * \param nome_campo char* : Nome do campo
 * \param tipo_campo char* : Tipo do Campo (INT, STRING, CHAR, FLOAT)
 * \return int             : SUCESSO/INSUCESSO
 * \author                 : CS, FM & JL              :
 * \version                : Versao 1.0
 * \date                   : 23/04/2022
 */
int Add_Campo_Tabela(TABELA *T, char *nome_campo, char *tipo_campo)
{
    CAMPO *C = (CAMPO *)malloc(sizeof(CAMPO));
    if (!C) return INSUCESSO;
    strcpy(C->NOME_CAMPO, nome_campo);
    strcpy(C->TIPO, tipo_campo);
    int res = AddFimLG(T->LCampos, C);
    return res;
}

/** \brief D)    Adicionar dados(registos) a uma tabela, os dados são dados numa string onde o separador é ‘;’m ex: Add_Valores_Tabela(T, “123;Joao;965654449”)
 *
 * \param  TABELA *T  : Ponteiro para a tabela
 * \param char *dados : Os dados seprados por ";"
 * \return int        : SUCESSO/INSUCESSO
 *
 */
int Add_Valores_Tabela(TABELA *T, char *dados)
{
    if(!T) return INSUCESSO;

    char *str = (char*) malloc(sizeof(char)*strlen(dados)+1);
    REGISTO * reg = CriarLG();
    int cont=0;
    int numero_campos=T->LCampos->NEL;
    int sem_erro = 1;
    strcpy(str,dados);
    char *token=strtok(str, ";");
    char *temp = NULL;
    if(numero_campos <= 0) return INSUCESSO; // caso a tabela nao tenha campos

    while( token != NULL && numero_campos>cont)
    {
        temp = (char*) malloc(sizeof(char)*strlen(token)+1);
        strcpy(temp,token);
        sem_erro = AddFimLG(reg, temp);
        if(!sem_erro) return INSUCESSO;
        token = strtok(NULL, ";");
        cont++;
    }
    AddFimLG(T->LRegistos, reg);
    free(str);

    //MostrarLG(T->LRegistos,Mostrar_Dado);
    return SUCESSO;
}


//E)	Adicionar dados(registos) a uma tabela, os dados são dados numa string onde o separador é ‘;’
int Add_Valores_Tabela_BDados(BDadosCoupe *BD, char *nome_tabela, char *dados)
{
    TABELA *T = Pesquisar_Tabela(BD, nome_tabela);
    int res = Add_Valores_Tabela(T, dados);
    return res;
}
//F)	Pesquisar uma Tabela da base de dados
TABELA *Pesquisar_Tabela(BDadosCoupe *BD, char *nome_tabela)
{
    TABELA * tab = (TABELA*) malloc(sizeof(TABELA));
    strcpy(tab->NOME_TABELA, nome_tabela);

    NOG * nogtemp = PesquisarElemento(BD->LTabelas, tab, Comparar_Tabelas);
    if(nogtemp)
    {

        return nogtemp->Info;
    }
    else
    {

        return NULL;
    }
}


//G)	Mostrar uma Tabela
void Mostrar_Tabela_NOME(BDadosCoupe *BD, char *tabela)
{
    if(!BD) return;
    Mostrar_Tabela(Pesquisar_Tabela(BD, tabela));
}
/** \brief Mostra a info pertinente a uma tabela, neste caso apenas o nome da tabela
 *
 * \param T TABELA*
 * \return void
 *
 */
void Mostrar_Tabela(TABELA *T)
{
    if(!T)
    {
        debugTxt("Tabela inexistente", FICH_DEBUG);
        return;
    }

    printf("\n Nome da tabela: %s", T->NOME_TABELA);

}

/** \brief Mostrar toda a base de dados, deverá mostrar todas as Tabelas da BDados.
 *
 * \param BD BDadosCoupe*
 * \return void
 *
 */
void Mostrar_BDados(BDadosCoupe *BD)
{
    if(!BD)
    {
        debugTxt("Base de dados inexistente", FICH_DEBUG);
        return;
    }
    if(!BD->LTabelas)
    {
        debugTxt("Nao existem listas", FICH_DEBUG);
        return;
    }
    MostrarLG(BD->LTabelas, Mostrar_Tabela);
}

/** \brief Libertar toda a memória alocada pela base de dados.
 *
 * \param BD BDadosCoupe*
 * \return void
 *
 */
void Destruir_BDados(BDadosCoupe *BD)
{
    if(!BD) return;
    DestruirLG(BD->LTabelas, Destruir_Tabela);
    free(BD);
}
//J)	Memória ocupada por toda a base de dados.
long int Memoria_BDados(BDadosCoupe *BD)
{


    return -1;
}
long int Memoria_Desperdicada_BDados(BDadosCoupe *BD)
{
    return -1;
}

/** \brief K)Exportar/Importar para/de Ficheiro (o retorno destas funções, permite saber se a função foi bem/mal-executada!):
 *
 * \param BD BDadosCoupe*
 * \param tabela char*
 * \param ficheir_csv char*
 * \return int
 *
 */
int Exportar_Tabela_BDados_Excel(BDadosCoupe *BD, char *tabela, char *ficheir_csv)
{
    if(!BD || !tabela || !ficheir_csv) return INSUCESSO;

    FILE *F = fopen(ficheir_csv, "w+");


    if(!F) return INSUCESSO; // caso o ficheiro nao consiga ser criado



    TABELA * T = Pesquisar_Tabela(BD, tabela); // procura a tabela na base de dados
    if(!T) return INSUCESSO; // caso nao ache a tabela

    GravarFicheiroTXTLG(T->LCampos,Gravar_Campo,F); // Gravar em um ficheiro excel (csv) nada difere de um txt, os ; são separadores
    fprintf(F,"\n "); // Vai para proxima linha de um ficheiro excel (csv)
    GravarFicheiroTXTLG(T->LRegistos,Gravar_Registo,F);
    return SUCESSO;
}
int Exportar_BDados_Excel(BDadosCoupe *BD, char *ficheir_csv)
{
    return SUCESSO;
}
int Importar_BDados_Excel(BDadosCoupe *BD, char *ficheir_csv)
{
    return SUCESSO;
}
int Exportar_BDados_Ficheiro_Binario(BDadosCoupe *BD, char *fich_dat)
{
    return SUCESSO;
}
int Importar_BDados_Ficheiro_Binario(BDadosCoupe *BD, char *fich_dat)
{

    return SUCESSO;
}

/** \brief Apagar o conteúdo de uma Tabela. A Tabela continua a existir na BDados, mas não contém os dados, ou seja, os campos continuam, mas os registos são eliminados.
 *
 * \param T TABELA*
 * \return int
 *
 */
int DELETE_TABLE_DATA(TABELA *T)
{
    if(!T || !T->LRegistos) return INSUCESSO;
    DestruirLG(T->LRegistos, Destruir_Registo);
    return SUCESSO;
}

/** \brief M)    Apagar o conteúdo de uma Tabela e remove a tabela da base de dados.
 *
 * \param BDadosCoupe *BD
 * \param  char *nome_tabela
 * \return int             : SUCESSO/INSUCESSO
 *
 */

int DROP_TABLE(BDadosCoupe *BD, char *nome_tabela)
{
    if(!BD) return INSUCESSO;

    TABELA *T = Pesquisar_Tabela(BD,nome_tabela);
    if(T)
    {
        RemoverElementoLG(BD->LTabelas,T,Destruir_Tabela,Comparar_Tabelas);
        return SUCESSO;
    }
    else
    {
        return INSUCESSO;
    }
}

//
/** \brief N)	Selecionar (Apresentar no ecran!) da base de dados todos os registos que obedeçam a uma dada condição,
 *a função deve retornar o número de registos selecionados. (Ter em atenção o exemplo das aulas teóricas!). Nota: esta é certamente a
 *funcionalidade mais usada num sistema de base de dados…, por isso se estiver bem otimizada…. O utilizador agradece!!!!
 *
 * \param  char*
 * \param  char*
 * \return int SELECT(BDadosCoupe *BD, char *_tabela, int
 *
 */
int SELECT(BDadosCoupe *BD, char *_tabela, int (*f_condicao)(char *, char *), char *nome_campo, char *valor_comparacao)
{
    return SUCESSO;
}

/** \brief O)	Remover todos os registos que obedeçam a uma dada condição, a função deve retornar o número de registos removidos.
 *
 * \param  char*
 * \param  char*
 * \return int DELETE(BDadosCoupe *BD, char *_tabela, int
 *
 */
int DELETE(BDadosCoupe *BD, char *_tabela, int (*f_condicao)(char *, char *), char *nome_campo, char *valor_comparacao)
{

    return SUCESSO;
}
//P)	Atualizar todos os registos da tabela onde o Campo é dado, que obedeçam a uma dada condição, a função deve retornar o número de registos que foram atualizados.
int UPDATE(BDadosCoupe *BD, char *_tabela, int (*f_condicao)(char *, char *), char *campo_comp, char *valor_campo_comp, char *nome_campo_update, char *valor_campo_update)
{
    return SUCESSO;
}

/** \brief Uma função para sempre retonar verdadeiro na condição de comprar duas infos
 *
 * \param info1 void*
 * \param info2 void*
 * \return int
 *
 */
int Condicao_Todos(void * info1, void *info2)
{
    if(!info1 || !info2) return INSUCESSO;
    return SUCESSO;
}

/** \brief Função nao parte da biblioteca, remover se necessário! MOSTRA TODOS OS REGISTOS DE UMA TABELA
 *
 * \param T TABELA*
 * \return int
 *
 */
int Mostrar_Todos_Registos(TABELA *T)
{
    if(!T) return INSUCESSO;

    Mostrar_Tabela(T);
    printf("\n\tCAMPOS: ");
    MostrarLG(T->LCampos, Mostrar_Campo_Simples);
    printf("\n");
    MostrarLG(T->LRegistos, Mostrar_Registo);
    return SUCESSO;
}

int Gravar_Todos_Registos(TABELA *T)
{

    return INSUCESSO;
}

/** \brief Mostra toda a base de dados, as tabelas e seus respectivos TODOS registos
 *
 * \param BD BDadosCoupe*
 * \return int
 *
 */
int Mostrar_BDados_toda(BDadosCoupe *BD)
{

    if(!BD) return INSUCESSO;

    printf("[%s]-[%s]",BD->NOME_BDADOS,BD->VERSAO_BDADOS);

    ListaGenerica *L=BD->LTabelas;
    NOG *P = L->Inicio;

    while(P)
    {
        TABELA *T=P->Info;
        Mostrar_Todos_Registos(T);

        P=P->Prox;
    }
    return SUCESSO;
}

/** \brief Exportar_BDados_Ficheiro_Texto É UMA FUNCAO EXTRA
 *
 * \param BDadosCoupe *BD
 * \param  char *fich_dat
 * \return int        : SUCESSO/INSUCESSO
 *
 */

int Exportar_BDados_Ficheiro_Texto(BDadosCoupe *BD, char *fich_dat)
{
    if(!BD || !fich_dat) return INSUCESSO;

    FILE *F=fopen(fich_dat,"w");

    if(!F) return INSUCESSO; // Caso o ficheiro não consiga ser aberto

    fprintf(F,"[%s]-[%s]\n",BD->NOME_BDADOS,BD->VERSAO_BDADOS);


    ListaGenerica *L=BD->LTabelas;

    NOG *P = L->Inicio;

    while(P)
    {
        TABELA *T=P->Info;
        Gravar_Tabela_TXT(T,F);

        P=P->Prox;
        fprintf(F,"\n");
    }

    fclose(F);
    return SUCESSO;
}
