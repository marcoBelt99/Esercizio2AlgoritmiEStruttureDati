#include "esercizio2.h"

//  DEFINIZIONE VARIABILI GLOBALI:

time_t RANDOM_SEED = 20;                       // Seme random (importante per la riproducibilità).
const unsigned int MAX_RANDOM_NUMBER = 500;   // Massimo numero casuale ammesso.
const unsigned int MIN_OPERATIONS = 1;       // Minimum number of operations.
const unsigned int MAX_OPERATIONS = 45;      // Maximum number of operations.
const unsigned int STEP = 1;                  // Step dell'esperimento.
const unsigned int NUM_EXPERIMENTS = 50;      // Numero di esperimenti.
const unsigned int PERCENTAGE_INSERTIONS = 40; // Percentuale di operazioni di inserimento.
const unsigned int NUM_ENTRIES = 59;           // Dimensione della HT.
const bool TEST_DATA_STRUCTURES = true;        // Test strutture dati?
const unsigned int NUM_ELEMENTS_FOR_TEST = 20; // Numero di elementi per testarle.
const outputEnum_t outputType = ONCONSOLE;        // Tipo di output.
FILE *outputPointer;                           // Puntatore di output (per la stampa).

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
        clearScreen();      // Pulisco la console
        fprintf(outputPointer, "+-----------------------------+---------------------+---------------------+\n");
        fprintf(outputPointer, "| Operations - %%I & %%S        | Hashtable - %-5d   | Red Black Tree      |\n", NUM_ENTRIES);
        fprintf(outputPointer, "+-----------------------------+---------------------+---------------------+\n");
    }

    // For each number of operations in the interval [MIN_OPERATIONS, MAX_OPERATIONS] with STEP
    for (unsigned int numOps = MIN_OPERATIONS; numOps <= MAX_OPERATIONS; numOps += STEP)
    {
        // printf("********numOps******** = %d. (STEP = %d)\n\n", numOps, STEP); // SOLO DI PROVA
        timeHashtable = timeRbt = 0; // Reset the times.

        for (unsigned int exper = 1; exper <= NUM_EXPERIMENTS; exper++) // For each experiment
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

     //if(TEST_DATA_STRUCTURE)
    if (outputPointer == ONCONSOLE && TEST_DATA_STRUCTURES) // aggiunto questa modifica per avere file results.txt corretto
    {
        fprintf(outputPointer, "| Hashtable implementation: %-12s                                  |\n", hashtableTest() ? "correct" : "not correct");
        fprintf(outputPointer, "| Red black tree implementation: %-12s                             |\n", rbtTest() ? "correct" : "not correct");
        fprintf(outputPointer, "+-------------------------------------------------------------------------+\n");
    }

    // Return 0.
    return 0;

} // fine main
