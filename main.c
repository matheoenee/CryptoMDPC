#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "binary_inverse.h"
#include "prange.h"
#include "matrix.h"

int main() {
    int n = 8;
    int k = 4;
    
    BinaryMatrix A = randomBinaryMatrix(n-k, k);
    printBinaryMatrix(A);

    printf("\n");

    BinaryMatrix I = binaryMatrixInverse(A);
    printBinaryMatrix(I);
    if(isMatrixEmpty(I)){
        printf("empty");
    }

    return 0;
}