#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Fonction pour allouer une matrice carrée de taille n
bool** allocateMatrix(int n) {
    bool** matrix = (bool**)malloc(n * sizeof(bool*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (bool*)malloc(n * sizeof(bool));
    }
    return matrix;
}

// Fonction pour libérer la mémoire d'une matrice carrée de taille n
void freeMatrix(bool** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Fonction pour afficher une matrice carrée de taille n
void printMatrix(bool** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Fonction pour trouver l'inverse binaire d'une matrice carrée de taille n
bool** binary_inverse(bool** A, int n) {
    int i, j, k;

    // Allocation de la matrice augmentée
    bool** augmented = (bool**)malloc(n * sizeof(bool*));
    for (i = 0; i < n; i++) {
        augmented[i] = (bool*)malloc(2 * n * sizeof(bool));
        for (j = 0; j < n; j++) {
            augmented[i][j] = A[i][j];
        }
        for (j = n; j < 2 * n; j++) {
            augmented[i][j] = (i == (j - n)) ? true : false;
        }
    }

    // Application de l'élimination de Gauss-Jordan
    for (i = 0; i < n; i++) {
        if (!augmented[i][i]) {
            // Trouver une ligne en dessous de i avec un 1 dans la colonne i et échanger
            for (j = i + 1; j < n; j++) {
                if (augmented[j][i]) {
                    bool* temp = augmented[i];
                    augmented[i] = augmented[j];
                    augmented[j] = temp;
                    break;
                }
            }
        }
        // Chercher parmi les autres lignes celle qui ont un 1 dans la colonne
        for (j = 0; j < n; j++) {
            if (i != j && augmented[j][i]) {
                for (k = 0; k < 2 * n; k++) {
                    augmented[j][k] ^= augmented[i][k]; // XOR avec la ligne i
                }
            }
        }
    }

    // Extraction de la matrice inverse
    bool** inverse = allocateMatrix(n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            inverse[i][j] = augmented[i][j + n];
        }
    }

    // Libération de la mémoire de la matrice augmentée
    for (i = 0; i < n; i++) {
        free(augmented[i]);
    }
    free(augmented);

    return inverse;
}

int main() {
    int n = 3;
    bool** A = allocateMatrix(n);

    // Exemple de matrice binaire
    A[0][0] = 1; A[0][1] = 0; A[0][2] = 1;
    A[1][0] = 0; A[1][1] = 1; A[1][2] = 1;
    A[2][0] = 1; A[2][1] = 1; A[2][2] = 0;

    printf("Matrice originale:\n");
    printMatrix(A, n);

    bool** inverse = binary_inverse(A, n);

    if (inverse != NULL) {
        printf("Matrice inverse:\n");
        printMatrix(inverse, n);
        freeMatrix(inverse, n);
    }

    freeMatrix(A, n);
    return 0;
}
