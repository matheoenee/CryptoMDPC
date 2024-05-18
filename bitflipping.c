#include "bitflipping.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "structures.h"

//comparative algorithm, order 1
int max(int a,int b){
    if (a>b){return a;}
    return b;
}

//naive algorithm, order n
int weight(Vector u){
    int w = 0;
    for(int i=0; i<u.size; i++){
        if(u.elements[i]){w+=1;}
    }
    return w;
}

void freeVectorInts(Vector vector) {
    free(vector.elemInts);
}
void freeVector(Vector vector) {
    free(vector.elements);
}

void freeMatrix(Matrix matrix) {
    int rows = matrix.rows;
    for (int i = 0; i < rows; i++) {
        free(matrix.elements[i]);
    }
    free(matrix.elements);
}

//logical xor : order 1
bool XOR(bool a, bool b) {
    return (a && !b) || (!a && b);
}

//create vector 0 in F_2^n
Vector initVect0(int n){
    Vector u;
    u.size = n;
    u.elements = (bool *)malloc(u.size * sizeof(bool));
    for(int i=0; i<u.size; i++){
        u.elements[i] = 0;
    }
    return u;
}


//order : 2n**2
Matrix rotMat(Vector h0, Vector h1){
    Matrix matrix;
    matrix.rows = max(h0.size, h1.size);
    matrix.cols = h0.size + h1.size;
    matrix.elements = (bool **)malloc(matrix.rows * sizeof(bool *));

    for(int i=0; i<matrix.rows; i++){
        matrix.elements[i] = (bool *)malloc(matrix.cols * sizeof(bool));
        //first block : h0
        for(int j =0; j<h0.size; j++){
            matrix.elements[i][j] = h0.elements[j-i % h0.size];
        }
        //second block : h1
        for(int j =0; j<h1.size; j++){
            matrix.elements[i][j+h0.size] = h0.elements[j-i % h1.size];
        }
    }
    return matrix;
}

Vector ProdMatVector(Matrix M, Vector u){
    if(M.cols!=u.size){
        printf(stderr, "sizes error : impossible to multiply matrix with %d columns and a vector with %d rows", M.rows, u.size);
        exit(EXIT_FAILURE);
    }
    Vector s;
    s.size = M.rows;
    s.elements = (bool *)malloc(s.size * sizeof(bool));
    bool b;
    for(int i=0; i<s.size; i++){
        b = False;
        for(int j=0; j<u.size; j++){
            b = XOR(b, XOR(M.elements[i][j], u.elements[j]));
        }
        s.elements[i] = b;
    }
    return s;
}


//naive product syndrome x H in BitFlipping, order : n**3
Vector ProdNoMod(Vector u, Matrix M){
    if(M.rows!=u.size){
        printf(stderr, "sizes error : impossible to multiply matrix with %d columns and a vector with %d rows", M.rows, u.size);
        exit(EXIT_FAILURE);
    }
    Vector s;
    s.size = M.cols;
    s.elemInts = (int *)malloc(s.size * sizeof(int));

    int k;
    for(int i=0; i<s.size; i++){
        k = 0;
        for(int j=0; j<u.size; j++){
            if(M.elements[j][i] && u.elements[j]){k += 1;}
        }
        s.elemInts[i] = k;
    }
    return s;
}

//the last check of BitFlipping algorithm
Vector Verification(Vector s, Matrix H, Vector u, Vector v){
    Vector uv;
    uv.size = 2*s.size;
    uv.elements = (bool *)malloc(uv.size * sizeof(bool));
    for(int i=0; i<s.size; i++){
        uv.elements[i] = u.elements[i];
        uv.elements[s.size + i] = v.elements[i];
    }
    Matrix Huv = ProdMatVector(H, uv);
    Vector verification;
    verification.size = s.size;
    verification.elements = (bool *) malloc(verification.size * sizeof(bool));
    int k = 0;
    do{
        verification[k] = XOR(s.elements[k], Huv.elements[k]);
        k+=1;
    } while (verification[k-1]==0 & k<verification.size);
    freeVector(verification);
    freeMatrix(Huv);
    if(k == verification.size){
        printf(stderr, "algorithm fail");
        exit(EXIT_FAILURE);
    }
    return uv;
}

Vector* BitFlipping(Vector h0, Vector h1, Vector s, int T, int t){
    int n = h0.size;
    Matrix H = rotMat(h0,h1);
    Vector u = initVect0(n);
    Vector v = initVect0(n);
    Vector syndrome = s;
    while((weight(u)!=t || weight(v)!=t) && weight(syndrome)!= 0){
        Vector sum = ProdNoMod(syndrome, H);

        Vector flp_pos = initVect0(2*n);
        for(int i=0; i<H.cols; i++){
            if(sum.elemInts[i] >= T){
                flp_pos.elements[i] = !flp_pos.elements[i];
            }
        }
        //(u|v) XOR flipped_positions
        for(int i=0; i<n;i++){
            u.elements[i] = XOR(u.elements[i], flp_pos.elements[i]);
            v.elements[i] = XOR(v.elements[i], flp_pos.elements[n+i]);
        }
        // H * flipped_positions ^T
        Vector HprodFLP = ProdMatVector(H, flp_pos);
        for(int i=0; i<syndrome.size; i++){
            syndrome.elements[i] = XOR(syndrome.elements[i],HprodFLP.elements[i]);
        }
    }
    Vector Return = Verification(s, H, u, v);
    return Return;
}