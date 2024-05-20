#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "binary_inverse.h"
#include "prange.h"
#include "matrix.h"
#include "bitflipping.h"

int main() {
    srand(time(NULL));
    int n = 200;
    int k = 100;
    int t = 10;

    BinaryMatrix H = randomBinaryMatrix(n-k, n);
    /*BinaryMatrix H = initBinaryMatrix(n-k, n);
    H.elements[0][0] = 1; H.elements[0][1] = 0; H.elements[0][2] = 1; H.elements[0][3] = 0; H.elements[0][4] = 1; H.elements[0][5] = 0; H.elements[0][6] = 0;
    H.elements[1][0] = 1; H.elements[1][1] = 0; H.elements[1][2] = 1; H.elements[1][3] = 1; H.elements[1][4] = 0; H.elements[1][5] = 0; H.elements[1][6] = 1;*/


    BinaryVector e = randomBinaryVectorHW(n,t);
    printf("e : \n");
    printBinaryVector(e);
    printf("\n");
    printf("w(e) = %d\n",hammingWeight(e));

    BinaryVector s = binaryMatrixVectorProduct(H,e);
    printf("s : \n");
    printBinaryVector(s);
    printf("\n");

    BinaryVector x = Prange(H,s,t,n,k);
    printf("x : \n");
    printBinaryVector(x);
    printf("\n");

    BinaryVector ss = binaryMatrixVectorProduct(H, x);
    printf("ss : \n");
    printBinaryVector(ss);
    printf("\n");

    freeBinaryMatrix(H);
    freeBinaryVector(e);
    freeBinaryVector(s);
    freeBinaryVector(x);
    freeBinaryVector(ss);

    return 0;
}

/*
int n = 8;
    BinaryVector h0 = initUnitVector(n, 1);
    printBinaryVector(h0);
    BinaryVector h0Inv = invertBinaryVector(h0);
    printBinaryVector(h0Inv);

    return 0;
*/

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