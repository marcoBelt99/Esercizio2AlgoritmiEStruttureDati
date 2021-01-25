#include "esercizio2.h"

//  VARIABILI GLOBALI: DEFINIZIONE qui
// Valori di default
/* time_t RANDOM_SEED = 20;                         // Random seed (important for reproducibility).
const unsigned int MAX_RANDOM_NUMBER = 10000000; // Maximum random number allowed.
const unsigned int MIN_OPERATIONS = 100;         // Minimum number of operations.
const unsigned int MAX_OPERATIONS = 2000;        // Maximum number of operations.
const unsigned int STEP = 100;                   // Step of the experiment.
const unsigned int NUM_EXPERIMENTS = 50;         // Number of experiments.
const unsigned int PERCENTAGE_INSERTIONS = 40;   // Percentage of insert operations.
const unsigned int NUM_ENTRIES = 59;             // Size of the hashtable.
const bool TEST_DATA_STRUCTURES = true;          // Test data structures?
const unsigned int NUM_ELEMENTS_FOR_TEST = 1000; // Number of elements for testing.
const outputEnum_t outputType = ONFILE;          // Output type.
FILE *outputPointer;                             // Output pointer (for printing). */

// Valori per prove iniziali
/* time_t RANDOM_SEED = 20;                       // Seme random (importante per la riproducibilità).
const unsigned int MAX_RANDOM_NUMBER = 1000;   // Massimo numero casuale ammesso.
const unsigned int MIN_OPERATIONS = 2;         // Minimum number of operations.
const unsigned int MAX_OPERATIONS = 10;        // Maximum number of operations.
const unsigned int STEP = 2;                   // Step dell'esperimento.
const unsigned int NUM_EXPERIMENTS = 5;        // Numero di esperimenti.
const unsigned int PERCENTAGE_INSERTIONS = 40; // Percentuale di operazioni di inserimento.
const unsigned int NUM_ENTRIES = 10;           // Dimensione della HT.
const bool TEST_DATA_STRUCTURES = true;        // Test strutture dati?
const unsigned int NUM_ELEMENTS_FOR_TEST = 10; // Numero di elementi per testarle.
const outputEnum_t outputType = ONCONSOLE;     // Tipo di output.
FILE *outputPointer;                           // Puntatore di output (per la stampa). */

time_t RANDOM_SEED = 20;                       // Seme random (importante per la riproducibilità).
const unsigned int MAX_RANDOM_NUMBER = 500;    // Massimo numero casuale ammesso.
const unsigned int MIN_OPERATIONS = 100;       // Minimum number of operations.
const unsigned int MAX_OPERATIONS = 10000;     // Maximum number of operations.
const unsigned int STEP = 150;                 // Step dell'esperimento.
const unsigned int NUM_EXPERIMENTS = 200;      // Numero di esperimenti.
const unsigned int PERCENTAGE_INSERTIONS = 60; // Percentuale di operazioni di inserimento.
const unsigned int NUM_ENTRIES = 1;            // Dimensione della HT.
const bool TEST_DATA_STRUCTURES = true;        // Test strutture dati?
const unsigned int NUM_ELEMENTS_FOR_TEST = 10; // Numero di elementi per testarle.
const outputEnum_t outputType = ONCONSOLE;     // Tipo di output.
FILE *outputPointer;                           // Puntatore di output (per la stampa).

void printArray(int *A, const int n);

