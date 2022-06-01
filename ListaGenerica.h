#ifndef LISTAGENERICA_H_INCLUDED
#define LISTAGENERICA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SUCESSO   1
#define INSUCESSO 0
#define  NAO_LISTA "Lista Inexistente"
#define FICH_DEBUG "testes.txt"

typedef struct NOG
{
    void       *Info;
    struct NOG *Prox;
}NOG;
typedef struct
{
    NOG *Inicio;
    NOG *Fim;
    int NEL;
}ListaGenerica;


ListaGenerica *CriarLG();
void DestruirLG(ListaGenerica *L, void (*func_remover)(void *));
int AddLG(ListaGenerica *L, void *X);
int AddFimLG(ListaGenerica *L, void *X);
void MostrarLG(ListaGenerica *L, void (*func_mostrar)(void *));
void MostrarInversoLG(ListaGenerica *L, void (*func_mostrar)(void *));
void RemoverPrimeiroLG(ListaGenerica *L, void (*func_remover) (void*));
void RemoverUltimoLG(ListaGenerica *L, void (*func_remover) (void*));
void RemoverElementoLG(ListaGenerica *L, void * ele_remover,  void (*func_remover) (void*), int (*func_comparar) (void*, void*));
int CompararInfoG(NOG * ele1, NOG * ele2, int (func) (void*, void*));
NOG * PesquisarElemento(ListaGenerica *L, void * Info, int (*func_comparar) (void*, void*));
int ObterPosicaoElementoLG(ListaGenerica *L, void * Info, int (*func_comparar) (void*, void*));
NOG * ObterElementoDaPosicao(ListaGenerica *L, int posicao);
long ObterTamanhoLG(ListaGenerica *L);
int GravarFicheiroTXTLG(ListaGenerica *L, void (*func_gravar) (void*, FILE*), FILE * F);
int GravarFicheiroBinarioLG(ListaGenerica *L, void (*func_gravar_binario) (void*, FILE*), FILE * F);

long int CalcularTamanhoMemoriaLG(ListaGenerica *L, long (func_obter_tamanho) (void * dado));








#endif // LISTAGENERICA_H_INCLUDED

