#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define SIZE_UNIVERSO 9
#define SIZE_UNIVERSO 20

// #################################################################################################
// DEFINIZIONE TIPI
// #################################################################################################
typedef struct linkedListNode_t // NODO della Lista
{
    int value;                     // Chiave del nodo. Value contained in the node.
    struct linkedListNode_t *next; // Puntatore al nodo successivo. Pointer to next node.
    struct linkedListNode_t *prev; // Puntatore al nodo precedente. Pointer to previous node.
} linkedListNode_t;

typedef struct linkedList_t // LISTA COLLEGATA
{
    unsigned int size;             // Dimensione della lista. Size in number of nodes of the list.
    struct linkedListNode_t *head; // Indirizzo della testa. Puntatore al nodo testa della lista. Pointer to the head node of the list.
} linkedList_t;

// ##############################################################################################
typedef struct hashtableEntry_t // "ENTRY" di una Tabella Hash.
{
    struct linkedList_t *list; // Puntatore a Lista
} hashtableEntry_t;

typedef struct hashtable_t // Tabella Hash
{
    unsigned int size;               // Quante "Caselle" ha la hash table. Size in number of entries of the hashtable.
    struct hashtableEntry_t **entry; // Array di puntatori a "Caselle". <--> struct hashtableEntry_t *entry[s]
} hashtable_t;

// #################################################################################################
/* DICHIARAZIONI FUNZIONI */
// #################################################################################################
linkedListNode_t *createLinkedListNode(const int v);
linkedList_t *createLinkedList();
void linkedListInsert(linkedList_t *list, linkedListNode_t *x);
linkedListNode_t *linkedListSearch(linkedList_t *list, const int v);
void linkedListDelete(linkedList_t *list, linkedListNode_t *x);
void linkedListPrint(linkedList_t *list); // implementata
void linkedListFree(linkedList_t *list);
// ----------------------------------------------------------------------------------------------
hashtable_t *createHashtable(const unsigned int s);                   // Creazione HashTable
const unsigned int hashFunction(hashtable_t *hashtbl, const int v);   // Funzione Modulo: implementata
void hashtableInsert(hashtable_t *hashtbl, const int v);              // Inserimento
linkedListNode_t *hashtableSearch(hashtable_t *hashtbl, const int v); // Ricerca di un elemento (Nodo della lista)
void hashtableDelete(hashtable_t *hashtbl, linkedListNode_t *x);      // Eliminazione --> non richiesta ma per correttezza
void hashtablePrint(hashtable_t *hashtbl);                            // Stampa: implementata
bool hashtableTest();                                                 // finita
void hashtableFree(hashtable_t *hashtbl);                             // finita

void printUniverso(int *A, int dim) // Pattern For-Each di stampa degli elementi di un array
{
    int i = 0;
    for (i = 0; i < dim; i++)
        printf("%d ", A[i]);
    printf("\n");
}
// Funzione getIndex() che mi ottiene l'indice della casella corrispondente

// #################################################################################################
/* MAIN */
// #################################################################################################
int main(void)
{
    // SIZE_UNIVERSO è la dimensione del vettore 'Universo'
    // m è la dimensione della Hash Table (ossia il numero di caselle di cui è composta)
    unsigned int m = 0; // dimensione della hashtable

    fprintf(stdout, "Inserire la dimensione m della hashtable: \n"); // Richiedo in input la dimensione della hashtable
    fscanf(stdin, "%u", &m);
    if (m <= 0)
    {
        fprintf(stderr, "Errore, struttura dati non definita\n");
        exit(EXIT_FAILURE);
    }

    hashtable_t *HT = NULL;  // Creo sullo STACK un puntatore ad una hashtable che si trova sullo HEAP
    HT = createHashtable(m); // Creo la HT

    // int Universo[SIZE_UNIVERSO] = {16, 12, 25, 39, 6, 122, 5, 68, 75}; // (Dominio), mentre i nodi delle liste formano il CODOMINIO
    int Universo[SIZE_UNIVERSO] = {26, 17, 41, 14, 21, 30, 47, 10, 16, 19, 23, 28, 38, 7, 12, 15, 20, 35, 39, 3};

    fprintf(stdout, "\nQueste sono le chiavi che voglio mappare nella tabella hash:\n");
    printUniverso(Universo, SIZE_UNIVERSO);

    // INSERIMENTO
    for (int i = 0; i < SIZE_UNIVERSO; i++)
        hashtableInsert(HT, Universo[i]);
    fprintf(stdout, "\n---------- TABELLA HASH DOPO INSERIMENTO DEI NODI ----------\n");
    hashtablePrint(HT); // Stampo la HT dopo l'inserimento di queste chiavi
    fprintf(stdout, "\nDimensione Hash Table dopo inserimento dei nodi:\t%d\n", HT->size);

    // RICERCA DI UN ELEMENTO (contenuto in un nodo di una delle s liste collegate )
    int chiaveDiRicerca = 0;
    fprintf(stdout, "Inserire una chiave da ricercare nella HT: ");
    fscanf(stdin, "%d", &chiaveDiRicerca);
    linkedListNode_t *nodoDaRicercare = hashtableSearch(HT, chiaveDiRicerca);
    if (nodoDaRicercare != NULL)
        fprintf(stdout, "Elemento trovato: %d\n", nodoDaRicercare->value);
    else
        fprintf(stdout, "Elemento non trovato.\n");

    // ELIMINAZIONE DI UN ELEMENTO:
    fprintf(stdout, "Inserire il nodo da cercare e, successivamente eliminare: ");
    fscanf(stdin, "%d", &chiaveDiRicerca);
    linkedListNode_t *nodoDaEliminare = hashtableSearch(HT, chiaveDiRicerca);
    while (!nodoDaEliminare) // Deve esistere per poterlo eliminare
    {
        fprintf(stdout, "\nL'elemento che si vuole eliminare non è presente nella HT\n\n");
        fprintf(stdout, "Inserire il nodo da cercare e, successivamente eliminare: ");
        scanf("%d", &chiaveDiRicerca);
        nodoDaEliminare = hashtableSearch(HT, chiaveDiRicerca);
    }
    printf("\n---------- TABELLA HASH DOPO ELIMINAZIONE DEL NODO %d ----------\n", nodoDaEliminare->value);
    hashtableDelete(HT, nodoDaEliminare); // Arrivato qui, il nodo da eliminare esiste proseguo con la sua eliminazione
    hashtablePrint(HT);                   // Stampo la HT dopo l'eliminazione di uno dei nodi
    hashtableFree(HT);                    // Ho finito di usare la HT, allora elimino tutte le liste, le entry e infine la HT
    return 0;
}

