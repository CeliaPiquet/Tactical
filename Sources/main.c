#include "../Headers/editor.h"


int main( int argc, char * argv[] )
{
    if (SDL_Init(SDL_INIT_VIDEO)){
        fprintf(stdout,"Echec : %s \n", SDL_GetError());
    }
    else{
        editor();
        //loadSound();
    }
    SDL_Quit();

    return 1;
}

