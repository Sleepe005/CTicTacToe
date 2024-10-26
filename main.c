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
    }

    *i_coutForWin = atoi(coutForWin);

    return true;
}

bool findIn2Array(int row, int column, int **arr, int rows){
    for(int i = 0; i < rows; i++){
        if(arr[i][0] == row && arr[i][1] == column){
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


int main(){
    setlocale(LC_ALL, "");

    return 0;
}