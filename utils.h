
#include <time.h>

typedef struct
{
    int ANO, MES, DIA;
    int HORA, MIN, SEG;
}DATA;


int aleatorio(int min, int max);

int lerString(char * texto, char * string);

int lerInteiro(char * texto);

float lerFloat(char * texto);

void debugInt(char * txt, char * file, int num);

void debugFloat(char * txt, char * file, float num);

void debugTxt(char * txt, char * file);

void calcularTempoExe();

void teclaParaContinuar();

void limparTeclado();

static char *util_cat(char *dest, char *end, const char *str);

int juntarStrings(char *dado1, char *dado2, char *junto, char *separador);

