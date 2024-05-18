#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "structures.h"

// Fonction pour créer une matrice binaire
BinaryMatrix initBinaryMatrix(int rows, int cols){
    BinaryMatrix A;
    A.rows = rows;
    A.cols = cols;
    bool** elements = (bool**)malloc(rows * sizeof(bool*));
    for(int i = 0; i < rows; i++){
        elements[i] = (bool*)malloc(cols * sizeof(bool));
    }
    A.elements = elements;
    return A;
}

// Fonnction pour créer un vecteur binaire
BinaryVector initBinaryVector(int n){
    BinaryVector u;
    u.size = n;
    bool* elements = (bool*)malloc(n * sizeof(bool*));
    u.elements = elements;
    return u;
}

// Fonnction pour créer un vecteur
Vector initVector(int n){
    Vector u;
    u.size = n;
    int* elements = (int*)malloc(n * sizeof(int*));
    u.elements = elements;
    return u;
}

// Fonction pour créer une matrice binaire aléatoire 
BinaryMatrix randomBinaryMatrix(int rows, int cols){
    srand(time(NULL));
    BinaryMatrix A = initBinaryMatrix(rows,cols);
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            A.elements[i][j] = rand() % 2;
        }
    }
    return A;
}

// Fonction pour le produit matriciel d'une matrice binaire et d'un vecteur binaire (A.u)
BinaryVector binaryMatrixVectorProduct(BinaryMatrix A, BinaryVector u){
    int n = u.size;
    BinaryVector v = initBinaryVector(n);
    if(A.cols != n){
        printf("[+] binary product error, matrix and vector are wrong size.\n");
        return v;
    }
    for(int i = 0; i < n; i++){
        int sum = 0;
        for(int j = 0; j < n; j++){
            sum += A.elements[i][j] * u.elements[j];
        }
        v.elements[i] = sum;
    }
    return v;
}

// Fonction pour le produit matriciel non modulaire (naive product syndrome x H in BitFlipping, order : n**3)
Vector matrixVectorProduct(BinaryVector u, BinaryMatrix A){
    int n = u.size;
    Vector v = initVector(n);
    if(A.cols != n){
        printf("[+] binary product error, matrix and vector are wrong size.\n");
        return v;
    }
    for(int i = 0; i < n; i++){
        int sum = 0;
        for(int j = 0; j < n; j++){
            if(A.elements[j][i] && u.elements[j]) sum += 1;
        }
        v.elements[i] = sum;
    }
    return v;
}

// Fonction pour calculer le poids de Hamming d'un vecteur binaire
int hammingWeight(BinaryVector u){
    int weight = 0;
    int n = u.size;
    for(int i = 0; i < n; i++){
        weight += u.elements[i];
    }
    return weight;
}

// Fonction pour libérer la mémoire d'un vecteur binaire
void freeBinaryVector(BinaryVector u) {
    free(u.elements);
}

// Fonction pour libérer la mémoire d'un vecteur
void freeVector(Vector u) {
    free(u.elements);
}

// Fonction pour libérer la mémoire d'une matrice binaire
void freeBinaryMatrix(BinaryMatrix A) {
    int rows = A.rows;
    for (int i = 0; i < rows; i++) {
        free(A.elements[i]);
    }
    free(A.elements);
}

// Fonction pour afficher une matrice
void printBinaryMatrix(BinaryMatrix A){
    for(int i = 0; i < A.rows; i++) {
        for(int j = 0; j < A.cols; j++) {
            printf("%d ", A.elements[i][j]);
        }
        printf("\n");
    }
}

// Fonction pour afficher un vecteur binaire
void printBinaryVector(BinaryVector u){
    for(int i = 0; i < u.size; i++) {
        printf("%d ", u.elements[i]);
    }
    printf("\n");
}

// Fonction qui renvoie si une matrice est vide ou non
bool isMatrixEmpty(BinaryMatrix A){
    for(int i = 0; i < A.rows; i++){
        for(int j = 0; j < A.cols; j++){
            if(A.elements[i][j]) return false;
        }
    }
    return true;
}