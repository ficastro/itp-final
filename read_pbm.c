#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "shared_pbm.h"

void readpbm (Pbm pbm_image, char l_code[28], char r_code[28]) { //Função para ler o arquivo PBM
    FILE *file = fopen(pbm_image.name, "r");

    if(!file) { //Arquivo existe?
        fprintf(stderr, "\nErro ao abrir arquivo PBM\n");
        exit(EXIT_FAILURE);
    }

    char verify_p1[3]; // Verificando se o arquivo é PBM
    fgets(verify_p1, 3, file);
    if (strcmp(verify_p1, "P1\n") != 0) {
        fprintf(stderr, "\nErro, arquivo PBM não inicia com P1\n");
        exit(EXIT_FAILURE);
    }

    char comments; //Aniquilando os comentários
    while ((comments = fgetc(file)) == '#') {
        while (fgetc(file) != '\n');
    }

    fscanf(file, "%d %d", &pbm_image.width, &pbm_image.height); //Descobrindo as medidas
    char *image_binary;
    char aux;

    int primeiro_1 = 0; //Descobrindo a primeira linha que não é composta apenas por zeros
    image_binary = calloc((pbm_image.width * pbm_image.height), sizeof(char)); //Limpando a memória para colocar as informações do PBM
    for (int i = 0; i < (pbm_image.width * pbm_image.height); i++) {
         aux = fgetc(file);
        if (aux  == "0") {
            image_binary[i] = aux;
            }
        else if(aux == "1"){
            image_binary[i] = aux;
            if(primeiro_1 == 0) {
                primeiro_1 = i;
            }
        }
        else if (aux == EOF) {
            fprintf(stderr, "\nErro, arquivo PBM não contém o código de barras adequado\n");
            exit(EXIT_FAILURE);
        } 
    }

    int chars_zero = (primeiro_1 / pbm_image.width) * pbm_image.width; //Eliminando os zeros
    if ((pbm_image.width) % 2 == 0){ //Descobrindo o thcikness
        pbm_image.thickness = 1;
        for (int i = (pbm_image.width / 2); image_binary[i + chars_zero] == "1"; i++){
            pbm_image.thickness++;
        }
    }
    else{
        pbm_image.thickness = 0;
        for (int i = (pbm_image.width / 2); image_binary[i + chars_zero] == "1"; i++){
            pbm_image.thickness++;
        }
    }

    char l_code[28];
    char r_code[28];
    int index = 0;
    int side_line_spacing = (pbm_image.width - (pbm_image.thickness * 67)) / 2; 
    for (int i = 0; i < (28 * pbm_image.thickness); i = i + pbm_image.thickness){
        image_binary[i + side_line_spacing + (3 * pbm_image.thickness)] = l_code[index];
        index++;
    }
    index = 0;
    for (int i = 0; i < (28 * pbm_image.thickness); i = i + pbm_image.thickness){
        image_binary[i + side_line_spacing + (36 * pbm_image.thickness)] = r_code[index];
        index++;
    }
    fclose(file);
}

void convert_from_binary(int decimal_identifier[], char binary_identifier[]){


}

int main() {

    char code_l[28];
    char code_r[28]; 
    Pbm pbm_image;

    prinf("Por favor, insira somente o nome do arquivo da imagem PBM com o código de barras\n");
    scanf("%s", pbm_image.name);

    read_pbm(pbm_image.name, code_l, code_r);

    

    
 
    return 0;
}