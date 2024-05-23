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
            M.elements[i][j] = h0.elements[(j-i+h0.size) % h0.size]; //important : il faut rester positif !
        }
        //second block : h1
        for(int j =0; j<h1.size; j++){
            M.elements[i][j+h0.size] = h1.elements[(j-i+h0.size) % h1.size];
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
    freeBinaryVector(Huv);
    if(k == verification.size){
        fprintf(stderr, "algorithm fail");
        exit(EXIT_FAILURE);
    }
    freeBinaryVector(verification);
    return uv;
}

// Algorithme BitFlip
BinaryVector BitFlipping(BinaryVector h0, BinaryVector h1, BinaryVector s, int T, int t){
    int n = h0.size;
    BinaryMatrix H = rotMat(h0,h1);
    BinaryVector u = initBinaryVector(n);
    BinaryVector v = initBinaryVector(n);
    BinaryVector syndrome = copyBinaryVector(s);
    int k = 0;
    while((hammingWeight(u)!=t || hammingWeight(v)!=t) && hammingWeight(syndrome)!= 0){
        printf("loop n°%d\n",k);
        Vector sum = matrixVectorProduct(syndrome, H);
        printf("sum = ");
        printVector(sum);
        BinaryVector flp_pos = initBinaryVector(2*n);
        for(int i=0; i<2*n; i++){
            if(sum.elements[i] >= T){flp_pos.elements[i] ^= 1;}
        }
        freeVector(sum);
        printf("flp_pos = ");
        printBinaryVector(flp_pos);

        //(u|v) XOR flipped_positions
        for(int i=0; i<n;i++){
            u.elements[i] ^= flp_pos.elements[i];
            v.elements[i] ^= flp_pos.elements[n+i];
        }
        printf("u = ");
        printBinaryVector(u);
        printf("v = ");
        printBinaryVector(v);
        // H * flipped_positions ^T
        BinaryVector HprodFLP = binaryMatrixVectorProduct(H, flp_pos);
        addBinaryVectors(syndrome, syndrome, HprodFLP);
        freeBinaryVector(flp_pos);
        freeBinaryVector(HprodFLP);
        k += 1;
    }
    BinaryVector Return = Verification(s, H, u, v);
    freeBinaryMatrix(H);
    freeBinaryVector(syndrome);

    return Return;
}