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


/**
* todo list:
 * randomVect(weight, size) -> usage : gen h0 h1, e0,e1
 * GenH(n) -> return h, first step of protocol
 * genC(t) -> return c1 second step
 * AliceSecret(c1) -> compute s, and BitFlpg(h0,h1,s,t,w) and hash result
 * BobSecret(e0,e1) -> hash(e0,e1)
*/

unsigned char* hashBinaryVector(const BinaryVector *vec) {
    unsigned char *outputBuffer = (unsigned char *)malloc(SHA256_DIGEST_LENGTH);
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

    return outputBuffer;
}

void printHash(unsigned char *hash) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

bool areHashsIdentical(unsigned char *hash1, unsigned char *hash2, size_t length){
    return memcmp(hash1, hash2, length) == 0;
}

//retourne h, h0, h1
BinaryVector* gen_h(int size, int weight, bool needRandom){
    printf("alice starts her protocol\n");
    if(needRandom) srand(time(NULL));
    BinaryVector h0 = randomBinaryVectorHW(size, weight);
    BinaryVector h1 = randomBinaryVectorHW(size, weight);
    BinaryVector invh0 = invertBinaryVector(h0);
    BinaryVector h = binaryVectorProduct(h1, invh0);
    freeBinaryVector(invh0);
    BinaryVector *temp = (BinaryVector*) malloc(3* sizeof(BinaryVector));
    temp[0] = initBinaryVector(h.size);
    temp[1] = initBinaryVector(h0);
    temp[2] = initBinaryVector(h1);
    recopyBinaryVector(temp[0], h);// temp[0] = h
    recopyBinaryVector(temp[1], h0);// temp[1] = h0
    recopyBinaryVector(temp[2], h1);// temp[2] = h1
    return temp;
}

// Retourne c1, e0, e1
BinaryVector* gen_e(int size, int t, BinaryVector h, bool needRandom){
    printf("bob starts his protocol\n");
    if(needRandom) srand(time(NULL));
    BinaryVector e = randomBinaryVectorHW(2*size, 2*t); // e = (e0|e1)
    BinaryVector e0 = initBinaryVector(size);
    BinaryVector e1 = initBinaryVector(size);
    for(int i=0; i<size; i++){
        e0.elements[i] = e.elements[i];
        e1.elements[i] = e.elements[i+size];
    }
    printf("vectors e0, e1 exists\n");
    BinaryVector c1 = binaryVectorProduct(h,e1);
    addBinaryVectors(c1, e0, c1); //c1 = e0 + he1
    BinaryVector *temp = (BinaryVector*) malloc(3* sizeof(BinaryVector));
    temp[0] = initBinaryVector(c1.size);
    temp[1] = initBinaryVector(e0.size);
    temp[2] = initBinaryVector(e1.size);
    recopyBinaryVector(temp[0], c1);// temp[0] = c1
    recopyBinaryVector(temp[1], e0);// temp[1] = e0
    recopyBinaryVector(temp[2], e0);// temp[2] = e1
    freeBinaryVector(e);
    return temp;
}

unsigned char* aliceComputeSecret(BinaryVector h0, BinaryVector h1, BinaryVector c1, int t, int w){
    BinaryVector s = binaryVectorProduct(h0, c1);
    BinaryVector e = BitFlipping(h0, h1, s, t, w);
    unsigned char* hash = hashBinaryVector(&e);
    freeBinaryVector(s);
    freeBinaryVector(e);
    return hash;
}

unsigned char* bobComputeSecret(BinaryVector e0, BinaryVector e1){
    BinaryVector e = initBinaryVector(e0.size * 2);
    for(int i=0; i<e0.size ; i++){
        e.elements[i] = e0.elements[i];
        e.elements[i+e0.size] = e1.elements[i];
    }
    unsigned char* hash = hashBinaryVector(&e);
    freeBinaryVector(e);
    return hash;
}