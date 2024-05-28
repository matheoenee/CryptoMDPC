#ifndef CRYPTOMDPC_MDPC_H
#define CRYPTOMDPC_MDPC_H

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

//Fonction qui hash un vecteur binaire
unsigned char* hashBinaryVector(const BinaryVector *vec);

// Fonction qui affiche un hash
void printHash(unsigned char *hash);

// Fonction qui détermine l'égalité entre deux hashs
bool areHashsIdentical(unsigned char *hash1, unsigned char *hash2);

// Retourne h, h0, h1
void gen_h(int size, int weight, bool needRandom);

// Retourne c1, e0, e1
void gen_e(int size, int t, BinaryVector h, bool needRandom);

// Fonction qui, à partir des données obtenues précédement par alice, lui permet d'obtenir le secret partagé avec bob
unsigned char* aliceComputeSecret(BinaryVector h0, BinaryVector h1, BinaryVector c1, int t, int w);

// Fonction qui calcule le hash de (e0|e1)
unsigned char* bobComputeSecret(BinaryVector e0, BinaryVector e1);

#endif //CRYPTOMDPC_MDPC_H
