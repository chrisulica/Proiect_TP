#ifndef TIPURI_H
#define TIPURI_H

typedef enum{
    gol =0,
    pion,
    cal,
    nebun,
    turn,
    regina,
    rege
}tip_piesa;

typedef enum {
    fara_culoare = 0,
    alb,
    negru
}culoare_piesa;

typedef struct{
    tip_piesa tip;
    culoare_piesa culoare;
    int a_mutat;
}piesa;

#endif
