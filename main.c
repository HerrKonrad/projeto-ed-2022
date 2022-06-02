/** PROJETO ESTRUTURA DE DADOS 2022
 * Base De Dados Coupe
 * ESCOLA SUPERIOR DE TECNOLOGIA E GESTÃO DE VISEU
 * NOMES: Arthur Konrad - 22062
 *        Leandro Dias - 23028
 *        Jesus Betancourt -
 *        Gonçalo Abreu -
 */

#include <stdio.h>
#include <stdlib.h>

#include "BDadosCoupe.h"
#include "Tipos_Dados.h"
#define ficheiro_binario "BD.dat"
#define ficheiro_excel "BD.csv"




void geradorRegistos(size_t n)
{


    BDadosCoupe *BD = Criar_BDados("XPTO", "Versao1");

    TABELA *T = Criar_Tabela(BD, "XPTO");
    TABELA *T2 = Criar_Tabela(BD, "PINGO");


    Add_Campo_Tabela(T, "ID", "INT");
    Add_Campo_Tabela(T, "NOME", "STRING");
    Add_Campo_Tabela(T, "E-MAIL", "STRING");
    Add_Campo_Tabela(T, "TELEMOVEL", "STRING");

    Add_Campo_Tabela(T2, "ID", "INT");
    Add_Campo_Tabela(T2, "NOME", "STRING");


    char registo[1200];
    char registo2[1200];
    int i;
    for ( i = 0 ; i < n ; i++)
    {

        sprintf(registo, "%d;xpto%d;xpto%d@outlook.com", i, i, i, aleatorio(50, 100), aleatorio(50, 100));
        Add_Valores_Tabela(T, registo);
        sprintf(registo2, "%d;nome%d", i, i);
        Add_Valores_Tabela(T2, registo2);
    }

    DELETE(BD, "XPTO", Condicao_Maior_Numericamente, "ID", "2");
    Exportar_BDados_Ficheiro_Binario(BD,ficheiro_binario);
   // Exportar_BDados_Excel(BD, ficheiro_excel);
    Destruir_BDados(BD);
}

void testes()
{
    BDadosCoupe *BD=Ler_nome_versao_BD_bin(ficheiro_binario);
    Importar_BDados_Ficheiro_Binario(BD,ficheiro_binario);

  // Importar_BDados_Excel(BD, "excel_arrumado.csv" );

   // Exportar_BDados_Excel(BD, "excel_arrumado.csv");

    //SELECT(BD, "XPTO", Condicao_Maior_Numericamente, "ID", "90");



   printf("\n tamanho BD: %ld bytes", Memoria_BDados(BD));
   printf("\n tamanho despedicado BD: %ld bytes", Memoria_Desperdicada_BDados(BD));
   Mostrar_BDados_toda(BD);

   // SELECT(BD, "XPTO", contemPalavra, "NOME", "9");

    Destruir_BDados(BD);
}
/*
Uma Base de dados Relacional é formada por tabelas,
onde cada tabela tem as várias colunas (campos)
e os registos (informação),
um registo é uma coleção de dados.
As tabelas podem ter relacionamentos entre elas
(mas esta parte será dada nas disciplinas de base de dados do 2ªano do curso).
*/
int main()
{
    geradorRegistos(500);
   // iniciarPrograma();
   // menuPrincipal();
    testes();
    return 0;
}
