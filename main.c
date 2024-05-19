#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "binary_inverse.h"
#include "prange.h"
#include "matrix.h"
#include "bitflipping.h"

int main() {
    int n = 8;
    BinaryVector h0 = initUnitVector(n, 1);
    printBinaryVector(h0);
    BinaryVector h0Inv = invertBinaryVector(h0);
    printBinaryVector(h0Inv);

    return 0;
}

/** test for bitflipping
* BinaryVector h0 = initBinaryVector(n);
    h0.elements[1] = true;
    h0.elements[3] = true;
    h0.elements[4] = true;
    h0.elements[6] = true;
    BinaryVector h1 = initBinaryVector(n);
    h1.elements[0] = true;
    h1.elements[1] = true;
    h1.elements[5] = true;
    h1.elements[7] = true;

    printBinaryVector(h0);
    printf("\n");
    printBinaryVector(h1);

    BinaryVector y = initBinaryVector(n);
    y.elements[-1] = true;

    BinaryVector e = BitFlipping(h0, h1, y, 3, 1);

    printBinaryVector(e);
    freeBinaryVector(h0);
    freeBinaryVector(h1);
    freeBinaryVector(y);
    freeBinaryVector(e);
*/