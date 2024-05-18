#ifndef CRYPTOMDPC_MDPC_H
#define CRYPTOMDPC_MDPC_H

#include "structures.h"

// Algortihme de comparaison d'odre 1
int max(int a,int b);

// Fonction RotMat
BinaryMatrix rotMat(BinaryVector h0, BinaryVector h1);

// Dernière vérification de l'algorithme BitFlip
BinaryVector Verification(BinaryVector s, BinaryMatrix H, BinaryVector u, BinaryVector v);

// Algorithme BitFlip
BinaryVector BitFlipping(BinaryVector h0, BinaryVector h1, BinaryVector s, int T, int t);

#endif //CRYPTOMDPC_MDPC_H
