#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "shared_pbm.h"

void read_pbm (Pbm *pbm_image, char l_code[28], char r_code[28]) { //Função para ler o arquivo PBM
    FILE *file = fopen(pbm_image->file_name, "r");

    if(!file) { //Arquivo existe?
        fprintf(stderr, "\nErro ao abrir arquivo PBM\n");
        exit(EXIT_FAILURE);
    }
    printf("Arquivo PBM aberto com sucesso.\n");

    char verif_p1[8];
    fgets(verif_p1, 8, file);
    if (strcmp(verif_p1, "P1\n") != 0) {
        fprintf(stderr, "\nErro, arquivo PBM nao inicia com P1\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    printf("Arquivo verificado como P1.\n");

    char comments;
    while ((comments = fgetc(file)) == '#') {
        while (fgetc(file) != '\n');
    }
    ungetc(comments, file);

    fscanf(file, "%d %d", &pbm_image->width, &pbm_image->height); //Descobrindo as medidas
    printf("Dimensoes do PBM: largura = %d, altura = %d\n", pbm_image->width, pbm_image->height);
    
    char *image_binary = calloc(pbm_image->width * pbm_image->height, sizeof(char));
    if (image_binary == NULL) {
        fprintf(stderr, "\nErro ao alocar memoria\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    printf("Memoria alocada para a imagem.\n");

    int primeiro_1 = 0; //Descobrindo a primeira linha que não é composta apenas por zeros
    for (int i = 0; i < (pbm_image->width * pbm_image->height); i++) {
        char aux = fgetc(file);
        if (aux == '0' || aux == '1') {
            image_binary[i] = aux;
            if (aux == '1' && primeiro_1 == 0) {
                primeiro_1 = i;
            }
        }
        else if (aux == EOF) {
            fprintf(stderr, "\nErro, arquivo PBM não contém o código de barras adequado\n");
            free(image_binary);
            fclose(file);
            exit(EXIT_FAILURE);
        } 
    }

    int chars_zero = (primeiro_1 / pbm_image->width) * pbm_image->width; //Eliminando os zeros
    int half_width = pbm_image->width / 2;
    
    if (image_binary[half_width + chars_zero] == '1') {
        pbm_image->thickness = 1;
    } 
    else {
        pbm_image->thickness = 0;
    }
    while (image_binary[half_width + chars_zero + pbm_image->thickness] == '1') {
        pbm_image->thickness++;
    }

    int index = 0;
    int side_line_spacing = (pbm_image->width - (pbm_image->thickness * 67)) / 2; 
    for (int i = 0; i < 28 * pbm_image->thickness; i += pbm_image->thickness){
        l_code[index] = image_binary[(i + 1) + side_line_spacing + (3 * pbm_image->thickness)];
        index++;
    }
    index = 0;
    for (int i = 0; i < 28 * pbm_image->thickness; i += pbm_image->thickness){
        r_code[index] = image_binary[(i + 1) + side_line_spacing + (36 * pbm_image->thickness)];
        index++;
    }
    fclose(file);
    free(image_binary);

    for (int i = 0; i < 28; i++) {
        printf("%c", r_code[i]);
    }
    printf("\n");

    for (int i = 0; i < 28; i++) {
        printf("%c", l_code[i]);
    }
    printf("\n");
}



char to_decimal(char decimal[], char* lr_codes[]) { 
    for (int i = 0; i < 10; i++) {
        if (strcmp(decimal, lr_codes[i]) == 0) {
            return '0' + i;
        }
    }
    return '?';
}

void convert_from_binary(char decimal_identifier[8], char l_code[28], char r_code[28]){
    for (int i = 0; i < 4; i++){
      char l_decimal[8];
      strncpy(l_decimal, l_code + i * 7, 7);
      l_decimal[7] = '\0';
      decimal_identifier[i] = to_decimal(l_decimal, l_codes);  
    }

    for (int i = 0; i < 4; i++){  
        char r_decimal[8];
        strncpy(r_decimal, r_code + i * 7, 7);
        r_decimal[7] = '\0';
        decimal_identifier[i + 4] = to_decimal(r_decimal, r_codes);
    }

}

void print_result(char result[8]) {
    for (int i = 0; i < 8; i++) {
        printf("%c", result[i]);
    }
    printf("\n");
}

int main(){
    char decimal_identifier[8];
    char l_code[28];
    char r_code[28];
    Pbm pbm_image;

    printf("Por favor, insira somente o nome do arquivo da imagem PBM com o codigo de barras\n");
    scanf("%s", pbm_image.file_name);

    read_pbm(&pbm_image, l_code, r_code);
    convert_from_binary(decimal_identifier, l_code, r_code);
    
    printf("Parabens! Aqui esta o identificador:");
    print_result(decimal_identifier);

    return 0;
}
