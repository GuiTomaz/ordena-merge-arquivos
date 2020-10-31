#include <stdio.h>
#include <stdlib.h>
#include "ordenacoes.h"
void swap(int* val1, int* val2){
    int aux = *val1;
    *val1 = *val2;
    *val2 = aux;
}

int particao(int vect[], int min, int max){
    int pivo = vect[max];
    int i = min -1;
    for(int j = min; j<=max-1; j++){
        if(vect[j]<pivo){
            i++;
            swap(&vect[i], &vect[j]);
        }
    }
    swap(&vect[i+1],&vect[max]);
    return i+1;
}

void quicksort(int vect[], int min, int max){
    int pi;
    if(min<max){
        pi = particao(vect, min, max);

    quicksort(vect, min, pi-1);
    quicksort(vect, pi+1, max);
    }
}
