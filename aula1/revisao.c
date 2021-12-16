#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno
{
    int matricula;
    char nome[80];
    char endereco[120];
    char telefone[20];

} Aluno;

void imprimeString(char *s)
{
    printf("%s\n");
}

int comprimentoDaString(char *s)
{
    if (s == '\0')
    {
        return;
    }

    else
    {
        return 1 + comprimentoDaString(s + 1);
    }
}

Aluno **criaVetor(int tamanho)
{
    Aluno **vetorAlunos;

    vetorAlunos = (Aluno **)malloc(tamanho * sizeof(Aluno *));

    for (int i = 0; i < tamanho; i++)
    {
        vetorAlunos[i] = (Aluno *)malloc(sizeof(Aluno));
    }

    return vetorAlunos;
}

int main()
{

    return 0;
}