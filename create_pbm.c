#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "shared_pbm.h"

void validate_input(int ean) {
    char str_ean[9];
    sprintf(str_ean, "%d", ean);

    int integer_test;
    if (sscanf(str_ean, "%d", &integer_test) != 1 || strlen(str_ean) != 8) {
        fprintf(stderr, "\nERRO: EAN DEVE CONTER APENAS NUMEROS E TER 8 DIGITOS\n");
        exit(1);
    }
}

void print_array(char* array[]) {
    printf("\nPrinting array...\n");
    for (int i = 0; i < 8; i++) {
        printf("%s ", array[i]);
    }
    printf("\n");
}

void convert_to_binary(int decimal_identifier[], char *binary_identifier[]) {
    printf("\nConverting decimal ean to binary ean...\n");
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
        }

    }
}

int convert_int_to_array(int integer, int identifier_array[]) {
    for (int i = 7; i >= 0; i--) {
        identifier_array[i] = integer % 10;
        integer = integer / 10;
    }
}

void create_whole_sequence(Pbm pbm_info, char whole_sequence[pbm_info.width], char *binary_identifier[], char thick_sequence[pbm_info.width * pbm_info.thickness]) {

    for (int space = 0; space < pbm_info.spacing; space++) { // Spacing
        strcat(whole_sequence, "0");
    }

    strcat(whole_sequence, "101"); // Initial mark

    for (int position = 0; position < 4; position++) { // 4 primeiros binários
        strcat(whole_sequence, binary_identifier[position]);
    }

    strcat(whole_sequence, "01010"); // Middle mark

    for (int position = 4; position < 8; position++) { // 4 últimos binários
        strcat(whole_sequence, binary_identifier[position]);
    }

    strcat(whole_sequence, "101"); // Final mark

    for (int space = 0; space < pbm_info.spacing; space++) { // Spacing
        strcat(whole_sequence, "0");
    }

    printf("\nFinal string (no thickness):\n%s\n", whole_sequence);

    char repetition[2];
    for (int position = 0; position < pbm_info.width; position++) {
        repetition[0] = whole_sequence[position];
        repetition[1] = '\0'; // Converte char para string
        for (int time = 1; time <= pbm_info.thickness; time++)
            strcat(thick_sequence, repetition);
    }

    printf("\nFinal string (with thickness %d):\n%s\n", pbm_info.thickness, thick_sequence);

}

void create_pbm(Pbm pbm_info, char final_sequence[pbm_info.width]) {
    FILE *file = fopen(pbm_info.name, "w");

    if (!file) {
        fprintf(stderr, "\nErro ao criar arquivo PBM\n");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "P1\n");
    fprintf(file, "%d %d\n", pbm_info.width, pbm_info.height); // height + 2

    for (int row = 1; row <= pbm_info.height; row++) {
        fprintf(file, "%s", final_sequence);
        if (row != pbm_info.height) {
            fprintf(file, "\n");
        }
    }

    fclose(file);
    printf("\nArquivo PBM criado com sucesso: %s\n", pbm_info.name);
}

int main(int argc, char* argv[]) {
    int spacing = 1;
    int thickness = 1;
    int height = 10;
    char* name = "barcode.pbm";
    
    int opt;
    while ((opt = getopt(argc, argv, "s:t:h:n:")) != -1) {
        switch (opt) {
            case 's':
                spacing = atoi(optarg);
                break;
            case 't':
                thickness = atoi(optarg);
                break;
            case 'h':
                height = atoi(optarg);
                break;
            case 'n':
                name = optarg;
                strcat(name, ".pbm");
                break;
            default:
                fprintf(stderr, "Uso: %s [-s spacing] [-t thickness] [-h height] [-n name]\n", argv[0]);
                exit(1);
        }
    }

    int ean;
    int identifier_array[8];
    char* binary_identifier[8];

    printf("Insira o EAN de 8 dígitos:\n");
    scanf("%d", &ean);

    validate_input(ean);
    verify(ean);

    convert_int_to_array(ean, identifier_array);
    convert_to_binary(identifier_array, binary_identifier);
    print_array(binary_identifier);

    Pbm pbm_info = {
        binary_identifier,
        spacing,
        thickness,
        height,
        ( (67 + (spacing * 2)) * thickness),
        name
    };

    char *whole_sequence;
    whole_sequence = calloc(pbm_info.width, sizeof(char));

    char *thick_sequence;
    thick_sequence = calloc((pbm_info.width * pbm_info.thickness), sizeof(char));

    create_whole_sequence(pbm_info, whole_sequence, binary_identifier, thick_sequence);
    create_pbm(pbm_info, thick_sequence);

    return 0;
}

