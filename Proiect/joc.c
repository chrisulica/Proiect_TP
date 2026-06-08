#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "joc.h"
#include "tabla.h"
#include "mutari.h"
#include "ai.h"
#include <raylib.h>

typedef enum{
    STARE_MENIU,
    STARE_SELECTIE_MOD,
    STARE_IN_JOC,
    STARE_PAUZA
} StareAplicatie;

int litera_la_index(char litera)
{
    return (litera - 'a');
}

int cifra_la_index(char cifra)
{
    return (cifra - '1');
}

int DeseneazaButon(Rectangle dreptunghi, const char *text)
{
    Vector2 mousePoint = GetMousePosition();
    int apasat =0; 
    Color culoare_buton = GetColor(0xF5F0E6FF);

    if(CheckCollisionPointRec(mousePoint, dreptunghi)){
        culoare_buton=GRAY;
        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            apasat =1;
    }
    
    DrawRectangleRec(dreptunghi, culoare_buton);
    DrawRectangleLinesEx(dreptunghi,3,BLACK);

    int textWidth = MeasureText(text, 30);
    DrawText(text, dreptunghi.x + (dreptunghi.width - textWidth)/2, dreptunghi.y + (dreptunghi.height - 30)/2, 30, BLACK);

    return apasat;
}

