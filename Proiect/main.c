#include <stdio.h>
#include "tabla.h"
#include "joc.h"

int main()
{
    piesa tabla[8][8];

    initializeaza_tabla(tabla);

    printf("=== SIMULATOR DE SAH ===\n");

    porneste_joc(tabla);
    
    return 0;
}