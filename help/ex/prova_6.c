#include <stdio.h>
#include <stdlib.h>

int main() {
    int rows = 2; cols= 3;

    int **matriz = (int **)malloc(rows * sizeof(int *))
    for (int=0; i<rows; i++) {
        matriz[i] = (int *)malloc(cols * sizeof(int))
    }

    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            matriz[i][j] = i + j;
        }
    }

    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
           printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    for (int i=0; i<rows; i++) {
        free(matriz[i]);
    }

    return 0;
}