int main(void)
{
    srand(RANDOM_SEED); // Inizializzo il seed casuale.

    // Le prossime 4 variabili le uso per ospitare il risultato dei calcoli per l'esperimento
    clock_t timeHashtable = 0;      // Tempo trascorso per la HashTable.
    clock_t timeRbt = 0;            // Tempo trascorso per l' RBT.
    unsigned int numInsertions = 0; // Numero di operazioni di inserimento.
    unsigned int numSearches = 0;   // Numero di operazioni di ricerca.

    if (outputType == ONCONSOLE || outputType == ONFILE) // What is the outputPointer?
    {

        if (outputType == ONCONSOLE) // On console.
            outputPointer = stdout;

        else // On file.
        {
            outputPointer = fopen("results.txt", "w"); // Open file.

            if (outputPointer == NULL) // Have we opened the file?
            {
                fprintf(stderr, "ERROR: The outputPointer has not been created\n");
                exit(-1);
            }
        }
    } // Fine if controllo: "Qual'è il tipo di input?"

    else // Error
    {
        fprintf(stderr, "ERROR: The outputType can be only ONCONSOLE or ONFILE\n");
        exit(-1);
    }

    // Print the header, only if it is on console.
    if (outputType == ONCONSOLE)
    {
        fprintf(outputPointer, "+-----------------------------+---------------------+---------------------+\n");
        fprintf(outputPointer, "| Operations - %%I & %%S        | Hashtable - %-5d   | Red Black Tree      |\n", NUM_ENTRIES);
        fprintf(outputPointer, "+-----------------------------+---------------------+---------------------+\n");
    }

    // For each number of operations in the interval [MIN_OPERATIONS, MAX_OPERATIONS] with STEP
    for (int numOps = MIN_OPERATIONS; numOps <= MAX_OPERATIONS; numOps += STEP)
    {
        // printf("********numOps******** = %d. (STEP = %d)\n\n", numOps, STEP); // SOLO DI PROVA
        timeHashtable = timeRbt = 0; // Reset the times.

        for (int exper = 1; exper <= NUM_EXPERIMENTS; exper++) // For each experiment
        {
            // printf("exper = %d\n", exper); // SOLO DI PROVA
            // Compute the number of insert operations.
            numInsertions = numOps * PERCENTAGE_INSERTIONS / 100;
            // Compute the number of search operations.
            numSearches = numOps - numInsertions; // me lo calcolo di conseguenza
            // Allocate numInsertions memory cells for the array of random numbers.
            int *randomArray = malloc(numInsertions * sizeof(int));
            // Fill-in the array with random numbers.
            generateRandomArray(randomArray, numInsertions);

            /* // Prova stampa array: // SOLO DI PROVA
            printf("\n"); // SOLO DI PROVA
            printArray(randomArray, numInsertions); // SOLO DI PROVA
            printf("\n"); // SOLO DI PROVA
            */
            // ***********************  Hashtable experiment ***********************.
            timeHashtable += doExperiment(randomArray, numInsertions, numSearches, "hashtable");
            // ***********************  RBT experiment *****************************.
            timeRbt += doExperiment(randomArray, numInsertions, numSearches, "rbt");

            /* // Prova stampa array: // SOLO DI PROVA
            printArray(randomArray, numInsertions); // SOLO DI PROVA
            printf("\n"); // SOLO DI PROVA */
            // SOLO DI PROVA
            // Free the array of random numbers.
            free(randomArray);
        } // Fine esperimento NUM_EXPERIMENTS-esimo
          // Printing the (sample mean as) result. Use TAB (\t) on file.
        if (outputType == ONCONSOLE)
            fprintf(outputPointer, "| %15d - %-3d & %-3d | %19f | %19f |\n",
                    numOps,
                    PERCENTAGE_INSERTIONS,
                    100 - PERCENTAGE_INSERTIONS,
                    (float)timeHashtable / NUM_EXPERIMENTS,
                    (float)timeRbt / NUM_EXPERIMENTS);
        else
            fprintf(outputPointer, "%d \t%f \t%f \n",
                    numOps,
                    (float)timeHashtable / NUM_EXPERIMENTS,
                    (float)timeRbt / NUM_EXPERIMENTS);
    }

    // Print the ending part, only if it is on console.
    if (outputType == ONCONSOLE)
    {
        fprintf(outputPointer, "+-----------------------------+---------------------+---------------------+\n");
        fprintf(outputPointer, "| Legend:                                                                 |\n");
        fprintf(outputPointer, "|                                                                         |\n");
        fprintf(outputPointer, "| %%I: Percentage of insertion operations                                  |\n");
        fprintf(outputPointer, "| %%S: Percentage of search operations                                     |\n");
        fprintf(outputPointer, "|                                                                         |\n");
        fprintf(outputPointer, "| The number near \"Hashtable\" is the number of entries in the hashtable   |\n");
        fprintf(outputPointer, "+-------------------------------------------------------------------------+\n");
    }

    if (TEST_DATA_STRUCTURES)
    {
        fprintf(outputPointer, "| Hashtable implementation: %-12s                                  |\n", hashtableTest() ? "correct" : "not correct");
        fprintf(outputPointer, "| Red black tree implementation: %-12s                             |\n", rbtTest() ? "correct" : "not correct");
        fprintf(outputPointer, "+-------------------------------------------------------------------------+\n");
    }

    // Return 0.
    return 0;

} // fine main

