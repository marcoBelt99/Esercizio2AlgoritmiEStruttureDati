#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define RED 'R'
#define BLACK 'B'

typedef struct rbtNode_t
{
    struct rbtNode_t *right;
    struct rbtNode_t *left;
    struct rbtNode_t *parent;
    int value;
    char color;
} rbtNode_t;

typedef struct rbt_t
{
    rbtNode_t *root;
    rbtNode_t *nil;
    int size; //MODIFICATO QUI
} rbt_t;

// ******************* DICHIARAZIONE FUNZIONI *******************
rbtNode_t *createRbtNode(const int);
rbt_t *createRbt();
void rbtLeftRotate(rbt_t *, rbtNode_t *);
void rbtRightRotate(rbt_t *, rbtNode_t *);
void rbtInsert(rbt_t *, rbtNode_t *);
void rbtInsertFixup(rbt_t *, rbtNode_t *);
rbtNode_t *rbtSearch(rbt_t *, const int);
/**
* @brief Ricerca Ricorsiva in un RBT: la faccio per vedere se è questa la causa di mal-funzionamento
* @param rbt albero in cui effettuare la ricerca
* @param x radice del sottoalbero in cui richiamarsi
* @param v chiave da ricercare 
*/
rbtNode_t *rbtSearchRicorsiva(rbt_t *, rbtNode_t *, const int);
void rbtInOrder(rbt_t *, rbtNode_t *);
bool rbtTest();
bool isRbt(rbt_t *);
bool rbtHasBstProperty(rbt_t *);
int rbtComputeBlackHeight(rbt_t *, rbtNode_t *);
void rbtFreeNodes(rbt_t *, rbtNode_t *);
void rbtFree(rbt_t *);
//Dichiarazione funzioni Ausiliarie
void stampaAltezzaNeraPreOrder(rbt_t *rbt, rbtNode_t *x);
void inorderToArray(rbt_t *rbt, rbtNode_t *x, rbtNode_t **Nodi, int *i);
void clearScreen();
rbtNode_t *rbtMinimum(rbt_t *rbt);
rbtNode_t *rbtMaximum(rbt_t *rbt);
int contaNeri(rbt_t *rbt, rbtNode_t *x);
void rbtPreOrder(rbt_t *rbt, rbtNode_t *x);
void rbtPostOrder(rbt_t *rbt, rbtNode_t *x);
void stampaAltezzaNeraInorder(rbt_t *rbt, rbtNode_t *x);
void stampaAltezzaNeraPostOrder(rbt_t *rbt, rbtNode_t *x);
bool rbtProprieta_1(rbt_t *rbt);
bool rbtProprieta_2(rbt_t *rbt);
bool rbtProprieta_3(rbt_t *rbt);
bool rbtProprieta_4(rbt_t *rbt);
bool rbtProprieta_5(rbt_t *rbt);

// ******************* MAIN *******************
int main()
{
    // clearScreen(); // Ripulisco il terminale
    // Creazione
    rbt_t *T = createRbt();                                                                   // Creo l'rbt nello HEAP
    int A[] = {26, 17, 41, 14, 21, 30, 47, 10, 16, 19, 23, 28, 38, 7, 12, 15, 20, 35, 39, 3}; // Vettore contente i valore dei nodi che creerò ed inserirò
    int chiave;                                                                               // Mi servirà per verificare la Ricerca

    for (int i = 0; i < 20; i++) // Creo nello HEAP 20 nodi e li Inserisco opportunamente nell'rbt T
        rbtInsert(T, createRbtNode(A[i]));
    printf("\n******************** RBT INSERT ********************\n");

    printf("\nVisita IN-ORDER\n");
    rbtInOrder(T, T->root);

    // Stampo la dimensione dell'albero
    printf("\nDimensione dell'albero:\t%d\n", T->size);
    // e le informazioni sulla sua radice, come ulteriore sicurezza di correttezza
    printf("Radice: %d di colore: %c\n", T->root->value, T->root->color);
    if (T->root->parent == T->nil)
        printf("Il Padre della radice è T->nil\n");
    else
        printf("Il Padre della radice NON è T->nil\n");
    sleep(1);

    // Mi occupo della Ricerca
    printf("\n******************** RBT SEARCH ********************\n");
    rbtNode_t *trovato = T->nil;               // Questo nodo conterrà il risultao della Ricerca
    printf("Inserire il valore da cercare: "); // Richiedo il valore da cercare all'utente
    scanf("%d", &chiave);

    // trovato = rbtSearch(T, chiave); // Versione iterativa (quella ricorsiva non mi veniva)
    trovato = rbtSearchRicorsiva(T, T->root, chiave); // Provo questa versione
    if (trovato->value == chiave)
        printf("Trovato\n");
    else
        printf("Non trovato\n");
    sleep(1);

    // Verifico per ulteriore sicurezza se l'albero effettivamente ha i propri minimo e massimo,
    // rispettivamente all'estrema sinistra ed all'estrema destra
    rbtNode_t *minimo, *massimo = T->nil;
    printf("\n******************** MINIMO-MASSIMO ********************\n");
    minimo = rbtMinimum(T);
    massimo = rbtMaximum(T);
    printf("Il nodo minimo vale: %d\n", minimo->value);
    printf("Il nodo massimo vale: %d\n", massimo->value);
    sleep(1);

    // Mi occupo di verificare l'Altezza Nera di ogni nodo, attraverso un attraversamento preOreder (risultante più comodo)
    printf("\n******************** ALTEZZA ALBERO ********************\n");
    printf("Visualizzo altezza albero (visitandolo in PreOrder):\n");
    stampaAltezzaNeraPreOrder(T, T->root); // Perfezionamento della funzione di attraversamento preOrder
    sleep(1);

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
    }

    if (isRbt(T) == true)
        printf("\nTutte le proprietà sono valide\n");
    else
        printf("\nErrore in una della proprietà\n");

    // A questo punto, Libero la memoria allocata precedentemente con la malloc in fase di creazione
    rbtFree(T);

    if ((T->root == NULL) && (T->nil == NULL)) // Ok non ci sono più memory leaks
        printf("Ripulito completamente\n");
    else
        printf("C'è qualche altro nodo da ripulire\n");
    printf("Dimensione in memoria di un nodo: %ld\n", sizeof(rbtNode_t));
    printf("Dimensione in memoria di un albero: %ld\n", sizeof(rbt_t));
    free(T); // Libero la memoria dell'albero
    return 0;
}

