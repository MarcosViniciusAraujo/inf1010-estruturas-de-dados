/**************************************************************************

    Breno Azevedo Marot - 1910423
    Marcos Vincius Araujo Almeida - 1910869

**************************************************************************/

#include <stdio.h>
#include <stdlib.h>

struct _abb
{
    int info;
    int altura;       //questao 3
    struct _abb *pai; //questao 2
    struct _abb *esquerda;
    struct _abb *direita;
};
typedef struct _abb Abb;

Abb *criaArvVazia()
{
    return NULL;
}

//função para inserir o elemento na ABB
Abb *insereElemento(Abb *a, int v)
{
    if (a == NULL)
    {
        a = (Abb *)malloc(sizeof(Abb));
        a->info = v;
        a->esquerda = a->direita = criaArvVazia();
    }

    else if (v < a->info)
        a->esquerda = insereElemento(a->esquerda, v);

    else if (v > a->info)
        a->direita = insereElemento(a->direita, v);

    return a;
}

//função para preencher os pais
void preenchePai(Abb *a)
{
    if (a == NULL)
        return;
    if (a->esquerda != NULL)
        a->esquerda->pai = a;

    if (a->direita != NULL)
        a->direita->pai = a;

    preenchePai(a->esquerda);
    preenchePai(a->direita);
}

//função para exibir a arvore
void exibeArvPosOrdem(Abb *a)
{

    if (a == NULL)
        return;

    exibeArvPosOrdem(a->esquerda);
    exibeArvPosOrdem(a->direita);
    if (a->pai != NULL)
        printf("info: %d altura: %d pai: %d\n", a->info, a->altura, a->pai->info);

    else
        printf("info: %d altura: %d pai: %p\n", a->info, a->altura, a->pai);
}

//função para criar a arvore dada na questão...
Abb *criaArvDada()
{
    Abb *arv = criaArvVazia();

    //altura = 0 pois não foi preenchida
    arv = insereElemento(arv, 15);
    exibeArvPosOrdem(arv);
    printf("\n\n");
    arv = insereElemento(arv, 10);
    exibeArvPosOrdem(arv);
    printf("\n\n");
    arv = insereElemento(arv, 20);
    exibeArvPosOrdem(arv);
    printf("\n\n");
    arv = insereElemento(arv, 5);
    exibeArvPosOrdem(arv);
    printf("\n\n");
    arv = insereElemento(arv, 18);
    exibeArvPosOrdem(arv);
    printf("\n\n");
    arv = insereElemento(arv, 25);
    exibeArvPosOrdem(arv);
    printf("\n\n");
    arv = insereElemento(arv, 16);
    exibeArvPosOrdem(arv);
    printf("\n\n");
    arv = insereElemento(arv, 19);
    exibeArvPosOrdem(arv);
    printf("\n\n");
    arv = insereElemento(arv, 22);
    exibeArvPosOrdem(arv);
    printf("\n\n");
    arv = insereElemento(arv, 30);
    exibeArvPosOrdem(arv);
    printf("\n\n");
    arv = insereElemento(arv, 21);

    return arv;
}

//função auxiliar para a preencheAlturas
int calculaAlturaNo(Abb *no)
{
    Abb *copia = no;

    if (copia == NULL)
    {
        return -1;
    }

    else
    {
        return calculaAlturaNo(copia->pai) + 1;
    }
}

//função para a questãop 3
void preencheAlturas(Abb *a)
{
    if (a == NULL)
        return;

    preencheAlturas(a->esquerda);
    a->altura = calculaAlturaNo(a);
    preencheAlturas(a->direita);
}

//função auxiliar para exibeNivelCompleto
int calculaAlturaMax(Abb *raiz)
{
    int hEsquerda, hDireita;

    if (raiz == NULL)
        return 0;
    hEsquerda = calculaAlturaMax(raiz->esquerda);
    hDireita = calculaAlturaMax(raiz->direita);
    return 1 + (hEsquerda > hDireita ? hEsquerda : hDireita);
}

//função auxiliar para exibeNivelCompleto
void exibeNivelAtual(Abb *arv, int nivel)
{
    if (arv == NULL)
        return;

    //usei o printf apenas como exemplo, mas podemos fazer qualquer tipo de operação
    if (nivel == 1)
        printf("%d ", arv->info);
    else if (nivel > 1)
    {
        exibeNivelAtual(arv->esquerda, nivel - 1);
        exibeNivelAtual(arv->direita, nivel - 1);
    }
}

//função para a questão 4
void exibeNivelCompleto(Abb *arv)
{
    int h = calculaAlturaMax(arv);

    for (int i = 1; i <= h; i++)
    {
        exibeNivelAtual(arv, i);
        printf("\n");
    }
}

int main(void)
{

    //ponteiro para o pai e altura dos nós preenchida
    printf("Preenchendo a arvore...\n\n");
    Abb *ARV = criaArvDada();

    printf("\nPreenchendo pai...\n\n");
    preenchePai(ARV);
    exibeArvPosOrdem(ARV);

    printf("\nPreenchendo as alturas...\n\n");
    preencheAlturas(ARV);
    exibeArvPosOrdem(ARV);

    printf("\n\nExibindo a arvore em níveis...\n\n");
    exibeNivelCompleto(ARV);

    return 0;
}
