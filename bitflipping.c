#include "bitflipping.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "structures.h"
#include "matrix.h"

// Algortihme de comparaison
int max(int a,int b){
    if (a>b) return a;
    return b;
}

// Fonction RotMat
BinaryMatrix rotMat(BinaryVector h0, BinaryVector h1){
    BinaryMatrix M = initBinaryMatrix(h0.size, 2*h0.size);
    if(h0.size != h1.size){
        printf("[+] size error : the two vectors have to be the same size.");
        return M;
    }
    for(int i=0; i<h0.size; i++){
        //first block : h0
        for(int j =0; j<h0.size; j++){
            M.elements[j][i] = h0.elements[(j-i+h0.size) % h0.size]; //important : il faut rester positif !
        }
        //second block : h1
        for(int j =0; j<h1.size; j++){
            M.elements[j][i+h0.size] = h1.elements[(j-i+h0.size) % h1.size];
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
    if(!areBinaryVectorEqual(s, Huv)){
        fprintf(stderr, "[+] Verification failure. End of the program.");
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
    BinaryVector syndrome = copyBinaryVector(s);
    while((hammingWeight(u)!=t || hammingWeight(v)!=t) && hammingWeight(syndrome)!= 0){
        Vector sum = matrixVectorProduct(syndrome, H);
        BinaryVector flp_pos = initBinaryVector(2*n);

        for(int i=0; i<2*n; i++){
            if(sum.elements[i] >= T){flp_pos.elements[i] ^= 1;}
        }
        freeVector(sum);

        //(u|v) XOR flipped_positions
        for(int i=0; i<n;i++){
            u.elements[i] ^= flp_pos.elements[i];
            v.elements[i] ^= flp_pos.elements[n+i];
        }
        // H * flipped_positions ^T
        BinaryVector HprodFLP = binaryMatrixVectorProduct(H, flp_pos);
        addBinaryVectors(syndrome, syndrome, HprodFLP);
        freeBinaryVector(flp_pos);
        freeBinaryVector(HprodFLP);
    }
    BinaryVector output = Verification(s, H, u, v);

    freeBinaryMatrix(H);
    freeBinaryVector(syndrome);
    freeBinaryVector(u);
    freeBinaryVector(v);

    return output;
}