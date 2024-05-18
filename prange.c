#include "prange.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "matrix.h"
#include "binary_inverse.h"

// Fonction pour choisir un ensemble d'information aléatoire
Vector randomInformationSet(int n, int k){
    srand(time(NULL));
    Vector I = initVector(n-k);
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
    for (int i = 0; i < I.size; i++) {
        I.elements[i] = array[i];
    }

    free(array);
    return I;
}

// Fonction qui retourne sous-matrice de taille (n-k) de A dont les colonnes sont indexées par I
BinaryMatrix indexedMatrix(BinaryMatrix A, Vector I, int n, int k){
    BinaryMatrix AI = initBinaryMatrix(A.rows, A.rows);
    for(int i = 0; i < A.rows; i++){
        for(int j = 0; j < A.rows; j++){
            AI.elements[i][j] = A.elements[i][I.elements[j]-1];
        }
    }
    return AI;
}

// Fonction qui retourne x de longeur n à partir de x de longueur n-k et I
BinaryVector resizeBinaryVector(BinaryVector x, Vector I, int n){
    BinaryVector u = initBinaryVector(n);
    for(int i = 0; i < I.size; i++){
        u.elements[I.elements[i]] = x.elements[i];
    }
    return u;
}

// Algorithme de Prange
BinaryVector Prange(BinaryMatrix H, BinaryVector s, int t, int n, int k){
    BinaryVector x = initBinaryVector(H.rows);
    Vector I = randomInformationSet(n,k);
    int w = 0;
    while(w != t){
        Vector I = randomInformationSet(n,k);
        BinaryMatrix HI = indexedMatrix(H, I, n, k);
        BinaryMatrix HII = binaryMatrixInverse(HI);
        if(!isMatrixEmpty(HII)){
            BinaryVector x = binaryMatrixVectorProduct(HII, s);
            w = hammingWeight(x);
        }
    }
    BinaryVector xx = resizeBinaryVector(x, I, n);
    return x;
}