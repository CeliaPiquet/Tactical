#include "../Headers/editor.h"


int main( int argc, char * argv[] )
{
    int toContinue =1;
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        fprintf(stdout,"Echec : %s \n", SDL_GetError());
    }

    SDL_Window* screen = NULL;
    screen = SDL_CreateWindow("Test fenêtre",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 320, SDL_WINDOW_SHOWN);

    if (screen){
        editor(screen);
        SDL_DestroyWindow(screen);
    }
    else {
        fprintf(stderr,"Erreur création fenêtre : %s \n", SDL_GetError());
    }

    SDL_Quit();

    return 1;
}
