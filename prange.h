#ifndef PRANGE_H
#define PRANGE_H

#include <stdbool.h>
#include "structures.h"

// Fonction pour choisir un ensemble d'information aléatoire
Vector randomInformationSet(int n, int k);

// Fonction qui retourne sous-matrice de taille (n-k) de A dont les colonnes sont indexées par I
BinaryMatrix indexedMatrix(BinaryMatrix A, Vector I, int n, int k);

// Fonction qui retourne x de longeur n à partir de x de longueur n-k et I
BinaryVector resizeBinaryVector(BinaryVector x, Vector I, int n);

// Algorithme de Prange
BinaryVector Prange(BinaryMatrix H, BinaryVector s, int t, int n, int k);

#endif // PRANGE_H
