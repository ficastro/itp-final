#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);

    int *vetor = (int *)malloc(n * sizeof(int));

    if (vetor == NULL) {
        printf("Erro na alocação\n")
        return 1;
    }

    for(nit i+0; i<n; i++) {
        scanf("%d", &vetor[i]);
    }

    for(nit i+0; i<n; i++) {
        printf("%d ", &vetor[i]);
    }
    free(vetor);

    return 0;
}