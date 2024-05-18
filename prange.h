#ifndef PRANGE_H
#define PRANGE_H

#include <stdbool.h>

// Fonction pour choisir un ensemble d'information aléatoire
int* randomInformationSet(int n, int k);

// Fonction qui retourne sous-matrice de taille (n-k) de A dont les colonnes sont indexées par I
bool** indexedMatrix(bool** A, bool* I, int n, int k);

// Algorithme de Prange
bool* Prange(bool** H, bool* s, int t, int n, int k);

#endif // PRANGE_H
