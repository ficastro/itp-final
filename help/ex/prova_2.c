#include <stdio.h>
#include <stdlib.h>

void alterar_valor(int *n) {
    *n = 20;
}

int main() {
    int num = 10;
    printf("Valor original: &d\n", num)
    alterar_valor(&num)
    printf("Valor alterado: &d\n", num)

    return 0;
}