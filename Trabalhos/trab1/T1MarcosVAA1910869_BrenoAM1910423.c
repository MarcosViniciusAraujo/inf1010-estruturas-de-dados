/*************************************************************
Breno Azevedo Marot - 1910423
Marcos Vinicius Araujo Almeida - 1910869
*************************************************************/
#include <stdio.h>
#include <stdlib.h>

//Constantes para tipos
#define RET 0
#define TRI 1
#define CIR 2

#define PI 3.14159265
//tipos estruturados
struct retangulo
{
    float b;
    float h;
};
typedef struct retangulo Retangulo;

struct triangulo
{
    float b;
    float h;
};
typedef struct triangulo Triangulo;

struct circulo
{
    float r;
};
typedef struct circulo Circulo;

struct lista_het
{
    int tipo;
    void *info;
    struct lista_het *prox;
    struct lista_het *ant;
};
typedef struct lista_het ListaHet;

//funções
float calculaAreaRet(float h, float b)
{
    return b * h;
}

float calculaAreaCirc(float r)
{
    return PI * r * r;
}

ListaHet *criaListaVazia(void)
{
    return NULL;
}

ListaHet *criaNoRet(ListaHet *l, float b, float h)
{

    Retangulo *r;
    ListaHet *novo;

    //cria um retangulo
    r = (Retangulo *)malloc(sizeof(Retangulo));
    r->b = b;
    r->h = h;

    //cria um novo nó
    novo = (ListaHet *)malloc(sizeof(ListaHet));
    novo->tipo = RET;
    novo->info = r;
    novo->prox = NULL;

    if (l == NULL)
    {
        return novo;
    }

    //percorrer a lista
    l->ant = novo;
    novo->prox = l;

    return novo;
}

ListaHet *criaNoCir(ListaHet *l, float r)
{
    Circulo *elemento;
    ListaHet *novo;

    elemento = (Circulo *)malloc(sizeof(Circulo));
    elemento->r = r;

    novo = (ListaHet *)malloc(sizeof(ListaHet));
    novo->tipo = CIR;
    novo->info = elemento;
    novo->prox = NULL;
    novo->ant = NULL;

    if (l == NULL)
    {
        return novo;
    }

    //percorrer a lista
    l->ant = novo;
    novo->prox = l;

    return novo;
}

ListaHet *criaNoTri(ListaHet *l, float b, float h)
{
    Triangulo *elemento;
    ListaHet *novo;

    elemento = (Triangulo *)malloc(sizeof(Triangulo));
    elemento->b = b;
    elemento->h = h;

    novo = (ListaHet *)malloc(sizeof(ListaHet));
    novo->tipo = TRI;
    novo->info = elemento;
    novo->prox = NULL;
    novo->ant = NULL;

    if (l == NULL)
    {
        return novo;
    }

    l->ant = novo;
    novo->prox = l;

    return novo;
}

void exibeListaInicioFim(ListaHet *l)
{
    ListaHet *p;
    for (p = l; p != NULL; p = p->prox)
    {
        if (p->tipo == TRI)
        {
            Triangulo *atual = (Triangulo *)p->info;
            printf("---------------TRI---------------\n");
            printf("Base: %.2f Altura: %.2f\n", atual->b, atual->h);
        }

        else if (p->tipo == RET)
        {
            printf("---------------RET---------------\n");
            Retangulo *atual = (Retangulo *)p->info;
            printf("Base: %.2f Altura: %.2f\n", atual->b, atual->h);
        }

        else if (p->tipo == CIR)
        {
            printf("---------------CIR---------------\n");
            Circulo *atual = (Circulo *)p->info;
            printf("Raio: %.2f\n", atual->r);
        }

        else
        {
            printf("Tipo definido incorrentamente\n");
        }
    }

    printf("\n\n\n");
}

