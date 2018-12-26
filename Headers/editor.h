 #ifndef DEF_PARAMS

    #define DEF_PARAMS
        #include <stdlib.h>
        #include <stdio.h>
        #include <SDL.h>
        #include <SDL_ttf.h>
        #define TILE_SIZE 32
        #define MAP_HEIGHT 20
        #define MAP_WIDTH 10
        #define TILE_TOTAL 3
        void editor(SDL_Window* pWindow);
        int isMapCorrect(int** map, int lines, int columns);
        int saveMapFile(int** map, int lines, int columns);
        int isEmptyTile(int** map, int lines, int columns);
        int saveMap(int** map, int lines, int columns);
        void freeMap(int ** map, int lines);
        void updateScreen(int ** map, SDL_Rect position, SDL_Renderer *pRenderer, SDL_Texture *waterTexture,SDL_Texture *grassTexture);
        int** newMap();
 #endif // DEF_PARAMS
