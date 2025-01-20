#include <stdio.h>
#include <stdlib.h>

void dobrar_valores(int *vetor, int tamanho) {
    for (int=0; i<tamanho; i++) {
        vetor[i] = vetor[i] * 2
    }
}

int main() {
    int n;

    printf("Digite o tamanho do vetor:\n> ");
    scanf("%d", &n);

    int vetor[n];

    printf("Digite os valores do vetor:\n> ");
    for (int i=0; i<n; i++) {
        scanf("%d", &vetor[i]);
    }

    for (int i=0; i<n; i++) {
        printf("%d", vetor[i]);
    }

    dobrar_valores(vetor, n);

    for (int i=0; i<n; i++) {
        printf("%d\n", vetor[i]);
    }

    return 0;
}