void exibeElementosArea(ListaHet *l, float a)
{
    ListaHet *p;
    float area;
    for (p = l; p != NULL; p = p->prox)
    {
        if (p->tipo == CIR)
        {
            Circulo *atual = (Circulo *)p->info;
            area = calculaAreaCirc(atual->r);

            if (area > a)
                printf("-----------------------CIRCULO-----------------------\nRaio: %.2f\n", atual->r);
        }

        else if (p->tipo == RET)
        {
            Retangulo *atual = (Retangulo *)p->info;
            area = calculaAreaRet(atual->b, atual->h);

            if (area > a)
                printf("-----------------------RETANGULO-----------------------\nBase: %.2f Altura: %.2f\n", atual->b, atual->h);
        }

        else if (p->tipo == TRI)
        {
            Triangulo *atual = (Triangulo *)p->info;
            area = calculaAreaRet(atual->b, atual->h);

            if (area > a)
                printf("-----------------------TRIANGULO-----------------------\nBase: %.2f Altura: %.2f\n", atual->b, atual->h);
        }
    }
}

void liberaLista(ListaHet *l)
{
    ListaHet *p;

    p = l;
    while (p != NULL)
    {
        ListaHet *t = p->prox;
        free(p->info);
        free(p);

        p = t;
    }
}

ListaHet *busca(ListaHet *lst, float area)
{
    ListaHet *p;
    for (p = lst; p != NULL; p = p->prox)
    {
        float a;
        if (p->tipo == RET)
        {
            Retangulo *atual = (Retangulo *)p->info;
            a = calculaAreaRet(atual->b, atual->h);
        }

        if (p->tipo == TRI)
        {
            Triangulo *atual = (Triangulo *)p->info;
            a = calculaAreaRet(atual->b, atual->h);
        }
        if (p->tipo == CIR)
        {
            Circulo *atual = (Circulo *)p->info;
            a = calculaAreaCirc(atual->r);
        }

        if (a <= area)
            return p;
    }

    return NULL;
}

ListaHet *removeElementoArea(ListaHet *l, float a)
{

    ListaHet *p = busca(l, a);

    if (p == NULL)
        return l;

    while (p != NULL)
    {

        if (l == p)
            l = p->prox;
        else
            p->ant->prox = p->prox;
        if (p->prox != NULL)
            p->prox->ant = p->ant;
        p = busca(l, a);
    }

    free(p);
    return l;
}

void exibeListaFimInicio(ListaHet *l)
{
    ListaHet *p, *t;

    p = l;
    while (p->prox != NULL)
    {
        p = p->prox;
    }

    t = p;

    for (; t != NULL; t = t->ant)
    {

        if (t->tipo == RET)
        {
            Retangulo *atual = (Retangulo *)t->info;
            printf("---------------------RETANGULO---------------------\n");
            printf("BASE: %.2f ALTURA: %.2f\n", atual->b, atual->h);
        }
        if (t->tipo == TRI)
        {
            Triangulo *atual = (Triangulo *)t->info;
            printf("---------------------TRIANGULO---------------------\n");
            printf("BASE: %.2f ALTURA: %.2f\n", atual->b, atual->h);
        }
        if (t->tipo == CIR)
        {
            Circulo *atual = (Circulo *)t->info;
            printf("---------------------CIRCULO---------------------\n");
            printf("RAIO: %.2f\n", atual->r);
        }
    }
}

int main(void)
{

    printf("==========================================\n");
    printf("A)\n");
    ListaHet *l = criaListaVazia();
    printf("Lista Criada!\n");
    printf("==========================================\n");
    printf("B & C)\n");
    l = criaNoRet(l, 1.0, 2.0);
    l = criaNoRet(l, 300.0, 600.0); //deve passar

    exibeListaInicioFim(l);

    l = criaNoCir(l, 3.0);
    l = criaNoCir(l, 200.0); //deve passar

    exibeListaInicioFim(l);

    l = criaNoTri(l, 5.0, 10.0);
    l = criaNoTri(l, 100.0, 200.0); //deve passar

    exibeListaInicioFim(l);
    printf("==========================================\n");
    printf("D)\n");
    exibeElementosArea(l, 2500.0);

    printf("==========================================\n");
    printf("E)\nANTES\n");

    exibeListaInicioFim(l);
    printf("***************************************************************\nDEPOIS\n");
    l = removeElementoArea(l, 2500.0);
    exibeListaInicioFim(l);

    printf("==========================================\n");
    printf("F)\n");

    exibeListaFimInicio(l);
    return 0;
}
