#include <stdio.h>
#include "tabla.h"
#include "joc.h"
#include "raylib.h"

int main()
{
    const int latime = 1180;
    const int inaltime = 880;

    InitWindow(latime, inaltime, "Simulator de Sah");
    SetTargetFPS(60);

    piesa tabla[8][8];
    initializeaza_tabla(tabla);
    porneste_joc(tabla);
    
    CloseWindow();

    return 0;
}