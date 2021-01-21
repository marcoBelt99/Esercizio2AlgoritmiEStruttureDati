#include "esercizio2.h"

/*
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
 */

// IMPLEMENTAZIONI DELLE FUNZIONI

// LISTE COLLEGATE

linkedListNode_t *createLinkedListNode(const int v)
{
    linkedListNode_t *risultato = malloc(sizeof(linkedListNode_t)); // alloco nello HEAP lo spazio necessario per il nuovo nodo
    risultato->value = v;                                           // ci metto la chiave
    risultato->next = NULL;                                         // inizializzo il puntatore next
    risultato->prev = NULL;                                         // inizializzo il puntatore prev
    return risultato;
}

linkedList_t *createLinkedList()
{
    linkedList_t *l = malloc(sizeof(linkedList_t)); // l è un puntatore di tipo lista. (Puntatore a struttura di tipo lista)
    l->head = NULL;                                 // l->head è di tipo nodo. All'inizio la testa non punta ad alcun nodo
    l->size = 0;                                    // all'inizio è vuota
    return l;                                       // ritorno la lista appena creata
}

void linkedListInsert(linkedList_t *list, linkedListNode_t *x)
{
    x->next = list->head; // assegno al campo next del nodo x, l'indirizzo della testa della lista list
    if (list->head != NULL)
        list->head->prev = x; // inserisco in testa alla lista list il nodo
    list->head = x;
    x->prev = NULL;
    list->size++; // incremento di 1 la dimensione della lista
}

linkedListNode_t *linkedListSearch(linkedList_t *list, const int v)
{
    linkedListNode_t *x = list->head;      // x contiene temporaneamente l'indirizzo del 1 ° elemento
    while ((x != NULL) && (x->value != v)) // confronto la chiave degli elementi con quella che cerco.
        x = x->next;
    return x;
    // Si esce dal while o perchè si è arrivati in fondo o perchè si è trovata la chiave
}

void linkedListDelete(linkedList_t *list, linkedListNode_t *x)
{
    if (x->prev != NULL)
        x->prev->next = x->next;
    else
        list->head = x->next; // list punta al successore
    if (x->next != NULL)
        x->next->prev = x->prev; // salto indietro di una posizione
    list->size--;                // decremento la dimensione della lista
    free(x);                     // precedentemente allocata per il nodo che ho appena reso indisponibile alla ricerca
}

void linkedListPrint(linkedList_t *list) // implementata
{
    linkedListNode_t *x = list->head;
    while (x)
    {
        fprintf(stdout, "%d ", x->value);
        x = x->next;
    }
}

void linkedListFree(linkedList_t *list)
{
    linkedListNode_t *aux;
    while (list->head != NULL) // finchè sto puntando a qualche nodo
    {
        aux = list->head;              // memorizzo l'indirizzo della testa
        list->head = list->head->next; // passo al prossimo elemento
        free(aux);
    }
    free(list);
}

// Fine LINKED LIST

// HASHTABLE

hashtable_t *createHashtable(const unsigned int s)
{
    unsigned int i;
    hashtable_t *HT = malloc(sizeof(hashtable_t)); // Alloco lo spazio per contenere la HT nello HEAP. HT è un puntatore di tipo hashtable_t
    if (!HT)                                       // Controllo correttezza dell'allocazione
        return NULL;
    HT->entry = malloc(sizeof(hashtableEntry_t) * s); // Alloco lo spazio per s caselle di puntatori a lista nello HEAP
    // HT->entry = malloc(sizeof(hashtableEntry_t **) * s)
    if (!(HT->entry)) // Controllo correttezza dell'allocazione
        return NULL;
    HT->size = s;                  // La tabella hash ha s caselle
    for (i = 0; i < HT->size; i++) // Inizializzo la tabella hash
    {
        hashtableEntry_t *casella = malloc(sizeof(hashtableEntry_t *)); // Alloco casella da essegnare alla posizione i-esima della lista
        if (!casella)                                                   // Controllo correttezza dell'allocazione
            return NULL;
        casella->list = createLinkedList(); // Per la entry i-esima, creo una nuova lista collegata che conterrà le chiavi
        HT->entry[i] = casella;             // Assegno casella alla posizione i-esima
    }
    return HT; // Ora posso ritornare l'indirizzo della HT creata
}

const unsigned int hashFunction(hashtable_t *hashtbl, const int v) // implementata
{
    return v % hashtbl->size;
}

void hashtableInsert(hashtable_t *hashtbl, const int v)
{
    linkedListNode_t *x = createLinkedListNode(v); // Creo un nuovo nodo per la lista
    int indiceCasella = hashFunction(hashtbl, v);  // Mi calcolo il valore di hash per la chiave v
    // linkedList_t *L = createLinkedList();       // Creo nello HEAP la lista che si "collegherà" alla entry di indice indiceCasella della hash table
    linkedListInsert(hashtbl->entry[indiceCasella]->list, x); // Inserisco il nodo x con chiave v all'interno della posizione indiceCasella-esima usando ListInsert
}

linkedListNode_t *hashtableSearch(hashtable_t *hashtbl, const int v)
{
    int indiceCasella = hashFunction(hashtbl, v);                    // Mi calcolo il valore di hash per la chiave v
    return linkedListSearch(hashtbl->entry[indiceCasella]->list, v); // Ritorno lo stesso risultato che avrebbe ListSearch (ritorno l'indirizzo di un nodo)
}

