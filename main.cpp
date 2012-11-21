#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "include/Map.h"

// Taille de la fenêtre
#define LARGEUR 1024
#define HAUTEUR 780

#define FRAMES_PER_SECOND 50

#define FIRE_TIME 100
#define MINE_TIME 800

#undef main

using namespace std;

int main(int argc, char *argv[])
{

    // Initialisation de SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Création de la surface d'affichage qui est en OpenGL
    // (changez le titre si besoin)
    SDL_WM_SetCaption("Spaceship",NULL);
    SDL_Surface* ecran = SDL_SetVideoMode(LARGEUR, HAUTEUR, 32, SDL_OPENGL);

    // Initialisation de l'affichage OpenGL
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D(0,LARGEUR,0,HAUTEUR); // Taille de l'écran
    SDL_Flip(ecran);

    // Boucle d'évènements
    bool continuer = true;

    SDL_Event event;
    SDL_EnableKeyRepeat(10,10); // Activation de la répétition de touches

    // Gestion des images par seconde
    Uint32 last_time = SDL_GetTicks(); // heure actuelle, derniere mise à jour
    Uint32 current_time;

    // Carte
    //Map map;

    // Tableau des états des touches
    Uint8 * keystate;

    while (continuer) {
        SDL_PollEvent(&event);

        // Selon le type d'evt, on choisi quoi faire
        switch(event.type) {
            case SDL_QUIT:
                continuer = false;
                break;

            case SDL_KEYDOWN:
                keystate = SDL_GetKeyState(NULL);

                if (keystate[SDLK_RIGHT]) {

                }

                if (keystate[SDLK_LEFT]) {

                }

                if (keystate[SDLK_UP]) {

                }

                if (keystate[SDLK_DOWN]) {

                }

                if (keystate[SDLK_q]) {
                }

                if (keystate[SDLK_w]) {

                }

                if (keystate[SDLK_SPACE]) {

                }

                break;
        }

        // Images par seconde
        current_time = SDL_GetTicks();
        while (current_time - last_time < (1000/FRAMES_PER_SECOND)) {
            // On se met en pause le temps voulu
            SDL_Delay(1000/FRAMES_PER_SECOND - (current_time - last_time));
            current_time = SDL_GetTicks();
        }

        last_time = SDL_GetTicks();

        // On efface la fenêtre
        glClear(GL_COLOR_BUFFER_BIT);

        // Dessin de la map
        //map.Draw(0, LARGEUR, 0, HAUTEUR);

        // Affichage (en double buffering)
        glFlush();
        SDL_GL_SwapBuffers();
    }

    // Fin du programme
    SDL_Quit();
    return 0;
}
