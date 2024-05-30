#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>
#include <openssl/evp.h>

#include "structures.h"
#include "matrix.h"
#include "binary_inverse.h"
#include "prange.h"
#include "bitflipping.h"
#include "mdpc.h"

// Utilisez les valeurs passées par le préprocesseur pour n, k, et t
#ifndef PARAM_N
#define PARAM_N 200
#endif

#ifndef PARAM_K
#define PARAM_K 100
#endif

#ifndef PARAM_T
#define PARAM_T 10
#endif

#ifndef PARAM_SIZE
#define PARAM_SIZE 4813
#endif

#ifndef PARAM_WEIGHT_H
#define PARAM_WEIGHT_H 39
#endif

#ifndef PARAM_WEIGHT_E
#define PARAM_WEIGHT_E 78
#endif

#ifndef PARAM_THRESHOLD
#define PARAM_THRESHOLD 26
#endif

int main() {
    srand(time(NULL));
    int size = PARAM_SIZE;
    int w = PARAM_WEIGHT_H;
    int t = PARAM_WEIGHT_E;
    int T = PARAM_THRESHOLD;
    printf("Temps d'exécution de l'algorithme MDPC avec les paramètres suivants :\n");
    printf(" - Longueur : %d\n - Poids de h0 et h1 : %d\n - Poids de l'erreur (totale) : %d\n - Seuil T du bitflipping : %d\n", size, w, t, T);
    clock_t step0, step1, step2, step3, step4, end;
    double cpu_time_used;
    step0 = clock();
    BinaryVectors aliceGen = initBinaryVectors(3, size);
    gen_h(aliceGen, size, w, false); // takes some times (around 140s)

    step1 = clock();
    cpu_time_used = ((double) (step1 - step0)) / CLOCKS_PER_SEC;
    printf("Temps pour l'algorithme gen_h : %f sec\n", cpu_time_used);

    BinaryVector h = copyBinaryVector(aliceGen.vectors[0]);// sent to Bob
    BinaryVectors bobGen = initBinaryVectors(3, size);
    gen_e(bobGen, size, t, h, false);
    step2 = clock();
    cpu_time_used = ((double) (step2 - step1)) / CLOCKS_PER_SEC;
    printf("Temps pour l'algorithme gen_e : %f sec\n", cpu_time_used);

    BinaryVector c1 = copyBinaryVector(bobGen.vectors[0]); // sent to Alice

    unsigned char *hashAlice = (unsigned char *)malloc(SHA256_DIGEST_LENGTH);
    aliceComputeSecret(hashAlice, aliceGen.vectors[1], aliceGen.vectors[2], c1, T, t);
    step3 = clock();
    cpu_time_used = ((double) (step3 - step2)) / CLOCKS_PER_SEC;
    printf("Temps pour l'algorithme aliceComputeSecret : %f sec\n", cpu_time_used);

    unsigned char *hashBob = (unsigned char *)malloc(SHA256_DIGEST_LENGTH);
    bobComputeSecret(hashBob, bobGen.vectors[1], bobGen.vectors[2]);
    step4 = clock();
    cpu_time_used = ((double) (step4 - step3)) / CLOCKS_PER_SEC;
    printf("Temps pour l'algorithme bobComputeSecret : %f sec\n", cpu_time_used);
    printf("Hash d'Alice: ");
    printHash(hashAlice);
    printf("Hash de Bob: ");
    printHash(hashBob);
    freeBinaryVector(c1);
    freeBinaryVector(h);

    freeBinaryVectors(aliceGen);
    freeBinaryVectors(bobGen);
    end = clock();
    free(hashAlice);
    free(hashBob);
    cpu_time_used = ((double) (end - step0)) / CLOCKS_PER_SEC;
    printf("Temps d'exécution total : %f sec\n", cpu_time_used);

    return 0;
}

