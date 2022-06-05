#include "Tipos_Dados.h"

/** \brief
 *
 * \param campo CAMPO*
 * \return void
 *
 */
void Mostrar_Campo(CAMPO * campo)
{
    if(!campo) return;
    printf ("Nome campo: %s, Tipo: %s ", campo->NOME_CAMPO, campo->TIPO );
}

void Mostrar_Campo_Simples(CAMPO * campo)
{
    if(!campo) return;

    printf ("%10s<%4s>\t", campo->NOME_CAMPO, campo->TIPO );

}

/** \brief
 *
 * \param c CAMPO*
 * \return void
 *
 */
void Destruir_Campo(void *c)
{
    if(!c) return;

    CAMPO *X = (CAMPO*) c;
    free(X);
}

/** \brief
 *
 * \param r REGISTO*
 * \return void
 *
 */
void Destruir_Registo(void *r)
{
    REGISTO *X = (REGISTO*) r;
    DestruirLG(X, Destruir_Dado);
}

void Destruir_Dado(void* dado)
{
    char *X = (char*) dado;
    free(X);
}


/** \brief
 *
 * \param tab TABELA*
 * \return void
 *
 */
void Destruir_Tabela(void *tab)
{

    if (!tab) return;

    TABELA * X = (TABELA*) tab;

    DestruirLG(X->LCampos, Destruir_Campo);
    DestruirLG(X->LRegistos, Destruir_Registo);
    free(X);

}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
CAMPO *Criar_Campo (char * nome_campo, char * tipo)
{
    if(!nome_campo || !tipo) return NULL;

    CAMPO * C = (CAMPO*) malloc(sizeof(CAMPO));
    strcpy(C->NOME_CAMPO, nome_campo);
    strcpy(C->TIPO, tipo);
    return C;
}


/** \brief Compara duas tabelas pelo nome
 *
 * \param tab1 TABELA*
 * \param tab2 TABELA*
 * \return int : 1 Se são iguais 0 caso não
 *
 */
int Comparar_Tabelas(void *tab1, void *tab2)
{
    if(!tab1 || !tab2) return INSUCESSO;
    TABELA *X1 = (TABELA*) tab1;
    TABELA *X2 = (TABELA*) tab2;
    return  stricmp(X1->NOME_TABELA, X2->NOME_TABELA) == 0 ? SUCESSO : INSUCESSO;
}

/** \brief Compara dois campo pelo nome
 *
 * \param campo1 CAMPO*
 * \param campo2 CAMPO*
 * \return int
 *
 */
int Comparar_Campos(CAMPO *campo1, CAMPO *campo2)
{
    if(!campo1 || !campo2) return INSUCESSO;
    return  stricmp(campo1->NOME_CAMPO, campo2->NOME_CAMPO) == 0 ? SUCESSO : INSUCESSO;
}


int Compara_Dado(char * dado1, char * dado2)
{
    if(!dado1 || !dado2) return INSUCESSO;
    return stricmp(dado1, dado2) == 0 ? SUCESSO : INSUCESSO;
}



int Compara_Registo(REGISTO * reg1, REGISTO * reg2)
{

    if(!reg1 || !reg2) return INSUCESSO;


    int IGUAL = 1;

    NOG * P2 = reg2->Inicio;

    // comparemos com o dado do segundo registo, veremos se batem igual

    while(P2 && IGUAL)
    {
        IGUAL = PesquisarElemento(reg1, P2->Info, Compara_Dado);
        P2 = P2->Prox;
    }

    return IGUAL;
}

/** \brief Mostra cada dado de um REGISTO
 *
 * \param dado char*
 * \return void
 *
 */
void Mostrar_Dado(char* dado)
{
    if(!dado) return;
    printf("|%15s|\t", dado);
}

