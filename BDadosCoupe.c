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
    clock_t exe;
    exe = clock();
    BDadosCoupe *BD = (BDadosCoupe *)malloc(sizeof(BDadosCoupe));
    strcpy(BD->NOME_BDADOS, nome_bd);
    strcpy(BD->VERSAO_BDADOS, versao);
    BD->LTabelas = CriarLG();
    exe = clock() - exe;
    double tempo = ((double)exe)/CLOCKS_PER_SEC;
    FILE *f1 = fopen("estatisticas.csv", "a");
    fprintf(f1,"%s;%.3f\n",__func__,tempo);
    fclose(f1);
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
    free(token);
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
    clock_t exe;
    exe = clock();
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
    exe = clock() - exe;
    double tempo = ((double)exe)/CLOCKS_PER_SEC;
    FILE *f1 = fopen("estatisticas.csv", "a");
    fprintf(f1,"%s;%.3f\n",__func__,tempo);
    fclose(f1);
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

    if(!T || !T->NOME_TABELA)
    {
        debugTxt("Tabela inexistente", FICH_DEBUG);
        return;
    }

    printf("\n Nome da tabela: |%s|", T->NOME_TABELA);

}

/** \brief Mostrar toda a base de dados, deverá mostrar todas as Tabelas da BDados.
 *
 * \param BD BDadosCoupe*
 * \return void
 *
 */
void Mostrar_BDados(BDadosCoupe *BD)
{
    clock_t exe;
    exe = clock();
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
    exe = clock() - exe;
    double tempo = ((double)exe)/CLOCKS_PER_SEC;
    FILE *f1 = fopen("estatisticas.csv", "a");
    fprintf(f1,"%s;%.3f\n",__func__,tempo);
    fclose(f1);
}

/** \brief Libertar toda a memória alocada pela base de dados.
 *
 * \param BD BDadosCoupe*
 * \return void
 *
 */

// TODO: ARRUMAR
void Destruir_BDados(BDadosCoupe *BD)
{
    if(!BD) return;
    clock_t exe;
    exe = clock();
    DestruirLG(BD->LTabelas, Destruir_Tabela);
    free(BD);

    exe = clock() - exe;
    double tempo = ((double)exe)/CLOCKS_PER_SEC;
    FILE *f1 = fopen("estatisticas.csv", "a");
    fprintf(f1,"%s;%.3f\n",__func__,tempo);
    fclose(f1);
}
//J)	Memória ocupada por toda a base de dados.
long int Memoria_BDados(BDadosCoupe *BD)
{
    if(!BD) return INSUCESSO;
    return CalcularTamanhoMemoriaLG(BD->LTabelas, Obter_Tamanho_Memoria_Tabela);
}

long int Memoria_Desperdicada_BDados(BDadosCoupe *BD)
{
    if(!BD) return 0;
    return CalcularTamanhoMemoriaLG(BD->LTabelas, Obter_Tamanho_Desperdicado_Memoria_Tabela);
}

/** \brief K)	Exportar/Importar para/de Ficheiro (o retorno destas funções, permite saber se a função foi bem/mal-executada!):
 *
 * \param BD BDadosCoupe*
 * \param tabela char*
 * \param ficheir_csv char*
 * \return int
 *
 */
int Exportar_Tabela_BDados_Excel(BDadosCoupe *BD, char *tabela, char *ficheir_csv)
{
    clock_t exe;
    exe = clock();
    if(!BD || !tabela || !ficheir_csv) return INSUCESSO;

    FILE *F = fopen(ficheir_csv, "w+");

    if(!F) return INSUCESSO; // caso o ficheiro nao consiga ser criado

    TABELA * T = Pesquisar_Tabela(BD, tabela); // procura a tabela na base de dados
    if(!T) return INSUCESSO; // caso nao ache a tabela

    GravarFicheiroTXTLG(T->LCampos,Gravar_Campo,F); // Gravar em um ficheiro excel (csv) nada difere de um txt, os , ou ; são separadores
    fprintf(F,"\n "); // Vai para proxima linha de um ficheiro excel (csv)
    GravarFicheiroTXTLG(T->LRegistos,Gravar_Registo,F);
    exe = clock() - exe;
    double tempo = ((double)exe)/CLOCKS_PER_SEC;
    FILE *f1 = fopen("estatisticas.csv", "a");
    fprintf(f1,"%s;%.3f\n",__func__,tempo);
    fclose(f1);
    return SUCESSO;

}
/** \brief Exportar_BDados_Excel
 *
 * \param BDadosCoupe *BD
 * \param char *ficheir_csv
 * \return int
 *
 */

