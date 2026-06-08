#include <stdio.h>
#include <ctype.h>
#include "tabla.h"

void initializeaza_tabla(piesa tabla[8][8])
{
    for( int i = 0 ; i < 8 ; i++ )
        {
            for( int j = 0 ; j<8 ; j++)
            {
                tabla[i][j].tip = gol;
                tabla[i][j].culoare = fara_culoare;
                tabla[i][j].a_mutat =0;
            }
        }

    for(int j = 0; j<8 ; j++)
    {
        tabla[1][j].tip = pion;
        tabla[1][j].culoare = alb;
        tabla[1][j].a_mutat = 0;
        
        tabla[6][j].tip = pion;
        tabla[6][j].culoare = negru;
        tabla[6][j].a_mutat = 0;
    }

    tip_piesa ordine_baza[8] = {turn, cal, nebun, regina, rege, nebun, cal, turn};

    for(int j = 0 ; j <8 ; j++)
    {
        tabla[0][j].tip = ordine_baza[j];
        tabla[0][j].culoare = alb;
        tabla[0][j].a_mutat =0;
        
        tabla[7][j].tip = ordine_baza[j];
        tabla[7][j].culoare = negru;
        tabla[7][j].a_mutat = 0;
    }
}

void afiseaza_tabla(piesa tabla[8][8])
{
    printf("\n  a b c d e f g h\n");

    
    for(int i = 7; i>= 0; i--)
    {
        printf("%d ", i +1);

        for(int j = 0 ; j < 8 ; j++)
        {
            if (tabla[i][j].tip == gol)
            {
                printf(". ");
            }
            else
            {
                char simbol;

                switch(tabla[i][j].tip)
                {
                    case pion: simbol = 'p'; break;
                    case cal: simbol = 'c'; break;
                    case nebun: simbol = 'n'; break;
                    case turn: simbol = 't'; break;
                    case regina: simbol = 'q'; break; //Queen
                    case rege: simbol = 'k'; break; //King
                    default: simbol = '?';
                }

                if(tabla[i][j].culoare == alb) // ALB - litere mari, NEGRU - litere mici
                {
                    simbol = toupper(simbol);
                }

                printf("%c ", simbol);
            }
        }
        printf("%d\n", i+1);
    }
    printf("  a b c d e f g h\n\n");
}