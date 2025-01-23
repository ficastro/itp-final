#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "shared_pbm.h"

void validate_file(char file_name[]) {
    FILE *file = fopen(file_name, "r");
    if(!file) {
        fprintf(stderr, "\nERRO: ARQUIVO NAO ENCONTRADO\n");
        exit(1);
    }

    char verif_p1[8];
    fgets(verif_p1, 8, file);
    if (strcmp(verif_p1, "P1\n") != 0) {
        fprintf(stderr, "\eERRO: ARQUIVO .PBM NAO CONTEM LINHA INICIAL 'P1'");
        exit(1);
    }
    printf("\nFile validated:");
}

void fetch_size(Pbm *pbm_info) {
    FILE *file = fopen(pbm_info->name, "r");

    char verif_p1[3];
    if (fgets(verif_p1, sizeof(verif_p1), file) == NULL) {
        fprintf(stderr, "\nErro ao ler o identificador do PBM\n");
        fclose(file);
        return;
    }

    if (fscanf(file, "%d %d", &pbm_info->width, &pbm_info->height) != 2) {
        fprintf(stderr, "\nErro ao ler a largura e altura do arquivo\n");
        fclose(file);
        return;
    }
    printf("\nWidth: %d\nHeight: %d\n", pbm_info->width, pbm_info->height);
}

void fetch_thickness(Pbm *pbm_info) {
    FILE *file = fopen(pbm_info->name, "r");
    char line[1000];
    while (fgets(line, sizeof(line), file) != NULL) {

        int first_1_position = -1; // Nenhum 1 ainda encontrado
        int last_1_position = -1;
        int line_size = strlen(line);
        if (line_size > 67) {
            for (int position = 0; position < pbm_info->width; position++) {
                if (line[position] == '1') {
                    if (first_1_position == -1) { // Primeiro 1 encontrado
                        first_1_position = position;
                    }
                    last_1_position = position;  // Atualiza último 1 encontrado
                }
                if (line[position] == '0' && first_1_position != -1) {
                    break;
                }
            }

            if (first_1_position != -1 && last_1_position != -1) {
                pbm_info->thickness = (last_1_position - first_1_position) + 1;
                printf("Thickness: %d\n", pbm_info->thickness);
                break;
            }
        }
    }
}

void fetch_spacing(Pbm *pbm_info) {
    FILE *file = fopen(pbm_info->name, "r");
    char line[1000];
    while (fgets(line, sizeof(line), file) != NULL) {

        int last_0_position = -1;
        int line_size = strlen(line);
        if (line_size > 67) {
            for (int position = 0; position < pbm_info->width; position++) {
                if (line[position] == '0') {
                    last_0_position = position;
                }
                if (line[position] == '1') {
                    break;
                }
            }
            if (last_0_position != -1) {
                pbm_info->spacing = (last_0_position / pbm_info->thickness) + 1;
                printf("Spacing: %d\n", pbm_info->spacing);
                break;
            }
        }
    }
}

void find_binaries(Pbm *pbm_info, char *binary_codes[8]) { //Função para ler o arquivo PBM
    FILE *file = fopen(pbm_info->name, "r");

    int binary_start = (pbm_info->spacing * pbm_info->thickness) + (3 * pbm_info->thickness);
    int binary_end = pbm_info->width - binary_start;
    int middle_marker = (pbm_info->thickness * pbm_info->spacing) + (pbm_info->thickness * 3) + (pbm_info->thickness * 7 * 4);

    char line[1000];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strlen(line) > 15) {

            int binaries_found = 0;
            for (int position = binary_start; position < binary_end; ) { // Itera ao longo de toda a string binária por caractere

                if (position == middle_marker) {
                    position += (5 * pbm_info->thickness); // Pula o marcador do meio
                }

                char *binary_code = calloc(8, sizeof(char));
                for (int binary_digit = 0; binary_digit < 7; binary_digit++) { // Itera ao longo dos 7 caracteres de um binário
                    strncat(binary_code, &line[position], 1);
                    position += pbm_info->thickness;
                }

                binary_codes[binaries_found] = binary_code;
                binaries_found++;
                if (binaries_found == 8) {
                    printf("\nBinary code:\n");
                    print_array(binary_codes);
                    break;
                }
            }
            return;
        }
    }
}

void convert_to_decimal(char* binaries_array[], char ean[]) {
    int ean_progress = 0;
    for (int binary = 0; binary < 8; binary++) {
        for (int index = 0; index < 10; index++) {
            if ( (binary < 4 && strcmp(binaries_array[binary], l_codes[index]) == 0) || (binary >= 4 && strcmp(binaries_array[binary], r_codes[index]) == 0) ) {
                ean[ean_progress++] = '0' + index;
                break;
            }
        }
    }
    ean[ean_progress] = '\0'; // Null-terminate the EAN string
}

void print_result(char result[8]) {
    for (int i = 0; i < 8; i++) {
        printf("%c", result[i]);
    }
    printf("\n");
}

int main(){
    char ean[8] = {0};
    char* binary_codes[8];
    Pbm pbm_info;

    char *name;
    size_t name_size = 100;
    name = malloc(name_size * sizeof(char));

    printf("Insira o nome do arquivo .pbm a ser lido:\n> ");
    scanf("%s", name);
    if (strstr(name, ".pbm") == NULL) {
        strcat(name, ".pbm");
    }
    pbm_info.name = name;
    validate_file(pbm_info.name);

    fetch_size(&pbm_info);
    fetch_thickness(&pbm_info);
    fetch_spacing(&pbm_info);

    find_binaries(&pbm_info, binary_codes);
    convert_to_decimal(binary_codes, ean);
    verify(atoi(ean));
    
    printf("\nIDENTIFICADOR GERADO:\n%s", ean);

    return 0;
}
