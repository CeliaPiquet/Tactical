 #ifndef DEF_PARAMS

    #define DEF_PARAMS
        #include <stdlib.h>
        #include <stdio.h>
        #include <SDL.h>
        #include <fmod.h>
        #include <SDL_ttf.h>
        #include <string.h>
        #define TILE_SIZE 32
        #define MAP_HEIGHT 20
        #define MAP_WIDTH 10
        #define WINDOW_HEIGHT 320
        #define WINDOW_WIDTH 640
        #define TILE_TOTAL 3

        //structures
        typedef struct Tile{
            int id;
            char* path;
            char* name;
            SDL_Texture* texture;
            struct Tile* next;
            struct Tile* previous;
        } Tile;

        typedef struct TilesList{
            struct Tile *first;
            struct Tile *last;
        } TilesList;

        //from editor.c
        void displayActualTile(Tile* actualTile, SDL_Renderer* pRenderer);
        void menu(SDL_Renderer* pRenderer);
        int isEventInMap(SDL_Event * event);
        int** newMap();
        void updateScreen(int ** map, SDL_Renderer *pRenderer, TilesList* tilesList, Tile* actualTile);
        void freeMap(int ** map, int lines);
        TilesList* generateList();
        void createTextures(TilesList* tilesList, SDL_Renderer* pRenderer);
        void changeClickingLeft(int x);
        void changeClickingRight(int x);
        int mouseButtonDown(SDL_Event *event, int ** map,Tile* actualTile, SDL_Renderer * pRenderer,TilesList* tilesList);
        int mouseButtonUp(SDL_Event *event);
        int mouseMotion(SDL_Event *event, int ** map,Tile* actualTile, SDL_Renderer * pRenderer,TilesList* tilesList);
        void editor();

        //from map.c
        int isMapCorrect(int** map);
        int saveMapFile(int** map, char* fileName);
        int isEmptyTile(int** map);
        int saveMap(int** map);

        //from list.c
        void freeTilesList(TilesList* list);
        Tile * getTileById(TilesList* list, int x);
        TilesList* init(char* nameFirst, char* pathFirst);
        int toPush(TilesList *list, char* newName, char* newPath);
        void toPrint(TilesList* list);

        //from sound
        void loadSound();

 #endif // DEF_PARAMS
