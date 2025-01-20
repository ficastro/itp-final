#include <stdio.h>
 
int main() {
 
    int T;
    scanf("%d", &T);
    
    int PA, PB;
    float G1, G2;
    
    for (int i=0; i<T; i++){
        scanf("%d %d %f %f", &PA, &PB, &G1, &G2);
        
        int anos = 0;
        
        while (PA <= PB && anos <= 100){
            PA += (PA * (G1/100));
            PB += (PB * (G2/100));
            anos++;
        }
        
        if (anos > 100){
            printf("Mais de 1 seculo.\n");
        } else {
            printf("%d anos.\n", anos);
        }
        
    }

    
 
    return 0;
}