// ******************* DEFINIZIONE FUNZIONI *******************
// Creazione
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

// Inserimento
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
void rbtRightRotate(rbt_t *rbt, rbtNode_t *x) // Basta scambiare left con right
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
/* void rbtInsertFixupLeft(rbt_t *rbt, rbtNode_t *z) // !!! Versione fixup left-right Non corretta... !!!
{

    rbtNode_t *y = z->parent->parent->right; 

    if (y->color == RED)
    { 
        z->parent->color = BLACK;
        y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
    }
    else
    { 
        if (z == z->parent->right)
        {                  
            z = z->parent; 
            rbtLeftRotate(rbt, z);
        }
        
        z->parent->color = BLACK;         
        z->parent->parent->color = BLACK; 
        rbtRightRotate(rbt, z->parent->parent);
    }
}

void rbtInsertFixupRight(rbt_t *rbt, rbtNode_t *z) // Con queste non funzionano i colori
{
    rbtNode_t *y = z->parent->parent->left; 

    if (y->color == RED)
    {
        z->parent->color = BLACK;
        y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
    }
    else
    {
        if (z == z->parent->left)
        {
            z = z->parent; 
            rbtRightRotate(rbt, z);
        }
        z->parent->color = BLACK;       
        z->parent->parent->color = RED; 
        rbtLeftRotate(rbt, z->parent->parent);
    }
}

void rbtInsertFixup(rbt_t *rbt, rbtNode_t *z)
{
    while (z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left) 
            rbtInsertFixupLeft(rbt, z);
        else
            rbtInsertFixupRight(rbt, z); 
    }
    rbt->root->color = BLACK;
}
*/
void rbtInsertFixup(rbt_t *rbt, rbtNode_t *z) // Con questa funziona perfettamente
{
    if (rbt && z) // Controllo validità puntatori
    {
        while (z->parent->color == RED)
        {
            if (z->parent == z->parent->parent->left)
            {

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

// Visita
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

// Ricerca
rbtNode_t *rbtSearch(rbt_t *T, const int v) // Ho seguito l'algoritmo non ricorsivo presente sul libro di testo "Cormen".
{
    if (T) // Se T è un puntatore valido
    {
        rbtNode_t *x = T->root; // Mi salvo la radice in x, così non modifico strutturalmente l'albero (Evito di muovere il puntatore T di tipo rbt)
        while ((x != T->nil) && (v != x->value))
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

// Altezza nera
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
int rbtComputeBlackHeight /* _Iterativa */ (rbt_t *rbt, rbtNode_t *x) // Calcolo dell'altezza nera di un dato nodo x dell'rbt
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
void stampaAltezzaNeraPreOrder(rbt_t *rbt, rbtNode_t *x) // Stampa altezza nera di ogni nodo con visita PreOrder
{
    if (x != rbt->nil)
    {
        printf("Nodo:\t%d\tcolore:\t%c\tAltezza Nera:\t%d\n", x->value, (x->color == RED) ? 'R' : 'B', rbtComputeBlackHeight(rbt, x));
        stampaAltezzaNeraPreOrder(rbt, x->left);
        stampaAltezzaNeraPreOrder(rbt, x->right);
    }
}

// Funzioni ausiliarie e propedeutiche per vedere le proprietà dell'albero
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

// IDEA: Usare array di nodi in cui mi salvo la visita in order e controllo se per tutti vale la proprietà
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

// Funzioni ausiliarie
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
        /* return contaNeriSinistra + ((x->color == BLACK) ? 1 : 0); */
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

// Deallocazione memoria precedentemente allocata per nodi e albero
void rbtFreeNodes(rbt_t *rbt, rbtNode_t *x)
{
    if (rbt && x) // Controllo validità dei puntatori
    {
        if (x == rbt->nil)
            return;

        rbtFreeNodes(rbt, x->left);
        rbtFreeNodes(rbt, x->right);

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
void rbtFree(rbt_t *rbt)
{
    if (rbt) // Controllo validità puntatori
    {
        rbtFreeNodes(rbt, rbt->root); // Prima libero tutti i nodi ricorsivamente
        rbt->size = 0;                // Poi azzero la size
        rbt->root = NULL;             // Poi rendo invalidi i puntatori della struttura ad albero
        rbt->nil = NULL;
        free(rbt->nil);  // Libero il nodo rbt->nil
        free(rbt->root); // Libero il nodo rbt->root
    }
    else
    {
        fprintf(stderr, "rbtFree: Errore puntatori NULL\n");
        exit(EXIT_FAILURE);
    }
}

rbtNode_t *rbtSearchRicorsiva(rbt_t *rbt, rbtNode_t *x, const int v)
{
    if (x == rbt->nil || v == x->value)
        return x;
    if (v < x->value)
        return rbtSearchRicorsiva(rbt, x->left, v);
    else
        return rbtSearchRicorsiva(rbt, x->right, v);
}