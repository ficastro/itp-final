#ifndef shared_bpm_h
#define shared_bpm_h
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

typedef struct {
    char** binary_identifier;
    int spacing;
    int thickness;
    int height;
    int width;
    char* name;
} Pbm ;

int verify(int int_ean) {
    char ean[8];
    sprintf(ean, "%d", int_ean);

    int sum = 0;
    for (int index = 1; index < 8; index++) {
        if (index % 2 == 0) {
            // char char_digit = ean[index - 1];
            int digit = ean[index - 1] - '0';
            sum = sum + (digit * 1);
        }
        else {
            char char_digit = ean[index - 1];
            int digit = char_digit - '0';
            sum = sum + (digit * 3);
        }
    }
    // printf("\nTotal sum: %d\n", sum);

    int closest_multiple = ((sum + 9) / 10) * 10;
    // printf("Closest multiple of %d is: %d\n", sum, closest_multiple);

    int verifier = closest_multiple - sum;
    printf("\nVerifier digit: %d\n", verifier);

    int last_digit = ean[7] - '0';
    if (last_digit != verifier) {
        fprintf(stderr, "\nERRO: DIGITO VERIFICADOR INVALIDO\n");
        exit(1);
    }
}

int validate_file_name(char file_name[]) {
    FILE *file = fopen(file_name, "r");

    if (file) {
        char overwrite;
        while (overwrite != 'Y' && overwrite != 'n') {

            fprintf(stderr, "\nATENCAO: ARQUIVO JA EXISTENTE. DESEJA SOBRESCREVE-LO? [Y/n]\n> ");
            scanf("%c", &overwrite);

            if (overwrite == 'n') {
                printf("\n\nENCERRADO\n\n");
                exit(1);
            }
        }
    }
}

#endif