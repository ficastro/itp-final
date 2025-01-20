#include <stdio.h>
#include <string.h>

typedef struct discente {
    char nome[100];
    float mc;
    char turno;
} Discente;

void trocar(Discente *a, Discente *b) {
    Discente temp = *a;
    *a = *b;
    *b = temp;
}

void ordernar(Discente alunos[], int nAlunos) {
    for (int i = 0; i < nAlunos - 1; i++) {
        for (int j = 0; j < nAlunos - i - 1; j++) {
            if (alunos[j].mc < alunos[j + 1].mc) {
                trocar(&alunos[j], &alunos[j + 1]);
            }
        }
    }
}

int main() {
    char turma[50], turno_turma;
    int nVagas, nAlunos;

    scanf("%s %d %c %d", turma, &nVagas, &turno_turma, &nAlunos);

    Discente alunos[nAlunos];
    for (int i = 0; i < nAlunos; i++) {
        scanf("%s %f %c", alunos[i].nome, &alunos[i].mc, &alunos[i].turno);
    }

    ordernar(alunos, nAlunos);

    int vagas_restantes = nVagas;
    for (int i = 0; i < nAlunos && vagas_restantes > 0; i++) {
        if (alunos[i].turno == turno_turma) {
            printf("%s\n", alunos[i].nome);
            vagas_restantes--;
        }
    }

    return 0;
}