// FUNZIONE AUSILIARIA:

void generateRandomArray(int *A, const int n) // implementata
{
    // For each i in 0..n-1, generate a random number.
    for (int i = 0; i < n; i++)
        A[i] = rand() % MAX_RANDOM_NUMBER;
}
// int generateRandomKey() { return rand() % MAX_RANDOM_NUMBER; }
void printArray(int *A, const int n)
{
    for (int i = 0; i < n; i++)
        printf("%d\n", A[i]);
    //printf("\n");
}
// CORE FUNCTIONS

clock_t doExperiment(int *randomArray, const unsigned int numInsertions, const unsigned int numSearches, char *dataStructure)
{
    /************** HASH TABLE **************/
    clock_t tempoInizio, tempoFine = 0; // Li uso per entrambe le strutture dati
    int chiaveDiRicerca = 250;
    // chiaveDiRicerca = generateRandomKey(); // La genero casualmente?
    if (strcmp(dataStructure, "hashtable") == 0)
    {
        // Creazione Hash Table
        hashtable_t *HT = NULL;             // Creo sullo STACK un puntatore ad una hashtable che si trova sullo HEAP
        linkedListNode_t *nodoLista = NULL; // Per cercare
        HT = createHashtable(NUM_ENTRIES);  // Creo la HT di dimensione NUM_ENTRIES

        tempoInizio = clock();
        // Inserimento
        for (int i = 0; i < numInsertions; i++)
            hashtableInsert(HT, randomArray[i]);

        // hashtablePrint(HT); // scopo di correttezza
        //  printf("\nChiave di ricerca:\t%d\n", chiaveDiRicerca);

        // Ricerca in Hash Table
        nodoLista = hashtableSearch(HT, chiaveDiRicerca);
        tempoFine = clock();

        hashtableFree(HT);
    }
    else if (strcmp(dataStructure, "rbt") == 0)
    {
        /************** RBT **************/
        // Creazione Red Black Tree
        rbt_t *T = NULL;
        T = createRbt();           // Creo l'rbt nello HEAP
        rbtNode_t *nodoRbt = NULL; // per cercare

        // Creazione dei nodi. Nota: per evitare di rallentare il tempo per gli rbt,
        rbtNode_t *Nodi[numInsertions];              // ho dichiarato un array di nodi per contenerli tutti,
        for (int i = 0; i < numInsertions; i++)      // in modo da non effettuare la creazione "a tempo di inserimento"
            Nodi[i] = createRbtNode(randomArray[i]); //  ma da effettuarla al di fuore del tempo di sperimentazione

        tempoInizio = clock();
        // Inserimento
        for (int i = 0; i < numInsertions; i++)
            rbtInsert(T, Nodi[i]); //rbtInsert(T, createRbtNode(randomArray[i]));

        //  rbtInOrder(T, T->root);
        // printf("\nChiave di ricerca:\t%d\n", chiaveDiRicerca); // scopo di correttezza

        //Ricerca
        // nodoRbt = rbtSearch(T, chiaveDiRicerca); // vedo se è questo che rallenta...
        nodoRbt = rbtSearchRicorsiva(T, T->root, chiaveDiRicerca); // Provo questa versione
        tempoFine = clock();

        rbtFree(T);
    }
    else
    {
        fprintf(stderr, "doExperiment: Errore sul nome della struttura dati inserita.\
        \nSi prega di utilizzare:\n\t'hashtable' per sperimentare le tabelle hash\n\t'rbt'\
        per sperimentare gli alberi red black\n");
        exit(EXIT_FAILURE);
    }

    return (tempoFine - tempoInizio); // Ritorno il tempo atteso per l'esperimento
}

//  Fine CORE FUNCTIONS