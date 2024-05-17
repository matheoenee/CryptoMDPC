 #include "binary_inverse.c"

int main() {
    int n = 3;
    bool** A = allocateMatrix(n);

    // Exemple de matrice binaire
    A[0][0] = 1; A[0][1] = 1; A[0][2] = 1;
    A[1][0] = 1; A[1][1] = 0; A[1][2] = 1;
    A[2][0] = 0; A[2][1] = 1; A[2][2] = 1;

    printf("Matrice originale:\n");
    printMatrix(A, n);

    bool** inverse = binary_inverse(A, n);

    if (inverse != NULL) {
        printf("Matrice inverse:\n");
        printMatrix(inverse, n);
        freeMatrix(inverse, n);
    }

    freeMatrix(A, n);
    return 0;
}