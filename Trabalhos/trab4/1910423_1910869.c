/*
    Breno Azevedo Marot - 1910423
    Marcos Vinicius Araujo Almeida - 1910869
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct _viz
{
    int noj;
    int peso;
    struct _viz *prox;
} Viz;

typedef struct _grafo
{
    int nv;    /* numero de nos ou vertices */
    int na;    /* numero de arestas */
    Viz **viz; /* viz[i] aponta para a lista
    de arestas incidindo em i */
} Grafo;

typedef struct uniaoBusca
{
    int n;
    int *v;
} UniaoBusca;

typedef struct elemento
{
    int peso;
    int ini;
    int fim;
    struct elemento *prox;
} Elemento;

static Viz *criaViz(Viz *head, int noj, int peso)
{
    /* insere vizinho no inicio da lista */
    Viz *no = (Viz *)malloc(sizeof(Viz));
    // assert(no);
    no->noj = noj;
    no->peso = peso;
    no->prox = head;
    return no;
}

int vetorAdjacencias[8];

Grafo *grafoCria(int nv, int na)
{
    int i;
    Grafo *g = (Grafo *)malloc(sizeof(Grafo));
    g->nv = nv;
    g->na = na;
    g->viz = (Viz **)malloc(sizeof(Viz *) * nv);
    for (i = 0; i < nv; i++)
        g->viz[i] = NULL;
    return g;
}

Grafo *criaGrafoDado(int nv, int na)
{
    Grafo *g = grafoCria(nv, na);
    // grafo->viz[no1] = criaViz(grafo->viz[no1], no2, peso);

    g->viz[0] = criaViz(g->viz[0], 1, 4);
    g->viz[0] = criaViz(g->viz[0], 8, 8);

    g->viz[1] = criaViz(g->viz[1], 8, 11);
    g->viz[1] = criaViz(g->viz[1], 3, 8);
    g->viz[1] = criaViz(g->viz[1], 0, 4);

    g->viz[8] = criaViz(g->viz[8], 0, 8);
    g->viz[8] = criaViz(g->viz[8], 1, 11);
    g->viz[8] = criaViz(g->viz[8], 9, 7);
    g->viz[8] = criaViz(g->viz[8], 7, 1);

    g->viz[9] = criaViz(g->viz[9], 8, 7);
    g->viz[9] = criaViz(g->viz[9], 7, 6);
    g->viz[9] = criaViz(g->viz[9], 3, 2);

    g->viz[3] = criaViz(g->viz[3], 9, 2);
    g->viz[3] = criaViz(g->viz[3], 1, 8);
    g->viz[3] = criaViz(g->viz[3], 6, 4);
    g->viz[3] = criaViz(g->viz[3], 4, 7);

    g->viz[7] = criaViz(g->viz[7], 9, 6);
    g->viz[7] = criaViz(g->viz[7], 8, 1);
    g->viz[7] = criaViz(g->viz[7], 6, 2);

    g->viz[4] = criaViz(g->viz[4], 3, 7);
    g->viz[4] = criaViz(g->viz[4], 6, 14);
    g->viz[4] = criaViz(g->viz[4], 5, 9);

    g->viz[6] = criaViz(g->viz[6], 7, 2);
    g->viz[6] = criaViz(g->viz[6], 3, 4);
    g->viz[6] = criaViz(g->viz[6], 4, 14);
    g->viz[6] = criaViz(g->viz[6], 5, 10);

    g->viz[5] = criaViz(g->viz[5], 4, 9);
    g->viz[5] = criaViz(g->viz[5], 6, 10);

    return g;
}

UniaoBusca *cria(int size)
{
    /* aloca novo item com tamanho dado e
    preenche vetor com -1 */

    UniaoBusca *uf = (UniaoBusca *)malloc(sizeof(UniaoBusca));

    if (uf == NULL)
        return NULL;

    uf->n = size;
    uf->v = (int *)malloc(size * sizeof(int));

    if (uf->v == NULL)
        return NULL;

    for (int i = 0; i < size; i++)
        uf->v[i] = i;

    return uf;
}

int ub_busca(UniaoBusca *ub, int u)
{
    int x = u;
    int aux;
    if ((u < 0) || (u > ub->n))
        return -1;
    while (ub->v[u] != u)
        u = ub->v[u];
    while (ub->v[x] != x)
    {
        aux = x;
        x = ub->v[x];
        ub->v[aux] = u;
    }
    return u;
}