CAMPO *Pesquisar_Campo(TABELA *T, char *nome_campo)
{
    CAMPO * camp = (CAMPO*) malloc(sizeof(CAMPO));
    strcpy(camp->NOME_CAMPO, nome_campo);

    NOG * nogtemp = PesquisarElemento(T->LCampos, camp, Comparar_Campos);
    if(nogtemp)
    {
        return nogtemp->Info;
    }
    else
    {
        return NULL;
    }
}

REGISTO * Criar_Registo(ListaGenerica * LISTA)
{
    if(!LISTA) return NULL;
    REGISTO * reg = (REGISTO * ) malloc(sizeof(REGISTO));
    return reg;
}

/** \brief Mostra um registo, que é uma lista de dados (strings) . OU SEJA MOSTRA UMA LINHA DA TABELA!!!
 *
 * \param r REGISTO* : Uma registo, QUE ATENÇÃO, É UMA LISTA!!!!!!!
 * \return void
 *
 */
void Mostrar_Registo(REGISTO *r)
{
    if(!r) return;
    MostrarLG(r, Mostrar_Dado);
    printf("\n");
}

/** \brief AVISO: FECHA O FICHEIRO PELA AMOR DE DEUS
 *
 * \param campo CAMPO*
 * \param F FILE*
 * \return void
 *
 */
void Gravar_Campo(CAMPO * campo, FILE *F)
{
    if(!F) return;
    fprintf(F, "%s(%s);", campo->NOME_CAMPO, campo->TIPO);
}

void Gravar_Dado(char * dado, FILE *F)
{
    if(!F) return;
    fprintf(F, "%s;", dado);
}

void Gravar_Registo(REGISTO *r, FILE *F)
{
    GravarFicheiroTXTLG(r, Gravar_Dado, F);
    fprintf(F,"\n");
}

int Gravar_Tabela_TXT(TABELA *T,FILE *F)
{
    if(!T) return INSUCESSO;
    fprintf(F,"%s\n",T->NOME_TABELA);
    GravarFicheiroTXTLG(T->LCampos,Gravar_Campo,F);
    fprintf(F,"\n");
    GravarFicheiroTXTLG(T->LRegistos,Gravar_Registo,F);

    return SUCESSO;
}


/** \brief Grava um dado do registo no ficheiro binario
 *
 * \param dado char*
 * \param F FILE*
 * \return void
 *
 */
void Gravar_Dado_Binario(char * dado, FILE *F)
{
    if(!F) return;

    char *s_dado = (char*) malloc(sizeof(char) * strlen(dado)+1);
    strcpy(s_dado, dado);
    int N_dado = strlen(s_dado);
    fwrite(&N_dado, sizeof(int), 1, F);
    fwrite(s_dado, sizeof(char), N_dado, F);
    free(s_dado);
}

/** \brief Grava um registo num ficheiro binario
 *
 * \param r REGISTO*
 * \param F FILE*
 * \return void
 *
 */
void Gravar_Registo_Binario(REGISTO *r, FILE *F)
{
    int qtd_dados = r->NEL;
    fwrite(&qtd_dados, sizeof(int), 1, F);
    GravarFicheiroBinarioLG(r,Gravar_Dado_Binario,F);
}

/** \brief Grava a informação de um campo, (nome e tipo) em binário
 *
 * \param campo CAMPO*
 * \param F FILE*
 * \return void
 *
 */
void Gravar_Campo_Binario(CAMPO * campo, FILE *F)
{
    // Grava o nome do campo
    char *s_nome = (char*) malloc(sizeof(char) * strlen(campo->NOME_CAMPO));
    strcpy(s_nome, campo->NOME_CAMPO);
    int N_nome = strlen(s_nome);
    fwrite(&N_nome, sizeof(int), 1, F);
    fwrite(s_nome, sizeof(char), N_nome, F);
    free(s_nome);
    // Grava o tipo do campo

    char *s_tipo = (char*) malloc(sizeof(char) * strlen(campo->TIPO));
    strcpy(s_tipo, campo->TIPO);
    int N_tipo = strlen(s_tipo);
    fwrite(&N_tipo, sizeof(int), 1, F);
    fwrite(s_tipo, sizeof(char), N_tipo, F);
    free(s_tipo);
}



