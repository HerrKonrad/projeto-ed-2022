
#include "ListaGenerica.h"

/** \brief
 *
 * \return ListaGenerica*
 *
 */
ListaGenerica *CriarLG()
{
    ListaGenerica *L = (ListaGenerica *)malloc(sizeof(ListaGenerica));
    L->Inicio = NULL;
    L->NEL = 0;
    return L;
}
/** \brief
 *
 * \param  void*
 * \return void DestuirLG(ListaGenerica *L, void
 *
 */
void DestruirLG(ListaGenerica *L, void (*func_remover)(void *))
{
    if (!L) return;
    NOG *P = L->Inicio;
    NOG *Aux;
    while (P)
    {
        Aux = P->Prox;
        func_remover(P->Info);
        free(P);
        P = Aux;
    }
    free(L);
}
/** \brief Adiciona um elemento no inicio de uma lista gen�rica
 *
 * \param L ListaGenerica*
 * \param X void*
 * \return int
 *
 */
int AddLG(ListaGenerica *L, void *X)
{
    if (!L) return INSUCESSO;
    NOG *nozito = (NOG *)malloc(sizeof(NOG));
    nozito->Info = X;
    nozito->Prox = L->Inicio;
    L->Inicio = nozito;
    L->NEL++;
    return SUCESSO;
}

/** \brief Adiciona um elemento ao fim da lista gen�rica
 *
 * \param L ListaGenerica*
 * \param X void*
 * \return int
 *
 */
int AddFimLG(ListaGenerica *L, void *X)
{
    if (!L || !X) return INSUCESSO;
    NOG *Novo = (NOG *)malloc(sizeof(NOG));
    Novo->Info = X;
    Novo->Prox = NULL;
    if (!L->Inicio)
        L->Inicio = Novo;
    else
    {
        NOG *X = L->Inicio;
        while (X->Prox)
        {
            X = X->Prox;
        }
        X->Prox = Novo;
    }
    L->NEL++;
    // Caso a lista esteja vazia
    return SUCESSO;
}
/** \brief Mostra se poss�vel todos os elementos da lista gen�rica
 *
 * \param  void* func_mostrar : Uma fun��o que mostra um tipo de dado
 * \return void
 *
 */
void MostrarLG(ListaGenerica *L, void (*func_mostrar)(void *))
{
    if (!L || !L->Inicio) return;
    NOG *P = L->Inicio;
    while (P)
    {
        func_mostrar(P->Info);
        P = P->Prox;
    }
}

/** \brief
 *
 * \param  void* func_mostrar
 * \return void MostrarInversoLG(ListaGenerica *L, void
 *
 */
void MostrarInversoLG(ListaGenerica *L, void (*func_mostrar)(void *))
{
    printf("<%s> nao implementada", __FUNCTION__);

}


/** \brief
 *
 * \param L ListaGenerica*
 * \param (*func_remover void
 * \return void
 *
 */
void RemoverPrimeiroLG(ListaGenerica *L, void (*func_remover) (void*))
{
    if (!L) return;
    if(!L->Inicio) return;
    NOG *primeiro = L->Inicio;
    if(!primeiro->Prox)
    {
        func_remover(primeiro->Info);
        free(primeiro);
        L->Inicio = NULL;
    }
    else
    {
        L->Inicio = primeiro->Prox;
        func_remover(primeiro->Info);
        free(primeiro);
    }
    L->NEL--;
}
// TODO: ARRUMAR ESSA FUN��O
/** \brief
 *
 * \param L ListaGenerica*
 * \param (*func_remover void
 * \return void
 *
 */
void RemoverUltimoLG(ListaGenerica *L, void (*func_remover) (void*))
{
    if (!L) return;
    if(!L->Inicio) return;

    NOG *P = L->Inicio;
    NOG * proximo = NULL;

    // Caso n�o seja o unico elemento da lista
    if(P->Prox)
    {
        proximo = P->Prox;
        // vai at� o fim da lista
        while(proximo->Prox)
        {
            P = proximo;
            proximo = proximo->Prox;
        }
        P->Prox = NULL;

        // TODO: AJUSTAR
        // ATEN��O: ERRO AQUI!!!!!
        // func_remover(proximo->Info);
        free(proximo);
    }
    else
    {
        // caso seja o unico elemento da lista
        func_remover(P->Info);
        free(P);
        L->Inicio = NULL;
    }

    L->NEL--;
}
/** \brief
 *
 * \param L ListaGenerica*
 * \param (*func_remover void
 * \return void
 *
 */
