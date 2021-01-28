#include "esercizio2.h"

time_t RANDOM_SEED = 20;                    // Seme random (importante per la riproducibilità).
const unsigned int MAX_RANDOM_NUMBER = 150; // Massimo numero casuale ammesso.
const unsigned int DIM = 15;                // Dimensione dell'array

void generateRandomArray(int *A, const int n) // implementata
{
    // For each i in 0..n-1, generate a random number.
    for (int i = 0; i < n; i++)
        A[i] = rand() % MAX_RANDOM_NUMBER;
}

int generateRandomKey()
{
    // srand(time(NULL));
    return (rand() % MAX_RANDOM_NUMBER);
}

void printArray(int *A, const int n)
{
    for (int i = 0; i < n; i++)
        printf("%d\n", A[i]);
    //printf("\n");
}

int main(void)
{
    srand(RANDOM_SEED);
    //  int num = rand() % MAX_RANDOM_NUMBER;
    int num = 0;
    num = generateRandomKey(); // metto dentro a num la chiave generata casualmente
    printf("\nnum =\t%d\n", num);
    num = rand() % MAX_RANDOM_NUMBER + 1;
    printf("\nnum =\t%d\n", num);
    num = generateRandomKey();
    printf("\nnum =\t%d\n", num);
    // int A[DIM];
    // generateRandomArray(A, DIM);
    // printArray(A, DIM);

    return 0;
}