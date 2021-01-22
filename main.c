#include "esercizio2.h"

//  VARIABILI GLOBALI
time_t RANDOM_SEED = 20;                         // Random seed (important for reproducibility).
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
FILE *outputPointer;                             // Output pointer (for printing).

int main()
{
    srand(RANDOM_SEED);             // Random seed initialization.
    clock_t timeHashtable = 0;      // Elapsed time for hashtable.
    clock_t timeRbt = 0;            // Elapsed time for RBT.
    unsigned int numInsertions = 0; // Number of insert operations.
    unsigned int numSearches = 0;   // Number of search operations.

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
    }

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

        timeHashtable = timeRbt = 0; // Reset the times.

        for (int exper = 1; exper <= NUM_EXPERIMENTS; exper++) // For each experiment
        {

            // Compute the number of insert operations.
            numInsertions = numOps * PERCENTAGE_INSERTIONS / 100;
            // Compute the number of search operations.
            numSearches = numOps - numInsertions;
            // Allocate numInsertions memory cells for the array of random numbers.
            int *randomArray = malloc(numInsertions * sizeof(int));
            // Fill-in the array with random numbers.
            generateRandomArray(randomArray, numInsertions);

            // ***********************  Hashtable experiment ***********************.
            timeHashtable += doExperiment(randomArray, numInsertions, numSearches, "hashtable");
            // ***********************  RBT experiment *****************************.
            timeRbt += doExperiment(randomArray, numInsertions, numSearches, "rbt");

            // Free the array of random numbers.
            free(randomArray);
        }
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