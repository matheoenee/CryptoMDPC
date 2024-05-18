#include "bitflipping.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "structures.h"
#include "matrix.h"

// Algortihme de comparaison d'odre 1
int max(int a,int b){
    if (a>b) return a;
    return b;
}

// Fonction RotMat
BinaryMatrix rotMat(BinaryVector h0, BinaryVector h1){
    BinaryMatrix M;
    M.rows = max(h0.size, h1.size);
    M.cols = h0.size + h1.size;
    M.elements = (bool **)malloc(M.rows * sizeof(bool *));

    for(int i=0; i<M.rows; i++){
        M.elements[i] = (bool *)malloc(M.cols * sizeof(bool));
        //first block : h0
        for(int j =0; j<h0.size; j++){
            M.elements[i][j] = h0.elements[j-i % h0.size];
        }
        //second block : h1
        for(int j =0; j<h1.size; j++){
            M.elements[i][j+h0.size] = h0.elements[j-i % h1.size];
        }
    }
    return M;
}

// Dernière vérification de l'algorithme BitFlip
BinaryVector Verification(BinaryVector s, BinaryMatrix H, BinaryVector u, BinaryVector v){
    BinaryVector uv = initBinaryVector(2*s.size);
    for(int i=0; i<s.size; i++){
        uv.elements[i] = u.elements[i];
        uv.elements[i + s.size] = v.elements[i];
    }
    BinaryVector Huv = binaryMatrixVectorProduct(H, uv);
    BinaryVector verification = initBinaryVector(s.size);
    int k = 0;
    do{
        verification.elements[k] = s.elements[k] ^ Huv.elements[k];
        k+=1;
    } while ((verification.elements[k-1] == 0) & (k < verification.size));
    freeBinaryVector(verification);
    freeBinaryVector(Huv);
    if(k == verification.size){
        fprintf(stderr, "algorithm fail");
        exit(EXIT_FAILURE);
    }
    return uv;
}

// Algorithme BitFlip
BinaryVector BitFlipping(BinaryVector h0, BinaryVector h1, BinaryVector s, int T, int t){
    int n = h0.size;
    BinaryMatrix H = rotMat(h0,h1);
    BinaryVector u = initBinaryVector(n);
    BinaryVector v = initBinaryVector(n);
    BinaryVector syndrome = s;
    while((hammingWeight(u)!=t || hammingWeight(v)!=t) && hammingWeight(syndrome)!= 0){
        Vector sum = matrixVectorProduct(syndrome, H);

        BinaryVector flp_pos = initBinaryVector(2*n);
        for(int i=0; i<H.cols; i++){
            if(sum.elements[i] >= T){
                flp_pos.elements[i] = !flp_pos.elements[i];
            }
        }
        //(u|v) XOR flipped_positions
        for(int i=0; i<n;i++){
            u.elements[i] = u.elements[i] ^ flp_pos.elements[i];
            v.elements[i] = v.elements[i] ^ flp_pos.elements[n+i];
        }
        // H * flipped_positions ^T
        BinaryVector HprodFLP = binaryMatrixVectorProduct(H, flp_pos);
        for(int i = 0; i < syndrome.size; i++){
            syndrome.elements[i] = syndrome.elements[i] ^ HprodFLP.elements[i];
        }
    }
    BinaryVector Return = Verification(s, H, u, v);
    return Return;
}