int Exportar_BDados_Excel(BDadosCoupe *BD, char *ficheir_csv)
{
    if(!BD || !ficheir_csv) return INSUCESSO;

       clock_t exe;
      exe = clock();

    FILE *F=fopen(ficheir_csv,"w");
    rewind(F);
    // fprintf(F,"%s;%s\n",BD->NOME_BDADOS,BD->VERSAO_BDADOS);

    ListaGenerica *L=BD->LTabelas;

    NOG *P = L->Inicio;

    while(P)
    {
        TABELA *T=P->Info;
        Gravar_Tabela_TXT(T,F);

        P=P->Prox;
        fprintf(F,"###\n"); // Delimita o fim de uma tabela
    }
    fprintf(F,"---\n"); // Delimita o fim da BD
    fclose(F);
    exe = clock() - exe;
    double tempo = ((double)exe)/CLOCKS_PER_SEC;
    FILE *f1 = fopen("estatisticas.csv", "a");
    fprintf(f1,"%s;%.3f\n",__func__,tempo);
    fclose(f1);
    return SUCESSO;
}
/** \brief Importar_BDados_Excel
 *
 * \param BD BDadosCoupe*
 * \param ficheir_csv char*
 * \return int
 *
 */
int Importar_BDados_Excel(BDadosCoupe *BD, char *ficheir_csv)
{
    if(!ficheir_csv) return INSUCESSO;
    FILE *F = fopen(ficheir_csv, "r");
    rewind(F);

    if(!F) return INSUCESSO;

    int ACABAR = 0;

    while(!ACABAR)
    {
        TABELA *T = Ler_Nome_Tabela(BD,F);
        if(T)
        {
            Ler_Campo_Tabela(F,T);
            Ler_Valores_Tabela(F,T);
        }
        else
        {

            ACABAR = 1;
        }
    }
    fclose(F);
    return SUCESSO;
}
int Exportar_BDados_Ficheiro_Binario(BDadosCoupe *BD, char *fich_dat)
{
    if(!BD || !fich_dat) return INSUCESSO;
    FILE *F = fopen(fich_dat, "wb");

    if(!F)return INSUCESSO;

    clock_t exe;
    exe = clock();

    //nome BD
    char *s_nome_BD = (char*) malloc(sizeof(char) * strlen(BD->NOME_BDADOS) + 1);
    strcpy(s_nome_BD, BD->NOME_BDADOS);
    int N_nome_BD = strlen(s_nome_BD);
    fwrite(&N_nome_BD, sizeof(int), 1, F);
    fwrite(s_nome_BD, sizeof(char), N_nome_BD, F);
    free(s_nome_BD);
    //versao BD
    char *s_versao_BD = (char*) malloc(sizeof(char) * strlen(BD->VERSAO_BDADOS) + 1);
    strcpy(s_versao_BD, BD->VERSAO_BDADOS);
    int N_versao_BD = strlen(s_versao_BD);
    fwrite(&N_versao_BD, sizeof(int), 1, F);
    fwrite(s_versao_BD, sizeof(char), N_versao_BD, F);
    free(s_versao_BD);

    ListaGenerica *L=BD->LTabelas;

    fwrite(&(L->NEL), sizeof(int), 1, F);//Quantas tabelas

    NOG *P = L->Inicio;

    while(P)
    {
        TABELA *T=P->Info;
        // TODO: ARRUMAR
        //nome tabela
        char s_nome_tabela[51];
        strncpy(s_nome_tabela, T->NOME_TABELA, 51);
        int N_nome_tabela = strlen(s_nome_tabela);
        fwrite(&N_nome_tabela, sizeof(int), 1, F);
        fwrite(s_nome_tabela, sizeof(char), N_nome_tabela, F);
        Gravar_Tabela_Binario(T,F);

        P=P->Prox;
    }


    fclose(F);
    exe = clock() - exe;
    double tempo = ((double)exe)/CLOCKS_PER_SEC;
    FILE *f1 = fopen("estatisticas.csv", "a");
    fprintf(f1,"%s;%.3f\n",__func__,tempo);
    fclose(f1);
    return SUCESSO;
}


