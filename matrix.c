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
        for(int j = 0; j < cols; j++){
            elements[i][j] = 0;
        }
    }
    A.elements = elements;
    return A;
}

// Fonnction pour créer un vecteur binaire
BinaryVector initBinaryVector(int size){
    BinaryVector u;
    u.size = size;
    bool* elements = (bool*)malloc(size * sizeof(bool*));
    for (int i = 0; i < size; i++) {
        elements[i] = 0;
    }
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
    for (int i = 0; i < size; i++) {
        elements[i] = 0;
    }
    u.elements = elements;
    return u;
}

// Fonction pour créer une matrice binaire aléatoire 
BinaryMatrix randomBinaryMatrix(int rows, int cols){
    BinaryMatrix A = initBinaryMatrix(rows,cols);
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            A.elements[i][j] = rand() % 2;
        }
    }
    return A;
}

// Fonction pour créer un vecteur binaire aléatoire de taille n et de poids t
BinaryVector randomBinaryVectorHW(int n, int t){
    BinaryVector r = initBinaryVector(n);
    // Initialiser un tableau d'index
    int *indices = (int*)malloc(r.size * sizeof(int));
    for (int i = 0; i < r.size; i++) {
        indices[i] = i;
    }

    // Mélanger le tableau d'index avec l'algorithme de Fisher-Yates
    for (int i = r.size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    // Placer t "1" dans les premières t positions du tableau mélangé
    for (int i = 0; i < t; i++) {
        r.elements[indices[i]] = 1;
    }
    free(indices);
    return r;
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
        bool sum = 0;
        for(int j = 0; j < m; j++){
            sum ^= (A.elements[i][j] && u.elements[j]);
        }
        v.elements[i] = sum;
    }
    return v;
}

// Fonction pour le produit matriciel non modulaire, avec le vecteur à gauche
Vector matrixVectorProduct(BinaryVector u, BinaryMatrix A){
    int n = u.size;
    Vector v = initVector(2*n);
    if(A.rows != n){
        printf("[+] binary product error, %d-size vector and %d-rows matrix can't be multiplied together.,\n", n, A.rows);
        return v;
    }
    for(int j = 0; j < 2*n; j++){
        for(int i = 0; i < n; i++){
            if(A.elements[i][j] && u.elements[i]) v.elements[j] += 1;
        }
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
        if(v.elements[i]){
            for(int j=0; j<n; j++){
                w.elements[(i+j)%n] ^= u.elements[j];
            }
        }
    }
    return w;
}

// Fonction XOR de deux vecteurs
void addBinaryVectors(BinaryVector sum, BinaryVector u, BinaryVector v) {
    if(v.size != u.size){
        printf("[+] binary sum error, %d-size vector and %d-vector can't be added together.\n", v.size, u.size);
    }
    for (int i = 0; i < u.size; i++) {
        sum.elements[i] = u.elements[i] ^ v.elements[i];
    }
}

//Multiplication par x**shift modulo x**n+1
BinaryVector shiftVector(BinaryVector u, int shift){
    BinaryVector v = initBinaryVector(u.size);
    for(int i=0; i<v.size; i++){
        v.elements[(i+shift)%v.size] = u.elements[i];
    }
    return v;
}

int binaryVectorDegree(BinaryVector u){
    int i = u.size - 1;
    if(hammingWeight(u)==0) return 0;
    while(!u.elements[i]){i--;}
    return i;
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

// Fonction pour comparer deux vecteurs binaires
bool areBinaryVectorEqual(BinaryVector u, BinaryVector v){
    if(u.size != v.size) return false;
    for(int i = 0; i < u.size; i++){
        if(u.elements[i] != v.elements[i]) return false;
    }
    return true;
}

// Calcul de l'inverse d'un vecteur binaire modulo (x^n - 1)
BinaryVector invertBinaryVector(BinaryVector vector) {
    int n = vector.size;
    BinaryVector r0 = initBinaryVector(vector.size);// =x^n-1
    BinaryVector r1 = copyBinaryVector(vector);
    BinaryVector r2 = initBinaryVector(n);
    BinaryVector q = initBinaryVector(n);

    //Division euclidienne de x^n+1 par u
    int r1_degree = binaryVectorDegree(r1);
    int r2_degree = n;
    int q_degree = r2_degree - r1_degree;
    while(r2_degree >= r1_degree){
        q.elements[q_degree] ^= 1;
        BinaryVector shift_r1 = shiftVector(r1, q_degree);
        addBinaryVectors(r2, r2, shift_r1);
        freeBinaryVector(shift_r1);
        r2_degree = binaryVectorDegree(r2);
        q_degree = r2_degree - r1_degree;
    }
    // Initialisation de l'AEE après le tour1
    BinaryVector u0 = initBinaryVector(n); //pour le premier tour, u0 = u1 = 0
    BinaryVector u1 = initUnitVector(n, 0); // u1 = u0-qu1 = u0
    BinaryVector v0 = initUnitVector(n, 0); //directement v0<-v1
    BinaryVector v1 = binaryVectorProduct(q,v0); //v1 = v0-qv1 or v0 =v1 juste au dessus
    freeBinaryVector(q);

    recopyBinaryVector(r0, r1);
    recopyBinaryVector(r1, r2);
    // AEE tourne tant que r1!=0
    while(hammingWeight(r2)!=0){
        recopyBinaryVector(r2, r0);
        r1_degree = binaryVectorDegree(r1);
        q = initBinaryVector(n);
        r2_degree = binaryVectorDegree(r2);
        q_degree = r2_degree - r1_degree;
        //Division euclidienne
        while(r2_degree >= r1_degree){
            if(r2_degree==0){r1_degree+=1;}// pour le cas deg(r2)=deg(r1)=0, ça tourne à l'infini
            q.elements[q_degree] ^= 1;
            BinaryVector s1 = shiftVector(r1, q_degree);
            addBinaryVectors(r2, r2, s1);
            freeBinaryVector(s1);
            r2_degree = binaryVectorDegree(r2);
            q_degree = r2_degree - r1_degree;
        }
        BinaryVector u1_bis = copyBinaryVector(u1);
        BinaryVector qu1 = binaryVectorProduct(q,u1);
        addBinaryVectors(u1, u0, qu1); //u1 <- u0-qu1
        recopyBinaryVector(u0, u1_bis);
        freeBinaryVector(u1_bis);
        freeBinaryVector(qu1);

        BinaryVector v1_bis = copyBinaryVector(v1);
        BinaryVector qv1 = binaryVectorProduct(q,v1);
        addBinaryVectors(v1, v0, qv1); //v1 <- v0-qv1
        recopyBinaryVector(v0, v1_bis);// v0<-v1
        freeBinaryVector(v1_bis);
        freeBinaryVector(qv1);

        recopyBinaryVector(r0, r1);
        recopyBinaryVector(r1, r2);
        freeBinaryVector(q);
    }
    freeBinaryVector(u0);
    freeBinaryVector(u1);
    freeBinaryVector(v1);
    freeBinaryVector(r0);
    freeBinaryVector(r1);
    freeBinaryVector(r2);
    return v0;
}