void porneste_joc(piesa tabla[8][8])
{
    Texture2D t_alb[7];
    t_alb[pion] = LoadTexture("assets/pion_alb.png");
    t_alb[turn] = LoadTexture("assets/turn_alb.png");
    t_alb[cal] = LoadTexture("assets/cal_alb.png");
    t_alb[nebun] = LoadTexture("assets/nebun_alb.png");
    t_alb[regina] = LoadTexture("assets/regina_alb.png");
    t_alb[rege] = LoadTexture("assets/rege_alb.png");

    Texture2D t_negru[7];
    t_negru[pion] = LoadTexture("assets/pion_negru.png");
    t_negru[turn] = LoadTexture("assets/turn_negru.png");
    t_negru[cal] = LoadTexture("assets/cal_negru.png");
    t_negru[nebun] = LoadTexture("assets/nebun_negru.png");
    t_negru[regina] = LoadTexture("assets/regina_negru.png");
    t_negru[rege] = LoadTexture("assets/rege_negru.png");   

    Texture2D t_tabla = LoadTexture("assets/tabla.png");
    Texture2D t_fundal = LoadTexture("assets/fundal.png");

    int latura = 100;
    int margin =40;

    int selectat =0;
    int sel_l= -1, sel_c =-1;
    int joc_activ =1;
    culoare_piesa randul_curent =alb;
    int ep_l = -1, ep_c =-1;

    char istoric_mutari[500][20];
    int nr_mutari=0;

    StareAplicatie stare_curenta = STARE_MENIU;
    int mod_ai=0;

    while(!WindowShouldClose())
    {
        if(stare_curenta == STARE_MENIU) //meniu pornire
        {
            BeginDrawing();
            DrawTexture(t_fundal, 0, 0,WHITE);
            DrawText("Jocul mintii: SAH",390, 150, 50, BLACK);

            if(DeseneazaButon((Rectangle){390, 300, 400, 80}, "Porneste jocul"))
            {
                stare_curenta=STARE_SELECTIE_MOD;
            }
            if(DeseneazaButon((Rectangle){390, 450, 400, 80}, "Inchide jocul")) break;

            EndDrawing();
        } else if(stare_curenta == STARE_SELECTIE_MOD) //selectia modului de joc
        {
            BeginDrawing();
            DrawTexture(t_fundal, 0, 0, WHITE);


            DrawText("Alege modul de joc:",360, 150, 50, BLACK);

            if(DeseneazaButon((Rectangle){390, 300, 400, 80}, "2 PLAYERS - local"))
            {
                mod_ai=0;
                stare_curenta = STARE_IN_JOC;
                initializeaza_tabla(tabla);
                joc_activ=1; randul_curent=alb;
            }
            if(DeseneazaButon((Rectangle){390, 450, 400, 80}, "SINGLEPLAYER (vs AI)")) 
            {
                mod_ai=1;
                stare_curenta=STARE_IN_JOC;
                initializeaza_tabla(tabla);
                joc_activ=1; randul_curent=alb;
            }
            if(DeseneazaButon((Rectangle){20,20,150,50}, "Inapoi"))
            {
                stare_curenta = STARE_MENIU;
            }

            EndDrawing();
        } else if(stare_curenta==STARE_IN_JOC || stare_curenta == STARE_PAUZA) //pornire joc
        {
            if(stare_curenta == STARE_IN_JOC)
            {
             if(mod_ai == 1 && randul_curent == negru && joc_activ)
            {
                if(mod_ai==1 && randul_curent == negru && joc_activ)
                {
                    int ai_sl, ai_sc, ai_dl, ai_dc;
                    mutare_ai(tabla, negru, &ep_l, &ep_c, &ai_sl, &ai_sc, &ai_dl, &ai_dc);
                    sprintf(istoric_mutari[nr_mutari], "%d. %c%d - %c%d", (nr_mutari/2)+1, ai_sc + 'a', ai_sl + 1, ai_dc + 'a', ai_dl + 1);
                    nr_mutari++;

                    randul_curent = alb;
                    if(este_in_sah(tabla, randul_curent)) {
                        if(!are_mutari_valide(tabla, randul_curent, ep_l, ep_c)) joc_activ = 0;
                    } else {
                        if(!are_mutari_valide(tabla, randul_curent, ep_l, ep_c)) joc_activ = 0;
                    }   
                }
            } 
            if(joc_activ)
            {
                if(!(mod_ai==1 && randul_curent == negru))
                {
                    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        int mx = GetMouseX();
                        int my = GetMouseY();

                        if(mx >= margin && mx < margin +800 && my >= margin && my < margin +800)
                        {
                            int col =(mx-margin)/latura;
                            int lin = 7-((my-margin)/latura);

                            if(tabla[lin][col].tip != gol && tabla[lin][col].culoare==randul_curent)
                            {
                                selectat=1;
                                sel_l=lin;
                                sel_c=col;
                            }
                        }
                    }
                    if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && selectat)
                    {
                        int col_stop = GetMouseX() / latura;
                        int lin_stop = 7 - (GetMouseY() / latura);

                        if(col_stop >=0 && col_stop <8 && lin_stop >=0 && lin_stop<8)
                        {
                            if(este_mutare_valida(tabla, sel_l, sel_c, lin_stop,col_stop,randul_curent,ep_l,ep_c))
                            {
                                piesa piesa_mutata = tabla[sel_l][sel_c];
                                piesa temp_dest = tabla[lin_stop][col_stop];
                                
                                tabla[lin_stop][col_stop] = tabla[sel_l][sel_c];
                                tabla[sel_l][sel_c].tip = gol;
                                tabla[sel_l][sel_c].culoare = fara_culoare;

                                if(este_in_sah(tabla, randul_curent))
                                {
                                    tabla[sel_l][sel_c] = piesa_mutata;
                                    tabla[lin_stop][col_stop] = temp_dest;
                                } else {
                                    sprintf(istoric_mutari[nr_mutari], "%d. %c%d - %c%d", (nr_mutari/2)+1, sel_c + 'a', sel_l+1, col_stop +'a', lin_stop +1);
                                    nr_mutari++;
                                    
                                    if(piesa_mutata.tip == pion && sel_c != col_stop && temp_dest.tip == gol)
                                    {
                                        tabla[sel_l][col_stop].tip = gol;
                                        tabla[sel_l][col_stop].culoare = fara_culoare;
                                    } //en passant

                                    if(piesa_mutata.tip == rege && abs(sel_c - col_stop) == 2)
                                    {
                                        if(col_stop == 6)
                                        {
                                            tabla[sel_l][5] = tabla[sel_l][7];
                                            tabla[sel_l][7].tip = gol;
                                            tabla[sel_l][7].culoare = fara_culoare;
                                            tabla[sel_l][5].a_mutat =1;
                                        } else if(col_stop == 2) {
                                            tabla[sel_l][3] = tabla[sel_l][0];
                                            tabla[sel_l][0].tip = gol;
                                            tabla[sel_l][0].culoare = fara_culoare;
                                            tabla[sel_l][3].a_mutat =1;
                                        } 
                                    }
                                    tabla[lin_stop][col_stop].a_mutat =1;

                                    if(piesa_mutata.tip == pion && abs(sel_l - lin_stop) == 2)
                                    {
                                        ep_l = (sel_l + lin_stop) / 2;
                                        ep_c=sel_c;
                                    } else {
                                        ep_l =-1;
                                        ep_c= -1;
                                    }

                                    if(tabla[lin_stop][col_stop].tip == pion)
                                    {
                                        if( (randul_curent == alb && lin_stop==7) || (randul_curent== negru && lin_stop == 0))
                                        {
                                            tabla[lin_stop][col_stop].tip = regina;
                                        }
                                    }

                                    randul_curent = (randul_curent == alb) ? negru : alb;

                                    if(este_in_sah(tabla, randul_curent))
                                    {
                                        if(!are_mutari_valide(tabla, randul_curent, ep_l, ep_c))
                                        {
                                            joc_activ=0;
                                        }
                                    } else {
                                        if(!are_mutari_valide(tabla, randul_curent, ep_l, ep_c))
                                        {
                                            joc_activ =0;
                                        }
                                    }
                                    }
                                }
                            }
                            selectat=0;
                        }
                
                    }
                }
             
            }
            BeginDrawing();
            ClearBackground(RAYWHITE);
            Color culoare_margine = GetColor(0x6B4423FF);
            DrawRectangle(0,0,880,880,culoare_margine);

            DrawTexturePro(t_tabla, 
                (Rectangle){0,0, (float)t_tabla.width, (float)t_tabla.height},
                (Rectangle){margin, margin, 800, 800},
                (Vector2){0,0}, 0.0f, WHITE);
            for(int k=0; k<8;k++){
                char litera[2] ={ 'A' +k, '\0'}; 
                char cifra[2] = {'8' - k, '\0'};

                int offsetx_litera = margin +(k*latura) + (latura/2) - (MeasureText(litera,20)/2);
                int offsety_cifra = margin + (k*latura) + (latura/2) -10;

                DrawText(litera,offsetx_litera,10, 20, BLACK);
                DrawText(litera, offsetx_litera, margin +800 +10, 20, BLACK);
               
                DrawText(cifra,12 ,offsety_cifra, 20, BLACK);
                DrawText(cifra, margin +800 + 12,offsety_cifra, 20, BLACK);
            }

            if(este_in_sah(tabla,randul_curent))
            {
                int l_rege =-1, c_rege =-1;
                for(int i =0; i<8; i++)
                {
                    for(int j=0; j<8; j++)
                    {
                        if(tabla[i][j].tip == rege && tabla[i][j].culoare == randul_curent)
                        {
                            l_rege = i;
                            c_rege = j;
                            break;
                        }
                    }
                    if(l_rege != -1) break;
                }
                DrawRectangle(c_rege * latura + margin, (7 - l_rege) * latura + margin, latura, latura, (Color){255, 0, 0, 150});
            }//in sah

            for(int i=0; i<8; i++)
            {
                for(int j=0; j<8; j++)
                {
                    if(tabla[i][j].tip != gol)
                    {
                        if(selectat && i == sel_l && j == sel_c) continue;

                        Texture2D tex = (tabla[i][j].culoare == alb) ? t_alb[tabla[i][j].tip] : t_negru[tabla[i][j].tip];

                        float dimensiune_piesa = 95.0f;
                        float offset = (dimensiune_piesa - latura) / 2.0f;

                        Rectangle sursa = {0, 0, (float)tex.width, (float)tex.height};
                        Rectangle destinatie ={ (j*latura) - offset + margin, ((7-i)*latura) - offset + margin, dimensiune_piesa, dimensiune_piesa};
                        Vector2 origine = {0,0};

                        DrawTexturePro(tex, sursa, destinatie, origine, 0.0f, WHITE);
                    }
                }
            } //piese

            if(selectat){
                piesa p = tabla[sel_l][sel_c];
                Texture2D tex = (p.culoare == alb) ? t_alb[p.tip] : t_negru[p.tip];
                
                float dimensiune_piesa = 95.0f;
                Rectangle sursa = {0, 0, (float)tex.width, (float)tex.height};
                Rectangle destinatie = { GetMouseX() - (dimensiune_piesa / 2.0f), GetMouseY() - (dimensiune_piesa /2.0f), dimensiune_piesa, dimensiune_piesa};
                Vector2 origine = {0,0};

                DrawTexturePro(tex, sursa, destinatie, origine, 0.0f, WHITE);
            }
            
            DrawRectangle(880, 0, 300, 880, GetColor(0xE8DAC3FF));
            DrawLine(880, 0, 880, 880, DARKGRAY);

            if(DeseneazaButon((Rectangle){905, 20, 250, 50}, "MENIU")) {
                stare_curenta= STARE_PAUZA;
            }

            DrawText(TextFormat("Randul: %s", (randul_curent == alb) ? "ALB" : "NEGRU"),905, 100, 30, (randul_curent == alb) ? WHITE : BLACK);

            DrawText("Istoric mutari:",905, 160, 25, GetColor(0x2B1A10FF));
            DrawLine(905, 190, 1155, 190, DARKGRAY);
            
            int maxim_afisat =18;
            int start_log = (nr_mutari > maxim_afisat) ? nr_mutari - maxim_afisat : 0;

            for(int i = start_log; i<nr_mutari; i++)
            {
                DrawText(istoric_mutari[i], 905, 210 + ((i - start_log) *30), 20, GetColor(0x2B1A10FF));
            }
            
            if(!joc_activ)
            {
                DrawRectangle(0, 390, 880, 100, (Color){0, 0, 0, 200});
                DrawText("Stop joc!",340, 415, 50, RED);
            }

            if(stare_curenta == STARE_PAUZA)
            {
                DrawRectangle(0, 0, 1180, 880, (Color){0,0,0,180});
                DrawText("Pauza", 490, 150, 60, WHITE);

                if(DeseneazaButon((Rectangle){390, 280, 400, 80}, "Continua jocul")) stare_curenta = STARE_IN_JOC;
                if(DeseneazaButon((Rectangle){390, 400, 400, 80}, "Reseteaza jocul")) {
                    initializeaza_tabla(tabla);
                    joc_activ =1;
                    randul_curent = alb;
                    nr_mutari = 0;
                    selectat =0;
                    stare_curenta=STARE_IN_JOC;
                }
                if(DeseneazaButon((Rectangle){390, 520, 400, 80}, "Opreste jocul")) stare_curenta=STARE_MENIU;
            }

            EndDrawing();

        }
    }
    for (int i =1; i<=6; i++)
    {
        UnloadTexture(t_alb[i]); 
        UnloadTexture(t_negru[i]);
    }
    UnloadTexture(t_tabla);
    UnloadTexture(t_fundal);
}