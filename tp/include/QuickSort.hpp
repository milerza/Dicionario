#ifndef _QUICKSORT_
#define _QUICKSORT_

#include "FilaEncadeada.hpp"

void Particao(TipoItem * vetor, int esquerda, int direita, int *i, int *j){
    *i = esquerda;
    *j = direita;
    
    std::string pivo = vetor[(*i + *j) / 2].palavra;

    TipoItem aux;

    while (*i <= *j)
    {
        while (vetor[*i].palavra < pivo){
            (*i)++;
        }
        while (vetor[*j].palavra > pivo){
            (*j)--;
        }

        if (*i <= *j){
            aux = vetor[*i];
            vetor[*i] = vetor[*j];
            vetor[*j] = aux;
            (*i)++;
            (*j)--;
        }
    }
}

void quickSortRecursivo(TipoItem *vetor, int esquerda, int direita){
    int i , j;
    Particao(vetor, esquerda, direita, &i, &j);

    if (j > esquerda){
        quickSortRecursivo(vetor, esquerda, j);
    }
    if (i < direita){
        quickSortRecursivo(vetor, i, direita);
    }
}

#endif