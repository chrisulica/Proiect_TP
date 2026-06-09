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

int este_mutare_valida(piesa tabla[8][8], int l_start, int c_start, int l_stop, int c_stop, culoare_piesa randul_curent, int ep_l, int ep_c)
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
            if(piesa_start.culoare == alb) {
                if(diff_c == 0 && piesa_stop.tip == gol) {
                    if (diff_l == 1) return 1;
                    if(l_start == 1 && diff_l == 2 && tabla[2][c_start].tip == gol) return 1;
                } else if(abs_c == 1 && diff_l == 1) {
                    if(piesa_stop.tip != gol) return 1;
                    if(l_stop == ep_l && c_stop == ep_c) return 1; 
                } 
                } else { 
                if(diff_c == 0 && piesa_stop.tip == gol) {
                if(diff_l == -1) return 1;
                    if (l_start == 6 && diff_l == -2 && tabla[5][c_start].tip == gol) return 1;
                } else if (abs_c == 1 && diff_l == -1) {
                    if(piesa_stop.tip != gol) return 1;
                    if(l_stop == ep_l && c_stop == ep_c) return 1;
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
            if (abs_l <= 1 && abs_c <= 1) return 1;
            if (diff_l == 0 && abs_c == 2 && piesa_start.a_mutat == 0) {
                if (este_in_sah(tabla, randul_curent)) return 0;
                int c_turn = (c_stop > c_start) ? 7 : 0;
                if (tabla[l_start][c_turn].tip == turn && tabla[l_start][c_turn].a_mutat == 0) {
                    return drum_liber(tabla, l_start, c_start, l_start, c_turn);
                }
            }
            return 0;
        
        default: 
            return 0;

    }
}

int este_in_sah(piesa tabla[8][8], culoare_piesa culoare_rege)
{
    int l_rege= -1, c_rege = -1;

    for(int i =0; i<8; i++){
        for(int j=0; j<8; j++){
            if(tabla[i][j].tip == rege && tabla[i][j].culoare == culoare_rege){
                l_rege = i;
                c_rege = j;
                break;
            }
        }
        if(l_rege != -1)break;
    }

    culoare_piesa inamic = (culoare_rege == alb) ? negru : alb;

    for(int i=0; i<8; i++){
        for(int j=0;j<8;j++){
            if(tabla[i][j].culoare == inamic){
                if(este_mutare_valida(tabla, i, j, l_rege, c_rege, inamic, -1, -1)){
                    return 1;
                }
            }
        }
    }
    return 0;
}

int este_lipsa_material(piesa tabla[8][8])
{
    int nr_cai =0;
    int nr_nebuni=0;
    int alte_piese=0;

    for(int i=0; i<8;i++)
    {
        for(int j=0; j<8;j++)
        {
            if(tabla[i][j].tip == gol || tabla[i][j].tip == rege) continue;
            if(tabla[i][j].tip == cal) nr_cai++;
            else if(tabla[i][j].tip == nebun) nr_nebuni++;
            else alte_piese++;
        }
    }
    if(alte_piese>0) return 0;
    if(nr_cai ==0 && nr_nebuni==0) return 1;
    if(nr_cai==0 && nr_nebuni ==0) return 1;
    if((nr_cai == 1 && nr_nebuni == 0) || (nr_cai == 0 && nr_nebuni == 1)) return 1;
    return 0;
}

int are_mutari_valide(piesa tabla[8][8], culoare_piesa jucator, int ep_l, int ep_c)
{
    for(int l_start =0; l_start<8; l_start++){
        for(int c_start =0; c_start<8; c_start++){
            if(tabla[l_start][c_start].culoare == jucator){
                for(int l_stop =0; l_stop<8; l_stop ++){
                    for(int c_stop=0;c_stop<8; c_stop++)
                    {
                        if(este_mutare_valida(tabla, l_start, c_start, l_stop, c_stop, jucator,ep_l, ep_c)){
                            piesa dest_salvata = tabla[l_stop][c_stop];
                            piesa piesa_mutata = tabla[l_start][c_start];

                            tabla[l_stop][c_stop] = piesa_mutata;
                            tabla[l_start][c_start].tip = gol;
                            tabla[l_start][c_start].culoare = fara_culoare;

                            int in_sah = este_in_sah(tabla, jucator);

                            tabla[l_start][c_start] = piesa_mutata;
                            tabla[l_stop][c_stop] = dest_salvata;

                            if(!in_sah)
                                return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

