#include "ai.h"
#include "mutari.h"
#include <stdlib.h>

int valoare_piesa(tip_piesa tip)
{
    switch(tip) {
        case pion: return 10;
        case cal: return 30;
        case nebun:return 30;
        case turn:return 50;
        case regina: return 90;
        case rege: return 900;
        default: return 0;
    }
}

int evalueaza_tabla(piesa tabla[8][8]) {
    int scor = 0;
    for(int i = 0; i<8; i++) {
        for(int j = 0; j<8; j++) {
            if(tabla[i][j].tip !=gol) {
                int val = valoare_piesa(tabla[i][j].tip);
                if(tabla[i][j].culoare==negru) {
                    scor+= val;
                } else {
                    scor-= val;
                }
            }
        }
    }
    return scor;
}

int minimax(piesa tabla[8][8], int adancime, int este_max, int ep_l, int ep_c)
{
    if(adancime == 0) return evalueaza_tabla(tabla);

    if(este_max)
    {
        int cel_mai_bun = INT_MIN;
        for(int sl=0; sl<8;sl++)
        {
            for(int sc=0; sc<8; sc++)
            {
                if(tabla[sl][sc].culoare == negru)
                {
                    for(int dl=0; dl<8; dl++)
                    {
                        for(int dc=0; dc<8; dc++)
                        {
                            if(este_mutare_valida(tabla, sl, sc, dl, dc, negru, ep_l, ep_c))
                            {
                                piesa orig=tabla[sl][sc];
                                piesa dest=tabla[dl][dc];
                                tabla[dl][dc] = tabla[sl][sc];
                                tabla[sl][sc].tip = gol;
                                int val=minimax(tabla, adancime -1, 0, ep_l, ep_c);
                                tabla[sl][sc] = orig; tabla[dl][dc] = dest;
                                if (val > cel_mai_bun) cel_mai_bun = val;
                            }
                        }
                    }
                }
            }
        }
        return cel_mai_bun;
    } else {
        int cel_mai_bun = INT_MAX;
        for(int sl=0; sl<8; sl++)
        {
            for(int sc=0; sc<8; sc++)
            {
                if(tabla[sl][sc].culoare == alb)
                {
                    for(int dl=0; dl<8; dl++)
                    {
                        for(int dc=0; dc<8; dc++)
                        {
                            if (este_mutare_valida(tabla, sl, sc, dl, dc, alb, ep_l, ep_c))
                            {
                                piesa orig = tabla[sl][sc]; 
                                piesa dest = tabla[dl][dc];
                                tabla[dl][dc] = tabla[sl][sc]; 
                                tabla[sl][sc].tip = gol;
                                int val = minimax(tabla, adancime - 1, 1, ep_l, ep_c);
                                tabla[sl][sc] = orig; tabla[dl][dc] = dest;
                                if (val < cel_mai_bun) cel_mai_bun = val;
                            }
                        }
                    }
                }
            }
        }
        return cel_mai_bun;
    }
}

void mutare_ai(piesa tabla[8][8], culoare_piesa culoare_ai, int *ep_l, int*ep_c, int *sl_out, int *sc_out, int *dl_out, int *dc_out)
{
    int scor_bun = INT_MIN;

    for (int sl = 0; sl < 8; sl++) 
    {
        for (int sc = 0; sc < 8; sc++) 
        {
            if (tabla[sl][sc].culoare == culoare_ai)
             {
                for (int dl = 0; dl < 8; dl++)
                 {
                    for (int dc = 0; dc < 8; dc++)
                     {
                        if (este_mutare_valida(tabla, sl, sc, dl, dc, culoare_ai, *ep_l, *ep_c)) 
                        {
                            piesa orig = tabla[sl][sc]; 
                            piesa dest = tabla[dl][dc];
                            tabla[dl][dc] = tabla[sl][sc]; 
                            tabla[sl][sc].tip = gol;
                            
                            int scor = minimax(tabla, 2, 0, *ep_l, *ep_c);
                            
                            tabla[sl][sc] = orig; tabla[dl][dc] = dest;
                            
                            if (scor > scor_bun) {
                                scor_bun = scor;
                                *sl_out = sl;
                                *sc_out = sc;
                                *dl_out = dl; 
                                *dc_out = dc;
                            }
                        }
                    }
                }
            }
        }
    }
}