/* TIME MDPC
int main() {
    srand(time(NULL));
    int size = PARAM_SIZE;
    int w = PARAM_WEIGHT_H;
    int t = PARAM_WEIGHT_E;
    int T = PARAM_THRESHOLD;
    printf("Temps d'exécution de l'algorithme MDPC avec les paramètres suivants :\n");
    printf(" - Longueur : %d\n - Poids de h0 et h1 : %d\n - Poids de l'erreur (totale) : %d\n - Seuil T du bitflipping : %d\n", size, w, t, T);
    clock_t step0, step1, step2, step3, step4, end;
    double cpu_time_used;
    step0 = clock();
    BinaryVectors aliceGen = initBinaryVectors(3, size);
    gen_h(aliceGen, size, w, false); // takes some times (around 140s)

    step1 = clock();
    cpu_time_used = ((double) (step1 - step0)) / CLOCKS_PER_SEC;
    printf("Temps pour l'algorithme gen_h : %f sec\n", cpu_time_used);

    BinaryVector h = copyBinaryVector(aliceGen.vectors[0]);// sent to Bob
    BinaryVectors bobGen = initBinaryVectors(3, size);
    gen_e(bobGen, size, t, h, false);
    step2 = clock();
    cpu_time_used = ((double) (step2 - step1)) / CLOCKS_PER_SEC;
    printf("Temps pour l'algorithme gen_e : %f sec\n", cpu_time_used);

    BinaryVector c1 = copyBinaryVector(bobGen.vectors[0]); // sent to Alice

    unsigned char *hashAlice = (unsigned char *)malloc(SHA256_DIGEST_LENGTH);
    aliceComputeSecret(hashAlice, aliceGen.vectors[1], aliceGen.vectors[2], c1, T, t);
    step3 = clock();
    cpu_time_used = ((double) (step3 - step2)) / CLOCKS_PER_SEC;
    printf("Temps pour l'algorithme aliceComputeSecret : %f sec\n", cpu_time_used);

    unsigned char *hashBob = (unsigned char *)malloc(SHA256_DIGEST_LENGTH);
    bobComputeSecret(hashBob, bobGen.vectors[1], bobGen.vectors[2]);
    step4 = clock();
    cpu_time_used = ((double) (step4 - step3)) / CLOCKS_PER_SEC;
    printf("Temps pour l'algorithme bobComputeSecret : %f sec\n", cpu_time_used);
    printf("Hash d'Alice: ");
    printHash(hashAlice);
    printf("Hash de Bob: ");
    printHash(hashBob);
    freeBinaryVector(c1);
    freeBinaryVector(h);

    freeBinaryVectors(aliceGen);
    freeBinaryVectors(bobGen);
    end = clock();
    free(hashAlice);
    free(hashBob);
    cpu_time_used = ((double) (end - step0)) / CLOCKS_PER_SEC;
    printf("Temps d'exécution total : %f sec\n", cpu_time_used);

    return 0;
}
*/
/* MEAN TIME MDPC
int main() {
    srand(time(NULL));
    int round = 10;
    int size = PARAM_SIZE;
    int w = PARAM_WEIGHT_H;
    int t = PARAM_WEIGHT_E;
    int T = PARAM_THRESHOLD;
    printf("Algorithme MDPC effectué avec les paramètres suivants :\n");
    printf(" - Longueur : %d\n - Poids de h0 et h1 : %d\n - Poids de l'erreur (totale) : %d\n - Seuil T du bitflipping : %d\n", size, w, t, T);
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    for(int i=0; i< round; i++){
        printf("Tour %d sur %d\n", i, round);
        BinaryVectors aliceGen = initBinaryVectors(3, size);
        gen_h(aliceGen, size, w, false);
        BinaryVector h = copyBinaryVector(aliceGen.vectors[0]);// sent to Bob

        BinaryVectors bobGen = initBinaryVectors(3, size);
        gen_e(bobGen, size, t, h, false);
        BinaryVector c1 = copyBinaryVector(bobGen.vectors[0]); // sent to Alice

        unsigned char *hashAlice = (unsigned char *)malloc(SHA256_DIGEST_LENGTH);
        aliceComputeSecret(hashAlice, aliceGen.vectors[1], aliceGen.vectors[2], c1, T, t);

        unsigned char *hashBob = (unsigned char *)malloc(SHA256_DIGEST_LENGTH);
        bobComputeSecret(hashBob, bobGen.vectors[1], bobGen.vectors[2]);
        printf("Hash d'Alice: ");
        printHash(hashAlice);
        printf("Hash de Bob: ");
        printHash(hashBob);
        freeBinaryVector(c1);
        freeBinaryVector(h);

        freeBinaryVectors(aliceGen);
        freeBinaryVectors(bobGen);

        free(hashAlice);
        free(hashBob);
        printf("Fin de tour\n");
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Temps d'exécution moyen : %f sec\n", cpu_time_used/round);

    return 0;
}


/* TIME BITFLIP
    int n = 1000; // le nombre de tests
    srand(time(NULL));
    int size = 4813;
    int w = 39;
    int t = 78;
    int T = 26;
    int good =0;
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    for(int i=0; i<n; i++){
        printf("round %d\n", i);
        BinaryVector h0 = randomBinaryVectorHW(size, w);
        BinaryVector h1 = randomBinaryVectorHW(size, w);
        BinaryVector e = randomBinaryVectorHW(2*size, t);
        BinaryVector e0 = initBinaryVector(size);
        BinaryVector e1 = initBinaryVector(size);
        for(int l=0; l<size; l++){
            e0.elements[l] = e.elements[l];
            e1.elements[l] = e.elements[l+size];
        }
        BinaryVector s0 = binaryVectorProduct(h0, e0);
        BinaryVector s1 = binaryVectorProduct(h1, e1);
        BinaryVector s = initBinaryVector(size);
        addBinaryVectors(s, s0, s1);

        BinaryVector output = BitFlipping(h0,h1, s, T, 2*t);
        if(areBinaryVectorEqual(output, e)){
            printf("algorithm sucess !\n");
            good+=1;
        }
        freeBinaryVector(h0);
        freeBinaryVector(h1);
        freeBinaryVector(e0);
        freeBinaryVector(e1);
        freeBinaryVector(e);
        freeBinaryVector(s0);
        freeBinaryVector(s1);
        freeBinaryVector(s);
        freeBinaryVector(output);
    }
    end = clock();
    printf("number of sucess : %d/%d\n", good, n);
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Executing time for %d bitflips : %f s\n", n, cpu_time_used);

    return 0;
 */

