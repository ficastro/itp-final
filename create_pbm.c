#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "create_pbm.h"

void print_array(char* array[]) {
    for (int i = 0; i < 8; i++) {
        printf("%s ", array[i]);
    }
}

void convert_to_binary(int decimal_identifier[], char *binary_identifier[]) {
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
        }

    }
}

int convert_int_to_array(int integer, int identifier_array[]) {
    for (int i = 7; i >= 0; i--) {
        identifier_array[i] = integer % 10;
        integer = integer / 10;
    }
}

void generate_matrix(Pbm pbm_info, char** binary_identifier, int matrix[pbm_info.width][pbm_info.height]) {
    
    for (int i = 0; i < pbm_info.width; i++) {    
        for (i; i < (pbm_info.spacing * pbm_info.thickness); i++) { // borda inicial
            matrix[i][0] = 0;
        }
        for (i; i < (i + (pbm_info.thickness)); i++) { // marcador inicial
            // matrix[i][0] = 1;
            matrix[i][0] = matrix[i + (2 * pbm_info.thickness)][0] = 1;
            matrix[i + pbm_info.thickness][0] = 0;
            // matrix[i + (2 * pbm_info.thickness)][0] = 1;
        }
        i = i + (2 * pbm_info.thickness);
        for (i; i < i + (4 * pbm_info.thickness); i++) { // primeiros 4 dígitps

            for(int j = 0; j < 4; j++){
               for (int k = 0; k < 7; k++){
                    matrix[i][0] = (binary_identifier[j])[k];
                    i++;
                }
            }       
        }
        for (i; i < i + pbm_info.thickness; i++) { //marcador do meio
            matrix[i][0] = matrix[i + (2 * pbm_info.thickness)][0] = matrix[i + (4 * pbm_info.thickness)][0] = 0;
            matrix[i + pbm_info.thickness][0] = matrix[i + (3 * pbm_info.thickness)][0] = 1;
        }
        i = i + (4 * pbm_info.thickness);
        for (i; i < i + (4 * pbm_info.thickness); i++) { // primeiros 4 dígitps

            for(int j = 4; j < 8; j++){
               for (int k = 0; k < 7; k++){
                    matrix[i][0] = (binary_identifier[j])[k];
                    i++;
                }
            }       
        }
        for (i; i < (i + (pbm_info.thickness)); i++) { //marcador final
            matrix[i][0] = matrix[i + (2 * pbm_info.thickness)][0] = 1;
            matrix[i + pbm_info.thickness][0] = 0;
        }
        i = i + (2 * pbm_info.thickness);
        for (i; i < (pbm_info.spacing * pbm_info.thickness); i++) { //borda final
            matrix[i][0] = 0;
        }
    }

//    for (int i = 0; i < pbm_info.thickness; i++) {
//        for (int j = 0; j < pbm_info.height; j++) {
//            fprintf(file, "%d ", matrix[i][j]);
//        }
//        fprintf(file, "\n");


}

void create_pbm(Pbm pbm_info, int matrix[pbm_info.width][pbm_info.height]) {
    FILE *file = fopen(pbm_info.name, "w");

    if (!file) {
        fprintf(stderr, "Erro ao criar arquivo PBM\n");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "P1\n");
    fprintf(file, "%d %d\n", pbm_info.thickness, pbm_info.height);

    for (int i = 0; i < pbm_info.thickness; i++) {
        for (int j = 0; j < pbm_info.height; j++) {
            fprintf(file, "%d ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Arquivo PBM criado com sucesso: %s\n", pbm_info.name);
}

int main(int argc, char* argv[]) {
    int spacing = 1;
    int thickness = 1;
    int height = 7;
    char* name = "codebar.pbm";
    
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
                break;
            default:
                fprintf(stderr, "Uso: %s [-s spacing] [-t thickness] [-h height] [-n name]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // printf("\nValor de spacing: %d\n", spacing);
    // printf("\nValor de thickness: %d\n", thickness);
    // printf("\nValor de height: %d\n", height);
    // printf("\nValor de name: %s\n", name);

    int identifier;
    int identifier_array[8];
    char* binary_identifier[8];

    printf("Insira o EAN de 8 dígitos:\n");
    scanf("%d", &identifier);

    convert_int_to_array(identifier, identifier_array);
    convert_to_binary(identifier_array, binary_identifier);
    print_array(binary_identifier);

    Pbm pbm_info = {
        binary_identifier,
        spacing,
        thickness,
        height,
        (69 * thickness),
        name
    };

    int matrix[pbm_info.width][pbm_info.height];
    generate_matrix(pbm_info, binary_identifier, matrix);

    printf("%d", matrix[0][2]);
    // int matrix[7][69] = {1};
    create_pbm(pbm_info, matrix);

    return 0;
}