int Importar_BDados_Ficheiro_Binario(BDadosCoupe *BD, char *fich_dat)
{
    FILE *F = fopen(fich_dat, "rb");
    if(!F)return INSUCESSO;

    int bytes_nome_versao_bd=sizeof(int)+(strlen(BD->NOME_BDADOS) * sizeof(char))+sizeof(int)+(strlen(BD->VERSAO_BDADOS)*sizeof(char)); // para saber onde o ponteiro esta depois de ler o nome e a versao da bd

    fseek(F,bytes_nome_versao_bd,SEEK_SET);

    ListaGenerica *L=BD->LTabelas;

    fread(&L->NEL, sizeof(int), 1, F);
    int numero_tabelas=L->NEL;
    TABELA *T;

    for(int i=0; i<numero_tabelas; i++)
    {
        int N_tabela;
        fread(&N_tabela, sizeof(int), 1, F);
        char *s_tabela = (char*) malloc(sizeof(char) * N_tabela);
        fread(s_tabela, sizeof(char), N_tabela, F);
        s_tabela[N_tabela]='\0';
        T = Criar_Tabela(BD,s_tabela);
        Ler_Tabela_Binario(T,F);
        free(s_tabela);
    }
    fclose(F);
    return SUCESSO;
}


/** \brief Exportar_BDados_Ficheiro_Texto É UMA FUNCAO EXTRA
 *
 * \param BDadosCoupe *BD
 * \param  char *fich_dat
 * \return int        : SUCESSO/INSUCESSO
 *
 */

