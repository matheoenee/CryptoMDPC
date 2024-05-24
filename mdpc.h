#ifndef CRYPTOMDPC_MDPC_H
#define CRYPTOMDPC_MDPC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include "matrix.h"
#include "bitflipping.h"
#include "structures.h"

unsigned char* hashBinaryVector(const BinaryVector *vec);

void printHash(unsigned char *hash);

bool areHashsIdentical(unsigned char *hash1, unsigned char *hash2, size_t lenght);

BinaryVector* gen_h(int size, int weight, bool needRandom);

BinaryVector* gen_e(int size, int t, BinaryVector h, bool needRandom);

unsigned char* aliceComputeSecret(BinaryVector h0, BinaryVector h1, BinaryVector c1, int t, int w);

unsigned char* bobComputeSecret(BinaryVector e0, BinaryVector e1);

#endif //CRYPTOMDPC_MDPC_H