/*
int main() {
    srand(time(NULL));

    clock_t start, end;
    double cpu_time_used;

    int n = PARAM_N;
    int k = PARAM_K;
    int t = PARAM_T;

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
}*/

/* TEST PRANGE 01 
    srand(time(NULL));

    clock_t start, end;
    double cpu_time_used;

    int n = PARAM_N;
    int k = PARAM_K;
    int t = PARAM_T;

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

/* TEST PRANGE 02 (LOOP)
srand(time(NULL));

    clock_t start, end;
    double cpu_time_used;
    double sum_time = 0;

    int n = 200;
    int k = 100;
    int t = 10;

    int loop = 1000;


    printf("Paramètres : (n = %d, k = %d, t = %d)\n",n,k,t);
    for(int i = 0; i < loop; i++){
        printf("[loop %02d]\n",i);
        BinaryMatrix H = randomBinaryMatrix(n-k, n);
        BinaryVector e = randomBinaryVectorHW(n,t);
        BinaryVector s = binaryMatrixVectorProduct(H,e);

        start = clock();
        BinaryVector x = Prange(H,s,t,n,k);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("    Temps d'éxecution : %f secondes.\n", cpu_time_used);
        sum_time += cpu_time_used;

        printf("    Vérification...");
        if(areBinaryVectorEqual(e,x)) printf("[OK] x == e\n");
        else printf("[NOK] x != e\n");

        freeBinaryMatrix(H);
        freeBinaryVector(s);
        freeBinaryVector(e);
        freeBinaryVector(x);
    }
    
    double avg_time = sum_time/loop;
    printf("Temps d'éxecution moyen : %f secondes.\n", avg_time);

    return 0;
*/

/* ESTIMATION TEMPS INVERSION
    srand(time(NULL));

    clock_t start, end;
    double cpu_time_used;

    int n = PARAM_N;
    int k = PARAM_K;
    int t = PARAM_T;

    int loop = 1000;
    int inv_count = 0;
    double time_inv = 0;

    BinaryMatrix H, HI;

    printf("Paramètres : (n = %d, k = %d, t = %d)\n",n,k,t);

    for(int i = 0; i < loop; i++){
        H = randomBinaryMatrix(n-k, n-k);
        start = clock();
        HI = binaryMatrixInverse(H);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        if(!isMatrixEmpty(HI)){
            time_inv += cpu_time_used;
            inv_count++;
        }
    }
    printf("[+] %d inversions sur %d en %f secondes de moyennes.\n",inv_count, loop, time_inv/inv_count);
    
    freeBinaryMatrix(H);
    freeBinaryMatrix(HI);

    return 0;
*/

/* TEST BITFLIPPING
    BinaryVector h0 = initBinaryVector(n);
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