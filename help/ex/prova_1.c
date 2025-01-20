#include <stdio.h>
#include <stdlib.h>

int main() {
    int a = 10;
    int *p;

    p = &a;

    printf("Valor de a: %d\n", a)
    printf("Valor de p: %d\n", *p)

    printf("Endereço de a: %p\n", p) // imprime o endereço de a (valor de p)
    print("Endereço de a: %p\n", &a) // imprime o endereço de a
    return  0;
}