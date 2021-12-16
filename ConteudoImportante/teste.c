#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno Aluno;
struct aluno
{
    int matricula;
    char nome[81];
    char endereco[121];
    char telefone[21];
};

typedef struct elemento Elemento;
struct elemento
{
    Aluno a;
    Elemento *prox;
};

Elemento *criaListaVazia()
{
    return NULL;
}

/* função insere_ordenado: insere elemento em ordem */
Elemento *lista_insere_ordenado(Elemento *lista, Aluno al)
{
    Elemento *novo;
    Elemento *a = NULL;  /* ponteiro para elemento anterior */
    Elemento *p = lista; /* ponteiro para percorrer a lista */

    while (p != NULL && strcmp(p->a.nome, al.nome) < 0)
    {
        a = p; /* procura posição de inserção */
        p = p->prox;
    }
    /* cria novo elemento */
    novo = (Elemento *)malloc(sizeof(Elemento));

    strcpy(novo->a.nome, al.nome);
    strcpy(novo->a.endereco, al.endereco);
    strcpy(novo->a.telefone, al.telefone);
    novo->a.matricula = al.matricula;

    if (a == NULL)
    {
        novo->prox = lista; /* insere elemento no início */
        lista = novo;
    }
    else
    {
        novo->prox = a->prox; /* insere elemento no meio da lista */
        a->prox = novo;
    }
    return lista;
}

/* função vazia: retorna 1 se vazia ou 0 se não vazia */
int lista_vazia(Elemento *lista)
{
    return lista == NULL;
}

int main()
{

    Elemento *p = NULL;
    Elemento *c = criaListaVazia();

    return 0;
}