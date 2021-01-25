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
    x->next = NULL;
    x->prev = NULL;
    // x = NULL;
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
        aux = list->head;              // Memorizzo l'indirizzo della testa ( che è sempre elemento corrente)
        list->head = list->head->next; // Passo al prossimo elemento
        free(aux);                     // Libero l'elemento corrente
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
    HT->entry = malloc(sizeof(hashtableEntry_t) * s); // Alloco lo spazio per s Caselle (di puntatori a lista) nello HEAP
    // HT->entry = malloc(sizeof(hashtableEntry_t **) * s)
    if (!(HT->entry)) // Controllo correttezza dell'allocazione
        return NULL;
    HT->size = s;                  // La tabella hash ha esattamente s caselle
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

void hashtablePrint(hashtable_t *hashtbl) // già implementata
{
    for (int i = 0; i < hashtbl->size; i++)
    {
        fprintf(stdout, "%d => ", i);
        linkedListPrint(hashtbl->entry[i]->list);
        fprintf(stdout, "\n");
    }
}

/* bool hashtableTest() // Dimostro su file Separato
{
    return;
} 
*/

void hashtableFree(hashtable_t *hashtbl)
{
    for (unsigned int i = 0; i < hashtbl->size; i++)
        linkedListFree(hashtbl->entry[i]->list); // Dealloco prima tutte le liste collegate di ogni entry della HT
    free(hashtbl);                               // Poi la hash table
}

// Fine HASHTABLE

// RBT

rbtNode_t *createRbtNode(const int v)
{
    rbtNode_t *risultato = malloc(sizeof(rbtNode_t));              // Alloco nello HEAP lo spazio necessario a contenere il Nodo
    risultato->left = risultato->right = risultato->parent = NULL; // Inizializzo a NULL i suoi puntatori
    risultato->color = RED;                                        // Ogni nuovo nodo è ROSSO
    risultato->value = v;                                          // Ci inserisco la chiave
    return risultato;                                              // Ritorno il nuovo nodo creato
}

rbt_t *createRbt()
{
    rbt_t *T = malloc(sizeof(rbt_t));               // Alloco nello HEAP lo spazio necessario per una struttura rbt_t
    rbtNode_t *nodoNIL = malloc(sizeof(rbtNode_t)); // Alloco nello HEAP lo spazio necessario per il nodo T.NIL

    nodoNIL->left = nodoNIL->right = nodoNIL->parent = NULL; // Inizializzo i suoi puntatori
    nodoNIL->color = BLACK;                                  // Il suo colore DEVE SEMPRE essere NERO
    nodoNIL->value = 0;                                      // Inizializzo la sua chiave a 0 (anche se non ne ha bisogno in realtà)

    T->nil = nodoNIL; // Assegno questo nodo speciale al campo nil dell'albero appena allocato
    T->root = T->nil; // Inizialmente, la radice dell'albero punta a questo nuovo nodo
    T->size = 0;      // Inizialmente la dimensione dell'albero è nulla: nessun nodo è ancora stato inserito
    return T;         // Ritorno il nuovo albero Red Black appena creato
}

