#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "binary_inverse.h"
#include "prange.h"
#include "matrix.h"
#include "bitflipping.h"

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

int main() {
    int n = 100; // le nombre de tests
    srand(time(NULL));
    int size = 4813;
    int w = 39;
    int t = 39;
    int T = 26;
    int good =0;
    for(int i=0; i<n; i++){
        BinaryVector h0 = randomBinaryVectorHW(size, w);
        BinaryVector h1 = randomBinaryVectorHW(size, w);
        BinaryVector e0 = randomBinaryVectorHW(size, t);
        BinaryVector e1 = randomBinaryVectorHW(size, w);
        BinaryVector e = initBinaryVector(2*size);
        for(int l=0; l<2*size; l++){
            e.elements[i] = e0.elements[i];
            e.elements[i+size] = e1.elements[i];
        }
        BinaryVector s0 = binaryVectorProduct(h0, e0);
        BinaryVector s1 = binaryVectorProduct(h1, e1);
        BinaryVector s = initBinaryVector(size);
        addBinaryVectors(s, s0, s1);

        BinaryVector output = BitFlipping(h0,h1, s, T, t);
        if(areBinaryVectorEqual(output, e)){
            printf("algorithm sucess");
            good+=1;
        }
        printf("end of round %d", i);
        freeBinaryVector(h0);
        freeBinaryVector(h1);
        freeBinaryVector(e0);
        freeBinaryVector(e1);
        freeBinaryVector(e0);
        freeBinaryVector(e);
        freeBinaryVector(s0);
        freeBinaryVector(s1);
        freeBinaryVector(s);
        freeBinaryVector(output);
    }

    printf("number of sucess : %d/%d\n", good, n);

    return 0;
}

/*
 *
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