int Gravar_Tabela_Binario(TABELA *T,FILE *F)
{
    if(!T) return INSUCESSO;
    int num_campos = T->LCampos->NEL;
    fwrite(&num_campos, sizeof(int), 1, F); //numero de Campos
    GravarFicheiroBinarioLG(T->LCampos,Gravar_Campo_Binario,F);
    int num_registos = T->LRegistos->NEL;
    fwrite(&num_registos, sizeof(int), 1, F);   //numero de Registos
    GravarFicheiroBinarioLG(T->LRegistos, Gravar_Registo_Binario, F);
    return SUCESSO;
}

/** \brief Lê todo conteudo de uma tabela de um ficheiro Binario
 *
 * \param T TABELA*
 * \param F FILE*
 * \return int
 *
 */
int Ler_Tabela_Binario(TABELA *T,FILE *F)
{
    if(!T || !F) return INSUCESSO;

    int n_campos = 0;
    fread(&n_campos, sizeof(int), 1, F);
    //printf("\n nel tabela:%d",T->LCampos->NEL);

    //TABELA
    for(int i=0; i<n_campos; i++)
    {
        // ler o nome do campo
        int N_campo;
        fread(&N_campo, sizeof(int), 1, F);
        char *s_campo = (char*) malloc(sizeof(char) * N_campo + 1);
        fread(s_campo, sizeof(char), N_campo, F);
        s_campo[N_campo]='\0';

        // ler o tipo do campo
        int N_tipo;
        fread(&N_tipo, sizeof(int), 1, F);
        char *s_tipo = (char*) malloc(sizeof(char) * N_tipo + 1);
        fread(s_tipo, sizeof(char), N_tipo, F);
        s_tipo[N_tipo]='\0';

        Add_Campo_Tabela(T,s_campo,s_tipo);
    }

    //REGISTOS
    int num_registos;
    fread(&num_registos, sizeof(int), 1, F);

    REGISTO *R;

    for(int i=0;i<num_registos;i++)
    {
        R = CriarLG();
        int qtd_dados = 0;
        fread(&qtd_dados, sizeof(int), 1, F);
        for(int j=0;j<qtd_dados;j++)
        {
        int N_registo;
        fread(&N_registo, sizeof(int), 1, F);
        char *s_registo = (char*) malloc((sizeof(char) * N_registo) + 2);

        fread(s_registo, sizeof(char), N_registo, F);
        s_registo[N_registo]='\0';
        AddFimLG(R,s_registo);
        }
        AddFimLG(T->LRegistos,R);
    }
    return SUCESSO;
}


/** \brief Lê o nome de uma tabela de um ficheiro TXT ou CSV
 *
 * \param BD BDadosCoupe*
 * \param F FILE*
 * \return TABELA*
 *
 */
TABELA *Ler_Nome_Tabela(BDadosCoupe *BD,FILE *F)
{
    if(!F || !BD) return NULL;
    int cont=0;

    char nome_tabela[51];


    if (F != EOF && fgets(nome_tabela,51, F)) // tenta ler a linha, caso seja vazia ou fim do ficheiro nao lemos
    {
        if(nome_tabela[0]=='-') return NULL;
        nome_tabela[strlen(nome_tabela) - 1] = '\0';
        return (TABELA*) Criar_Tabela(BD, nome_tabela);
    }

    return NULL;
}


/** \brief Lê os campos de uma tabela de um ficheiro TXT ou CSV
 *
 * \param F FILE*
 * \param T TABELA*
 * \return void
 *
 */
