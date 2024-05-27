#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include "structures.h"

// Fonction pour créer une matrice binaire
BinaryMatrix initBinaryMatrix(int rows, int cols);

// Fonction pour créer une liste de vecteurs binaires
BinaryVectors initBinaryVectors(int size, int length);

// Fonction pour créer un vecteur binaire
BinaryVector initBinaryVector(int n);

// Pour entrer les valeurs d'un vecteur dans un autre
BinaryVector copyBinaryVector(BinaryVector u);

// Pour entrer les valeurs d'un vecteur dans un autre (déjà existant)
void recopyBinaryVector(BinaryVector new, BinaryVector old);

// Initialise un vecteur binaire avec un élément unique à 1
BinaryVector initUnitVector(int size, int position);

// Fonnction pour créer un vecteur
Vector initVector(int n);

// Fonction pour créer une matrice binaire aléatoire 
BinaryMatrix randomBinaryMatrix(int rows, int cols);

// Fonction pour créer un vecteur binaire aléatoire de taille n et de poids t
BinaryVector randomBinaryVectorHW(int n, int t);

// Fonction pour le produit matriciel d'une matrice binaire et d'un vecteur binaire (A.u)
BinaryVector binaryMatrixVectorProduct(BinaryMatrix A, BinaryVector u);

// Fonction pour le produit matriciel non modulaire (naive product syndrome x H in BitFlipping, order : n**3)
Vector matrixVectorProduct(BinaryVector u, BinaryMatrix A);

// Produit de vecteurs comme étant des polynômes
BinaryVector binaryVectorProduct(BinaryVector u, BinaryVector v);

// Fonction XOR de deux vecteurs
void addBinaryVectors(BinaryVector sum, BinaryVector u, BinaryVector v);

//Multiplication par x**shift modulo x**n+1
BinaryVector shiftVector(BinaryVector u, int shift);

// Fonction pour calculer le poids de Hamming d'un vecteur binaire
int hammingWeight(BinaryVector u);

// Fonction pour libérer la mémoire d'un vecteur binaire
void freeBinaryVector(BinaryVector u);

// Fonction pour libérer la mémoire d'un vecteur
void freeVector(Vector u);

// Fonction pour libérer la mémoire d'une matrice binaire
void freeBinaryMatrix(BinaryMatrix A);

// Fonction pour libérer la mémoire d'une liste de vecteurs binaires
void freeBinaryVectors(BinaryVectors V);

// Fonction pour afficher une matrice
void printBinaryMatrix(BinaryMatrix A);

// Fonction pour afficher un vecteur binaire
void printBinaryVector(BinaryVector u);

// Fonction pour afficher un vecteur binaire
void printVector(Vector u);

// Fonction qui renvoie si une matrice est vide ou non
bool isMatrixEmpty(BinaryMatrix A);

// Fonction pour comparer deux vecteurs binaires
bool areBinaryVectorEqual(BinaryVector u, BinaryVector v);

// Calcul de l'inverse d'un vecteur binaire modulo (x^n - 1)
BinaryVector invertBinaryVector(BinaryVector u);

#endif // MATRIX_H
