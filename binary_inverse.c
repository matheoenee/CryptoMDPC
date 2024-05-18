#include "binary_inverse.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "matrix.h"
#include "structures.h"

// Fonction pour calculer l'inverse d'une matrice binaire
BinaryMatrix binaryMatrixInverse(BinaryMatrix A) {
    int i, j, k;
    int n = A.rows;

    // Tester si la matrice est bien carré, sinon renvoyer une matrice vide
    BinaryMatrix I = initBinaryMatrix(n,n);
    if (A.cols != n){
        printf("[+] binary inversion impossible.\n");
        return I;
    }

    // Allocation de la matrice augmentée
    BinaryMatrix B = initBinaryMatrix(n,2*n);
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++){
            B.elements[i][j] = A.elements[i][j];
        }
        for(j = n; j < 2 * n; j++) {
            B.elements[i][j] = (i == (j - n)) ? true : false;
        }
    }

    // Application de l'élimination de Gauss-Jordan
    for(i = 0; i < n; i++) {
        if(B.elements[i][i] == 0) {
            // Trouver une ligne en dessous de i avec un 1 dans la colonne i et échanger
            for(j = i + 1; j < n; j++) {
                if(B.elements[j][i]) {
                    bool* temp = B.elements[i];
                    B.elements[i] = B.elements[j];
                    B.elements[j] = temp;
                    break;
                }
            }
            if(j == n){
                printf("[+] binary inversion impossible.\n");
                return I; // La matrice n'est pas inversible
            } 
        }
        // Chercher parmi les autres lignes celle qui ont un 1 dans la colonne
        for(j = 0; j < n; j++) {
            if(i != j && B.elements[j][i]) {
                for(k = 0; k < 2 * n; k++) {
                    B.elements[j][k] ^= B.elements[i][k]; // XOR avec la ligne i
                }
            }
        }
    }

    // Extraction de la matrice inverse
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            I.elements[i][j] = B.elements[i][j + n];
        }
    }

    // Libération de la mémoire de la matrice augmentée
    freeBinaryMatrix(B);
    return I;
}
