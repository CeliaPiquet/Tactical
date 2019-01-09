#include "../Headers/editor.h"

int isMapCorrect(int** map){            //vérifier pathfinding
    if (isEmptyTile(map)){
        newWindow("Veillez à ne pas laisser de cases vides!","ERREUR");
        return 0;
    }
    if (isAbsentHQ1(map)){
        newWindow("Il vous manque un QG rouge","ERREUR");
        return 0;
    }
    if (isAbsentHQ2(map)){
        newWindow("Il vous manque un QG bleu","ERREUR");
        return 0;
    }
    return 1; //true, the map is correct
}

int isAbsentHQ1(int** map){
    int i, j;
    for (i=0; i<MAP_HEIGHT; i++){
        for (j=0; j<MAP_WIDTH; j++){
            if (map[i][j] == 3){
                return 0; //false, HQ1 is not absent
            }
        }
    }
    return 1; //true, HQ1 is absent
}

int isAbsentHQ2(int** map){
    int i, j;
    for (i=0; i<MAP_HEIGHT; i++){
        for (j=0; j<MAP_WIDTH; j++){
            if (map[i][j] == 4){
                return 0; //false, HQ2 is not absent
            }
        }
    }
    return 1; //true, HQ2 is absent
}

int isEmptyTile(int** map){
    int i, j;
    for (i=0; i<MAP_HEIGHT; i++){
        for (j=0; j<MAP_WIDTH; j++){
            if (map[i][j] == 0){
                return 1; //true, there is at least one empty tile
            }
        }
    }
    return 0; //false, there is not empty tile
}

int saveMap(int** map){
    char* fileName;
    if (!isMapCorrect(map)) {
        return 0;
    }
    inputWindow(fileName,"Nouvelle Map - Sauvegarde");
    if(fileName!= NULL){
        while (isFileExisting(fileName)){
            newWindow("Un fichier avec le même nom existe déjà","ERREUR");
            inputWindow(fileName,"Nouvelle Map - Sauvegarde");
        }
        if(saveMapFile(map,fileName)!=0){
            newWindow("Votre map a bien été sauvegardée !","SAUVEGARDE REUSSIE");
        }
        else {
            newWindow("Erreur lors de la sauvegarde","ERREUR");
            return 0;
        }
    }
    else {
        newWindow("Erreur lors de la sauvegarde","ERREUR");
    }
    return 1;
}

int saveMapFile(int** map, char* fileName){  //rajouter la taille de MAP_HEIGHT et MAP_WIDTH
    FILE *file = fopen(fileName,"wb");
    int i,j,x;
    if (file != NULL){
        for (i=0; i<MAP_HEIGHT; i++){
            for(j=0; j<MAP_WIDTH; j++){
                fprintf(file, "%d", map[i][j]);
            }
        }
        fclose(file);
        return 1;
    }
    return 0;
}
