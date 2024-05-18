#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Fonction pour allouer une matrice carrée de taille (n-k)*n
bool** allocateMatrix(int n, int k) {
    bool** matrix = (bool**)malloc(n * sizeof(bool*));
    for(int i = 0; i < (n-k); i++) {
        matrix[i] = (bool*)malloc(n * sizeof(bool));
    }
    return matrix;
}

// Fonction pour libérer la mémoire d'une matrice carrée de n lignes
void freeMatrix(bool** matrix, int n) {
    for(int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Fonction pour afficher une matrice carrée de taille (n-k)*n
void printMatrix(bool** matrix, int n, int k) {
    for(int i = 0; i < (n-k); i++) {
        for(int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Fonction pour allouer un vecteur de taille n
bool* allocateVector(int n){
    bool* vector = (bool*)malloc(n * sizeof(bool));
    return vector;
}

// Fonction pour afficher un vecteur de taille n
void printVector(bool* vector, int n){
    for(int i = 0; i < n; i++) {
        printf("%d ", vector[i]);
    }
}

// Fonction pour créer une matrice binaire aléatoire de taille (n-k)*n 
bool** randomMatrix(int n, int k){
    srand(time(NULL));
    bool** R = allocateMatrix(n,k);
    for(int i = 0; i < (n-k); i++) {
        for(int j = 0; j < n; j++) {
            R[i][j] = rand() % 2;
        }
    }
    return R;
}

// Fonction pour le produit matriciel d'une matrice de taille n par un vecteur de taille n
bool* matrixProduct(int n, bool* x, bool** A){
    bool* p = allocateVector(n);
    for(int i = 0; i < n; i++){
        int s = 0;
        for(int j = 0; j < n; j++){
            s += A[i][j] * x[j];
        }
    }
    return p;
}

// Fonction pour calculer le poids de Hamming d'un vecteur de taille n
int hammingWeight(bool* x, int n){
    int weight = 0;
    for(int i = 0; i < n; i++){
        weight += x[i];
    }
    return weight;
}