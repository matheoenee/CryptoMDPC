#include "prange.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "matrix.h"
#include "binary_inverse.h"

// Fonction pour choisir un ensemble d'information aléatoire
int* randomInformationSet(int n, int k){
    srand(time(NULL));
    int* I = (int*)malloc((n-k) * sizeof(int));
    int *array = (int*)malloc(n * sizeof(int));

    // Remplir l'array avec les nombres de 1 à n
    for (int i = 0; i < n; i++) {
        array[i] = i + 1;
    }

    // Mélange de Fisher-Yates
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }

    // Sélectionner les premiers n-k éléments
    for (int i = 0; i < (n-k); i++) {
        I[i] = array[i];
    }

    free(array);
    return I;
}

// Fonction qui retourne sous-matrice de taille (n-k) de A dont les colonnes sont indexées par I
bool** indexedMatrix(bool** A, int* I, int n, int k){
    bool** AI = allocateMatrix(n-k, 0);
    for(int i = 0; i < (n-k); i++){
        for(int j = 0; j < (n-k); j++){
            AI[i][j] = A[i][I[j]-1];
        }
    }
    return AI;
}

// Algorithme de Prange
bool* Prange(bool** H, bool* s, int t, int n, int k){
    bool* x = allocateVector(n-k);
    int w = 0;
    while(w != t){
        int* I = randomInformationSet(n,k);
        bool** HI = indexedMatrix(H, I, n, k);
        bool** HII = binary_inverse(HI, n-k);
        if(HII){
            bool* x = matrixProduct(n-k, s, HII);
            w = hammingWeight(x, n);
        }
        return x;
    }
}