void rbtLeftRotate(rbt_t *rbt, rbtNode_t *x)
{
    if (rbt && x) // Controllo validità dei puntatori
    {
        rbtNode_t *y = x->right; // Imposta y
        x->right = y->left;      // Sposta il sottoalbero sinistro di y nel sottoalbero destro di x
        if (y->left != rbt->nil)
        {
            y->left->parent = x;
        }
        y->parent = x->parent; // Collega il padre di x a y
        if (x->parent == rbt->nil)
        { // x è la radice
            rbt->root = y;
        }
        else if (x == x->parent->left)
        { //x è il figlio sinistro
            x->parent->left = y;
        }
        else
        { // x è il figlio destro
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    } // Fine controllo validità puntatori
    else
    {
        fprintf(stderr, "rbtLeftRotate: Errore, puntatori NULL\n");
        exit(EXIT_FAILURE);
    }
} // fine rbtLeftRotate

void rbtRightRotate(rbt_t *rbt, rbtNode_t *x)
{
    if (rbt && x) // Controllo validità puntatori
    {
        rbtNode_t *y = x->left;
        x->left = y->right;
        if (y->right != rbt->nil)
        {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == rbt->nil)
        { //x è la radice
            rbt->root = y;
        }
        else if (x == x->parent->right)
        { //x è il figlio sinistro
            x->parent->right = y;
        }
        else
        { //x è il figlio destro
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    } // fine if controllo validità dei puntatori
    else
    {
        fprintf(stderr, "rbtLeftRotate: Errore, puntatori NULL\n");
        exit(EXIT_FAILURE);
    }
} // fine rbtRightRotate

void rbtInsert(rbt_t *rbt, rbtNode_t *z)
{
    if (rbt && z) // Controllo validità puntatori
    {
        rbtNode_t *y = rbt->nil;  // y è usato come puntatore di inseguimento
        rbtNode_t *x = rbt->root; // x parte dalla radice

        while (x != rbt->nil) // Trova la posizione giusta per inserire il nuovo nodo z
        {
            y = x;
            if (z->value < x->value)
                x = x->left;
            else
                x = x->right;
        }
        z->parent = y;

        if (y == rbt->nil)
        {
            rbt->root = z; // Il nuovo nodo è la radice
        }
        else if (z->value < y->value)
            y->left = z;
        else
            y->right = z;

        // Fin qui era analogo all'inserimento in BST
        z->right = rbt->nil;
        z->left = rbt->nil;
        z->color = RED;
        rbtInsertFixup(rbt, z);

        rbt->size++; // mi serve incrementare la dimensione dell'albero per ogni nuovo nodo inserito
    }                // fine if controllo validità puntatori
    else
    {
        fprintf(stderr, "rbtInsert: Errore, puntatori NULL\n");
        exit(EXIT_FAILURE);
    }
} //fine insert

void rbtInsertFixup(rbt_t *rbt, rbtNode_t *z)
{
    if (rbt && z) // Controllo validità puntatori
    {
        while (z->parent->color == RED)
        {
            if (z->parent == z->parent->parent->left)
            { // z parente è il figlio sinistro

                rbtNode_t *y = z->parent->parent->right; // y è lo zio del nodo z appena inserito

                if (y->color == RED)
                {                             // Caso 1
                    z->parent->color = BLACK; // padre diventa nero
                    y->color = BLACK;
                    z->parent->parent->color = RED; // il nonno diventa rosso
                    z = z->parent->parent;          // continua sistemando i nonni (vai verso l'alto)
                }
                else
                {                              // Caso 2 o caso 3
                    if (z == z->parent->right) // Sono nel figlio destro?
                    {                          // Caso 2
                        z = z->parent;         // il nuovo z è z.parent
                        rbtLeftRotate(rbt, z);
                    }
                    // Caso 3
                    z->parent->color = BLACK;       // padre nero
                    z->parent->parent->color = RED; // nonno rosso
                    rbtRightRotate(rbt, z->parent->parent);
                }
            }
            else
            {
                rbtNode_t *y = z->parent->parent->left; // y è lo zio di z

                if (y->color == RED) // Se lo zio è rosso
                {
                    z->parent->color = BLACK; // Ricolora
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->left)
                    {
                        z = z->parent; // z è diventato suo padre
                        rbtRightRotate(rbt, z);
                    }
                    z->parent->color = BLACK;       // padre nero
                    z->parent->parent->color = RED; // nonno rosso
                    rbtLeftRotate(rbt, z->parent->parent);
                }
            }
        }
        rbt->root->color = BLACK; // La radice deve sempre essere NERA

    } // fine controllo validità puntatori
    else
    {
        fprintf(stderr, "rbtInsertFixup: Errore, puntatori NULL\n");
        exit(EXIT_FAILURE);
    }
} // fine rbtInsertFixup

rbtNode_t *rbtSearch(rbt_t *rbt, const int v)
{
    if (rbt) // Se T è un puntatore valido
    {
        rbtNode_t *x = rbt->root; // Mi salvo la radice in x, così non modifico strutturalmente l'albero (Evito di muovere il puntatore T di tipo rbt)
        while ((x != rbt->nil) && (v != x->value))
        {
            if (v < x->value)
                x = x->left;
            else
                x = x->right;
        }
        return x;
    }
    else
    {
        fprintf(stderr, "rbtSearch: T è NULL\n");
        exit(EXIT_FAILURE);
    }
} // fine ricerca

void rbtInOrder(rbt_t *rbt, rbtNode_t *x) // Visita InOrder
{
    if (rbt && x) // Controllo validità puntatori
    {
        if (x != rbt->nil)
        {
            rbtInOrder(rbt, x->left);
            printf("Nodo:\t%d\tcolore:\t%c\n", x->value, (x->color == RED) ? 'R' : 'B');
            rbtInOrder(rbt, x->right);
        }
    }
    else
    {
        fprintf(stderr, "rbtInOrder: Errore, puntatori NULL\n");
        exit(EXIT_FAILURE);
    }
} // fine rbtInOrder

/* bool rbtTest() // Funzione su file separato:
{
    return;
} */

bool isRbt(rbt_t *rbt)
{
    if (rbt) // Controllo validità dei puntatori
    {        // (Provare con switch)
        bool pbst = rbtHasBstProperty(rbt);
        // 1. Ogni nodo è rosso o nero.
        bool p1 = rbtProprieta_1(rbt);
        // 2. La radice è nera
        bool p2 = rbtProprieta_2(rbt);
        // 3. Ogni foglia (NIL) è nera
        bool p3 = rbtProprieta_3(rbt);
        // 4. Se un nodo è rosso, allora entrambi i suoi figli sono neri
        bool p4 = rbtProprieta_4(rbt);
        // 5. Per ogni nodo, tutti i cammini semplici che vanno dal nodo alle foglie sue
        //    discendenti contengono lo stesso numero di nodi neri
        bool p5 = rbtProprieta_5(rbt);

        if (pbst && p1 && p2 && p3 && p4 && p5) // and logico di tutte le proprietà
            return true;
        else
            return false;
    }
    else
    {
        fprintf(stderr, "isRbt: Errore, puntatori NULL\n");
        exit(EXIT_FAILURE);
    }
} // fine isRbt

bool rbtHasBstProperty(rbt_t *rbt)
{
    rbtNode_t *Nodi[rbt->size]; // Dichiaro array di nodi
    int i = 0;                  // Variabile contatore

    inorderToArray(rbt, rbt->root, Nodi, &i); // Popolo l'array con la visita in order dell'albero

    i = 0;
    for (i = 0; i < rbt->size; i++)
    {

        if ((Nodi[i]->left != rbt->nil) && (Nodi[i]->right != rbt->nil)) // Se non sono foglie
        {
            if (Nodi[i]->value > Nodi[i]->left->value && Nodi[i]->value <= Nodi[i]->right->value) // Verifico questa proprietà per questo sottoalbero
                continue;
            else
            {
                *Nodi = NULL;
                free(Nodi);
                return false;
            }
        }

    } // fine for

    // Arrivato qui, ho soddisfatto la Proprietà BST
    return true;
}

void rbtHasBstPropertyUtil(rbt_t *rbt, rbtNode_t *x, rbtTestStructure_t *test) // Non l'ho prevista
{
}

int rbtComputeBlackHeight(rbt_t *rbt, rbtNode_t *x)
{
    if (rbt && x) // Controllo validità dei puntatori

    {
        int altezzaNeraSinstra = 0;
        int altezzaNeraDestra = 0;
        if (x == rbt->nil)
            return altezzaNeraSinstra; // I nodi T.NIL hanno altezza nera zero
        rbtNode_t *partenza = x;       // Nodo dal quale parto (livello dell'albero da cui parto)
        while (partenza != rbt->nil)   // Controllo altezza nera di sinistra
        {
            if (partenza->left->color == BLACK) // se il nodo che incontro è nero
            {
                altezzaNeraSinstra++;
                partenza = partenza->left;
            }
            else
                partenza = partenza->left;
        }
        partenza = x;                // Ritorno al livello del nodo corrente
        while (partenza != rbt->nil) // Controllo altezza nera di sinistra
        {
            if (partenza->right->color == BLACK) // se il nodo che incontro è nero
            {
                altezzaNeraDestra++;
                partenza = partenza->right;
            }
            else
                partenza = partenza->right;
        }
        if (altezzaNeraSinstra == altezzaNeraDestra)
            return altezzaNeraSinstra; // Devono essere uguali le altezza nere di destra e di sinistra
        else
            return -1; // Codice di errore
    }                  // fine if controllo validità dei puntatori
    else
    {
        fprintf(stderr, "rbtComputeBlackHeight: Errore puntatori NULL\n");
        exit(EXIT_FAILURE);
    }
} // fine rbtComputeBlackHeight

void rbtFreeNodes(rbt_t *T, rbtNode_t *x)
{
    if (T && x) // Controllo validità dei puntatori
    {
        if (x == T->nil)
            return;

        rbtFreeNodes(T, x->left);
        rbtFreeNodes(T, x->right);

        x->left = NULL; // Rendo invalidi i puntatori
        x->right = NULL;
        free(x); // Libero il nodo
        //free(rbt->nil); // Aggiunto questo pezzo
    }
    else
    {
        fprintf(stderr, "rbtFreeNodes: Errore puntatori NULL\n");
        exit(EXIT_FAILURE);
    } // fine rbtFreeNodes
}

void rbtFree(rbt_t *T)
{
    if (T) // Controllo validità puntatori
    {
        rbtFreeNodes(T, T->root); // Prima libero tutti i nodi ricorsivamente
        T->size = 0;              // Poi azzero la size
        T->root = NULL;           // Poi rendo invalidi i puntatori della struttura ad albero
        T->nil = NULL;
        free(T->nil);  // Libero il nodo rbt->nil
        free(T->root); // Libero il nodo rbt->root
    }
    else
    {
        fprintf(stderr, "rbtFree: Errore puntatori NULL\n");
        exit(EXIT_FAILURE);
    }
}

// End of RBT

// AUXILIARY FUNCTIONS

// funzione generateRandomArray spostata sul main. Ho spostato anche la funzione doExperiment

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

// IDEA: Usare array di nodi in cui mi salvo la visita in order e controllo se per tutti vale la proprietà
void inorderToArray(rbt_t *rbt, rbtNode_t *x, rbtNode_t **Nodi, int *i)
{
    if (rbt && x && Nodi && i)
    {
        if (x != rbt->nil)
        {
            inorderToArray(rbt, x->left, Nodi, i); // Richiamati ricorsivamente sul sotto-albero sinistro
            Nodi[(*i)++] = x;                      // Salva il risultato nel vettore di nodi
            /* ++(*i);
        Nodi[(*i)] = x; */
            inorderToArray(rbt, x->right, Nodi, i); // Richiamati ricorsivamente sul sotto-albero destro
        }
    }
    else
    {
        fprintf(stderr, "inorderToArray: Errore, puntatori NULL\n");
        exit(EXIT_FAILURE);
    }
} // fine inorderToArray
bool rbtProprieta_1(rbt_t *rbt) // 1. Ogni nodo è rosso o nero.
{
    if (rbt) // Controllo che il puntatore sia valido
    {
        rbtNode_t *Nodi[rbt->size];               // Dichiaro un array di nodi, tanti quanti ne contiene l'albero
        int i = 0;                                // Variabile per scorrere l'array di nodi
        inorderToArray(rbt, rbt->root, Nodi, &i); // Riempio con i nodi ordinati l'array di nodi Nodi.
        // TODO: L'indice lo passo per riferimento, altrimenti alla fine di ogni chiamata ricorsiva sarebbe verrebbe distrutto
        //e le modifiche non sarebbero permanenti

        for (i = 0; i < rbt->size; i++) // Controllo la proprietà per ogni elemento salvato nell'array Nodi
        {
            if ((Nodi[i]->color == RED) || (Nodi[i]->color == BLACK))
                continue; // Ok, passa al prossimo elemento del vettore di nodi
            else
                return false;
            /* printf("%d\n", Nodi[i]->value); */
        }
        // Ho controllato che ogni elemento del vettore (di nodi) rispetti la proprietà 1
        // Arrivato qui allora sono sicuro che tale proprietà sia rispettata
        return true;
    } // fine if controllo validità dei puntatori
    else
    {
        fprintf(stderr, "rbtProprieta_1: Puntatori NULL\n");
        exit(EXIT_FAILURE);
    } // fine else controllo validità dei puntatori
}
bool rbtProprieta_2(rbt_t *rbt) // 2. La radice è nera
{
    // Molto semplice
    if (rbt->root->color != BLACK)
    {
        fprintf(stderr, "isRbt: Violazione proprietà 2: La radice non è nera\n");
        return false;
    }
    else
        return true;
}
bool rbtProprieta_3(rbt_t *rbt) // 3. Ogni foglia (NIL) è nera
{
    if (rbt) // Se è valido
    {
        rbtNode_t *Nodi[rbt->size];               // Dichiaro un array di nodi, tanti quanti ne contiene l'albero
        int i = 0;                                // Variabile per scorrere l'array di nodi
        inorderToArray(rbt, rbt->root, Nodi, &i); // Riempio con i nodi ordinati l'array di nodi Nodi.

        for (i = 0; i < rbt->size; i++) // Controllo la proprietà per ogni nodo salvato nell'array Nodi
        {
            // Se un nodo punta da sinistra o da destra a T->Nil allora è una foglia
            if ((Nodi[i]->left == rbt->nil) || (Nodi[i]->right == rbt->nil))
            {
                // Controllo se vale a sinistra
                if ((Nodi[i]->left == rbt->nil) && (Nodi[i]->left->color != BLACK)) // Se è solo da sinistra (o anche da sinistra) allora deve essere nero per forza
                    return false;                                                   // Se non è nero, allora ritorna falso

                //Controllo se vale anche a destra
                if ((Nodi[i]->right == rbt->nil) && (Nodi[i]->right->color != BLACK)) // Se è solo da destra (o anche da destra) allora deve essere nero per forza
                    return false;                                                     // Se non è nero, allora ritorna falso
            }
            else          // Altrimenti, Se il nodo non è una foglia che punta a T.Nil
                continue; // Passa al prossimo elemento per vedere se è un nodo foglia che punta a T.Nil

        } // Fine for

        // Ho controllato che ogni elemento del vettore (di nodi) rispetti la proprietà 3.
        // Arrivato qui, allora sono sicuro che tale proprietà sia rispettata.
        return true;
    } // Fine if controllo validità dei puntatori
    else
    {
        fprintf(stderr, "rbtProprieta_3: Puntatori NULL\n");
        exit(EXIT_FAILURE);
    } // fine else controllo validità dei puntatori
}
bool rbtProprieta_4(rbt_t *rbt) // 4. Se un nodo è rosso, allora entrambi i suoi figli sono neri
{
    if (rbt)
    {
        rbtNode_t *Nodi[rbt->size];               // Dichiaro un array di nodi, tanti quanti ne contiene l'albero
        int i = 0;                                // Variabile per scorrere l'array di nodi
        inorderToArray(rbt, rbt->root, Nodi, &i); // Riempio con i nodi ordinati l'array di nodi Nodi

        for (i = 0; i < rbt->size; i++) // Controllo la proprietà per ogni nodo salvato nell'array Nodi
        {
            if ((Nodi[i]->color == RED)) // Se un nodo è rosso
            {
                if ((Nodi[i]->left->color == BLACK) && (Nodi[i]->right->color == BLACK)) // Allora entrambi i suoi figli devono essere neri
                    continue;                                                            // Ok, per questo nodo è rispettata la proprietà
                else                                                                     // Altrimenti, se entrambi i suoi figli non sono neri
                    return false;                                                        // Proprietà non rispettata, Allora ritorna falso
            }
            else          // Altrimenti se il nodo non è rosso
                continue; // Passa al prossimo elemento del vettore
        }                 // fine for

        // Ho controllato che ogni elemento del vettore (di nodi) rispetti la proprietà 4
        // Arrivato qui allora sono sicuro che tale proprietà sia rispettata
        return true;
    } // Fine if controllo validità dei puntatori
    else
    {
        fprintf(stderr, "rbtProprieta_4: Puntatori NULL\n");
        exit(EXIT_FAILURE);
    } // fine else controllo validità dei puntatori
}
bool rbtProprieta_5(rbt_t *rbt) // 5. Per ogni nodo, tutti i cammini semplici che vanno dal nodo alle foglie sue discendenti contengono lo stesso numero di nodi neri.
{
    if (rbt) // Se è valido
    {
        rbtNode_t *Nodi[rbt->size];               // Dichiaro un array di nodi, tanti quanti ne contiene l'albero
        int i = 0;                                // Variabile per scorrere l'array di nodi
        inorderToArray(rbt, rbt->root, Nodi, &i); // Riempio con i nodi ordinati l'array di nodi: 'Nodi'
        // int contaNeriLeft, contaNeriRight = 0;    // Contatori di nodi neri a sinistra e a destra

        for (i = 0; i < rbt->size; i++) // Controllo la proprietà per ogni nodo salvato nell'array Nodi
        {
            int res = contaNeri(rbt, Nodi[i]); // Verifico se vale per l'i-esimo nodo
            if (res == 0)
                return false;
        } // Fine for
        // Ho controllato che ogni elemento del vettore (di nodi) rispetti la proprietà 3
        // Arrivato qui allora sono sicuro che tale proprietà sia rispettata SE:
        return true;
    } // Fine if controllo validità dei puntatori
    else
    {
        fprintf(stderr, "rbtProprieta_5: Puntatori NULL\n");
        exit(EXIT_FAILURE);
    } // fine else controllo validità dei puntatori
}
void clearScreen() // Procedura POSIX dell'analogo comando 'clear'
{
    const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
    write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}
rbtNode_t *rbtMinimum(rbt_t *rbt) // Ricerca del minimo
{
    if (rbt) // Controllo validità dei puntatori
    {
        rbtNode_t *x = rbt->root;
        while (x->left != rbt->nil)
            x = x->left;
        return x;
    }
    else
    {
        fprintf(stderr, "rbtMinimum: Errore, puntatori NULL\n");
        exit(EXIT_FAILURE);
    }

} // fine rbtMinimum
rbtNode_t *rbtMaximum(rbt_t *rbt) // Ricerca del massimo
{
    if (rbt) // Controllo validità dei puntatori
    {
        rbtNode_t *x = rbt->root;
        while (x->right != rbt->nil)
            x = x->right;
        return x;
    }
    else
    {
        fprintf(stderr, "rbtMaximum: Errore, puntatori NULL\n");
        exit(EXIT_FAILURE);
    }
}
int contaNeri(rbt_t *rbt, rbtNode_t *x)
{
    if (rbt && x)
    {
        if (x == rbt->nil) // Caso base
            return 1;

        int contaNeriSinistra = contaNeri(rbt, x->left);
        if (contaNeriSinistra == 0)
            return contaNeriSinistra;

        int contaNeriDestra = contaNeri(rbt, x->right);
        if (contaNeriDestra == 0)
            return contaNeriDestra;

        if (contaNeriSinistra != contaNeriDestra) // Il numero deve essere lo stesso a sx e a dx
            return 0;
        else
        {
            if (x->color == BLACK)
                return contaNeriSinistra + 1;
            else
                return contaNeriSinistra + 0;
        }
    }
    else
    {
        fprintf(stderr, "contaNeri: Errore, puntatori NULL\n");
        exit(EXIT_FAILURE);
    }

} // fine contaNeri
void rbtPreOrder(rbt_t *rbt, rbtNode_t *x) // Visita PreOrder
{
    if (x != rbt->nil)
    {
        printf("Nodo:\t%d\tcolore:\t%c\n", x->value, (x->color == RED) ? 'R' : 'B');
        rbtPreOrder(rbt, x->left);
        rbtPreOrder(rbt, x->right);
    }
}
void rbtPostOrder(rbt_t *rbt, rbtNode_t *x) // Visit PostOrder
{
    if (x != rbt->nil)
    {
        rbtPostOrder(rbt, x->left);
        rbtPostOrder(rbt, x->right);
        printf("Nodo:\t%d\tcolore:\t%c\n", x->value, (x->color == RED) ? 'R' : 'B');
    }
}
void stampaAltezzaNeraInorder(rbt_t *rbt, rbtNode_t *x) // Stampa altezza nera di ogni nodo con visita InOrder
{
    if (x != rbt->nil)
    {
        stampaAltezzaNeraInorder(rbt, x->left);
        printf("Nodo:\t%d\tcolore:\t%c\tAltezza Nera:\t%d\n", x->value, (x->color == RED) ? 'R' : 'B', rbtComputeBlackHeight(rbt, x));
        stampaAltezzaNeraInorder(rbt, x->right);
    }
}
void stampaAltezzaNeraPostOrder(rbt_t *rbt, rbtNode_t *x) // Stampa altezza nera di ogni nodo con visita PostOrder
{
    if (x != rbt->nil)
    {
        stampaAltezzaNeraPostOrder(rbt, x->left);
        stampaAltezzaNeraPostOrder(rbt, x->right);
        printf("Nodo:\t%d\tcolore:\t%c\tAltezza Nera:\t%d\n", x->value, (x->color == RED) ? 'R' : 'B', rbtComputeBlackHeight(rbt, x));
    }
}
void stampaAltezzaNeraPreOrder(rbt_t *rbt, rbtNode_t *x) // Stampa altezza nera di ogni nodo con visita PreOrder
{
    if (x != rbt->nil)
    {
        printf("Nodo:\t%d\tcolore:\t%c\tAltezza Nera:\t%d\n", x->value, (x->color == RED) ? 'R' : 'B', rbtComputeBlackHeight(rbt, x));
        stampaAltezzaNeraPreOrder(rbt, x->left);
        stampaAltezzaNeraPreOrder(rbt, x->right);
    }
}
int rbtComputeBlackHeightRicorsiva(rbt_t *rbt, rbtNode_t *x) // !!! Pare non funzionare !!!
{
    if (rbt && x) // Controllo validità dei puntatori
    {
        if (x == rbt->nil) // L'altezza nera dei nodi T->NIL è sempre 0
            return 0;
        /* if (x == rbt->nil || x->color == RED)
        return 1; */

        int altezzaNeraSinstra = rbtComputeBlackHeightRicorsiva(rbt, x->left); // Mi richiamo ricorsivamente sulla parte sinistra
        int altezzaNeraDestra = rbtComputeBlackHeightRicorsiva(rbt, x->right); // e destra (il calcolo lo fanno le chiamate ricorsive)

        int contatore = 0; // andrà sommato ad una delle due altezze nere
        if (x->color == BLACK)
            contatore++;
        else
            contatore = 0;
        // La correttezza vuole che a sinistra e a destra io abbia lo stesso numero di nodi neri
        if (altezzaNeraSinstra == -1 || altezzaNeraDestra == -1 || altezzaNeraSinstra != altezzaNeraDestra)
            return -1;
        else
            return altezzaNeraSinstra + contatore;
    }
    else
    {
        fprintf(stderr, "rbtComputeBlackHeightRicorsiva: errore Puntatori NULL\n");
        exit(EXIT_FAILURE);
    }
} // fine rbtComputeBlackHeightRicorsiva
bool rbtHasBstProperty_Iterativa(rbt_t *rbt) // !!!Non propriamente corretta !!!
{
    rbtNode_t *min = rbtMinimum(rbt); // Salvo il nodo minimo
    rbtNode_t *max = rbtMaximum(rbt); // Salvo il nodo massimo
    rbtNode_t *nodo = rbt->root;
    while ((nodo != rbt->nil)) // Verifico da sinistra
    {
        if (nodo->value < min->value)
            return false;
        nodo = nodo->left;
    }
    nodo = rbt->root;        // Resetto il nodo
    while (nodo != rbt->nil) // Verifico da destra
    {
        if (nodo->value > max->value)
            return false;
        nodo = nodo->right;
    }
    return true;
}
// End of AUXILIARY FUNCTIONS

// Fine IMPLEMENTATION OF THE FUNCTIONS

// Aggiungo funzione ricerca ricorsiva allo scopo di verificare se è questa l'operazione che rallenta
rbtNode_t *rbtSearchRicorsiva(rbt_t *rbt, rbtNode_t *x, const int v)
{
    if (x == rbt->nil || v == x->value)
        return x;
    if (v < x->value)
        return rbtSearchRicorsiva(rbt, x->left, v);
    else
        return rbtSearchRicorsiva(rbt, x->right, v);
}