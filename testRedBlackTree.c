#include "esercizio2.h"

/********************************************
    Nota sulla variabili/costanti utilizzate
 ********************************************/
// T:               è l'albero Red Black su cui operare
// SIZE_UNIVERSO:   è la dimensione del vettore 'Universo'
// A[]:             è il vettore di interi che voglio inserire nel campo 'value' di ciascun nodo
// chiave:          è la chiave che si vuole ricercare. La utilizzo solo per l'operazione di ricerca
// trovato:         è il nodo da ricercare risultante dalla ricerca. Lo utilizzo solo per la ricerca
// minimo:          è il nodo risultato della ricerca del minimo.  (Potevo usare 'trovato', ma non l'ho usato per ragioni di leggibilità)
// massimo:         è il nodo risultato della ricerca del massimo. (Potevo usare 'trovato', ma non l'ho usato per ragioni di leggibilità)

// Prova al volo correttezza con main
/* int main()
{
    bool correttezza = rbtTest();
    if (correttezza)
        printf("Corretto!!!\n");
    else
    {
        printf("Scorretto :( \n");
    }
    return 0;
} */

bool rbtTest()
{
    // CREAZIONE
    rbt_t *T = createRbt();                                                                   // Creo l'rbt nello HEAP
    int A[] = {26, 17, 41, 14, 21, 30, 47, 10, 16, 19, 23, 28, 38, 7, 12, 15, 20, 35, 39, 3}; // Vettore contente i valore dei nodi che creerò ed inserirò
    int chiave = 47;                                                                          // Mi servirà per verificare la Ricerca

    // INSERIMENTO (preceduto dalla creazione di alcuni nodi)
    for (int i = 0; i < 20; i++) // Creo nello HEAP 20 nodi e li Inserisco opportunamente nell'rbt T
        rbtInsert(T, createRbtNode(A[i]));
    /* Questo codice è commentato per automatizzare le operazioni delle funzione bool rbtTest(); 
    printf("\n******************** RBT INSERT ********************\n"); 
    printf("\nVisita IN-ORDER\n");
    */

    // rbtInOrder(T, T->root); // // Commentare per non sporcare lo stdoutput

    /* Questo codice è commentato per automatizzare le operazioni delle funzione bool rbtTest(); 
    // Stampo la dimensione dell'albero
    printf("\nDimensione dell'albero:\t%d\n", T->size);
    // Stampo le informazioni sulla sua radice, come ulteriore sicurezza di correttezza
    printf("Radice: %d di colore: %c\n", T->root->value, T->root->color);
    if (T->root->parent == T->nil)
        printf("Il Padre della radice è T->nil\n");
    else
        printf("Il Padre della radice NON è T->nil\n");
    sleep(1);
    
    // Mi occupo della Ricerca
     printf("\n******************** RBT SEARCH ********************\n"); 
    printf("Inserire il valore da cercare: "); // Richiedo il valore da cercare all'utente
    scanf("%d", &chiave);
    */

    rbtNode_t *trovato = T->nil;    // Questo nodo conterrà il risultato della Ricerca
    trovato = rbtSearch(T, chiave); // Versione iterativa (quella ricorsiva non mi veniva)
    if (trovato == T->nil)
    {
        fprintf(stderr, "Non Trovato\n");
    }
    /* else
        fprintf(stdout, "Trovato!\n"); */

    // sleep(1);

    // Verifico per ulteriore sicurezza se l'albero effettivamente ha i propri minimo e massimo,
    // rispettivamente all'estrema sinistra ed all'estrema destra
    rbtNode_t *minimo, *massimo = T->nil;
    minimo = rbtMinimum(T);
    massimo = rbtMaximum(T);

    if ((minimo == T->nil) || (massimo == T->nil))
    {
        fprintf(stderr, "Errore ricerca minimo e/o massimo\n");
        return false;
    }

    /* Questo codice è commentato ai fini della funzione rbtTest
    printf("\n******************** MINIMO-MASSIMO ********************\n");
    printf("Il nodo minimo vale: %d\n", minimo->value);
    printf("Il nodo massimo vale: %d\n", massimo->value);
    sleep(1); */

    /* Questo codice è commentato ai fini della funzione rbtTest
    // Mi occupo di verificare l'Altezza Nera di ogni nodo, attraverso un attraversamento preOreder (risultante più comodo)
    printf("\n******************** ALTEZZA ALBERO ********************\n");
    printf("Visualizzo altezza albero (visitandolo in PreOrder):\n"); */

    // printf("\n");                          // Commentare per non sporcare lo stdoutput
    // stampaAltezzaNeraPreOrder(T, T->root); // Commento per non sporcare lo stdoutput
    // sleep(1);

    /* Questo codice è commentato ai fini della funzione rbtTest   
    // Mi occupo di verificare le proprietà dell'albero
    printf("\nProprietà BST: ");
    if (rbtHasBstProperty(T) == true)
        printf("OK\n");
    else
        printf("Errore proprietà BST\n");

    // Proprietà 1 RBT
    if (rbtProprieta_1(T) == true)
    {
        fprintf(stdout, "Proprietà 1: OK\n");
    }
    else
    {
        fprintf(stderr, "Errore Proprietà 1\n");
        exit(EXIT_FAILURE);
    }

    // Proprietà 2 RBT
    if (rbtProprieta_2(T) == true)
    {
        fprintf(stdout, "Proprietà 2: OK\n");
    }
    else
    {
        fprintf(stderr, "Errore Proprietà 2\n");
        exit(EXIT_FAILURE);
    }

    // Proprietà 3 RBT
    if (rbtProprieta_3(T) == true)
    {
        fprintf(stdout, "Proprietà 3: OK\n");
    }
    else
    {
        fprintf(stderr, "Errore Proprietà 3\n");
        exit(EXIT_FAILURE);
    }

    // Proprietà 4 RBT
    if (rbtProprieta_4(T) == true)
    {
        fprintf(stdout, "Proprietà 4: OK\n");
    }
    else
    {
        fprintf(stderr, "Errore Proprietà 4\n");
        exit(EXIT_FAILURE);
    }

    // Proprietà 5 RBT
    if (rbtProprieta_5(T) == true)
    {
        fprintf(stdout, "Proprietà 5: OK\n");
    }
    else
    {
        fprintf(stderr, "Errore Proprietà 5\n");
        exit(EXIT_FAILURE);
    } */

    if (isRbt(T) == false)
    {
        fprintf(stderr, "rbtTest:isRbt: Errore in qualche proprietà\n");
        return false;
    }

    // A questo punto, Libero la memoria allocata precedentemente con la malloc in fase di creazione
    rbtFree(T);
    if ((T->root != NULL) && (T->nil != NULL)) // Controllo che non ci siano memory leaks
    {
        fprintf(stderr, "rbtTest:isRbt:rbtFree: Errore, Memory leaks\n");
        return false;
    }
    /* else
    printf("C'è qualche altro nodo da ripulire\n");
    printf("Dimensione in memoria di un nodo: %ld\n", sizeof(rbtNode_t));
    printf("Dimensione in memoria di un albero: %ld\n", sizeof(rbt_t)); */

    free(T); // Libero la memoria dell'albero

    //********** Se il flusso è arrivato fino a qui, la struttura dati è corretta. ***********/
    return true;
}
