#include "../Headers/editor.h"

void newWindow(char* errorMessage, char* displayTYPE){
    int toContinue = 1;
    SDL_Event eventError;
    SDL_Window* screenErrors = SDL_CreateWindow(displayTYPE,SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 300, 100, SDL_WINDOW_SHOWN);
    SDL_Renderer *pRendererError = SDL_CreateRenderer(screenErrors,-1,SDL_RENDERER_ACCELERATED);
    if (screenErrors && pRendererError){
        writeMessage(errorMessage, pRendererError);
        while (toContinue){
            SDL_WaitEvent(&eventError);
            switch (eventError.type){
            case SDL_WINDOWEVENT :
                if (eventError.window.event == SDL_WINDOWEVENT_CLOSE){
                    toContinue = 0;
                }
                break;
            }
        }
        SDL_DestroyWindow(screenErrors);
    }
    else {
        fprintf(stderr,"Erreur création fenêtre : %s \n", SDL_GetError());
    }
}

void writeMessage(char *errorMessage, SDL_Renderer *pRendererError){
    SDL_SetRenderDrawColor(pRendererError,255,255,255,255);
    SDL_RenderClear(pRendererError);
    TTF_Init();
    TTF_Font * font1;
    font1 = TTF_OpenFont("Police/cour.ttf", 12);
    SDL_Color Black = {0, 0, 0};
    SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font1, errorMessage, Black);
    SDL_Texture* message = SDL_CreateTextureFromSurface(pRendererError, surfaceMessage);
    SDL_Rect position;
    if (surfaceMessage && message && pRendererError){
        position.x = 5;
        position.y = 50;
        position.h = surfaceMessage->h;
        position.w = surfaceMessage->w;
        SDL_RenderCopy(pRendererError, message, NULL, &position);
        SDL_RenderPresent(pRendererError);
    }

}
