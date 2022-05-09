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
    printf ("%s/%s ", campo->NOME_CAMPO, campo->TIPO );

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
     debugTxt("Campo destruido", FICH_DEBUG);
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
    free(tab);
    debugTxt("Tabela destruida", FICH_DEBUG);
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

/** \brief Mostra cada dado de um REGISTO
 *
 * \param dado char*
 * \return void
 *
 */
void Mostrar_Dado(char* dado)
{
    printf("\t<%s>", dado);
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
    MostrarLG(r, Mostrar_Dado);
    printf("\n");
}

/** \brief AVISO: FECHA O FICHEIRO PELA AMOR DE DEUS.
 *
 * \param campo CAMPO*
 * \param F FILE*
 * \return void
 *
 */
void Gravar_Campo(CAMPO * campo, FILE *F)
{
    if(!F) return;
    fprintf(F, "%s;", campo->NOME_CAMPO, campo->TIPO);
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
    char *s_nome = (char*) malloc(sizeof(char) * strlen(campo->NOME_CAMPO) + 1);
    strcpy(s_nome, campo->NOME_CAMPO);
    int N_nome = strlen(s_nome);
    fwrite(&N_nome, sizeof(int), 1, F);
    fwrite(s_nome, sizeof(char), N_nome, F);
    free(s_nome);
    // Grava o tipo do campo

    char *s_tipo = (char*) malloc(sizeof(char) * strlen(campo->TIPO) + 1);
    strcpy(s_tipo, campo->TIPO);
    int N_tipo = strlen(s_tipo);
    fwrite(&N_tipo, sizeof(int), 1, F);
    fwrite(s_tipo, sizeof(char), N_tipo, F);
    free(s_tipo);
}

int Gravar_Tabela_TXT(TABELA *T,FILE *F)
{
    if(!T) return INSUCESSO;

    fprintf(F,"%s",T->NOME_TABELA);
    fprintf(F,"\n\tCAMPOS: ");
    GravarFicheiroTXTLG(T->LCampos,Gravar_Campo,F);
    fprintf(F,"\n ");
    GravarFicheiroTXTLG(T->LRegistos,Gravar_Registo,F);
    return SUCESSO;
}



// gravar_registo

// gravar_campo



