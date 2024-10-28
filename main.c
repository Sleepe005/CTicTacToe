#include <stdio.h>
#include <ncurses.h>
#include <locale.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void Split(char data[7], int *value){
    char element[3] = "";
    int pos = 0;
    int j = 0;
    for(int i = 0; i < strlen(data); ++i){
        if(!isdigit(data[i])){
            value[j] = atoi(element);
            j++;
            strcpy(element, "");
            pos = 0;
        }else{
            element[pos] = data[i];
            pos++;
        }
    }
    value[j] = atoi(element);
}

bool getValuesForField(int* sizeX, int* sizeY, int* i_coutForWin){
    // Получаем размер игрового поля
    bool allGood = false;
    while(!allGood){
        clear();
        printw("Введите размеры игрового поля в формате <X>:<Y>\n(Два числа, разделённых двоеточием):");

        char sizes[7];

        // Обрабатываем неверный формат ввода данных
        bool isSample = true;
        scanw("%s", &sizes);
        if(strlen(sizes) > 5){
            isSample = false;
        }else if(strlen(sizes) == 4){
            if(ispunct(sizes[1]) && !(isdigit(sizes[0]) && isdigit(sizes[2]) && isdigit(sizes[3]))){
                isSample = false;
            }else if(ispunct(sizes[2]) && !(isdigit(sizes[0]) && isdigit(sizes[1]) && isdigit(sizes[3]))){
                isSample = false;
            }else if(!(ispunct(sizes[1]) || ispunct(sizes[2]))){
                isSample = false;
            }
        }else if(strlen(sizes) == 3){
            if(!isdigit(sizes[0]) && !ispunct(sizes[1]) && !isdigit(sizes[2])){
                isSample = false;
            }
        }else if(strlen(sizes) < 3){
            isSample = false;
        }
        
        if(!isSample){
            clear();
            printw("Неверный формат входных данных\n");
            printw("Нажмите любую клавишу");
            getch();
        }

        bool inDiapozon = false;
        if(isSample){
            int sizesValues[2];
            Split(sizes, sizesValues);

            if(sizesValues[0] < 4 || sizesValues[1] < 4 || sizesValues[0] > 20 || sizesValues[1] > 20){
                clear();
                printw("Неверный формат входных данных\n");
                printw("Минимальный размер - 4, максимальный размер - 20\n");
                printw("Нажмите любую клавишу");
                getch();
            }else{
                inDiapozon = true;
                *sizeX = sizesValues[0];
                *sizeY = sizesValues[1];
            }
        }

        allGood = isSample && inDiapozon;

    }   
    
    bool isSample = false;
    // Получаем количество элементов, необходимых для победы
    clear();
    printw("Введи количество крестиков или ноликов, необходимых для победы");
    while(!isSample){
        char coutForWin[3];
        scanw("%s", &coutForWin);

        // Обрабатываем неверный формат ввода данных
        bool goodInputCout = true;
        for(int i = 0; i < strlen(coutForWin); i++){
            if(!isdigit(coutForWin[i])){
                goodInputCout = false;
            }
        }

        if(!goodInputCout || strlen(coutForWin) == 0){
            clear();
            printw("Неверный формат данных :(\nВведите число снова");
            strcpy(coutForWin, "");
        }else{
            isSample = true;
        *i_coutForWin = atoi(coutForWin);

        }
    }
    return true;
}

bool findIn2Array(int item1, int item2, int **arr, int rowsInArray){
    for(int i = 0; i < rowsInArray; i++){
        if(arr[i][0] == item1 && arr[i][1] == item2){
            return true;
        }
    }

    return false;
}

void zeroArray(int row, int column, int **arr){
//    TODO: Do it
    arr = (int **)malloc(row * sizeof(int *));
    for (int i = 0; i < row; i++) {
        arr[i] = (int *)malloc(column * sizeof(int));
    }
    // Инициализация массива
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            arr[i][j] = 0; // Присваиваем 0 всем элементам
        }
    }
}