// #################################################################################################
/* DEFINIZIONI FUNZIONI */
// #################################################################################################
linkedListNode_t *createLinkedListNode(const int v)
{
    linkedListNode_t *risultato = malloc(sizeof(linkedListNode_t)); // alloco nello HEAP lo spazio necessario per il nuovo nodo
    risultato->value = v;                                           // ci metto la chiave
    risultato->next = NULL;                                         // inizializzo il puntatore next
    risultato->prev = NULL;                                         // inizializzo il puntatore prev
    return risultato;                                               // ritorno il nodo risultante                                                // provo a fare la free
}

linkedList_t *createLinkedList() // Creazione di una nuova lista collegata
{
    linkedList_t *l = malloc(sizeof(linkedList_t)); // l è un puntatore di tipo lista. (Puntatore a struttura di tipo lista)
    l->head = NULL;                                 // l->head è di tipo nodo. All'inizio la testa non punta ad alcun nodo
    l->size = 0;                                    // all'inizio è vuota
    return l;                                       // ritorno la lista appena creata
}

void linkedListInsert(linkedList_t *list, linkedListNode_t *x) // Assumo che il nodo x da inserire esista già
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

void linkedListDelete(linkedList_t *list, linkedListNode_t *x) // Assumo di conoscere l'indirizzo dell'elemento da cancellare
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

void linkedListPrint(linkedList_t *list)
{
    linkedListNode_t *x = list->head; // finchè sto puntando a qualcosa. l è una lista, mentre l.head è un nodo di una lista
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

// #####################################################################################################################
hashtable_t *createHashtable(const unsigned int s) // s è il numero di entries della HT. HT è un array di puntatori
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

const unsigned int hashFunction(hashtable_t *hashtbl, const int v) // implementata; v è una costante
{
    return v % hashtbl->size; // chiaveHashTable % dimensioneHashTable
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
    for (unsigned int i = 0; i < hashtbl->size; i++)
    {
        fprintf(stdout, "%d => ", i);
        linkedListPrint(hashtbl->entry[i]->list);
        fprintf(stdout, "\n");
    }
}

bool hashtableTest() // Vedere file testHashTable
{
    return true;
}

/* VECCHIA 
void hashtableFree(hashtable_t *hashtbl)
{
    for (unsigned int i = 0; i < hashtbl->size; i++)
        linkedListFree(hashtbl->entry[i]->list); // dealloco prima tutte le liste collegate di ogni entry della HT
    free(hashtbl);                               // poi la hash table
} */

// NUOVA
/** @author Eduard  */
void hashtableFree(hashtable_t *hashtbl)
{
    for (unsigned int i = 0; i < hashtbl->size; i++)
    {
        linkedListFree(hashtbl->entry[i]->list); // dealloco prima tutte le liste collegate di ogni entry della HT
        free(hashtbl->entry[i]);                 // AGGIUNTO
    }
    free(hashtbl->entry); // AGGIUNTO
    free(hashtbl);        // poi la hash table
}

// Fine HASHTABLE