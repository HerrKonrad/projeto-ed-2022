/** PROJETO ESTRUTURA DE DADOS 2022
 * Base De Dados Coupe
 * ESCOLA SUPERIOR DE TECNOLOGIA E GEST�O DE VISEU
 * NOMES: Arthur Konrad - 22062
 *        Leandro Dias - 23028
 *        Jesus Betancourt -
 *        Gon�alo Abreu -
 */



#include <stdio.h>
#include <stdlib.h>

#include "BDadosCoupe.h"
#include "Tipos_Dados.h"




extern int contemPalavra(char * str, char * substr);


void geradorRegistos(size_t n)
{


    BDadosCoupe *BD = Criar_BDados("XPTO", "Versao1");

    TABELA *T = Criar_Tabela(BD, "XPTO");
    TABELA *T2 = Criar_Tabela(BD, "XPTO2");


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
        sprintf(registo, "%d;xpto%d;xpto%d@outlook.com;%d-%d", i, i, i, aleatorio(50, 100), aleatorio(50, 100));
        Add_Valores_Tabela(T, registo);
        sprintf(registo2, "%d;nome%d", i, i);
        Add_Valores_Tabela(T2, registo2);

    }

    //DELETE(BD, "XPTO", contemPalavra, "NOME", "3");

    // UPDATE(BD, "XPTO", contemPalavra, "ID", "1", "NOME", "MUDEI");
    // DELETE(BD, "XPTO", contemPalavra, "NOME", "xpto");
    // SELECT(BD, "XPTO", Condicao_Todos, "NOME", "1");





    // Mostrar_Todos_Registos(T);

    Exportar_BDados_Excel(BD, "toda.csv");
    Destruir_BDados(BD);


}





void testes()
{
    debugTxt("AREA DE TESTES: ", FICH_DEBUG);



    BDadosCoupe *BD = Criar_BDados("bdteste", "1");

    Importar_BDados_Excel(BD, "toda_bd.csv");


    DELETE(BD, "XPTO", contemPalavra, "NOME", "0");
    UPDATE(BD, "XPTO", contemPalavra, "NOME", "2", "E-MAIL", "mudei@gmail.com");

   SELECT(BD, "XPTO", contemPalavra, "NOME", "2");

   //Mostrar_BDados_toda(BD);


    //int att = UPDATE(BD, "VEICULO", contemPalavra, "TIPO_VEICULO", "bikes", "NUMERO", "123");



    //Exportar_Tabela_BDados_Excel(BD, "VEICULO", "veiculo_sem_truck.csv");



    Destruir_BDados(BD);


    debugTxt("FIM DOS TESTES: ", FICH_DEBUG);

}
/*
Uma Base de dados Relacional � formada por tabelas,
onde cada tabela tem as v�rias colunas (campos)
e os registos (informa��o),
um registo � uma cole��o de dados.
As tabelas podem ter relacionamentos entre elas
(mas esta parte ser� dada nas disciplinas de base de dados do 2�ano do curso).
*/
int main()
{
  //  geradorRegistos(99999);


    testes();

    return 0;
}
