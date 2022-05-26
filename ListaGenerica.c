
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
    L->Fim = NULL;
    return L;
}
/** \brief Elimina uma lista gen�rica, removendo a lista e todos elementos da mem�ria
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
    if(!nozito->Prox) // caso seja o unico elemento, ser� o ultimo
    {
        L->Fim = nozito;
    }
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
        NOG *Y = L->Fim;
        Y->Prox = Novo;
    }
    L->Fim = Novo;
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


/** \brief Remove o primeiro elemento de uma lista gen�rica
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
        L->Fim = NULL;
    }
    else
    {
        L->Inicio = primeiro->Prox;
        func_remover(primeiro->Info);
        free(primeiro);
        // caso s� sobre um elemento
        if(!L->Inicio->Prox)
        {
            L->Fim = L->Inicio;
        }
    }


    L->NEL--;
}
// TODO: ARRUMAR ESSA FUN��O
 // TODO: OTIMIZAR PARA USAR O PONTEIRO DO FIM DA LISTA
/** \brief Remove o �ltimo elemento de uma lista gen�rica
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
         func_remover(proximo->Info);
        free(proximo);
        L->Fim = P;
    }
    else
    {
        // caso seja o unico elemento da lista
        func_remover(P->Info);
        free(P);
        L->Inicio = NULL;
        L->Fim = NULL;
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
    }
    else
    {
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
        return NULL;
    }
    if(!Info)
    {
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

/** \brief Retorna a posi��o que um elemento se encontra numa lista, aten��o, contagem inicia do 0, e -1 caso elemento n�o exista
 *
 * \param L ListaGenerica*
 * \param Info void*
 * \param (*func_comparar int
 * \return int : Posicao do elemento a partir do 0, retorna -1 caso elemento n�o exista
 *
 */
int ObterPosicaoElementoLG(ListaGenerica *L, void * Info, int (*func_comparar) (void*, void*))
{
    if(!L || !Info) return -1;

    int posicao = 0;
    NOG * elemLista = L->Inicio;
    int ENCONTRADO = INSUCESSO;

    while(elemLista && !ENCONTRADO)
    {
        posicao ++;
        if(func_comparar(elemLista->Info, Info))
        {
            ENCONTRADO = SUCESSO;
            break;
        }

        elemLista = elemLista->Prox;
    }

    if(ENCONTRADO)
    {
        return posicao;
    }
    else
    {
        return -1;
    }
}

/** \brief Dada uma posi��o na lista, obtem se existir o elemento da posi��o
 *
 * \param L ListaGenerica*
 * \param posicao int
 * \return NOG* : Um n� da lista gen�rica, caso precise usar o elemento, nao esquecer do ->Info
 *
 */
NOG * ObterElementoDaPosicao(ListaGenerica *L, int posicao)
{
    if(!L || posicao < 0) return NULL;
    // n�o faz sentido buscar um elemento numa posicao que nem est� na lista
    if(ObterTamanhoLG(L) < posicao) return NULL;
    // vamos direto a posicao do elemento
    NOG * elemLista = L->Inicio;
    int i;
    for( i = 1 ; i < posicao ; i++) elemLista = elemLista->Prox;
    return elemLista;
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
 *  c
 *
 * \param L ListaGenerica*
 * \param nome_fich char*
 * \return int
 *
 */
int GravarFicheiroTXTLG(ListaGenerica *L, void (*func_gravar) (void*, FILE*), FILE * F)
{
    if (!L || !L->Inicio || !F) return INSUCESSO;
    // FILE *F = fopen(nome_fich, "a");
    if(!F) return INSUCESSO;
    NOG *P = L->Inicio;
    while (P)
    {

        func_gravar(P->Info, F);

        P = P->Prox;
    }
    // fclose(F);
    return SUCESSO;
}

/** \brief Grava toda uma lista gen�rica em um ficheiro bin�rio
 *       ATEN��O: ESTA FUN��O N�O FECHA O FICHEIRO, SER� NECESS�RIO FECHAR DEPOIS
 * \param L ListaGenerica*
 * \param (*func_gravar_binario void : Uma fun��o que grava um tipo de dados num ficheiro bin�rio
 * \return int: SUCESSO/INSUCESSO
 *
 */
int GravarFicheiroBinarioLG(ListaGenerica *L, void (*func_gravar_binario) (void*, FILE*), FILE * F)
{
    if (!L)  return INSUCESSO;
    if (!F) return INSUCESSO;
    fwrite(&(L->NEL), sizeof(int), 1, F);
   // printf("Nelementos- %d",L->NEL);
    NOG *P = L->Inicio;

    while (P)
    {
        func_gravar_binario(P->Info, F);
        P = P->Prox;

    }
    return SUCESSO;
}

long int CalcularTamanhoMemoriaLG(ListaGenerica *L)
{
    if(!L) return 0;


    return sizeof(L) + sizeof(L->Inicio) * L->NEL; // o tamanho de um n� multiplicado pela quantidade de elementos
}

