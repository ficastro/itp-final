#include <stdio.h>
 
char *l_codes[10] = {
        "0001101", // dígito 0
        "0011001",
        "0010011",
        "0111101",
        "0100011",
        "0110001", // dígito 5
        "0101111",
        "0111011",
        "0110111",
        "0001011"  // dígito 9
    };

char *r_codes[10] = {
        "1110010", // dígito 0
        "1100110",
        "1101100",
        "1000010",
        "1011100",
        "1001110", // dígito 5
        "1010000",
        "1000100",
        "1001000",
        "1110100"  // dígito 9
    };

void print_array(char* array[]) {
    for (int i = 0; i < 8; i++) {
        printf("%s ", array[i]);  
    }
}

int convert_to_binary(int decimal_identifier[], char *binary_identifier[]) {
    printf("\nConverting...\n");

    for (int i = 0; i < 8; i++) {

        int digit = decimal_identifier[i];

        if (digit >= 0 && digit <= 9) {

            if (i < 4) {
                binary_identifier[i] = l_codes[digit];
            }
            else {
                binary_identifier[i] = r_codes[digit];
            }

        }
        else {
            printf("(ERRO) Dígito inválido inserido: %d (na posição %d)\n", digit, i);
            return 1;
        }

    }
}

int main() {
 
    int identifier[8];
    char* binary_identifier[8];

    printf("Insira 8 dígitos (0 ou 1), apertando Enter entre cada um:\n");
    for (int i = 0; i < 8; i++) {
        scanf("%d", &identifier[i]);
        
    }

    convert_to_binary(identifier, binary_identifier);

    print_array(binary_identifier);


 
    return 0;
}