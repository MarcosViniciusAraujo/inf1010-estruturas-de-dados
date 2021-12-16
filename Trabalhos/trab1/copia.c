#include <stdio.h>
#include <stdlib.h>

//Constantes para tipos
#define RET 0
#define TRI 1
#define CIR 2

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
ListaHet *criaListaVazia(void);
ListaHet *criaNoRet(float b, float h);
ListaHet *criaNoTri(float b, float h);
ListaHet *criaNoCir(float r);
ListaHet *insereElementoFinalLista(ListaHet *l, int tipo, void *poligono);
void exibeListaInicioFim(ListaHet *l);
ListaHet *removeElementoLista(ListaHet *l, int tipo, void *poligono);

int main(void)
{
}

ListaHet *criaListaVazia(void)
{
    return NULL;
}

ListaHet *criaNoRet(float b, float h)
{
    Retangulo *r;
    ListaHet *p;

    r = (Retangulo *)malloc(sizeof(Retangulo));
    r->b = b;
    r->h = h;

    p = (ListaHet *)malloc(sizeof(ListaHet));
    p->tipo = RET;
    p->info = r;
    p->prox = NULL;

    return p;
}

ListaHet *criaNoCir(float r)
{
    Circulo *elemento;
    ListaHet *p;

    elemento = (Circulo *)malloc(sizeof(Circulo));
    elemento->r = r;

    p = (ListaHet *)malloc(sizeof(ListaHet));
    p->tipo = CIR;
    p->info = elemento;
    p->prox = NULL;

    return p;
}

ListaHet *criaNoTri(float b, float h)
{
    Triangulo *r;
    ListaHet *p;

    r = (Triangulo *)malloc(sizeof(Triangulo));
    r->b = b;
    r->h = h;

    p = (ListaHet *)malloc(sizeof(ListaHet));
    p->tipo = TRI;
    p->info = r;
    p->prox = NULL;

    return p;
}

ListaHet *insereElementoFinalLista(ListaHet *l, int tipo, void *poligono)
{

    ListaHet *elemento;

    if (tipo == RET)
    {

        elemento = criaNoRet(poligono->b, (Retangulo *)poligono->h);
    }

    else if (tipo == CIR)
    {
    }

    else if (tipo == TRI)
    {
    }
}
