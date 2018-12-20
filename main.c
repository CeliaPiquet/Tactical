#include "editor.h"


int main( int argc, char * argv[] )
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        fprintf(stdout,"Echec : %s \n", SDL_GetError());
    }

    SDL_Window* pWindow = NULL;
    pWindow = SDL_CreateWindow("Test fen�tre",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

    if (pWindow){
        editor(pWindow);
        SDL_DestroyWindow(pWindow);
    }



    else {
        fprintf(stderr,"Erreur cr�ation fen�tre : %s \n", SDL_GetError());
    }

    SDL_Quit();

    return 1;
}
