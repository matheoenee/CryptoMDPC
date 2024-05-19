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
BinaryVector initBinaryVector(int size){
    BinaryVector u;
    u.size = size;
    bool* elements = (bool*)malloc(size * sizeof(bool*));
    u.elements = elements;
    return u;
}

// Pour entrer les valeurs d'un vecteur dans un autre
BinaryVector copyBinaryVector(BinaryVector u){
    BinaryVector v = initBinaryVector(u.size);
    for(int i=0; i<u.size; i++){
        v.elements[i] = u.elements[i];
    }
    return v;
}

// Pour entrer les valeurs d'un vecteur dans un autre (déjà existant)
void recopyBinaryVector(BinaryVector new, BinaryVector old){
    if (old.size != new.size){
        printf("[+] recopy error, %d-size vector can't be copied as %d-sie one.\n", new.size, old.size);
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<old.size; i++){
        new.elements[i] = old.elements[i];
    }
}

// Initialise un vecteur binaire avec un élément unique à 1
BinaryVector initUnitVector(int size, int position) {
    BinaryVector u;
    u.size = size;
    bool* elements = (bool*)malloc(size * sizeof(bool*));
    elements[position] = true;
    u.elements = elements;
    return u;
}

// Fonction pour créer un vecteur
Vector initVector(int size){
    Vector u;
    u.size = size;
    int* elements = (int*)malloc(size * sizeof(int*));
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
    int n = A.rows;
    int m = A.cols;
    BinaryVector v = initBinaryVector(n);
    if(m != u.size){
        printf("[+] binary product error, matrix (%d) and vector (%d) are wrong size.\n", A.cols, n);
        return v;
    }
    for(int i = 0; i < n; i++){
        int sum = 0;
        for(int j = 0; j < m; j++){
            sum += A.elements[i][j] * u.elements[j];
        }
        v.elements[i] = sum;
    }
    return v;
}

// Fonction pour le produit matriciel non modulaire, avec le vecteur à gauche
Vector matrixVectorProduct(BinaryVector u, BinaryMatrix A){
    int n = u.size;
    Vector v = initVector(n);
    if(A.rows != n){
        printf("[+] binary product error, %d-size vector and %d-rows matrix can't be multiplied together.,\n", n, A.rows);
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

// Produit de vecteurs comme étant des polynômes
BinaryVector binaryVectorProduct(BinaryVector u, BinaryVector v){
    int n = u.size;
    BinaryVector w = initBinaryVector(n);
    if(v.size != n){
        printf("[+] binary product error, %d-size vector and %d-vector can't be multiplied together.\n", v.size, n);
        return w;
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            w.elements[(i+j)%n] ^= (u.elements[i]^v.elements[j]);
        }
    }
    return w;
}

// Fonction XOR de deux vecteurs
BinaryVector addVectors(BinaryVector u, BinaryVector v) {
    BinaryVector w = initBinaryVector(u.size);
    if(v.size != u.size){
        printf("[+] binary product error, %d-size vector and %d-vector can't be multiplied together.\n", v.size, u.size);
        return w;
    }
    for (int i = 0; i < u.size; i++) {
        w.elements[i] = u.elements[i] ^ v.elements[i];
    }
    return w;
}

// Fonction pour calculer le poids de Hamming d'un vecteur binaire
int hammingWeight(BinaryVector u){
    int weight = 0;
    for(int i = 0; i < u.size; i++){
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
    for (int i = 0; i < A.rows; i++) {
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

// Fonction pour afficher un vecteur binaire
void printVector(Vector u){
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

// Calcul de l'inverse d'un vecteur binaire modulo (x^n - 1)
BinaryVector invertBinaryVector(BinaryVector v) {
    int n = v.size;
    BinaryVector r0 = copyBinaryVector(v);
    BinaryVector r1 = initUnitVector(n, 0);
    BinaryVector s0 = initUnitVector(n, 0);
    BinaryVector s1 = initUnitVector(n, 1);

    while (true) {
        int r0_degree = 0;
        int r1_degree = 0;
        for (int i = n-1; i >= 0; i--) {
            if (r0.elements[i]) {
                r0_degree = i;
                break;
            }
        }
        for (int i = n-1; i >= 0; i--) {
            if (r1.elements[i]) {
                r1_degree = i;
                break;
            }
        }
        if (r1_degree == 0 && r1.elements[0] == 0) {
            break;
        }
        int shift = r0_degree - r1_degree;
        if (shift < 0) {
            BinaryVector tmp = initBinaryVector(r0.size);
            recopyBinaryVector(tmp, r0);
            recopyBinaryVector(r0, r1);
            recopyBinaryVector(r1, tmp);
            recopyBinaryVector(tmp, s0);
            recopyBinaryVector(s0, s1);
            recopyBinaryVector(s1, tmp);
            shift = -shift;
        }
        BinaryVector r1_shifted = initUnitVector(n, shift);
        r1_shifted = binaryVectorProduct(r1, r1_shifted);
        r0 = addVectors(r0, r1_shifted);

        BinaryVector s1_shifted = initUnitVector(n, shift);
        s1_shifted = binaryVectorProduct(s1, s1_shifted);
        s0 = addVectors(s0, s1_shifted);

        freeBinaryVector(r1_shifted);
        freeBinaryVector(s1_shifted);
    }

    freeBinaryVector(r0);
    freeBinaryVector(s1);

    return s0;
}