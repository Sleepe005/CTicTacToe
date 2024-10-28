#include <stdio.h>

int main(){
    int arr[4][5] = {{10,20,30,40,50},
                     {11,21,31,41,51},
                     {12,22,32,42,52},
                     {13,23,33,43,53}};

    int sizeX = 4, sizeY = 5;
    int coutForWin = 4;
    // // Перебор всех строк длины X
    // for(int i = 0; i < sizeX; i++){
    //     for(int j = 0; j <= sizeY-coutForWin; j++){
    //         for(int it = j; it < j+coutForWin; it++){
    //             printf(" %d ", arr[i][it]);                
    //         }
    //         printf("|");            
    //     }
    //     printf("\n");
    // }

    // // Перебор всех столбцов длины X
    // for(int i = 0; i < sizeX; i++){
    //     for(int j = 0; j <= sizeY-coutForWin; j++){
    //         for(int it = j; it < j+coutForWin; it++){
    //             printf(" %d ", arr[it][i]);
    //         }
    //          printf("|");
    //     }
    //     printf("\n");
    // }

    for(int i = 0; i < sizeY; i++){
        for(int j = 0; j <= sizeX-coutForWin; j++){
            for(int it = j; it < j+coutForWin; it++){
                printf(" %d ", arr[it][i]);
            }
            printf("|");
        }
        printf("\n");
    }

    // // Перебор всех диагоналей длины X
    // for(int i = 0; i <= sizeX-coutForWin; i++){
    //     for(int j = 0; j <= sizeY-coutForWin; j++){
    //         for(int d = 0; d < coutForWin; d++){
    //             printf(" %d ", arr[i+d][j+d]);
    //         }
    //         printf("|");
    //     }
    //     printf("\n");
    // }

    // Перебор всех побочных диагоналей длины X
    // for(int i = 0; i <= sizeX-coutForWin; i++){
    //     for(int j = sizeY-1; j >= coutForWin-1; j--){
    //         for(int d = 0; d<coutForWin; d++){
    //             printf(" %d ", arr[i+d][j-d]);
    //         }
    //         printf("|");
    //     }
    //     printf("\n");
    // }

    return 0;
}