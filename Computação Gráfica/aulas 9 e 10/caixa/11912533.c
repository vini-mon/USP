// Faça um programa que leia vários números inteiros positivos e imprima o maior e menor número (um em cada linha). O programa é encerrado se for informado um número zero ou negativo.

#include <stdio.h>
#include <stdlib.h>
int insercao(int *vet);
int tam;

int main(){
    int numeroDigitado, *vet = (int*) malloc (sizeof(int));
    scanf("%d", &numeroDigitado);
    for (tam = 0; numeroDigitado > 0; tam ++){
        vet = (int*) realloc (vet, sizeof(int)*(tam +  1));
        vet[tam] = numeroDigitado;
        scanf("%d", &numeroDigitado);
    }
	tam--;
    insercao(vet);
    printf("%d\n%d\n", vet[tam], vet[0]);
    return 0;
}

int insercao(int *vet){
    int i, j, x;
    for (i = 0; i < tam+1; i++){
        x = vet[i];
        j = i - 1;
        vet[i] = x;
        while (x < vet[j]){
            vet[j + 1] = vet[j];
            j--;
        }
        vet[j + 1] = x;
    }
    return 0;
}



