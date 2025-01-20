#include <stdio.h>
 
int main() {
 
    int quantidade, numero;
    scanf("%d", &quantidade);
    
    int multiplos_2 = 0; 
    int multiplos_3 = 0;
    int multiplos_4 = 0;
    int multiplos_5 = 0;
    
    for (int i=0; i<quantidade; i++) {
        scanf("%d", &numero);
        
        if (numero % 2 == 0) multiplos_2++;
        if (numero % 3 == 0) multiplos_3++;
        if (numero % 4 == 0) multiplos_4++;
        if (numero % 5 == 0) multiplos_5++;
   
    }
    
    printf("%d Multiplo(s) de 2\n", multiplos_2);
    printf("%d Multiplo(s) de 3\n", multiplos_3);
    printf("%d Multiplo(s) de 4\n", multiplos_4);
    printf("%d Multiplo(s) de 5\n", multiplos_5);
 
    return 0;
}