bool findWin(int coutForWin, int sizeX, int sizeY, int **arr){
    // Перебор всех строк длины X
    for(int i = 0; i < sizeX; i++){
        for(int j = 0; j <= sizeY-coutForWin; j++){
            int cnt = 0;
            for(int it = j; it < j+coutForWin; it++){
                if(findIn2Array(i, it, arr, sizeX*sizeY)){
                    cnt += 1;
                }
            }
            if(cnt == coutForWin){
                return true;
            }
        }
    }

    // Перебор всех столбцов длины X
     for(int i = 0; i < sizeY; i++){
        for(int j = 0; j <= sizeX-coutForWin; j++){
            int cnt = 0;
            for(int it = j; it < j+coutForWin; it++){
                if(findIn2Array(it, i, arr, sizeX*sizeY)){
                    cnt += 1;
                }
            }
            if(cnt == coutForWin){
                return true;
            }
        }
    }

    // Перебор всех диагоналей длины X
    for(int i = 0; i <= sizeX-coutForWin; i++){
        for(int j = 0; j <= sizeY-coutForWin; j++){
            int cnt = 0;
            for(int d = 0; d < coutForWin; d++){
                if(findIn2Array(i+d, j+d, arr, sizeX*sizeY)){
                    cnt += 1;
                }
            }
            if(cnt == coutForWin){
                return true;
            }
        }
    }

    // Перебор всех побочных диагоналей длины X
    for(int i = 0; i <= sizeX-coutForWin; i++){
        for(int j = sizeY-1; j >= coutForWin-1; j--){
            int cnt = 0;
            for(int d = 0; d<coutForWin; d++){
                if(findIn2Array(i+d, j-d, arr, sizeX*sizeY)){
                    cnt += 1;
                }
            }
            if(cnt == coutForWin){
                return true;
            }
        }
    }

    return false;
}

bool canWin(int coutForWin, int sizeX, int sizeY, int **arrToWin, int **arrToLose){
     // Перебор всех строк длины X
    for(int i = 0; i < sizeX; i++){
        for(int j = 0; j <= sizeY-coutForWin; j++){
            int cnt = 0;
            for(int it = j; it < j+coutForWin; it++){
                if(findIn2Array(i, it, arrToWin, sizeX*sizeY) || !findIn2Array(i, it, arrToLose, sizeX*sizeY)){
                    cnt += 1;
                }
            }
            if(cnt == coutForWin){
                return true;
            }
        }
    }

    // Перебор всех столбцов длины X
     for(int i = 0; i < sizeY; i++){
        for(int j = 0; j <= sizeX-coutForWin; j++){
            int cnt = 0;
            for(int it = j; it < j+coutForWin; it++){
                if(findIn2Array(it, i, arrToWin, sizeX*sizeY) || !findIn2Array(i, it, arrToLose, sizeX*sizeY)){
                    cnt += 1;
                }
            }
            if(cnt == coutForWin){
                return true;
            }
        }
    }

    // Перебор всех диагоналей длины X
    for(int i = 0; i <= sizeX-coutForWin; i++){
        for(int j = 0; j <= sizeY-coutForWin; j++){
            int cnt = 0;
            for(int d = 0; d < coutForWin; d++){
                if(findIn2Array(i+d, j+d, arrToWin, sizeX*sizeY) || !findIn2Array(i+d, j+d, arrToLose, sizeX*sizeY)){
                    cnt += 1;
                }
            }
            if(cnt == coutForWin){
                return true;
            }
        }
    }

    // Перебор всех побочных диагоналей длины X
    for(int i = 0; i <= sizeX-coutForWin; i++){
        for(int j = sizeY-1; j >= coutForWin-1; j--){
            int cnt = 0;
            for(int d = 0; d<coutForWin; d++){
                if(findIn2Array(i+d, j-d, arrToWin, sizeX*sizeY) || !findIn2Array(i+d, j-d, arrToLose, sizeX*sizeY)){
                    cnt += 1;
                }
            }
            if(cnt == coutForWin){
                return true;
            }
        }
    }

    return false;
}

