#include "../Headers/editor.h"

void freeTilesList(TilesList* list){
    if (list != NULL){
        Tile* tile = list->first;
        do{
            SDL_DestroyTexture(tile->texture);
            tile = tile->next;
        } while (tile != list->first);
    }
}

TilesList* generateList(){
    TilesList* list = init("HQ1", "./sprites/red.bmp");
    toPush(list, "HQ2", "./sprites/blue.bmp");
    toPush(list, "GRASS", "./sprites/grass1.bmp");
    toPush(list, "WATER", "./sprites/wtr.bmp");
    toPush(list, "MONTAIN", "./sprites/mnt1.bmp");
    return list;
}

Tile * getTileById(TilesList* list, int x){
    if (list && list->first){
        Tile * actualTile = list->first;
        do {
            if (actualTile->id == x){
                return actualTile;
            }
            actualTile = actualTile->next;
        } while (actualTile != list->first);
    }
    return NULL;
}

TilesList* init(char* nameFirst, char* pathFirst){
    TilesList *list = malloc(sizeof(*list));
    Tile *tile = malloc(sizeof(*tile));

    if (list == NULL || tile == NULL){
        exit(EXIT_FAILURE);
    }

    tile->id = 1;
    tile->name = nameFirst;
    tile->path = pathFirst;
    list->first = tile;
    list->last = tile;
    tile->next = tile;
    tile->previous = tile;

    return list;
}

int toPush(TilesList *list, char* newName, char* newPath){
    Tile *tileToAdd = malloc(sizeof(*tileToAdd));
    if (list == NULL || tileToAdd == NULL){
        exit(EXIT_FAILURE);
    }
    tileToAdd->id = list->last->id + 1;
    tileToAdd->name = newName;
    tileToAdd->path = newPath;
    tileToAdd->next = list->first;
    list->first->previous = tileToAdd;
    tileToAdd->previous = list->last;
    list->last->next = tileToAdd;
    list->last = tileToAdd;
    return 1;
}

//for checking
void toPrint(TilesList* list){
    if (list != NULL && list->first != NULL){
        Tile *actualTile = list->first;
        do{
            printf("id : %d, name : %s, next : %s, previous : %s \n", actualTile->id, actualTile->name, actualTile->next->name, actualTile->previous->name);
            actualTile = actualTile->next;
        }while (actualTile != list->first);
    }
}
