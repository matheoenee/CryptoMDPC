#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>
#include <openssl/evp.h>

#include "structures.h"
#include "matrix.h"
#include "bitflipping.h"
#include "mdpc.h"


//Fonction qui hash un vecteur binaire
void hashBinaryVector(unsigned char *outputBuffer , const BinaryVector *vec) {
    if (outputBuffer == NULL) {
        perror("Unable to allocate memory for hash output");
        exit(EXIT_FAILURE);
    }

    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) {
        perror("EVP_MD_CTX_new failed");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL)) {
        perror("EVP_DigestInit_ex failed");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestUpdate(mdctx, vec->elements, vec->size * sizeof(bool))) {
        perror("EVP_DigestUpdate failed");
        exit(EXIT_FAILURE);
    }

    unsigned int length = 0;
    if (1 != EVP_DigestFinal_ex(mdctx, outputBuffer, &length)) {
        perror("EVP_DigestFinal_ex failed");
        exit(EXIT_FAILURE);
    }

    EVP_MD_CTX_free(mdctx);
}

// Fonction qui affiche un hash
void printHash(unsigned char *hash) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

// Fonction qui détermine l'égalité entre deux hashs
bool areHashsIdentical(unsigned char *hash1, unsigned char *hash2){
    for(int i=0; i<SHA256_DIGEST_LENGTH; i++){
        if(hash1[i]!=hash2[i]){ return false;}
    }
    //return memcmp(hash1, hash2, length) == 0;
    return true;
}

//retourne h, h0, h1
void gen_h(BinaryVectors data, int size, int weight, bool needRandom){
    if(needRandom) srand(time(NULL));

    BinaryVector h0 = randomBinaryVectorHW(size, weight);
    BinaryVector h1 = randomBinaryVectorHW(size, weight);
    BinaryVector invh0 = invertBinaryVector(h0);
    BinaryVector h = binaryVectorProduct(h1, invh0);
    freeBinaryVector(invh0);

    recopyBinaryVector(data.vectors[0], h);
    recopyBinaryVector(data.vectors[1], h0);
    recopyBinaryVector(data.vectors[2], h1);
}

// Retourne c1, e0, e1
void gen_e(BinaryVectors data, int size, int t, BinaryVector h, bool needRandom){
    if(needRandom) srand(time(NULL));
    BinaryVector e = randomBinaryVectorHW(2*size, t); // e = (e0|e1)
    BinaryVector e0 = initBinaryVector(size);
    BinaryVector e1 = initBinaryVector(size);
    for(int i=0; i<size; i++){
        e0.elements[i] = e.elements[i];
        e1.elements[i] = e.elements[i+size];
    }
    BinaryVector c1 = binaryVectorProduct(h,e1);
    addBinaryVectors(c1, e0, c1); //c1 = e0 + he1

    recopyBinaryVector(data.vectors[0], c1);// data[0] = c1
    recopyBinaryVector(data.vectors[1], e0);// data[1] = e0
    recopyBinaryVector(data.vectors[2], e1);// data[2] = e1

    freeBinaryVector(c1);
    freeBinaryVector(e0);
    freeBinaryVector(e1);
}


// Fonction qui, à partir des données obtenues précédement par alice, lui permet d'obtenir le secret partagé avec bob
void aliceComputeSecret(unsigned char* hash, BinaryVector h0, BinaryVector h1, BinaryVector c1, int T, int w){
    BinaryVector s = binaryVectorProduct(h0, c1);
    BinaryVector e = BitFlipping(h0, h1, s, T, w);
    hashBinaryVector(hash, &e);
    freeBinaryVector(s);
    freeBinaryVector(e);
}

void bobComputeSecret(unsigned char* hash, BinaryVector e0, BinaryVector e1){
    BinaryVector e = initBinaryVector(e0.size * 2);
    for(int i=0; i<e0.size ; i++){
        e.elements[i] = e0.elements[i];
        e.elements[i+e0.size] = e1.elements[i];
    }
    hashBinaryVector(hash,&e);
    freeBinaryVector(e);
}