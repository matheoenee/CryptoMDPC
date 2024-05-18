#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>

// Fonction pour allouer une matrice carrée de taille (n-k)*n
bool** allocateMatrix(int n, int k);

// Fonction pour libérer la mémoire d'une matrice carrée de n lignes
void freeMatrix(bool** matrix, int n);

// Fonction pour afficher une matrice carrée de taille (n-k)*n
void printMatrix(bool** matrix, int n, int k);

// Fonction pour allouer un vecteur de taille n
bool* allocateVector(int n);

// Fonction pour afficher un vecteur de taille n
void printVector(bool* vector, int n);

// Fonction pour créer une matrice binaire aléatoire de taille (n-k)*n 
bool** randomMatrix(int n, int k);

// Fonction pour le produit matriciel d'une matrice de taille n par un vecteur de taille n
bool* matrixProduct(int n, bool* x, bool** A);

// Fonction pour calculer le poids de Hamming d'un vecteur de taille n
int hammingWeight(bool* x, int n);

#endif // MATRIX_H
