#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "binary_inverse.h"
#include "prange.h"
#include "matrix.h"
#include "bitflipping.h"

int main() {
    srand(time(NULL));

    clock_t start, end;
    double cpu_time_used;

    int n = 400;
    int k = 200;
    int t = 15;

    printf("Paramètres : (n = %d, k = %d, t = %d)\n",n,k,t);
    printf("[+] Génération d'une matrice H aléatoire...\n");
    BinaryMatrix H = randomBinaryMatrix(n-k, n);

    printf("[+] Génération d'une vecteur erreur aléatoire...\n");
    BinaryVector e = randomBinaryVectorHW(n,t);
    printf("Erreur e : \n");
    printBinaryVector(e);
    printf("HW(e) = %d\n",hammingWeight(e));

    printf("[+] Calcul du syndrome...\n");
    BinaryVector s = binaryMatrixVectorProduct(H,e);
    printf("Syndrome s : \n");
    printBinaryVector(s);
    printf("\n");

    printf("[+] Début de l'algorithme de Prange...\n");
    start = clock();
    BinaryVector x = Prange(H,s,t,n,k);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("[info] Temps d'éxecution : %f secondes.\n", cpu_time_used);
    printf("Résultat x : \n");
    printBinaryVector(x);
    printf("\n");

    printf("Vérification...\n");
    if(areBinaryVectorEqual(e,x)) printf("x == e\n");
    else printf("x != e\n");

    freeBinaryMatrix(H);
    freeBinaryVector(e);
    freeBinaryVector(s);
    freeBinaryVector(x);

    return 0;
}

/* TEST PRANGE
srand(time(NULL));

    clock_t start, end;
    double cpu_time_used;

    int n = 300;
    int k = 150;
    int t = 15;

    printf("Paramètres : (n = %d, k = %d, t = %d)\n",n,k,t);
    printf("[+] Génération d'une matrice H aléatoire...\n");
    BinaryMatrix H = randomBinaryMatrix(n-k, n);

    printf("[+] Génération d'une vecteur erreur aléatoire...\n");
    BinaryVector e = randomBinaryVectorHW(n,t);
    printf("Erreur e : \n");
    printBinaryVector(e);
    printf("HW(e) = %d\n",hammingWeight(e));

    printf("[+] Calcul du syndrome...\n");
    BinaryVector s = binaryMatrixVectorProduct(H,e);
    printf("Syndrome s : \n");
    printBinaryVector(s);
    printf("\n");

    printf("[+] Début de l'algorithme de Prange...\n");
    start = clock();
    BinaryVector x = Prange(H,s,t,n,k);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("[info] Temps d'éxecution : %f secondes.\n", cpu_time_used);
    printf("Résultat x : \n");
    printBinaryVector(x);
    printf("\n");

    printf("Vérification...\n");
    if(areBinaryVectorEqual(e,x)) printf("x == e\n");
    else printf("x != e\n");

    freeBinaryMatrix(H);
    freeBinaryVector(e);
    freeBinaryVector(s);
    freeBinaryVector(x);

    return 0;
*/

/** test for bitflipping
* BinaryVector h0 = initBinaryVector(n);
    h0.elements[1] = true;
    h0.elements[3] = true;
    h0.elements[4] = true;
    h0.elements[6] = true;
    BinaryVector h1 = initBinaryVector(n);
    h1.elements[0] = true;
    h1.elements[1] = true;
    h1.elements[5] = true;
    h1.elements[7] = true;

    printBinaryVector(h0);
    printf("\n");
    printBinaryVector(h1);

    BinaryVector y = initBinaryVector(n);
    y.elements[-1] = true;

    BinaryVector e = BitFlipping(h0, h1, y, 3, 1);

    printBinaryVector(e);
    freeBinaryVector(h0);
    freeBinaryVector(h1);
    freeBinaryVector(y);
    freeBinaryVector(e);
*/