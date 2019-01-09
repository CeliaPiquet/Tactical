#include "../Headers/editor.h"

int inputWindow(char* fileName, char* title){
    char input[255];
    int toContinue = 1,x;
    SDL_Event event;
    SDL_Window* screen = SDL_CreateWindow(title,SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 200, SDL_WINDOW_SHOWN);
    SDL_Renderer *pRenderer = SDL_CreateRenderer(screen,-1,SDL_RENDERER_ACCELERATED);
    if (screen && pRenderer){
        fileName[0]='\0';
        input[0]='\0';  //on réinitialise input à chaque appel de la fonction
        SDL_SetRenderDrawColor(pRenderer, 255,255,255,255);
        SDL_RenderClear(pRenderer);
        SDL_StartTextInput();
        displayInput(input, pRenderer);
        while (toContinue){
            SDL_WaitEvent(&event);
            switch (event.type){
                case SDL_WINDOWEVENT :
                    if (event.window.event == SDL_WINDOWEVENT_CLOSE){
                        toContinue = 0;
                    }
                    break;
                case SDL_TEXTINPUT :
                    strcat(input,event.text.text);
                    displayInput(input, pRenderer);
                    break;
                case SDL_KEYDOWN :
                    if (event.key.keysym.sym == SDLK_BACKSPACE && strlen(input)!= 0){
                        x = strlen(input);
                        input[x-1]='\0';
                        displayInput(input, pRenderer);
                    }
                    if (event.key.keysym.sym == SDLK_RETURN){
                        if(inputIsOk(input)){
                            strcpy(fileName,input);
                            toContinue = 0;
                        }
                    }
                    break;

            }
        }
    }
    else {
        fprintf(stderr,"Erreur création fenêtre : %s \n", SDL_GetError());
    }
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(screen);
    if (strlen(fileName)!=0){
        return 1;
    }
    return 0;
}

int thereIsSpace(char* input){
    int i;
    if (strchr(input,' ')!= NULL){
        return 1;
    }
    return 0; //false, there is not
}

int inputIsOk(char* input){
    int size = strlen(input);
    if (size == 0 || strcmp(input,".map") == 0){
        newWindow("Il vous faut entrer au moins 1 caractère","ERREUR");
        return 0;
    }
    else if (strcmp(input+(size-4),".map") != 0){
        newWindow("Vous n'avez pas fini par .map","ERREUR");
        return 0;
    }
    else if (thereIsSpace(input)!= 0){
        newWindow("Il ne faut pas d'espace","ERREUR");
        return 0;
    }
    return 1;
}

void displayMessage(SDL_Renderer* pRenderer, TTF_Font* font1){
    char* message1 = "Entrez le nom de votre map SANS espace puis finissez par \".map\"";
    char* message2 = "Finissez avec ENTREE";
    SDL_RenderClear(pRenderer);
    SDL_Color Black = {0, 0, 0};
    SDL_Surface* surfaceMessage1 = TTF_RenderText_Blended(font1, message1, Black);
    SDL_Texture* textureMessage1 = SDL_CreateTextureFromSurface(pRenderer, surfaceMessage1);
    SDL_Surface* surfaceMessage2 = TTF_RenderText_Blended(font1, message2, Black);
    SDL_Texture* textureMessage2 = SDL_CreateTextureFromSurface(pRenderer, surfaceMessage2);
    SDL_Rect position1, position2;
    if (surfaceMessage1 && surfaceMessage2 && textureMessage1 && pRenderer && textureMessage2){
        position1.x = 5;
        position1.y = 50;
        position1.h = surfaceMessage1->h;
        position1.w = surfaceMessage1->w;
        SDL_RenderCopy(pRenderer, textureMessage1, NULL, &position1);
        position2.x = 5;
        position2.y = 70;
        position2.h = surfaceMessage2->h;
        position2.w = surfaceMessage2->w;
        SDL_RenderCopy(pRenderer, textureMessage2, NULL, &position2);
        SDL_RenderPresent(pRenderer);
        SDL_DestroyTexture(textureMessage2);
        SDL_FreeSurface(surfaceMessage2);
        SDL_DestroyTexture(textureMessage1);
        SDL_FreeSurface(surfaceMessage1);
    }
}

void displayInput(char * input, SDL_Renderer* pRenderer){
    SDL_RenderClear(pRenderer);
    TTF_Init();
    TTF_Font * font1;
    font1 = TTF_OpenFont("Police/cour.ttf", 12);
    displayMessage(pRenderer, font1);
    SDL_Color Black = {0, 0, 0};
    SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font1, input, Black);
    SDL_Texture* message = SDL_CreateTextureFromSurface(pRenderer, surfaceMessage);
    SDL_Rect position;
    if (surfaceMessage && message && pRenderer){
        position.x = 200;
        position.y = 110;
        position.h = surfaceMessage->h;
        position.w = surfaceMessage->w;
        SDL_RenderCopy(pRenderer, message, NULL, &position);
        SDL_RenderPresent(pRenderer);
        SDL_DestroyTexture(message);
        SDL_FreeSurface(surfaceMessage);
    }
}
