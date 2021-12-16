/********************************************************************
 * 
 *                          Trabalho 3 
 * 
 * 
 *  - Marcos Vinicius Araujo Almeida - 1910869
 * 
 *  - Breno Azevedo Marot - 1910423
 * 
 * 
 * *****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define TAMANHO_PLACA 7
#define MAX_PLACAS 1109
#define BASE 256

int colisoes = 0;
char **arr;
int *pos_colididas;
long *tempos;

/*******************************************
 * 
 *          Método da Divisão 
 *              Hashing
 * 
 ********************************************/
unsigned int hash(char *s)
{
    unsigned int h; // valor do hash
    unsigned const char *us;

    us = (unsigned const char *)s;

    h = 0;
    while (*us != '\0') //percorrendo a string
    {
        h = (h * BASE + *us) % MAX_PLACAS; //mod m
        us++;
    }

    return h;
}

char **init()
{

    char **saida;
    saida = (char **)malloc((MAX_PLACAS) * sizeof(char *));

    return saida;
}

void reseta(char **v)
{

    for (int i = 0; i < MAX_PLACAS; i++)
    {
        v[i] = (char *)malloc((TAMANHO_PLACA + 1) * sizeof(char));
        strcpy(v[i], "xxxxxxx");
    }
}
/**************************************************
 * 
 *              Encadeamento interior
 * 
 * ************************************************/
void insere(char placa[])
{
    unsigned int pos = hash(placa);

    if (strcmp(arr[pos], "xxxxxxx") != 0)
    {
        colisoes++;
        //printf("[%s] colidiu com [%s] (pos: %d)\n", placa, arr[pos], pos);

        pos_colididas[pos]++;

        for (int i = (pos + 1) % MAX_PLACAS;; i++)
        {

            if (i == MAX_PLACAS)
            {
                i = 0;
                continue;
            }
            //primeira casa vazia
            if (strcmp(arr[i], "xxxxxxx") == 0)
            {
                strcpy(arr[i], placa);
                break;
            }
        }
    }

    //sem colisões, livre para inserir
    else
    {
        strcpy(arr[pos], placa);
    }
}

void exibeArr(int n)
{
    for (int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
}

void initVetorColisoes()
{
    pos_colididas = (int *)malloc(MAX_PLACAS * sizeof(int));
    for (int i = 0; i < MAX_PLACAS; i++)
        pos_colididas[i] = 0;
}

void exibeVetColisoes()
{
    for (int i = 0; i < MAX_PLACAS; i++)
    {
        if (pos_colididas[i] != 0)
            printf("Pos: %d  Colisões-locais: %d\n", i, pos_colididas[i]);
    }
}

void initVetorTempos()
{
    tempos = (long *)malloc(10 * sizeof(long));
}

void leArquivo(int n)
{

    FILE *fp = fopen("placas.txt", "r");
    char placa[7];
    int cont = 0;

    initVetorColisoes();

    while (fscanf(fp, "%s", placa) == 1)
    {

        //printf("%s\n", placa);
        insere(placa);
        if (cont == n)
            break;

        cont++;
    }
}

void preencheVetorTempos()
{
    arr = init();

    initVetorTempos();

    for (int i = 1; i <= 10; i++)
    {
        struct timeval start, end;

        colisoes = 0;

        reseta(arr);

        gettimeofday(&start, NULL);

        leArquivo(i * 100);

        gettimeofday(&end, NULL);
        printf("==========> TOTAL DE COLISÕES:: %d\n", colisoes);
        long seconds = (end.tv_sec - start.tv_sec);
        long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

        //printf("The elapsed time is %ld seconds and %ld micros\n", seconds, micros);

        tempos[i - 1] = micros;
    }
}

void exibeVetorTempos(long *v, int n)
{

    for (int i = 0; i < n; i++)
    {
        printf("Com %d elementos -> %ld mcirosegundos\n", (i + 1) * 100, v[i]);
    }
}

int main()
{

    preencheVetorTempos();

    exibeVetorTempos(tempos, 10);

    return 0;
}