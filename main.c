#include <stdio.h>
#include <ncurses.h>
#include <locale.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void Split(char data[6], int *value){
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

bool isSample(char strData[6]){
    bool allDigIsDig = true;
    bool hasSep = true; // __.__.____
    for(int i = 0; i < strlen(strData); ++i){
        // TODO: Разрешить на вход цифры
        if(i == 2){
            if(!ispunct(strData[i])){
                hasSep = false;
            }
        }else if(!isdigit(strData[i]))
            allDigIsDig = false;
        }
    return allDigIsDig && hasSep;
}

bool getValuesForField(int* sizeX, int* sizeY, int* i_coutForWin){
    // Получаем размер игрового поля
    clear();
    printw("Введите размеры игрового поля в формате <X>:<Y>\n(Два числа разделённых двоеточием):");

    char sizes[6];
    scanw("%s", &sizes);

    // Обрабатываем неверный формат ввода данных
    // if(!isSample(sizes)){
    //     clear();
    //     printw("Неверный формат входных данных");
    //     getch();
    //     return false;
    // }

    int sizesValues[2];
    Split(sizes, sizesValues);
    *sizeX = sizesValues[0];
    *sizeY = sizesValues[1];

    // Обрабатываем нееверные числовые значения данных
    if(*sizeX < 4 || *sizeY < 4 || *sizeX > 20 || *sizeY > 20){
        clear();
        printw("Минимальный размер - 4, максимальный размер - 20");
        getch();
        *sizeX = 0;
        *sizeY = 0;
        return false;
    }

    // Получаем количество элементов, необходимых для победы
    clear();
    printw("Введи количество крестиков или ноликов, необходимых для победы");

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
        printw("Неверный формат данных");
        getch();
        strcpy(coutForWin, "");
        return false;
        // TODO: И чё?
    }

    *i_coutForWin = atoi(coutForWin);

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
                if((i < 0 || j < 0) || (i > sizeX || it > sizeY) ){break;}
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
    for(int i = 0; i < sizeX; i++){
        for(int j = 0; j <= sizeY-coutForWin; j++){
            int cnt = 0;
            for(int it = j; it < j+coutForWin; it++){
                if((i < 0 || j < 0) || (it > sizeX || i > sizeY) ){break;}
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
    if(sizeX >= coutForWin && sizeY >= coutForWin){
        for(int i = 0; i <= sizeX-coutForWin; i++){
            for(int j = 0; j <= sizeY-coutForWin; j++){
                if(i < 0 || j < 0 ){break;}
                int cnt = 0;
                for(int d = 0; d < coutForWin; d++){
                    if((i < 0 || j < 0) || (i+d > sizeX || j+d > sizeY) ){break;}
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
        for(int i = sizeX-1; i >= coutForWin-1; i--){
            for(int j = sizeY-1; j >= coutForWin-1; j--){
                if(i < 0 || j < 0){break;}
                int cnt = 0;
                for(int d = 0; d<coutForWin; d++){
                    if((i < 0 || j < 0) || (i-d < 0 || j-d < 0) ){break;}
                    if(findIn2Array(i-d, j-d, arr, sizeX*sizeY)){
                        cnt += 1;
                    }
                }
                if(cnt == coutForWin){
                    return true;
                }
            }
        }
    }

    return false;
}

void printField(int sizeX, int sizeY, int cursePosX, int cursePosY, bool ticGo, int **tics, int **toes){
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
        
        // else if(!findDraw(i_coutForWin, sizeX, sizeY, tics, toes) && !findDraw(i_coutForWin, sizeX, sizeY, toes, tics)){
        //     clear();
        //     printw("Ничья");
        //     break;
        // }
        printField(sizeX, sizeY, cursePosX, cursePosY, ticGo, tics, toes);

        if(findWin(i_coutForWin, sizeX, sizeY, tics)){
            // clear();
            printw("\nКрестики выйграли");
            break;
        }else if(findWin(i_coutForWin, sizeX, sizeY, toes)){
            // clear();
            printw("\nНолики выйграли");
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