int Exportar_BDados_Ficheiro_Texto(BDadosCoupe *BD, char *fich_text)
{
    clock_t exe;
    exe = clock();
    if(!BD || !fich_text) return INSUCESSO;

    FILE *F=fopen(fich_text,"w");

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
    exe = clock() - exe;
    double tempo = ((double)exe)/CLOCKS_PER_SEC;
    FILE *f1 = fopen("estatisticas.csv", "a");
    fprintf(f1,"%s;%.3f\n",__func__,tempo);
    fclose(f1);
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
    clock_t exe;
    exe = clock();
    if(!T || !T->LRegistos) return INSUCESSO;
    DestruirLG(T->LRegistos, Destruir_Registo);
    T->LRegistos = NULL;
    exe = clock() - exe;
    double tempo = ((double)exe)/CLOCKS_PER_SEC;
    FILE *f1 = fopen("estatisticas.csv", "a");
    fprintf(f1,"%s;%.3f\n",__func__,tempo);
    fclose(f1);
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
    clock_t exe;
    exe = clock();
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
    exe = clock() - exe;
    double tempo = ((double)exe)/CLOCKS_PER_SEC;
    FILE *f1 = fopen("estatisticas.csv", "a");
    fprintf(f1,"%s;%.3f\n",__func__,tempo);
    fclose(f1);
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

// TODO: AJUSTAR O CASO DE NÃO ENCONTRAR DADOS
int SELECT(BDadosCoupe *BD, char *_tabela, int (*f_condicao)(char *, char *), char *nome_campo, char *valor_comparacao)
{
    if(!BD || !_tabela || !nome_campo || !valor_comparacao) return INSUCESSO;
    clock_t exe;
    exe = clock();



    // 1º Verificar se a tabela passada existe
    TABELA * T = Pesquisar_Tabela(BD, _tabela);

    // Caso a tabela indicada não exista retorna insucesso
    if( !T ) return INSUCESSO;

    // 2º Verificar se o campo passado existe na tabela

    CAMPO * C = Pesquisar_Campo(T, nome_campo);

    // 3º Caso o campo indicado não exista na tabel,a retorna insucesso
    if( !C ) return INSUCESSO;

    // 4º Tabela e campo OK, passamos as variaveis que utilizaremos

    ListaGenerica * Campos = T->LCampos;
    ListaGenerica * Registos = T->LRegistos;
    int POS_CAMPO = ObterPosicaoElementoLG(Campos, C, Comparar_Campos); // a posicao do campo

    // Percorremos todos os registos e verificaremos o dado relativo ao campo está de acordo com a condição, caso sim, apaga o registo

    NOG * elem = Registos->Inicio;

    int SATISFAZ = INSUCESSO;

    // Mostrar na tela os campo
    MostrarLG(Campos, Mostrar_Campo);
    printf("\n");
    while(elem)
    {
        NOG * achado = ObterElementoDaPosicao(elem->Info, POS_CAMPO);

        if(achado) // caso tenha encontra um dado no respectivo campo
        {
            char * dado = achado->Info;
            SATISFAZ = f_condicao(dado, valor_comparacao);

            if(SATISFAZ) // caso o dado satisfaça a condição proposta
            {
                REGISTO * reg_atual = elem->Info;
                Mostrar_Registo(reg_atual);
            }
        }
        elem = elem->Prox;
    }

    exe = clock() - exe;
    double tempo = ((double)exe)/CLOCKS_PER_SEC;
    FILE *f1 =  fopen("estatisticas.csv", "a+");
    fprintf(f1, "%s;%.3f\n",__func__,tempo);
    fclose(f1);
    return SUCESSO;
}

/** \brief O)	Remover todos os registos que obedeçam a uma dada condição, a função deve retornar o número de registos removidos.
 *
 * \param  char*
 * \param  char*
 * \return int : INSUCESSO caso não seja possível deletar, caso contrário o numero de elementos deletados
 *
 */

// TODO: AJUSTAR
int DELETE(BDadosCoupe *BD, char *_tabela, int (*f_condicao)(char *, char *), char *nome_campo, char *valor_comparacao)
{
    clock_t exe;
    exe = clock();
    // Verificacoes de segurança usuais
    if(!BD || !_tabela || !nome_campo || !valor_comparacao) return INSUCESSO;

    // 1º Verificar se a tabela passada existe
    TABELA * T = Pesquisar_Tabela(BD, _tabela);

    // Caso a tabela indicada não exista retorna insucesso
    if( !T ) return INSUCESSO;

    // 2º Verificar se o campo passado existe na tabela

    CAMPO * C = Pesquisar_Campo(T, nome_campo);

    // 3º Caso o campo indicado não exista na tabel,a retorna insucesso
    if( !C ) return INSUCESSO;

    // 4º Tabela e campo OK, passamos as variaveis que utilizaremos

    ListaGenerica * Campos = T->LCampos;
    ListaGenerica * Registos = T->LRegistos;
    int POS_CAMPO = ObterPosicaoElementoLG(Campos, C, Comparar_Campos); // a posicao do campo

    // Percorremos todos os registos e verificaremos o dado relativo ao campo está de acordo com a condição, caso sim, apaga o registo

    NOG * elem = NULL;
    NOG * anterior = Registos->Inicio;
    elem = anterior;

    int SATISFAZ = INSUCESSO;
    int EXCLUIDOS = 0;

    // verifica pro primeiro elemento

    NOG * PRIMEIRO = ObterElementoDaPosicao(anterior->Info, POS_CAMPO);

    // verifica o caso o primeiro necessita ser deletado

    if(f_condicao(PRIMEIRO->Info, valor_comparacao))
    {
        RemoverPrimeiroLG(Registos, Destruir_Registo);
        anterior = Registos->Inicio; // atualiza o novo inicio
    }

    elem = anterior;

    while(anterior->Prox)
    {
        elem = anterior->Prox;

        NOG * achado = ObterElementoDaPosicao(elem->Info, POS_CAMPO);


        if(achado) // caso tenha encontra um dado no respectivo campo
        {
            char * dado = achado->Info;
            SATISFAZ = f_condicao(dado, valor_comparacao);

            if(SATISFAZ) // caso o dado satisfaça a condição proposta
            {
                // TODO: RESOLVER

                // caso seja o primeiro
                if(Compara_Registo(anterior->Info, Registos->Inicio->Info))
                {
                    //   Registos->Inicio = anterior->Prox;
                    //  Destruir_Registo(anterior->Info);

                }
                EXCLUIDOS++;
                anterior->Prox = elem->Prox;
                if(!elem->Prox) // caso seja o ultimo
                {
                    Registos->Fim = anterior;
                }
                Destruir_Registo(elem);
                // free(elem->Info);
                //free(elem);
                continue;
            }
        }

        anterior = anterior->Prox;
    }
    exe = clock() - exe;
    double tempo = ((double)exe)/CLOCKS_PER_SEC;
    FILE *f1 =  fopen("estatisticas.csv", "a+");
    fprintf(f1, "%s;%.3f\n",__func__,tempo);
    fclose(f1);
    return EXCLUIDOS;
}

/** \brief P)	Atualizar todos os registos da tabela onde o Campo é dado,
 * que obedeçam a uma dada condição, a função deve retornar o número de registos que foram atualizados.
 *
 * \param  char*
 * \param  char*
 * \return int :  INSUCESSO caso não seja possível atualizar, caso contrário o numero de elementos atualizados
 *
 */
int UPDATE(BDadosCoupe *BD, char *_tabela, int (*f_condicao)(char *, char *),
           char *campo_comp, char *valor_campo_comp, char *nome_campo_update, char *valor_campo_update)
{
    clock_t exe;
    exe = clock();
    if(!BD || !_tabela || !campo_comp || !valor_campo_comp || !nome_campo_update
            || !valor_campo_update) return INSUCESSO;

    int atualizados = 0;


    // 1º Verificar se a tabela passada existe
    TABELA * T = Pesquisar_Tabela(BD, _tabela);

    // Caso a tabela indicada não exista retorna insucesso
    if( !T ) return INSUCESSO;

    // 2º Verificar se ambos os campos passados existem na tabela

    CAMPO * C = Pesquisar_Campo(T, campo_comp); // o campo onde está o valor que queremos procurar
    CAMPO * ATT = Pesquisar_Campo(T, nome_campo_update); // o campo que atualizeremos


    // 3º Caso os campos indicados não existam na tabela, retorna insucesso
    if( !C  || !ATT ) return INSUCESSO;

    // 4º Tabela e campo OK, passamos as variaveis que utilizaremos

    ListaGenerica * Campos = T->LCampos;
    ListaGenerica * Registos = T->LRegistos;
    int POS_CAMPO = ObterPosicaoElementoLG(Campos, C, Comparar_Campos); // a posicao do campo que queremos procurar o dado
    int POS_CAMPO_ATT = ObterPosicaoElementoLG(Campos, ATT, Comparar_Campos); // a posicao do campo que queremos atualizar

    // Percorremos todos os registos e verificaremos o dado relativo ao campo está de acordo com a condição, caso sim, apaga o registo

    NOG * elem = Registos->Inicio;

    int SATISFAZ = INSUCESSO;

    while(elem)
    {
        NOG * achado = ObterElementoDaPosicao(elem->Info, POS_CAMPO);

        if(achado) // caso tenha encontra um dado no respectivo campo
        {
            char * dado = achado->Info;
            SATISFAZ = f_condicao(dado, valor_campo_comp);

            if(SATISFAZ) // caso o dado satisfaça a condição proposta
            {
                REGISTO * reg_atual = elem->Info;
                //ok, já estamos no registo correto, queremos atualizar o campo que foi indicado
                // basta irmos ao dado na posição equivalente do campo
                NOG * dado_att = ObterElementoDaPosicao(reg_atual, POS_CAMPO_ATT); // cuidado, essa função retorna um nó, e não a Info
                // agora basta atualizar o valor do dado (string)

                // TODO: Verificar se essa forma de atualização não dá problema
                dado_att->Info = valor_campo_update;
                atualizados++;
            }
        }
        elem = elem->Prox;
    }
    exe = clock() - exe;
    double tempo = ((double)exe)/CLOCKS_PER_SEC;
    FILE *f1 =  fopen("estatisticas.csv", "a+");
    fprintf(f1, "%s;%.3f\n",__func__,tempo);
    fclose(f1);
    return atualizados ;
}

/** \brief Uma função para sempre retonar verdadeiro na condição de comprar duas infos, EXCLUIR DEPOIS?
 *
 * \param info1 void*
 * \param info2 void*
 * \return int: SUCESSO sempre, a não ser que ocorra algo errado, como as info não existirem
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
    clock_t exe;
    exe = clock();
    if(!T) return INSUCESSO;

    Mostrar_Tabela(T);
    printf("\nCAMPOS: \n");
    MostrarLG(T->LCampos, Mostrar_Campo_Simples);
    printf("\n");
    MostrarLG(T->LRegistos, Mostrar_Registo);
    exe = clock() - exe;
    double tempo = ((double)exe)/CLOCKS_PER_SEC;
    FILE *f1 =  fopen("estatisticas.csv", "a+");
    fprintf(f1, "%s;%.3f\n",__func__,tempo);
    fclose(f1);
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
    clock_t exe;
    exe = clock();
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
    exe = clock() - exe;
    double tempo = ((double)exe)/CLOCKS_PER_SEC;
    FILE *f1 =  fopen("estatisticas.csv", "a+");
    fprintf(f1, "%s;%.3f\n",__func__,tempo);
    fclose(f1);
    return SUCESSO;
}


BDadosCoupe *Ler_nome_versao_BD_bin(char *fich_dat)
{
    FILE *F = fopen(fich_dat, "rb");

    if(!F)return NULL;

    //nome_BD
    int N_nome_BD;
    fread(&N_nome_BD, sizeof(int), 1, F);
    char *s_nome_BD = (char*) malloc(sizeof(char) * N_nome_BD);
    fread(s_nome_BD, sizeof(char), N_nome_BD, F);
    s_nome_BD[N_nome_BD]='\0';

    //vesao_BD
    int N_versao_BD;
    fread(&N_versao_BD, sizeof(int), 1, F);
    char *s_versao_BD = (char*) malloc(sizeof(char) * N_versao_BD);
    fread(s_versao_BD, sizeof(char), N_versao_BD, F);
    s_versao_BD[N_versao_BD]='\0';


    //int len = ftell(F);
    //printf("Size of file: %d bytes", len);
    fclose(F);


    return Criar_BDados(s_nome_BD,s_versao_BD);
}