void hashtableDelete(hashtable_t *hashtbl, linkedListNode_t *x)
{
    int indiceCasella = hashFunction(hashtbl, x->value);      // Mi calcolo il valore di hash per la chiave x->value
    linkedListDelete(hashtbl->entry[indiceCasella]->list, x); // Cancella x dalla lista T[hashtbl(x.value)]
}

void hashtablePrint(hashtable_t *hashtbl) // implementata
{
    for (int i = 0; i < hashtbl->size; i++)
    {
        fprintf(stdout, "%d => ", i);
        linkedListPrint(hashtbl->entry[i]->list);
        fprintf(stdout, "\n");
    }
}

bool hashtableTest() // Dimostro su file con main saparato
{
    return;
}

void hashtableFree(hashtable_t *hashtbl)
{
    for (unsigned int i = 0; i < hashtbl->size; i++)
        linkedListFree(hashtbl->entry[i]->list); // dealloco prima tutte le liste collegate di ogni entry della HT
    free(hashtbl);
}

// Fine HASHTABLE

// RBT

rbtNode_t *createRbtNode(const int v)
{
    // I allocate on the HEAP the necessary space
    rbtNode_t *risultato = malloc(sizeof(rbtNode_t));
    // Initialize pointers
    risultato->left = risultato->right = risultato->parent = NULL;
    // Newly node has always red color
    risultato->color = RED;
    // I put the key
    risultato->value = v;
    // return the newly node created

    return risultato;
    //free(risultato); // Libero?
}

rbt_t *createRbt()
{
    // Allocate in HEAP the necessary space for an rbt structure
    rbt_t *T = malloc(sizeof(rbt_t));
    // Allocate in HEAP the space for node T.NIL
    rbtNode_t *nodoNIL = malloc(sizeof(rbtNode_t));
    nodoNIL->left = nodoNIL->right = nodoNIL->parent = NULL;
    // T.NIL must be BLACK
    nodoNIL->color = BLACK;
    // I initialize its key at 0 (even if it do not really need the key)
    nodoNIL->value = 0;
    // Assignments
    T->nil = nodoNIL;
    T->root = T->nil;
    // Initially rbt has not any node
    T->size = 0;
    // Return newly rbt created
    //free(nodoNIL); // Libero
    return T;
    //free(T); // Libero?
}

void rbtLeftRotate(rbt_t *rbt, rbtNode_t *x)
{
    if (rbt && x) // Controllo validità dei puntatori
    {
        rbtNode_t *y = x->right;

        x->right = y->left;
        if (y->left != rbt->nil)
        {
            y->left->parent = x;
        }

        y->parent = x->parent;
        if (x->parent == rbt->nil)
        {
            rbt->root = y;
        }
        else if (x->parent->left == x)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }

        y->left = x;
        x->parent = y;
    }
    else
    {
        fprintf(stderr, "rbtLeftRotate: Puntatori NULL\n");
        exit(EXIT_FAILURE);
    }
}

void rbtRightRotate(rbt_t *rbt, rbtNode_t *x)
{
    if (rbt && x) // Controllo validità dei puntatori

    {
        rbtNode_t *y = x->left;

        x->left = y->right;
        if (y->right != rbt->nil)
        {
            y->right->parent = x;
        }

        y->parent = x->parent;
        if (x->parent == rbt->nil)
        {
            rbt->root = y;
        }
        else if (x->parent->left == x)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }

        y->right = x;
        x->parent = y;
    }
    else
    {
        fprintf(stderr, "rbtRightRotate: puntatori NULL\n");
        exit(EXIT_FAILURE);
    }
}

void rbtInsert(rbt_t *rbt, rbtNode_t *z)
{
}

void rbtInsertFixup(rbt_t *rbt, rbtNode_t *z)
{
}

rbtNode_t *rbtSearch(rbt_t *rbt, const int v)
{
}

void rbtInOrder(rbt_t *rbt, rbtNode_t *x) // implementata
{
    if (x != rbt->nil)
    {
        rbtInOrder(rbt, x->left);
        printf("%d ", x->value);
        rbtInOrder(rbt, x->right);
    }
}

bool rbtTest()
{
    return;
}

bool isRbt(rbt_t *rbt)
{
}

bool rbtHasBstProperty(rbt_t *rbt)
{
    return;
}

void rbtHasBstPropertyUtil(rbt_t *rbt, rbtNode_t *x, rbtTestStructure_t *test) // Manca il terzo parametro formale perchè la testStructure non la uso
{
}

int rbtComputeBlackHeight(rbt_t *rbt, rbtNode_t *x)
{
}

void rbtFreeNodes(rbt_t *T, rbtNode_t *x)
{
}

void rbtFree(rbt_t *T)
{
}

// End of RBT

// AUXILIARY FUNCTIONS

void generateRandomArray(int *A, const int n) // implementata
{
    // For each i in 0..n-1, generate a random number.
    for (int i = 0; i < n; i++)
        A[i] = rand() % MAX_RANDOM_NUMBER;
}

bool isSorted(const int *A, const int n) // implementata
{
    // For each i in 0..n-2, if the current element is greater than the next one,
    // then it is unsorted.
    for (int i = 0; i < n - 1; i++)
        if (A[i] > A[i + 1])
            return false;
    // Otherwise it is.
    return true;
}

// End of AUXILIARY FUNCTIONS

// CORE FUNCTIONS

clock_t doExperiment(int *randomArray, const unsigned int numInsertions, const unsigned int numSearches, char *dataStructure)
{
    return;
}

//  Fine CORE FUNCTIONS

// Fine IMPLEMENTATION OF THE FUNCTIONS