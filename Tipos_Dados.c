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

    printf ("%10s(%4s)\t", campo->NOME_CAMPO, campo->TIPO );

}

/** \brief
 *
 * \param c CAMPO*
 * \return void
 *
 */
void Destruir_Campo(CAMPO *c)
{
    if(!c) return;
    free(c);
}

/** \brief
 *
 * \param r REGISTO*
 * \return void
 *
 */
void Destruir_Registo(REGISTO *r)
{
    DestruirLG(r, Destruir_Dado);
    free(r);
}

void Destruir_Dado(char* dado)
{
    free(dado);
}


/** \brief
 *
 * \param tab TABELA*
 * \return void
 *
 */
void Destruir_Tabela(TABELA *tab)
{

    if (!tab) return;


    DestruirLG(tab->LCampos, Destruir_Campo);
    DestruirLG(tab->LRegistos, Destruir_Registo);
    tab->LCampos = NULL;
    tab->LRegistos = NULL;
    free(tab);

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
int Comparar_Tabelas(TABELA *tab1, TABELA *tab2)
{
    if(!tab1 || !tab2) return INSUCESSO;
    return  stricmp(tab1->NOME_TABELA, tab2->NOME_TABELA) == 0 ? SUCESSO : INSUCESSO;
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
      fprintf(F,"\n ");

}

int Gravar_Tabela_TXT(TABELA *T,FILE *F)
{
    if(!T) return INSUCESSO;

    fprintf(F,"%s\n",T->NOME_TABELA);


    GravarFicheiroTXTLG(T->LCampos,Gravar_Campo,F);
    fprintf(F,"\n ");
    GravarFicheiroTXTLG(T->LRegistos,Gravar_Registo,F);

    return SUCESSO;
}


void Gravar_Dado_Binario(char * dado, FILE *F)
{
    if(!F) return;
    int tam_dado =strlen(dado) + 1;
    char *s_dado = (char*) malloc(sizeof(char) * tam_dado);
    strcpy(s_dado, dado);
    fwrite(&tam_dado, sizeof(int), 1, F);
    fwrite(s_dado, sizeof(char), tam_dado, F);
    free(s_dado);
}

void Gravar_Registo_Binario(REGISTO *r, FILE *F)
{

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
    int N_nome = strlen(s_nome) + 1;
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

    // fprintf(F,"%s",T->NOME_TABELA);

    //fprintf(F,"\n\tCAMPOS: ");

    GravarFicheiroBinarioLG(T->LCampos,Gravar_Campo_Binario,F);
    //fprintf(F,"\n ");
    GravarFicheiroBinarioLG(T->LRegistos,Gravar_Registo_Binario,F);

    return SUCESSO;
}

BDadosCoupe *Ler_Nome_Base_Dados(FILE *F)
{
    if(!F) return NULL;
    char c;
    int cont=0;
    int cont1=0;
    char *nome_bd=malloc (sizeof (char)*50);
    char *versao_bd=malloc (sizeof (char)*50);

    do
    {
        nome_bd[cont]=fgetc(F);
        cont++;
    }while (nome_bd[cont-1]!=',' && nome_bd[cont-1]!=';');

    nome_bd[cont-1]='\0';

    do
    {
        versao_bd[cont1]=fgetc(F);
        cont1++;
    }while (versao_bd[cont1-1]!='\n');

    versao_bd[cont1-1]='\0';

    nome_bd =realloc (nome_bd,sizeof (char)*cont);
    versao_bd =realloc (versao_bd,sizeof (char)*cont1);

    return Criar_BDados(nome_bd,versao_bd);
}

TABELA *Ler_Nome_Tabela(BDadosCoupe *BD,FILE *F)
{
    if(!F || !BD) return NULL;
    int cont=0;

    char nome_tabela[51];


    if (fgets(nome_tabela,51, F)) // tenta ler a linha, caso seja vazia não lê
    {

        if (nome_tabela[0] != '\n')
        {

        nome_tabela[strlen(nome_tabela) - 1] = '\0';
        return Criar_Tabela(BD, nome_tabela);
        }
        printf("ola...");

    }


    return NULL;
}


void  Ler_Campo_Tabela(FILE *F, TABELA *T)
{
    if(!F || !T) return NULL;
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
                }while( nome_tipo[count1-1] != ')');
            }
            count++;

       }while(nome_campo[count-1] != ';' && nome_campo[count - 1] != '\n');
       if((nome_campo[count-1] == '\n') || (nome_campo[count] == '\n'))
       {
           SAIR = 1; return;
        }
            if(count1 < 1) // caso não leia um tipo, define por padão como string
            {
                strcpy(nome_tipo, "STRING");
                count1 = strlen(nome_tipo) + 1;
            }
        nome_campo[count-2]='\0';
        nome_tipo[count1-1]='\0';
       nome_campo=realloc (nome_campo,sizeof (char)*count);
        nome_tipo=realloc (nome_tipo,sizeof (char)*count1);
       CAMPO * C = Criar_Campo(nome_campo, nome_tipo);

       count=0;
       count1=0;
       AddFimLG(T->LCampos, C);


    }while(!SAIR);
}

void  Ler_Valores_Tabela(FILE *F, TABELA *T)
{
    if(!F || !T) return NULL;
    int count=0;
    int coluna = 0;
    int SAIR = 0;
    char c;

     char registo[1024];



    while (fgets(registo,1024, F))
    {
        if(strlen(registo) > 2)
        {
        Add_Valores_Tabela(T, registo);
        }
        else
        {
        break;
        }
    }
}