void RemoverElementoLG(ListaGenerica *L, void * ele_remover, void (*func_remover) (void*), int (*func_comparar) (void*, void*))
{
    if( !L || !ele_remover || !L->Inicio) return;

    int STOP = 0;

    NOG * P = L->Inicio;
    NOG * anterior = NULL;

    // Procura o elemento at� acabar a lista
    while(P && !STOP)
    {
        if(func_comparar(P->Info, ele_remover))
        {
            debugTxt("Encontrei elemento", FICH_DEBUG);
            STOP = 1;
        }
        else
        {
            anterior = P;
            P = P->Prox;
        }
    }

    // caso encontre o elemento
    if(STOP)
    {
        // CASO SEJA  O PRIMEIRO
        if(func_comparar(P, L->Inicio))
        {
            RemoverPrimeiroLG(L, func_remover);
        }
        // CASO SEJA O ULTIMO
        else if(!P->Prox)
        {
            RemoverUltimoLG(L, func_remover);
        }
        // CASO ESTEJA NO MEIO
        else
        {
            anterior->Prox = P->Prox;
            func_remover(P->Info);
            free(P);
        }
        L->NEL--;
        debugTxt("Elemento encotrado e excluido", FICH_DEBUG);
    }
    else
    {
        debugTxt("Elemento nao encontrado :-(", FICH_DEBUG);
    }
}

/** \brief Tenta encontrar um elemento especificado no argumento da fun��o, caso consiga retorna o N� (NOG) correspondente, caso n�o ache
 *  retorna nulo
 *  ATEN��O: Esse � um m�todo de pesquisa simples, pode ser necess�rio para tarefas que exigem mais desempenho outra fun��o mais avan�ada
 * \param L ListaGenerica* : Uma lista
 * \param Info void*: O elemento de um n�
 * \param (*func_comparar int : uma fun��o que compare dois elementos
 * \return NOG* : O n� correspodente ao conteudo encontrado
 *
 */
NOG * PesquisarElemento(ListaGenerica *L, void * Info, int (*func_comparar) (void*, void*))
{
    if(!L)
    {
        debugTxt("Nao existe lista", FICH_DEBUG);
        return NULL;
    }
    if(!Info)
    {
        debugTxt("informacao inexistente", FICH_DEBUG);
        return NULL;
    }

    NOG * elemLista = L->Inicio;
    int ENCONTRADO = INSUCESSO;

    while(elemLista && !ENCONTRADO)
    {
        if(func_comparar(elemLista->Info, Info))
        {
            ENCONTRADO = SUCESSO;
            break;
        }
        elemLista = elemLista->Prox;
    }

    if(ENCONTRADO)
    {
        return elemLista;
    }
    else
    {
        return NULL;
    }
}

/** \brief Obtem o tamanho da lista, caso n�o exista retorna -1
 *
 * \param L ListaGenerica*
 * \return long : o tamanho da lista, e -1 caso n�o exista
 *
 */
long ObterTamanhoLG(ListaGenerica *L)
{
    return L ? L->NEL : -1;
}

/** \brief Grava toda a informa��o de uma lista gen�rica em um ficheiro, � preciso que o ficheiro j� existe e esteja aberto
 *  ATEN��O: ESTA FUN��O N�O FECHA O FICHEIRO, SER� NECESS�RIO FECHAR DEPOIS
 *
 * \param L ListaGenerica*
 * \param nome_fich char*
 * \return int
 *
 */
int GravarFicheiroTXTLG(ListaGenerica *L, void (*func_gravar) (void*, FILE*), FILE * F)
{
    if (!L || !L->Inicio || !F) return INSUCESSO;
    if(!F) return INSUCESSO;
    NOG *P = L->Inicio;
    while (P)
    {
        func_gravar(P->Info, F);
        P = P->Prox;
    }
    return SUCESSO;
}

/** \brief Grava toda uma lista gen�rica em um ficheiro bin�rio
 *
 * \param L ListaGenerica*
 * \param (*func_gravar_binario void : Uma fun��o que grava um tipo de dados num ficheiro bin�rio
 * \return int
 *
 */
int GravarFicheiroBinarioLG(ListaGenerica *L, void (*func_gravar_binario) (void*, FILE*), FILE * F)
{
    if (!L)  return INSUCESSO;
    if (!F) return INSUCESSO;
    //FILE *F = fopen(ficheiro, "wb");
    fwrite(&(L->NEL), sizeof(int), 1, F);
    NOG *P = L->Inicio;

    while (P)
    {
        func_gravar_binario(P->Info, F);
        /*
        char *s = (char *)P->Info;
        int N = strlen(s);
        fwrite(&N, sizeof(int), 1, F);
        fwrite(s, sizeof(char), N, F);
        */
        P = P->Prox;

    }
    return SUCESSO;
}


