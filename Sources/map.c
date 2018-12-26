#include "../Headers/editor.h"

int isMapCorrect(int** map, int lines, int columns){
    if (isEmptyTile(map, lines, columns)){
        errorWindow("Veillez à ne pas laisser de cases vides!");
        return 0;
    }
//    if (isAbsentHQ1(map, lines, columns)){
//        errorAbsentHQ1();
//        return 0;
//    }
//    if (isAbsentHQ2(map, lines, columns)){
//        errorAbsentHQ2();
//        return 0;
//    }
//    if (absentPath(map, lines, columns)){
//        errorAbsentPath();
//        return 0;
//    }
    return 1; //true, the map is correct
}

int isEmptyTile(int** map, int lines, int columns){
    int i, j;
    for (i=0; i<lines; i++){
        for (j=0; j<columns; j++){
            if (map[i][j] == 0){
                return 1; //true, there is at least one empty tile
            }
        }
    }
    return 0; //false, there is not empty tile
}

int saveMap(int** map, int lines, int columns){
    if (!isMapCorrect(map, lines, columns)) {
        return 0;
    }
    saveMapFile(map, lines, columns);
    return 1;
}

int saveMapFile(int** map, int lines, int columns){
    FILE *file = fopen("mapSave.map","wb");
    if (file != NULL){
        fwrite(map,sizeof(int),lines,file);
        fclose(file);
        return 1;
    }
    return 0;
}
