#include "../Headers/editor.h"


void menu(SDL_Renderer* pRenderer){
    SDL_Rect position;
    SDL_Surface *menu = SDL_LoadBMP("./sprites/menu.bmp");
    position.x = WINDOW_WIDTH;
    position.y = 0;
    position.h = menu->h;
    position.w = menu->w;
    if (pRenderer && menu){
        SDL_Texture *menuTexture = SDL_CreateTextureFromSurface(pRenderer, menu);
        if (menuTexture){
            SDL_FreeSurface(menu);
            SDL_RenderCopy(pRenderer, menuTexture, NULL,&position);
            SDL_DestroyTexture(menuTexture);
        }
        else{
            printf("Action failed: %s\n", SDL_GetError());
        }
    }
    else{
        printf("Action failed: %s\n", SDL_GetError());
    }
    return;
}