void  Ler_Campo_Tabela(FILE *F, TABELA *T)
{
    if(!F || !T) return;
    int count=0;
    int count1=0;
    int SAIR = 0;

    do
    {
        char *nome_campo = malloc (sizeof (char)*50);
        char *nome_tipo = malloc (sizeof (char)*50);
        do
        {
            nome_campo[count]=fgetc(F);

            if(nome_campo[count] == '(')
            {
                do
                {
                    nome_tipo[count1]=fgetc(F);
                    count1++;
                }
                while( nome_tipo[count1-1] != ')');
            }
            count++;

        }
        while(nome_campo[count-1] != ';' && nome_campo[count - 1] != '\n');
        if((nome_campo[count-1] == '\n') || (nome_campo[count] == '\n'))
        {
            SAIR = 1;
            return;
        }

        nome_campo[count-2]='\0';
        nome_tipo[count1-1]='\0';
        nome_campo=realloc (nome_campo,sizeof (char)*count);
        nome_tipo=realloc (nome_tipo,sizeof (char)*count1);
        CAMPO * C = Criar_Campo(nome_campo, nome_tipo);

        count=0;
        count1=0;
        AddFimLG(T->LCampos, C);
    }
    while(!SAIR);
}

void  Ler_Valores_Tabela(FILE *F, TABELA *T)
{
    if(!F || !T) return;
    int SAIR = 0;


    char registo[1024];

    while (fgets(registo,1024, F) && registo[0] != '#')
    {
        int tam = strlen(registo);
        registo[tam-1] = '\0';
            Add_Valores_Tabela(T, registo);
    }
}

long Obter_Tamanho_Memoria_Campo(void *C)
{
    if(!C) return 0;
    CAMPO *X = (CAMPO*) C;
    long memoria = 0;
    memoria += sizeof(X->NOME_CAMPO);
    memoria += sizeof(X->TIPO);
    return memoria;
}

long Obter_Tamanho_Memoria_Registo(void *R)
{
    if(!R) return 0;
    REGISTO *X = (REGISTO*) R;
    return CalcularTamanhoMemoriaLG(X,Obter_Tamanho_Memoria_Dado); // calcula o tamanho de dados
}

long Obter_Tamanho_Memoria_Dado(void *D)
{
    if(!D) return 0;
    char *X = (char*) D;
    return strlen(X);
}
long Obter_Tamanho_Memoria_Tabela(void *T)
{
    if(!T) return 0;
    TABELA *X = (TABELA*) T;
    long memoria = 0;
    memoria += sizeof(X->NOME_TABELA);
   memoria += CalcularTamanhoMemoriaLG(X->LCampos, Obter_Tamanho_Memoria_Campo);
   memoria += CalcularTamanhoMemoriaLG(X->LRegistos, Obter_Tamanho_Memoria_Registo);

   return memoria;
}

/** \brief Segundo nossa estrutura de dados, a estruturas de tabela aloca um tamanho fixo
 * para a string do nome da tabela, e geralmente nao utilizará tudo, o que é um despedicio
 * esta função tem o intuito de calcular este desperdicio de uma dada tabela
 *
 * \param T void*
 * \return long
 *
 */
long Obter_Tamanho_Desperdicado_Memoria_Tabela(void *T)
{
    if(!T) return 0;
    TABELA *X = (TABELA*) T;
    long memoria = 0;
    memoria += sizeof(X->NOME_TABELA) - strlen(X->NOME_TABELA);
    memoria += CalcularTamanhoMemoriaLG(X->LCampos, Obter_Tamanho_Memoria_Campo);
    return memoria;
}

/** \brief Segundo nossa estrutura de dados, a estruturas de campo aloca um tamanho fixo
 * para as string do nome e tipo. Essa função é similiar a Obter_Tamanho_Desperdicado_Memoria_Tabela,
 * e é usada pela mesma
 *
 * \param C void*
 * \return long
 *
 */
long Obter_Tamanho_Desperdicado_Memoria_Campo(void *C)
{
    if(!C) return 0;
    CAMPO *X = (CAMPO*) C;
    long memoria = 0;
    memoria += sizeof(X->NOME_CAMPO) - strlen(X->NOME_CAMPO);
    memoria += sizeof(X->TIPO) - strlen(X->TIPO);
    return memoria;
}




