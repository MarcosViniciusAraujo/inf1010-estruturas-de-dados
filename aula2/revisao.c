#include <stdio.h>
#include <stdlib.h>
#define EQ ==

double fatRec(int n){

    if (n EQ 1) return 1;
    return n * fatRec(n - 1);

}

double fatNoRec(int n){

    double valor = 1;
    while (n > 1){
        valor *= n--;
    }
    return valor;
}


int maiorElementoVetorRec(int *v, int n){
    int max;
    if (n EQ 1) return v[0];
    max = maiorElementoVetoRec(v, n-1);
    if(max < v[n-1]) return v[n-1];
    return max;

}

int maiorElementoVetorNoRec(int *v, int n){
    int maior = 0;
    for(int i = 0; i < n; i++)
        if (v[i] > maior) maior = v[i];
    
    return maior;
}
int main(){
    
    printf("Fatorial de %d (Recursivo): %g\n", 5, fatRec(5));
    printf("Fatorial de %d (Sem Recursão): %g\n", 5, fatNoRec(5));

    return 0;
}
