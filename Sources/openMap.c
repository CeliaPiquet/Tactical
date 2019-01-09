#include "../Headers/editor.h"

void copyMapFromFile(char* fileName, int** map){ //taille de la map ajouté à la sauvegarde
    FILE *file = fopen(fileName,"rb");
    int i,j;
    if (file && map){
        for (i = 0; i < MAP_HEIGHT; i++){
            for (j = 0; j < MAP_WIDTH; j++){
                //changer fgetc car binary fonctionnera pas
                map[i][j]=fgetc(file)-48; //-48 because fgetc send a char with ascii code
            }
        }
        fclose(file);
    }
}
int isFileExisting(char* fileName){
    FILE *file = fopen(fileName,"r");
    if (file != NULL){
        fclose(file);
        return 1;
    }
    return 0;
}

char* openMap(int** map){
    char fileName[255];
    int** newArray;
    if (inputWindow(fileName, "Ouvrir map déjà existante") && fileName != NULL){
        if(!isFileExisting(fileName)){
            newWindow("Le fichier n'existe pas","ERREUR");
            return NULL;
        }
        copyMapFromFile(fileName,map);
    }
    return fileName;
}

//for checking
void displayMap(int** map){
    if (map){
        for(int i=0; i<MAP_HEIGHT; i++){
            for (int j=0; j<MAP_WIDTH; j++){
                printf("map[%d][%d] = %d\n", i, j, map[i][j]);
            }
        }
    }
}