/* implementacao de uniao ineficiente */
int ub_uniao(UniaoBusca *ub, int u, int v)
{
    v = ub_busca(ub, v); /* acha raiz da árvore de v */
    u = ub_busca(ub, u); /* acha raiz da árvore de u */

    ub->v[u] = v;
    return v;
}

Elemento *lista_insere_ordenado(Elemento *lista, int val, int ori, int fim)
{
    Elemento *novo;
    Elemento *a = NULL;  /* ponteiro para elemento anterior */
    Elemento *p = lista; /* ponteiro para percorrer a lista */

    while (p != NULL && p->peso < val)
    {
        a = p; /* procura posição de inserção */
        p = p->prox;
    }
    /* cria novo elemento */
    novo = (Elemento *)malloc(sizeof(Elemento));
    novo->peso = val;
    novo->fim = fim;
    novo->ini = ori;

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

Elemento *lst_cria()
{
    return 0;
}

/* função busca: busca um elemento na lista */
Elemento *busca(Elemento *lista, int v)
{
    Elemento *p;
    for (p = lista; p != NULL; p = p->prox)
    {
        if (p->peso == v)
            return p; /* achou o elemento */
    }
    return NULL; /* não achou o elemento */
}

Elemento *lista_retira(Elemento *lista, int val, int ini, int fim)
{
    Elemento *a = NULL;  /* ponteiro para elemento anterior */
    Elemento *p = lista; /* ponteiro para percorrer a lista */
    /* procura elemento na lista, guardando anterior */
    while (p != NULL && (p->peso != val || p->ini != ini || p->fim != fim))
    {
        // printf("oi\n");
        a = p;
        p = p->prox;
    }
    /* verifica se achou elemento */
    if (p == NULL)
    {
        // printf("[%d, %d]\n", a->ini, a->fim);
        return lista; /* não achou: retorna lista original */
    }
    /* retira elemento */
    if (a == NULL)
    {
        // printf("[%d, %d]\n", p->ini, p->fim);
        lista = p->prox; /* retira elemento do inicio */
    }
    else
    {
        // printf("[%d, %d]\n", p->ini, p->fim);
        a->prox = p->prox; /* retira elemento do meio da lista */
    }
    free(p);
    return lista;
}

Elemento *preencheListaOrdenada(Grafo *g)
{
    int i;
    Viz *p;
    Elemento *lst = lst_cria();
    Elemento *aux;

    for (i = 0; i < g->nv; i++)
        for (p = g->viz[i]; p != NULL; p = p->prox)
            lst = lista_insere_ordenado(lst, p->peso, i, p->noj);

    for (aux = lst; aux != NULL; aux = aux->prox)
        lst = lista_retira(lst, aux->peso, aux->fim, aux->ini);

    return lst;
}

void geraArvoreMinima(Grafo *g, Elemento *arestas)
{
    UniaoBusca *ub = cria(g->nv);
    Elemento *p;
    int vertex1, vertex2;
    int cont = 0;

    for (p = arestas; p != NULL; p = p->prox)
    {
        vertex1 = p->ini;
        vertex2 = p->fim;

        if (vertex1 == 9)
            vertex1 = 2;
        if (vertex2 == 9)
            vertex2 = 2;

        // printf("[%d, %d] - %d\n", vertex1, vertex2, ub->v[ub_uniao(ub, vertex2, vertex1)]);
        int b1 = ub_busca(ub, vertex1);

        if (ub->v[ub_uniao(ub, vertex1, vertex2)] != b1)
        {
            // printf("[%d, %d] - %d\n\n", vertex1, vertex2, p->peso);
            vetorAdjacencias[cont] = p->peso;
            cont++;
        }
    }
}

void exibeVetorAdjacencias()
{
    for (int i = 0; i < 8; i++)
    {
        printf("-> %d\n\n", vetorAdjacencias[i]);
    }
}

int main()
{

    Grafo *g = criaGrafoDado(9, 14);

    Elemento *arestas = preencheListaOrdenada(g);

    geraArvoreMinima(g, arestas);

    exibeVetorAdjacencias();

    return 0;
}