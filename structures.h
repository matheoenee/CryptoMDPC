#ifndef CRYPTOMDPC_STRUCTURES_H
#define CRYPTOMDPC_STRUCTURES_H

#include <stdbool.h>

typedef struct {
    bool *elements;
    int size;
} BinaryVector;

typedef struct {
    int *elements;
    int size;
} Vector;

typedef struct {
    bool **elements;
    int rows;
    int cols;
} BinaryMatrix;

typedef struct {
    BinaryVector *vectors;
    int size;
    int length;
}BinaryVectors;

#endif //CRYPTOMDPC_STRUCTURES_H
