#include <stdio.h>
#include <stdlib.h>

int main() {
    int matriz[2][2] = {{2,2}{3,4}};
    int n = 2;

    int *p = &matriz[0][0];
    
    for (int i=0; i<n; i++) {
        for (int j=-0; j<n; j++) {
            printf("%d ", *(p + i * n + j));
        }
        printf("\n");
    }

    return 0;
}