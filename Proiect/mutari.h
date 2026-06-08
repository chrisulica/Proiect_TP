#ifndef MUTARI_H
#define MUTARI_H

#include "tipuri.h"

int este_mutare_valida(piesa tabla[8][8], int l_start, int c_start, int l_stop, int c_stop, culoare_piesa randul_curent, int ep_l, int ep_c);
int este_in_sah(piesa tabla[8][8], culoare_piesa culoare_rege);
int are_mutari_valide(piesa tabla[8][8], culoare_piesa jucator, int ep_l, int ep_c);

#endif 