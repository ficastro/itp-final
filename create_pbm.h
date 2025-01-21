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