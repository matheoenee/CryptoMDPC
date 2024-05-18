#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "binary_inverse.h"
#include "prange.h"
#include "matrix.h"

int main() {
    int n = 8;
    int k = 4;
    bool** H = randomMatrix(n,k);
    printMatrix(H,n,k);

    bool* e = allocateVector(n);
    e[0] = 0; e[1] = 0; e[2] = 0; e[3] = 0;  e[4] = 1; e[5] = 0; e[6] = 0; e[7] = 0;
    printVector(e,n);

    bool* s = matrixProduct(n,e,H);
    print(s,n-k);

    return 0;
}