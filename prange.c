#include "prange.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "matrix.h"
#include "binary_inverse.h"

// Fonction pour choisir un ensemble d'information aléatoire
Vector randomInformationSet(int n, int k){
    //srand(time(NULL));
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
BinaryMatrix indexedMatrix(BinaryMatrix A, Vector I){
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
    printf("I : \n");
    printVector(I);
    printf("\n");

    printf("x : \n");
    printBinaryVector(x);
    printf("\n");
    BinaryVector u = initBinaryVector(n);
    for(int i = 0; i < I.size; i++){
        //printf("x[%d] = %d\n",i,x.elements[i]);
        //printf("I[%d]-1 = %d\n",i,I.elements[i]-1);
        u.elements[I.elements[i]-1] = x.elements[i];
    }
    return u;
}

// Algorithme de Prange
BinaryVector Prange(BinaryMatrix H, BinaryVector s, int t, int n, int k){
    BinaryVector x = initBinaryVector(H.rows);
    Vector I = randomInformationSet(n,k);
    int w = 0;
    int count = 0;
    while(w != t && count < 10){
        printf("Prange [%d]\n", count);
        I = randomInformationSet(n,k);
        /*printf("I : \n");
        printVector(I);
        printf("\n");*/

        BinaryMatrix HI = indexedMatrix(H, I);
        /*printf("HI : \n");
        printBinaryMatrix(HI);
        printf("\n");*/

        BinaryMatrix HII = binaryMatrixInverse(HI);
        /*printf("HII : \n");
        printBinaryMatrix(HII);
        printf("\n");*/

        if(!isMatrixEmpty(HII)){
            x = binaryMatrixVectorProduct(HII, s);
            /*printf("x : \n");
            printBinaryVector(x);
            printf("\n");*/
            w = hammingWeight(x);
            //printf("w(x) = %d\n",w);
        }
        count++;
    }
    BinaryVector xx = resizeBinaryVector(x, I, n);
    return xx;
}