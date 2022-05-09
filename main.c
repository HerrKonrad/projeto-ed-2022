/** PROJETO ESTRUTURA DE DADOS 2022/20
 * Base De Dados Coupe
 * ESCOLA SUPERIOR DE TECNOLOGIA E GESTÃO DE VISEU
 * NOMES:
 *
 *
 *
 */



#include <stdio.h>
#include <stdlib.h>

#include "BDadosCoupe.h"
#include "Tipos_Dados.h"


void geradorRegistos(size_t n)
{

    BDadosCoupe *BD = Criar_BDados("XPTO", "Versao 1.0");

    TABELA *T = Criar_Tabela(BD, "XPTO");
     Add_Campo_Tabela(T, "ID", "INT");
     Add_Campo_Tabela(T, "NOME", "STRING");
     Add_Campo_Tabela(T, "E-MAIL", "STRING");
     Add_Campo_Tabela(T, "TELEMOVEL", "STRING");

     char registo[1200];
     int i;
     for ( i = 0 ; i < n ; i++)
     {
         sprintf(registo, "%d;xpto%d;xpto%d@outlook.com;%d-%d", i, i, i, aleatorio(50, 100), aleatorio(50, 100));
         Add_Valores_Tabela(T, registo);

     }
            puts("terminado");
            Exportar_Tabela_BDados_Excel(BD, T, "excel.csv");
       // Exportar_BDados_Ficheiro_Texto(BD, "basedadosxpto.txt");
     Destruir_BDados(BD);
     sleep(20000);

}

void testeMemoria(size_t n)
{

    BDadosCoupe *BD = Criar_BDados("BD-Banco", "Versao 1.0");

    TABELA *T = Criar_Tabela(BD, "CLIENTES");
     Add_Campo_Tabela(T, "ID", "INT");

     int i;
     for ( i = 0 ;  i < n ; i++ )
     {
     // char * string =  Obter_String_Campo(T->LCampos->Inicio->Info);
     // puts(string);
     }

}

void testes()
{
    debugTxt("AREA DE TESTES: ", FICH_DEBUG);

    BDadosCoupe *BD = Criar_BDados("BD-Coupe", "Versao 1.0");

    TABELA *T = Criar_Tabela(BD, "CLIENTES");
    TABELA *T2 = Criar_Tabela(BD, "PRODUTOS");
    TABELA *T3 = Criar_Tabela(BD, "LOGIN");

  //RemoverElementoLG(BD->LTabelas, T1, Destruir_Tabela, Comparar_Tabelas );
   // RemoverUltimoLG(BD->LTabelas, Destruir_Tabela);



    Add_Campo_Tabela(T, "ID", "INT");
    Add_Campo_Tabela(T, "NOME", "STRING");
    Add_Campo_Tabela(T, "Telemovel", "STRING");
    Add_Valores_Tabela(T, "23;Joao;666-655");
    Add_Valores_Tabela(T, "24;Maria;132-444");
    Add_Valores_Tabela(T, "25;Pedro;1323-2322");

    Add_Campo_Tabela(T2, "id", "INT");
    Add_Campo_Tabela(T2, "nome", "STRING");

    Add_Valores_Tabela(T2, "23;Pera");
    Add_Valores_Tabela(T2, "24;Laranja");
    Add_Valores_Tabela(T2, "25;Morango");




   Exportar_BDados_Ficheiro_Texto(BD, "base_dados.txt");
   Exportar_BDados_Excel(BD, "excel.csv");




  //  Add_Valores_Tabela_BDados(BD, "CLIENTES", "23;Joao");

      Mostrar_BDados_toda(BD);

   // Destruir_BDados(BD);


    debugTxt("FIM DOS TESTES: ", FICH_DEBUG);

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
    geradorRegistos(10);
  // testeMemoria(99999999);
   // testes();

    return 0;
}
