#include <stdio.h>
#include <stdlib.h>
#include "mutari.h"

int drum_liber(piesa tabla[8][8], int l_start, int c_start, int l_stop, int c_stop)
{
    int pas_l = (l_stop > l_start) ? 1 : ((l_stop < l_start) ? -1: 0);
    int pas_c = (c_stop > c_start) ? 1 : ((c_stop < c_start) ? -1 : 0);

    int l_curent = l_start + pas_l;
    int c_curent = c_start + pas_c;

    while( l_curent != l_stop || c_curent != c_stop)
    {
        if( tabla[l_curent][c_curent].tip != gol)
        {
            return 0;
        }

        l_curent += pas_l;
        c_curent += pas_c;
    }
    return 1;
}

int este_mutare_valida (piesa tabla[8][8], int l_start, int c_start, int l_stop, int c_stop, culoare_piesa randul_curent)
{
    piesa piesa_start = tabla[l_start][c_start];
    piesa piesa_stop = tabla[l_stop][c_stop];

    if(l_start == l_stop && c_start == c_stop) return 0;
    
    if(piesa_start.tip == gol || piesa_start.culoare != randul_curent) return 0;
    
    if (piesa_stop.tip != gol && piesa_stop.culoare == randul_curent) return 0;

    int diff_l = l_stop - l_start;
    int diff_c = c_stop - c_start;
    int abs_l = abs(diff_l);
    int abs_c = abs(diff_c);

    switch (piesa_start.tip)
    {
        case pion:
        if(piesa_start.culoare == alb)
        {
            if(diff_c == 0 && piesa_stop.tip == gol)
            {
                if (diff_l == 1) return 1;
                if(l_start == 1 && diff_l == 2 && tabla[2][c_start].tip == gol) return 1;
            }
            else if(abs_c == 1 && diff_l == 1 && piesa_stop.tip != gol)
                return 1;
        } else {
            if(diff_c == 0 && piesa_stop.tip == gol) {
                if(diff_l == -1) return 1;
                if (l_start == 6 && diff_l == -2 && tabla[5][c_start].tip == gol) return 1;
            }
            else if (abs_c == 1 && diff_l == -1 && piesa_stop.tip != gol)
            {
                return 1;
            }
        }
        return 0;

        case cal:
            if ( (abs_l == 2 && abs_c == 1)  || (abs_l == 1 && abs_c == 2)) return 1;
            return 0;

        case nebun: 
            if (abs_l != abs_c) return 0;
            return drum_liber(tabla, l_start, c_start, l_stop, c_stop);

        case turn:
            if(diff_l != 0 && diff_c !=0) return 0;
            return drum_liber(tabla, l_start, c_start, l_stop, c_stop);

        case regina:
            if ((diff_l != 0 && diff_c != 0) && (abs_l != abs_c)) return 0;
            return drum_liber(tabla, l_start, c_start, l_stop, c_stop);

        case rege:
            if (abs_l <=1 && abs_c <= 1) return 1;
            return 0;
        
        default: 
            return 0;

    }
}

