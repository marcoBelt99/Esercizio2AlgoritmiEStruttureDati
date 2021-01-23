#include "esercizio2.h"

/********************************************
    Nota sulla variabili/costanti utilizzate
 ********************************************/
// HT:              è la hash table su cui operare
// SIZE_UNIVERSO:   è la dimensione del vettore 'Universo'
// m:               è la dimensione della Hash Table (ossia il numero di 'Caselle' di cui è composta)
// Universo[]:      è il dominio, ossia l'insieme di chiavi che voglio mappare in HT. Ha dimensione prefissata SIZE_UNIVERSO
// nodoDiRicerca:   è il nodo da ricercare risultante dalla ricerca. Lo utilizzo sia per ricerca che per eliminazione
// chiaveDiRicerca: è la chiave che si vuole ricercare. La utilizzo per entrambe le operazioni di ricerca ed eliminazione

// #define SIZE_UNIVERSO 10

/* void printUniverso(int *A, int dim) // Pattern For-Each di stampa degli elementi di un array
{
    int i = 0;
    for (i = 0; i < dim; i++)
        printf("%d ", A[i]);
    printf("\n");
} */
// Funzione getIndex() che mi ottiene l'indice della casella corrispondente

// Prova al volo correttezza con main
/*  int main()
{
    bool correttezza = hashtableTest();
    if (correttezza)
        printf("Corretto!!!\n");
    else
    {
        printf("Scorretto :( \n");
    }
    return 0;
}  */

// Funzione vera e propria
bool hashtableTest()
{
    // Parametri controllo automatico ai fini della funzione test
    int SIZE_UNIVERSO = 20;
    int chiaveDiRicerca = 35;
    unsigned int m = 10; // Dimensione della hashtable: La setto in automatico ai fini della funzione di test

    /* Questo codice è commentato per non "sporcare lo stdoutput"
    // unsigned int m = 0; // Dimensione della hashtable  
        fprintf(stdout, "Inserire la dimensione m della hashtable: \n"); // Richiedo in input per l'utente la dimensione della hashtable
        fscanf(stdin, "%u", &m); 
        */

    // (DOMINIO), mentre i nodi delle liste formano il CODOMINIO
    // int Universo[] = {16, 12, 25, 39, 6, 122, 5, 68, 75, 10};
    int Universo[] = {26, 17, 41, 14, 21, 30, 47, 10, 16, 19, 23, 28, 38, 7, 12, 15, 20, 35, 39, 3};
    /* Questo codice è commentato per non "sporcare lo stdoutput" 
    printf("\nQueste sono le chiavi che voglio mappare nella tabella hash:\n");
    printUniverso(Universo, SIZE_UNIVERSO); 
    */

    if (m < 1)
    {
        fprintf(stderr, "Errore, struttura dati non definita\n");
        // exit(EXIT_FAILURE);
        return false;
    }

    // CREAZIONE
    hashtable_t *HT = NULL;  // Creo sullo STACK un puntatore ad una hashtable che si trova, dopo la sua creazione, sullo HEAP
    HT = createHashtable(m); // Creo la HT passandole l'opportuna dimensione (10 è una dimensione che mi è comoda)
    if (HT == NULL)
    {
        fprintf(stderr, "Errore in fase di creazione\n");
        // exit(EXIT_FAILURE);
        return false;
    }

    // INSERIMENTO
    for (int i = 0; i < SIZE_UNIVERSO; i++)
    {
        hashtableInsert(HT, Universo[i]);
        if (HT->entry[hashFunction(HT, i)] == NULL) // Almeno una casella della HT deve puntare ad un elemento di tipo lista contenente Universo[i]
        {
            fprintf(stderr, "Errore in fase di inserimento\n");
            // exit(EXIT_FAILURE);
            return false;
        }
    } // fine for inserimento

    /* // Questo codice è commentato per non "sporcare lo stdoutput"
    printf("\n---------- TABELLA HASH DOPO INSERIMENTO DEI NODI ----------\n");
    */
    //hashtablePrint(HT); // Stampo la HT dopo l'inserimento di queste chiavi
    //fprintf(stdout, "La tabella hash ha %d caselle:\n", HT->size);
    /*
    // RICERCA DI UN ELEMENTO (contenuto in un nodo di una delle s liste collegate):
    int chiaveDiRicerca = 0;
    printf("Inserire una chiave da ricercare nella HT: ");
    fscanf(stdin, "%d", &chiaveDiRicerca); */

    linkedListNode_t *nodoDaRicercare = hashtableSearch(HT, chiaveDiRicerca);

    if (nodoDaRicercare == NULL)
    {
        fprintf(stderr, "Nodo non trovato...\n");
        // exit(EXIT_FAILURE);
    }
   /*  else
        fprintf(stdout, "Trovato\n"); */
    

    // ELIMINAZIONE DI UN ELEMENTO:
    /* // Questo codice è commentato per non "sporcare lo stdoutput"
    printf("Inserire il nodo da cercare e, successivamente eliminare: ");
    fscanf(stdin, "%d", &chiaveDiRicerca);
    
    chiaveDiRicerca = 5; // Automatizzazione solo per funzione test
    linkedListNode_t *nodoDaEliminare = hashtableSearch(HT, chiaveDiRicerca); 

    while (!nodoDaEliminare) // Deve esistere per poterlo eliminare
    {
        printf("\nL'elemento che si vuole eliminare non è presente nella HT\n\n");
        printf("Inserire il nodo da cercare e, successivamente eliminare: ");
        scanf("%d", &chiaveDiRicerca);
        nodoDaEliminare = hashtableSearch(HT, chiaveDiRicerca);
    }
    printf("\n---------- TABELLA HASH DOPO ELIMINAZIONE DEL NODO %d ----------\n", nodoDaEliminare->value); 
    */

    int sizeListaPrimaDiEliminare, sizeListaDopoEliminazione = 0;
    sizeListaPrimaDiEliminare = HT->entry[hashFunction(HT, chiaveDiRicerca)]->list->size; // Mi salvo la dimensione della lista prima di eliminare il nodo da tale lista

    // hashtableDelete(HT, nodoDaEliminare); // Arrivato qui, il nodo da eliminare esiste proseguo con la sua eliminazione
    hashtableDelete(HT, nodoDaRicercare); // Solo per automatizzare funzione test

    sizeListaDopoEliminazione = HT->entry[hashFunction(HT, chiaveDiRicerca)]->list->size; // Mi salvo la dimensione della lista dopo l'eliminazione del nodo dalla lista
    // if ((nodoDaEliminare->prev != NULL) || (nodoDaEliminare->next != NULL) || (sizeListaPrimaDiEliminare <= sizeListaDopoEliminazione))

    if ((nodoDaRicercare->prev != NULL) || (nodoDaRicercare->next != NULL) || (sizeListaPrimaDiEliminare <= sizeListaDopoEliminazione)) // Solo per automatizzare funzione test
    {
        fprintf(stderr, "Errore in fase di eliminazione del nodo\n");
        // exit(EXIT_FAILURE);
        return false;
    }
    
    // hashtablePrint(HT); // Stampo la HT dopo l'eliminazione di uno dei nodi
    
    // free(nodoDaRicercare);
    // free(nodoDaEliminare);
    hashtableFree(HT); // Ho finito di usare la HT, allora elimino tutte le liste, le entry e infine la HT

    /********** Se il flusso è arrivato fino a qui, la struttura dati è corretta. ***********/
    return true;

} // fine funzione
