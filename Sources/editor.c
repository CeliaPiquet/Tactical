#include "../Headers/editor.h"
//to change
int toContinue = 1,
    clickingLeft = 0,
    clickingRight = 0;

void displayActualTile(Tile* actualTile, SDL_Renderer* pRenderer){
    Tile* next, *previous;
    next = actualTile->next;
    previous = actualTile->previous;
    SDL_Rect posPrev, posAct, posNext;

    posPrev.x = WINDOW_WIDTH + 10;
    posPrev.y = WINDOW_HEIGHT - TILE_SIZE - 10;
    posPrev.h = TILE_SIZE;
    posPrev.w = TILE_SIZE;

    posAct.x = WINDOW_WIDTH + WINDOW_WIDTH/4 -10;
    posAct.y = WINDOW_HEIGHT - TILE_SIZE - 10;
    posAct.h = TILE_SIZE;
    posAct.w = TILE_SIZE;

    posNext.x = WINDOW_WIDTH + WINDOW_WIDTH/2 - (TILE_SIZE+10);
    posNext.y = WINDOW_HEIGHT - TILE_SIZE - 10;
    posNext.h = TILE_SIZE;
    posNext.w = TILE_SIZE;

    SDL_RenderCopy(pRenderer, previous->texture , NULL,&posPrev);
    SDL_RenderCopy(pRenderer, actualTile->texture , NULL,&posAct);
    SDL_RenderCopy(pRenderer, next->texture , NULL,&posNext);
}

int isEventInMap(SDL_Event * event){
    if (event->button.x < WINDOW_WIDTH){
        return 1;
    }
    return 0;
}

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
    return NULL;
}

void updateScreen(int ** map, SDL_Renderer *pRenderer, TilesList* tilesList, Tile* actualTile){
    int i, j;
    SDL_Rect position;
    Tile* tile;
    for (i = 0 ; i < MAP_HEIGHT ; i++){
        for (j = 0 ; j < MAP_WIDTH ; j++){
            position.x = i * TILE_SIZE;
            position.y = j * TILE_SIZE;
            position.w = TILE_SIZE;
            position.h = TILE_SIZE;
            if (map[i][j] != 0){
                tile = getTileById(tilesList, map[i][j]);
                SDL_RenderCopy(pRenderer, tile->texture, NULL, &position);
            }
        }
    }
    menu(pRenderer);
    displayActualTile(actualTile, pRenderer);
    SDL_RenderPresent(pRenderer);

}

void freeMap(int ** map, int lines) {
    int i;
    for (i = 0; i < lines; i ++ ) {
        free(*(map + i));
    }
    free(map);
}

void createTextures(TilesList* tilesList, SDL_Renderer* pRenderer){
    Tile* actualTile = tilesList->first;
    SDL_Surface* tileSurface = NULL;
    SDL_Texture* tileTexture = NULL;
    do {
        tileSurface = SDL_LoadBMP(actualTile->path);
        tileTexture = SDL_CreateTextureFromSurface(pRenderer,tileSurface);
        actualTile->texture = tileTexture;
        actualTile = actualTile->next;
    } while (actualTile != tilesList->first);
    SDL_FreeSurface(tileSurface);
}

void changeClickingLeft(int x){
    clickingLeft = x;
}

void changeClickingRight(int x){
    clickingRight = x;
}

int mouseButtonDown(SDL_Event *event, int ** map,Tile* actualTile, SDL_Renderer * pRenderer,TilesList* tilesList){
    if (isEventInMap(event)){
        if (event->button.button == SDL_BUTTON_LEFT) {
            map[event->button.x / TILE_SIZE][event->button.y / TILE_SIZE] = actualTile->id;
            updateScreen(map, pRenderer, tilesList, actualTile);
            changeClickingLeft(1);
            return 1;
        }

        else if (event->button.button == SDL_BUTTON_RIGHT ) {
            map[event->button.x / TILE_SIZE][event->button.y /TILE_SIZE] = 0;
            updateScreen(map, pRenderer, tilesList, actualTile);
            changeClickingRight(1);
            return 1;
        }
    }
    return 0;
}

