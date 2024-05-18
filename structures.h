#ifndef CRYPTOMDPC_STRUCTURES_H
#define CRYPTOMDPC_STRUCTURES_H

#include <stdbool.h>

typedef struct {
    bool *elements;
    int *elemInts;
    int size;
} Vector;

typedef struct {
    bool **elements;
    int rows;
    int cols;
} Matrix;

#endif //CRYPTOMDPC_STRUCTURES_H
