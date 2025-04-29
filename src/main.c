// NOM prenom etudiant 1 : FOURNET Romain
// NOM prenom etudiant 2 : LOISON Nathan

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "maSDL.h"
#include "SDL_VSYNC.h"
#include "sort.h"
#include "listeDouble.h"

// #include "types.h"
#include "ligneBus.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NB_BUS 4 // à ajuster, mais ≤ *nbLignes
Tbus tableauBus[NB_BUS];
int indexBusActuel = 0;
LTexture gSpriteBus[NB_BUS];

/*--------- Main ---------------------*/
int main(int argc, char *argv[])
{
        // SDL
        // fenetre dans windows
        SDL_Window *gWindow = NULL;
        SDL_Init(SDL_INIT_VIDEO);

        // la texture (chargee dans la ram de la carte graphique) target representant tout le jeu
        SDL_Renderer *gRenderer = NULL;

        // Les textures, le type Ltexture est defini dans SDL_VSYNC.h

        LTexture gSpriteArretBus;

        // Start up SDL and create window
        if (!init(&gWindow, &gRenderer)) // initialise la fenetre SDL et charge UNE texture
        {
                printf("Failed to initialize!\n");
        }
        else
        {
        // Load media
        if (!loadSprite(&gSpriteArretBus, gRenderer, "./data/arret_bus_50x27.png")){
                fprintf(stdout, "echec de chargement du sprite d'arrêt de bus (%s)\n", SDL_GetError());
        }
            
        // Chargement des textures des bus
        for (int i = 0; i < NB_BUS; i++) {
            if (!loadAnimation(&gSpriteBus[i], gRenderer, "./data/4bus.png")) {
                fprintf(stderr, "Erreur de chargement sprite bus %d\n", i);
            }
        }

                /**********************************************************************/
                /*                                                                    */
                /*              DEFINISSEZ/INITIALISER ICI VOS VARIABLES              */
                /*                                                                    */
                /**********************************************************************/

                int *nbLignes = malloc(sizeof(int));

                TlisteStation *lignesBus = creeLignesDeBus(nbLignes);

                printf("Nombre de lignes : %d\n", *nbLignes);

                // JONCTION ENTRE DEUX LIGNES DE BUS POUR TEST (NE PAS EFFACER)
                TlisteStation nouvelleLigne = jonctionLigneDeBus(lignesBus[0], lignesBus[1]);

                lignesBus = realloc(lignesBus, (*nbLignes + 1) * sizeof(TlisteStation));
                if (lignesBus == NULL)
                {
                        printf("Erreur : échec de la réallocation de mémoire pour lignesBus.\n");
                        exit(EXIT_FAILURE);
                }

                lignesBus[*nbLignes] = nouvelleLigne;

                (*nbLignes)++;

                printf("Nombre total de lignes apres ajout : %d\n", *nbLignes);
                // JONCTION ENTRE DEUX LIGNES DE BUS POUR TEST (NE PAS EFFACER)

                for (int i = 0; i < NB_BUS; i++) {
                        tableauBus[i] = creeBus(i + 1, lignesBus[i]);
                }

                // affiche sur la console les stations et troncons des lignes de bus
                for (int i = 0; i < *nbLignes; i++)
                {
                        afficheConsoleLigneBus(lignesBus[i]);
                }

                // SUPRESSION D'UNE STATION DE BUS POUR TEST (NE PAS EFFACER)
                supprimerStation(&lignesBus[0], 1);
                // SUPRESSION D'UNE STATION DE BUS POUR TEST (NE PAS EFFACER)

                // TEST DE LA FONCTION CIRCULAIRE (NE PAS EFFACER)
                //circulaire(&lignesBus[0]);
                // TEST DE LA FONCTION CIRCULAIRE (NE PAS EFFACER)

                int tourCount = -1;

                // Current animation frame
                int frame = 0;

                // affiche et initialise le sprite du bus au depart
                for(int i = 0; i < NB_BUS; i++){
                        Affiche_Sprite(&gSpriteBus[i], gRenderer, getPosXBus(tableauBus[i]), getPosYBus(tableauBus[i]), getIdFrame(frame));
                }

                // boucle principale du jeu
                int cont = 1;
                int incXDeplSpriteBus1 = 0, incYDeplSpriteBus1 = 0; // deplacement du sprite du bus e chaque passage dans la boucle principale
                int incXDeplSpriteBus2 = 0, incYDeplSpriteBus2 = 0;
                while (cont != 0)
                {
                        SDL_PumpEvents(); // do events

                        /***********************************************************************/
                        /*                                                                     */
                        // APPELEZ ICI VOS FONCTIONS QUI FONT EVOLUER LE "JEU"
                        /*                                                                     */
                        /***********************************************************************/
                        
                        const Uint8 *pKeyStates = SDL_GetKeyboardState(NULL);
                        
                        Tbus busActuel = tableauBus[indexBusActuel];
                        // les touches sont lues en Qwerty
                        if (pKeyStates[SDL_SCANCODE_W])
                        {
                                /* Ajouter vos appels de fonctions ci-dessous qd le joueur appuye sur Z */
                                printf("\nTouche Z, sens deplacement depart vers terminus\n");
                                setSensParcours(busActuel, depart_vers_arrivee);
                        }
                        if (pKeyStates[SDL_SCANCODE_S])
                        {

                                printf("\nTouche S, sens deplacement terminus vers depart\n");
                                setSensParcours(busActuel, arrivee_vers_depart);
                        }
                        if (pKeyStates[SDL_SCANCODE_T])
                        {

                                printf("\nTouche T, Tri:\n");
                                TlisteStation ligneActuelle = getActualStation(busActuel);
                                sort(getFirstCell(ligneActuelle));
                        }
                        if (pKeyStates[SDL_SCANCODE_1])
                        {

                                printf("\nTouche 1, Bus au depart de la ligne 1\n");
                                busSurStation(busActuel, lignesBus[0], depart_vers_arrivee);
                                Affiche_Sprite(&gSpriteBus[indexBusActuel], gRenderer, getPosXBus(busActuel), getPosYBus(busActuel), getIdFrame(frame));
                        }
                        if (pKeyStates[SDL_SCANCODE_2])
                        {

                                printf("\nTouche 2, Bus au depart de la ligne 2\n");
                                busSurStation(busActuel, lignesBus[1], depart_vers_arrivee);
                                Affiche_Sprite(&gSpriteBus[indexBusActuel], gRenderer, getPosXBus(busActuel), getPosYBus(busActuel), getIdFrame(frame));
                        }
                        if (pKeyStates[SDL_SCANCODE_3])
                        {

                                printf("\nTouche 3, Bus au depart de la ligne 3\n");
                                busSurStation(busActuel, lignesBus[2], depart_vers_arrivee);
                                Affiche_Sprite(&gSpriteBus[indexBusActuel], gRenderer, getPosXBus(busActuel), getPosYBus(busActuel), getIdFrame(frame));
                        }
                        if (pKeyStates[SDL_SCANCODE_4])
                        {

                                printf("\nTouche 4, Bus au depart de la ligne 3\n");
                                busSurStation(busActuel, lignesBus[3], depart_vers_arrivee);
                                Affiche_Sprite(&gSpriteBus[indexBusActuel], gRenderer, getPosXBus(busActuel), getPosYBus(busActuel), getIdFrame(frame));
                        }
                        if (pKeyStates[SDL_SCANCODE_J])
                        {

                                printf("\nTouche j, Bus au depart de la ligne jointe\n");
                                busSurStation(busActuel, lignesBus[*nbLignes - 1], depart_vers_arrivee);
                                Affiche_Sprite(&gSpriteBus[indexBusActuel], gRenderer, getPosXBus(busActuel), getPosYBus(busActuel), getIdFrame(frame));
                        }
                        if (pKeyStates[SDL_SCANCODE_ESCAPE])
                        {

                                printf("\nTouche ECHAP");
                                cont = 0; // sortie de la boucle
                        }
                        if (pKeyStates[SDL_SCANCODE_LEFT]) {
                                indexBusActuel = (indexBusActuel - 1 + NB_BUS) % NB_BUS;
                                printf("\nTouche <-, Le bus actuel est maintenant : %d", indexBusActuel);
                                SDL_Delay(150); 
                        }
                        if (pKeyStates[SDL_SCANCODE_RIGHT]) {
                                indexBusActuel = (indexBusActuel + 1) % NB_BUS;
                                printf("\nTouche ->, Le bus actuel est maintenant : %d", indexBusActuel);
                                SDL_Delay(150);
                        }
                        // affichage du jeu e chaque tour

                        // on efface toute la fenetre
                        efface_fenetre_texture(gRenderer);

                        // Deplacement de sprite du bus sur la texture
                        for (int i = 0; i < NB_BUS; i++) {
                                int dx = 0, dy = 0;
                                deplaceBus(tableauBus[i], getSensParcours(tableauBus[i]), &dx, &dy);
                                Deplace_Sprite(&gSpriteBus[i], gRenderer, dx, dy, getIdFrame(frame));
                            }

                        // reaffichage e chaque tour de toutes les stations
                        for (int i = 0; i < *nbLignes; i++)
                        {
                                DessineUneLigneBus(lignesBus[i], gSpriteArretBus, gRenderer);
                        }

                        // affichage de la texture ainsi mis e jour
                        maj_fenetre_texture(gRenderer);

                        SDL_Delay(1); // valeur du delai modifiable en fonction de votre CPU
                        ++frame;

                }
                // fin boucle du jeu
        }

        // Free resources and close SDL
        for(int i = 0; i < NB_BUS; i++){   
                free_Ltexture(&gSpriteBus[i]);
        }
        free_Ltexture(&gSpriteArretBus);
        close(gWindow, gRenderer);

        return 0;
}
