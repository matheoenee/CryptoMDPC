#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "binary_inverse.h"
#include "prange.h"
#include "matrix.h"

int main() {
    int n = 3;
    bool* v = allocateVector(n);

    // Exemple de matrice binaire
    v[0] = 1; v[1] = 0; v[2] = 1;

    printf("Vecteur originale:\n");
    printVector(v, n);

    int weight = hammingWeight(v,n);
    printf("Poids : %d",weight);

    free(v);
    return 0;
}