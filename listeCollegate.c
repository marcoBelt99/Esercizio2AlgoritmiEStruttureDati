#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
// #################################################################################################
// MAIN
// #################################################################################################
int main(void)
{
    printf("********* Test Liste collegate *********\n");
    // Creo la lista (nello HEAP). Per riferirmi al suo indirizzo uso un puntatore di tipo lista
    linkedList_t *L = createLinkedList();
    // Creo nello STACK alcuni puntatori a nodi per potermi riferire ai nodi che sono creati nello HEAP
    linkedListNode_t *nodo1 = createLinkedListNode(17);
    linkedListNode_t *nodo2 = createLinkedListNode(5); // creo nello STACK un puntatore ad un nodo creato nello HEAP
    linkedListNode_t *nodo3 = createLinkedListNode(190);
    linkedListNode_t *nodo4 = createLinkedListNode(6);
    linkedListNode_t *nodo5 = createLinkedListNode(45);
    linkedListNode_t *nodo6 = createLinkedListNode(66);
    linkedListNode_t *nodo7 = createLinkedListNode(23);

    // Inserisco il nodo appena creato in testa alla lista
    linkedListInsert(L, nodo1);
    linkedListInsert(L, nodo2);
    linkedListInsert(L, nodo3);
    linkedListInsert(L, nodo4);
    linkedListInsert(L, nodo5);
    linkedListInsert(L, nodo6);
    linkedListInsert(L, nodo7);
    // Stampo la lista dopo l'inserimento
    printf("Situazione della Lista dopo l'inserimento dei nodi:\n");
    linkedListPrint(L);
    printf("\nLa dimensione della Lista è: %d\n", L->size);

    // Cancello il nodo 5 (il cui value è 45)
    linkedListDelete(L, nodo5);
    // linkedListDelete(L,nodo1);
    // linkedListDelete(L,nodo7);
    // Stampo la lista dopo la cancellazione del nodo
    printf("Situazione della Lista dopo la cancellazione del nodo il cui valore è 45:\n");
    linkedListPrint(L);
    printf("\nLa dimensione della Lista è: %d\n", L->size);

    // Ricerca
    int chiave = 0;
    printf("\n");
    printf("Inserire la chiave da cercare: ");
    scanf("%d", &chiave);
    printf("Ricerca del nodo con chiave %d:\n", chiave);
    linkedListNode_t *nodoRicerca; //
    nodoRicerca = linkedListSearch(L, chiave);
    // printf("\nLista:\n");
    // linkedListPrint(L);
    if ((nodoRicerca != NULL) && (nodoRicerca->value == chiave))
        printf("Trovato\n");
    else
        printf("Non trovato\n");
    // free(nodoRicerca); // Non serve a niente :-/
    // Libero la memoria occupata dalla lista, che ora non mi serve più
    linkedListFree(L);
    return 0;
} // fine main

// #################################################################################################
/* DEFINIZIONI FUNZIONI */
// #################################################################################################
linkedListNode_t *createLinkedListNode(const int v)
{
    linkedListNode_t *risultato = malloc(sizeof(linkedListNode_t)); // Alloco nello HEAP lo spazio necessario per il nuovo nodo
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
    linkedListNode_t *x = list->head;      // x parte dalla testa della lista
    while ((x != NULL) && (x->value != v)) // confronto la chiave degli elementi con quella che cerco.
        x = x->next;                       // passo al prossimo nodo
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
                                 // free(x);                     // precedentemente allocata per il nodo che ho appena reso indisponibile alla ricerca
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