void printField(int sizeX, int sizeY, int cursePosX, int cursePosY, bool ticGo, int **tics, int **toes, int countForWin){
    clear();
    for(int row = 0; row < sizeX; row++){
        for(int column = 0; column < sizeY; column++){
            if(cursePosX == column && cursePosY == row && findIn2Array(row, column, tics, sizeX*sizeY)){
                printw("x");
            }else if(cursePosX == column && cursePosY == row && findIn2Array(row, column, toes, sizeX*sizeY)){
                printw("o");
            }else if(cursePosX == column && cursePosY == row){
                printw("*");
            }else if(findIn2Array(row, column, tics, sizeX*sizeY)){
                printw("X");
            }else if(findIn2Array(row, column, toes, sizeX*sizeY)){
                printw("O");
            }else{
                printw("·");
            }
        }
        printw("\n");
    }
    printw("\n");
    if(ticGo){printw("Ход крестиков\n");}
    else{printw("Ход ноликов\n");}
    printw("Для победы нужно сделать ряд из %d элементов подряд\n", countForWin);
    printw("Для перемещения по полю используйте стрелочки\n");

}

void play(){
    int sizeX = 0, sizeY = 0;

    int i_coutForWin;

    getValuesForField(&sizeX, &sizeY, &i_coutForWin);

    // Tics Array
    int **tics = (int **)malloc((sizeX*sizeY) * sizeof(int *));
    for (int i = 0; i < sizeX*sizeY; i++) {
        tics[i] = (int *)malloc(2 * sizeof(int));
    }
    // Инициализация массива
    for (int i = 0; i < sizeX*sizeY; i++) {
        for (int j = 0; j < 2; j++) {
            tics[i][j] = -1; // Присваиваем 0 всем элементам
        }
    }
    int ticPos = 0;

    // Toes Array
    int **toes = (int **)malloc((sizeX*sizeY) * sizeof(int *));
    for (int i = 0; i < (sizeX*sizeY); i++) {
        toes[i] = (int *)malloc(2 * sizeof(int));
    }
    // Инициализация массива
    for (int i = 0; i < (sizeX*sizeY); i++) {
        for (int j = 0; j < 2; j++) {
            toes[i][j] = -1; // Присваиваем 0 всем элементам
        }
    }
    int toePos = 0;

    bool ticGo = true;
    int cursePosX = 0, cursePosY = 0;
    int key;
    bool letsPlay = true;
    while(letsPlay){
        printField(sizeX, sizeY, cursePosX, cursePosY, ticGo, tics, toes, i_coutForWin);

        if(findWin(i_coutForWin, sizeX, sizeY, tics)){
            printw("\nКрестики выйграли");
            break;
        }else if(findWin(i_coutForWin, sizeX, sizeY, toes)){
            printw("\nНолики выйграли");
            break;
        }else if(!canWin(i_coutForWin, sizeX, sizeY, tics, toes) && !canWin(i_coutForWin, sizeX, sizeY, toes, tics)){
            printw("Ничья");
            break;
        }

        key = getch();
        if(key == 27){
            key = getch();
            if(key == 91){
                key = getch();
                if(key == 65){
                    cursePosY--;
                    if(cursePosY < 0){
                        cursePosY = sizeX-1;
                    }
                }else if(key == 66){
                    cursePosY++;
                    if(cursePosY > sizeX-1){
                        cursePosY = 0;
                    }
                }else if(key == 68){
                    cursePosX--;
                    if(cursePosX < 0){
                        cursePosX = sizeY-1;
                    }
                }else if(key == 67){
                    cursePosX++;
                    if(cursePosX > sizeY-1){
                        cursePosX = 0;
                    }
                }
            }
        }else if(key == 10){
            if(ticGo && !findIn2Array(cursePosY, cursePosX, toes, sizeX*sizeY) && !findIn2Array(cursePosY, cursePosX, tics, sizeX*sizeY)){
                tics[ticPos][0] = cursePosY;
                tics[ticPos][1] = cursePosX;
                ticPos++;
                ticGo = !ticGo;
            }else if(!ticGo && !findIn2Array(cursePosY, cursePosX, tics, sizeX*sizeY) && !findIn2Array(cursePosY, cursePosX, toes, sizeX*sizeY)){
                toes[toePos][0] = cursePosY;
                toes[toePos][1] = cursePosX;
                toePos++;
                ticGo = !ticGo;
            }
        }
    }
}

int main(){
    setlocale(LC_ALL, "");
    initscr();

    bool goPlay = true;
    while(goPlay){
        clear();
        play();
        getch();
    }
    
    return 0;
}