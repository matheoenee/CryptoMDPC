#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include "structures.h"

// Fonction pour créer une matrice binaire
BinaryMatrix initBinaryMatrix(int rows, int cols);

// Fonnction pour créer un vecteur binaire
BinaryVector initBinaryVector(int n);

// Fonnction pour créer un vecteur
Vector initVector(int n);

// Fonction pour créer une matrice binaire aléatoire 
BinaryMatrix randomBinaryMatrix(int rows, int cols);

// Fonction pour le produit matriciel d'une matrice binaire et d'un vecteur binaire (A.u)
BinaryVector binaryMatrixVectorProduct(BinaryMatrix A, BinaryVector u);

// Fonction pour le produit matriciel non modulaire (naive product syndrome x H in BitFlipping, order : n**3)
Vector matrixVectorProduct(BinaryVector u, BinaryMatrix A);

// Fonction pour calculer le poids de Hamming d'un vecteur binaire
int hammingWeight(BinaryVector u);

// Fonction pour libérer la mémoire d'un vecteur binaire
void freeBinaryVector(BinaryVector u);

// Fonction pour libérer la mémoire d'un vecteur
void freeVector(Vector u);

// Fonction pour libérer la mémoire d'une matrice binaire
void freeBinaryMatrix(BinaryMatrix A);

// Fonction pour afficher une matrice
void printBinaryMatrix(BinaryMatrix A);

// Fonction pour afficher un vecteur binaire
void printBinaryVector(BinaryVector u);

// Fonction qui renvoie si une matrice est vide ou non
bool isMatrixEmpty(BinaryMatrix A);

#endif // MATRIX_H
