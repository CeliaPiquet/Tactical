#include "../Headers/editor.h"



void errorWindow(char* errorMessage){
    int toContinue = 1;
    SDL_Event eventError;
    SDL_Window* screenErrors = SDL_CreateWindow("ERREUR",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 300, 100, SDL_WINDOW_SHOWN);
    SDL_Renderer *pRenderer = SDL_CreateRenderer(screenErrors,-1,SDL_RENDERER_ACCELERATED);
    if (screenErrors && pRenderer){
        writeMessage(errorMessage, pRenderer);
        while (toContinue){
            printf("dans while \n");
            SDL_WaitEvent(&eventError);
            switch (eventError.type){
                case SDL_MOUSEBUTTONDOWN:
                    printf("event quit");
                    toContinue = 0;
                    break;
            }
        }
        SDL_DestroyWindow(screenErrors);
    }
    else {
        fprintf(stderr,"Erreur création fenêtre : %s \n", SDL_GetError());
    }
}

void writeMessage(char *errorMessage, SDL_Renderer *pRenderer){
    SDL_SetRenderDrawColor(pRenderer,255,255,255,255);
    SDL_RenderClear(pRenderer);
    TTF_Init();
    TTF_Font * font1;
    font1 = TTF_OpenFont("Police/cour.ttf", 12);
    SDL_Color Black = {0, 0, 0};
    SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font1, errorMessage, Black);
    SDL_Texture* message = SDL_CreateTextureFromSurface(pRenderer, surfaceMessage);
    SDL_Rect position;
    if (surfaceMessage && message && pRenderer){
        position.x = 5;
        position.y = 50;
        position.h = surfaceMessage->h;
        position.w = surfaceMessage->w;
        SDL_RenderCopy(pRenderer, message, NULL, &position);
        SDL_RenderPresent(pRenderer);
    }

}
