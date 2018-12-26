#include "../Headers/editor.h"

int** newMap(){
    int i;
    int ** map;
    map = (int**)malloc(MAP_HEIGHT * sizeof(int*));
    if (map != NULL) {
        for (i=0; i < MAP_HEIGHT; i++) {
            int * mapLine = (int*)calloc(MAP_WIDTH, sizeof(int));
            if (mapLine != NULL) {
                *(map + i) = mapLine;
            }
        }
        return map;
    }
}

void updateScreen(int ** map, SDL_Rect position, SDL_Renderer *pRenderer, SDL_Texture *waterTexture,SDL_Texture *grassTexture){
    int i, j;
    for (i = 0 ; i < MAP_HEIGHT ; i++){
        for (j = 0 ; j < MAP_WIDTH ; j++){
            position.x = i * TILE_SIZE;
            position.y = j * TILE_SIZE;
            position.w = TILE_SIZE;
            position.h = TILE_SIZE;
            switch(map[i][j]){
                case 1:
                    SDL_RenderCopy(pRenderer,waterTexture,NULL,&position);
                    break;
                case 2:
                    SDL_RenderCopy(pRenderer,grassTexture,NULL,&position);
                    break;
            }
        }
    }
    SDL_RenderPresent(pRenderer);
}

void freeMap(int ** map, int lines) {
    int i;
    for (i = 0; i < lines; i ++ ) {
        free(*(map + i));
    }
    free(map);
}

void editor(SDL_Window* screen){
    //initializing
    SDL_Event event;                                                                            //event from the user
    int i, j;
    int actualSprite = 1;
    int ** map = newMap();                                                                      //array with 20 columns and 10 lines
    int toContinue = 1,
        clickingLeft = 0,
        clickingRight = 0;                                                                      //boolean for the end of the loops
    SDL_Surface *water = NULL, *grass = NULL;
    SDL_Texture *waterTexture = NULL, *grassTexture = NULL;                                                   //initializing the surfaces
    SDL_Rect position;                                                                          //represents the place we want to change
    SDL_Renderer *pRenderer = SDL_CreateRenderer(screen,-1,SDL_RENDERER_ACCELERATED);           // creation of a SDL_Renderer using hardware acceleration (faster)


    //loading of the different objects and creating their texture, once we have the textures we can free the surfaces
    grass = SDL_LoadBMP("./sprites/grass.bmp");
    water = SDL_LoadBMP("./sprites/water.bmp");
    waterTexture = SDL_CreateTextureFromSurface(pRenderer,water);
    grassTexture = SDL_CreateTextureFromSurface(pRenderer,grass);
    SDL_FreeSurface(water);
    SDL_FreeSurface(grass);

    if (map != NULL && grass && water && pRenderer && waterTexture && grassTexture){         //we check if everything has been correctly created
        while (toContinue){
            SDL_WaitEvent(&event);
                switch(event.type){
                    case SDL_QUIT:
                        toContinue = 0;
                        break;
                    case SDL_MOUSEBUTTONDOWN :
                        if (event.button.button == SDL_BUTTON_LEFT) {
                            map[event.button.x / TILE_SIZE][event.button.y / TILE_SIZE] = actualSprite;
                            clickingLeft = 1;                                                                        // On active le booléen pour retenir que le bouton gauche est enfoncé
                        }

                        else if (event.button.button == SDL_BUTTON_RIGHT) {                         // Le clic droit sert à effacer
                            map[event.button.x / TILE_SIZE][event.button.y /TILE_SIZE] = 0;
                            clickingRight = 1;
                        }
                        break;
                    case SDL_MOUSEBUTTONUP:                                                       // On désactive le booléen qui disait qu'un bouton était enfoncé
                        if (event.button.button == SDL_BUTTON_LEFT){
                            clickingLeft = 0;
                        }
                        else if (event.button.button == SDL_BUTTON_RIGHT){
                            clickingRight = 0;
                        }
                        break;
                    case SDL_MOUSEMOTION:
                        if (clickingLeft) {                                                         // in case the click
                            map[event.motion.x / TILE_SIZE][event.motion.y / TILE_SIZE] = actualSprite;
                        }
                        else if (clickingRight){                                                    // same for the right click
                            map[event.motion.x / TILE_SIZE][event.motion.y / TILE_SIZE] = 0;
                        }
                        break;

                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym){
                            case SDLK_ESCAPE:
                                toContinue = 0;
                                break;
                            case SDLK_PAGEUP:
                                actualSprite = (actualSprite + 1)% TILE_TOTAL;
                                break;
                            case SDLK_PAGEDOWN:
                                actualSprite = (actualSprite - 1);
                                break;
                            case SDLK_s:
                                saveMap(map,MAP_HEIGHT,MAP_WIDTH);
                                break;
                        }
                        break;
                }

                //clean the screen after each event
                SDL_SetRenderDrawColor(pRenderer,255,255,255,255);
                SDL_RenderClear(pRenderer);


                 // Placement des objets à l'écran et mise à jour
                updateScreen(map, position, pRenderer, waterTexture,grassTexture);


        }
        freeMap(map, MAP_HEIGHT);
        SDL_DestroyTexture(waterTexture);
        SDL_DestroyTexture(grassTexture);
        SDL_DestroyRenderer(pRenderer);
    }


}
