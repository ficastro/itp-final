#include <stdio.h>

void gerar (int numero) {
  printf("\n%d", numero);

  if (numero % 2 == 0) {
    numero = numero / 2;
    return gerar(numero);
  }
  else if (numero % 3 == 0) {
    numero = numero / 3;
    return gerar(numero);
  }
  else if (numero % 5 == 0) {
    numero = numero / 5;
    return gerar(numero);
  }
  else if (numero % 7 == 0) {
    numero = numero / 7;
    return gerar(numero);
  }

}

int main() {

  int numero;
  scanf("%d", &numero);
  gerar(numero);

  return 0;
}