int mouseButtonUp(SDL_Event *event){
    if (isEventInMap(event)){
        if (event->button.button == SDL_BUTTON_LEFT){
            changeClickingLeft(0);
            return 1;
        }
        else if (event->button.button == SDL_BUTTON_RIGHT){
            changeClickingRight(0);
            return 1;
        }
        return 0;
    }
    return 0;
}

int mouseMotion(SDL_Event *event, int ** map,Tile* actualTile, SDL_Renderer * pRenderer,TilesList* tilesList){
    if (isEventInMap(event)){
        if (clickingLeft) {                                                         // in case the click
            map[event->motion.x / TILE_SIZE][event->motion.y / TILE_SIZE] = actualTile->id;
            updateScreen(map, pRenderer, tilesList, actualTile);
            return 1;
        }
        else if (clickingRight){                                                    // same for the right click
            map[event->motion.x / TILE_SIZE][event->motion.y / TILE_SIZE] = 0;
            updateScreen(map, pRenderer, tilesList, actualTile);
            return 1;
        }
    }
    return 0;
}

void editor(){
    TilesList* tilesList = generateList();
    Tile* actualTile = tilesList->first;
    SDL_Window* screen = NULL;
    SDL_Event event;
    int ** map = newMap();                                                                                                                     //array with 20 columns and 10 lines
    screen = SDL_CreateWindow("New Map",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH +(WINDOW_WIDTH/2),WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (screen && map && tilesList){
        SDL_Renderer *pRenderer = SDL_CreateRenderer(screen,-1,SDL_RENDERER_ACCELERATED);                                                     // creation of a SDL_Renderer using hardware acceleration (faster)
        if (pRenderer){
            createTextures(tilesList, pRenderer);
            updateScreen(map, pRenderer, tilesList, actualTile);                                                                                          //create all the textures from the tiles list
            while (toContinue){
                SDL_WaitEvent(&event);
                switch(event.type){
                        case SDL_WINDOWEVENT :
                            if (event.window.event == SDL_WINDOWEVENT_CLOSE){
                                toContinue = 0;
                            }
                            break;
                        case SDL_MOUSEBUTTONDOWN :
                            mouseButtonDown(&event, map, actualTile, pRenderer, tilesList);
                            break;
                        case SDL_MOUSEBUTTONUP:
                            mouseButtonUp(&event);
                            break;
                        case SDL_MOUSEMOTION:
                            mouseMotion(&event, map, actualTile, pRenderer, tilesList);
                            break;

                        case SDL_KEYDOWN:
                            switch(event.key.keysym.sym){
                                case SDLK_ESCAPE:
                                    toContinue = 0;
                                    break;
                                case SDLK_RIGHT:     //change
                                    if (actualTile->next->id != 0){
                                        actualTile = actualTile->next;
                                    }
                                    else {
                                        actualTile = actualTile->next->next;
                                    }
                                    updateScreen(map, pRenderer, tilesList, actualTile);
                                    break;
                                case SDLK_LEFT:
                                    if (actualTile->previous->id != 0){
                                        actualTile = actualTile->previous;
                                    }
                                    else {
                                        actualTile = actualTile->previous->previous;
                                    }
                                    updateScreen(map, pRenderer, tilesList, actualTile);
                                    break;
                                case SDLK_s:
                                    saveMap(map);
                                    break;
                                case SDLK_o:
                                    openMap(map);
                                    updateScreen(map, pRenderer, tilesList, actualTile);
                                    break;
                            }
                            break;
                    }
                    //clean the screen after each event
                    SDL_RenderClear(pRenderer);
            }
            freeMap(map, MAP_HEIGHT);
            SDL_DestroyRenderer(pRenderer);
            freeTilesList(tilesList);
        }
    }
}
