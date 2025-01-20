#include <stdio.h>

#define MAX 10  // No momento da compilação, os textos MAX serão substituídos por 10. Não foi criada a variável MAX!

int main(){
    // Variáveis devem ser declaradas no início do bloco. Não podem começar com números e são case-sensitive.
    
    int inteiros = 2;                       // 4 bytes      // %d ou %i
    int array[10];
    char caracteres_unicos = 'A';           // 1 byte       // %c
    char* string = "Hello!";                                // %s
    float reais = 2.5;                      // 4 bytes      // %f
    double reais_maiores = 20.5495;         // 8 bytes      // %lf "long-float"
    // Double tem mais números depois da vírgula que o float
    // Aspas simples: caractere
    // Aspas duplas: string

    double altura_metros, comprimento_metros;
    const float PI = 3.1415;


    printf("\nBom dia, ");  // Todo comando deve terminar em ;
    printf("Juninho Babalu");
    // \n       ENTER
    // \t       TAB
    printf("\n %7c", caracteres_unicos);  // 7 depois de %  -->  queremos que ocupe um espaço de 7 caracteres 
    printf("\n %.2lf", reais_maiores);  // .2 depois de %  -->  queremos apenas 2 casas depois da vírgula
    printf("\n %07.2lf", reais_maiores);  // 0 antes de 7.2  -->  queremos que os espaços restantes sejam completados com 0

    printf("\nSoma de float com double: %lf", reais + reais_maiores);  // + - * / %  --> Operadores matemáticos
    
    printf("\nInteiro: %d", ++inteiros);  // Soma 1 antes de ser utilizado
    printf("\nInteiro: %d", --inteiros);  // Subtrai 1 antes de ser utilizado
    // Se fosse inteiros++, o valor seria utilizado e só depois seria somado 1


    // INPUT
    int numero;
    printf("\nInsira um número: ");
    scanf("%d", &numero);
        // scanf("%d %d", &numero, &numero2);
    // %d indica que um inteiro será lido:
    // & indica o endereço de memória onde está alocada a variável numero
    printf("\nVocê comeu pão no café da manhã %d vezes\n", numero);


    // LOGICA
    x > y
    x < y
    x >= y
    x <= y
    x == y
    x != y

    x>y && a>b      // (X maior que Y) e (A maior que B)
    x>y || a> b     // (X maior que Y) ou (A maior que B)
    !(x>y)          // O inverso de (X maior que Y)


    // CONDIÇÕES E REPETIÇÕES

    if(x>y){
        // ...
    }
    else if(){
        // ...
    }
    else{
        // ...
    }

    a > b ? printf("a é maior") : printf("b é maior");

    switch (valor){
        case VALOR1:
            comandos quando esse valor é igual a VALOR1;
            break;
        case VALOR2:
            printf("Valor 2");
            break;
        case VALOR3: comandos quando esse valor é igual a VALOR3; break;
        default: comandos quando nenhum dos casos anteriores foi verdadeiro;
    };

    while(){
        // ...
    };

    do{
        // ...
    }while();
    // Esta estrutura executa pelo menos uma vez, e então verifica a condição

    int i;
    for (i = 0; i < 10; i++){
        // ...
    }





    return 0;
}

/*
No MacOs:

    1. Certifique-se de que o Clang está instalado, pelo terminal:

        clang --version

    2. Compile o código:

        clang c_main.c
        OU
        clang -o outputname c_main.c  // Nomeando o arquivo compilado

    3. Rode o código compilado:

        ./a.out  // Nome padrão
        OU
        ./outputname
*/