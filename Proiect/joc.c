#include <stdio.h>
#include <string.h>
#include "joc.h"
#include "tabla.h"
#include "mutari.h"

int litera_la_index(char litera)
{
    return (litera - 'a');
}

int cifra_la_index(char cifra)
{
    return (cifra - '1');
}

void porneste_joc(piesa tabla[8][8])
{
    int joc_activ = 1;
    culoare_piesa randul_curent = alb;
    char comanda[10];

    while(joc_activ)
    {
        afiseaza_tabla(tabla);

        if(randul_curent == alb)
        {
            printf("Este randul ALBULUI. ");
        }
        else
        {
            printf("Este randul NEGRULUI. ");
        }

        printf("Introdu mutarea sau 'exit' pentru a iesi: ");
        scanf("%s", comanda);

        if(strcmp(comanda, "exit") == 0)
        {
            printf("Stop joc.\n");
            joc_activ = 0;
            continue;
        }
        
        if(strlen(comanda) != 4)
        {
            printf("Format invalid! Foloseste notatia de 4 caractere (ex: e2e4). \n");
            continue;
        }
        
        int col_start = litera_la_index(comanda[0]);
        int lin_start = cifra_la_index(comanda[1]);
        int col_stop = litera_la_index(comanda[2]);
        int lin_stop = cifra_la_index(comanda[3]);

        if(col_start < 0 || col_start > 7 || lin_start < 0 || lin_start > 7 ||
            col_stop < 0 || col_stop > 7 || lin_stop < 0 || lin_stop > 7)
            {
                printf("Mutare in afara tablei \n");
                continue;
            }
        
        if (!este_mutare_valida(tabla, lin_start, col_start, lin_stop, col_stop, randul_curent)) 
        { 
            printf("Mutare ilegala!\n"); continue;
        }

        tabla[lin_stop][col_stop] = tabla[lin_start][col_start];

        tabla[lin_start][col_start].tip = gol;
        tabla[lin_start][col_start].culoare = fara_culoare;

        if(randul_curent == alb)
        {
            randul_curent = negru;
        }
        else
        {
            randul_curent = alb;
        }
    }
}