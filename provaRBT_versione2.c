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

// CREAZIONE
rbtNode_t *createRbtNode(int data)
{
    rbtNode_t *n = malloc(sizeof(rbtNode_t));
    n->left = NULL;
    n->right = NULL;
    n->parent = NULL;
    n->value = data;
    n->color = RED;

    return n;
}

rbt_t *createRbt()
{
    rbt_t *t = malloc(sizeof(rbt_t));
    rbtNode_t *nil_node = malloc(sizeof(rbtNode_t));
    nil_node->left = NULL;
    nil_node->right = NULL;
    nil_node->parent = NULL;
    nil_node->color = BLACK;
    nil_node->value = 0;
    t->nil = nil_node;
    t->root = t->nil;

    return t;
}

// INSERIMENTO
void rbtLeftRotate(rbt_t *t, rbtNode_t *x)
{
    rbtNode_t *y = x->right;
    x->right = y->left;
    if (y->left != t->nil)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == t->nil)
    { //x is root
        t->root = y;
    }
    else if (x == x->parent->left)
    { //x is left child
        x->parent->left = y;
    }
    else
    { //x is right child
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void rbtRightRotate(rbt_t *t, rbtNode_t *x)
{
    rbtNode_t *y = x->left;
    x->left = y->right;
    if (y->right != t->nil)
    {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == t->nil)
    { //x is root
        t->root = y;
    }
    else if (x == x->parent->right)
    { //x is left child
        x->parent->right = y;
    }
    else
    { //x is right child
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

/*
void rbtInsertFixupLeft(rbt_t *rbt, rbtNode_t *z)
{

    rbtNode_t *y = z->parent->parent->right; //uncle of z

    if (y->color == RED)
    { //case 1
        z->parent->color = BLACK;
        y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
    }
    else
    { //case2 or case3
        if (z == z->parent->right)
        {                  //case2
            z = z->parent; //marked z.parent as new z
            rbtLeftRotate(rbt, z);
        }
        //case3
        z->parent->color = BLACK;         //made parent black
        z->parent->parent->color = BLACK; //made parent red
        rbtRightRotate(rbt, z->parent->parent);
    }
}

void rbtInsertFixupRight(rbt_t *rbt, rbtNode_t *z) // Con queste non funzionano i colori
{
    rbtNode_t *y = z->parent->parent->left; //uncle of z

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
            z = z->parent; //marked z.parent as new z
            rbtRightRotate(rbt, z);
        }
        z->parent->color = BLACK;       //made parent black
        z->parent->parent->color = RED; //made parent red
        rbtLeftRotate(rbt, z->parent->parent);
    }
}

void rbtInsertFixup(rbt_t *rbt, rbtNode_t *z)
{
    while (z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left) //z.parent is the left child
            rbtInsertFixupLeft(rbt, z);
        else
            rbtInsertFixupRight(rbt, z); //z.parent is the right child
    }
    rbt->root->color = BLACK;
}
*/
void rbtInsertFixup(rbt_t *rbt, rbtNode_t *z) // Con questa funziona perfettamente
{
    while (z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        { //z.parent is the left child

            rbtNode_t *y = z->parent->parent->right; //uncle of z

            if (y->color == RED)
            { //case 1
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            { //case2 or case3
                if (z == z->parent->right)
                {                  //case2
                    z = z->parent; //marked z.parent as new z
                    rbtLeftRotate(rbt, z);
                }
                //case3
                z->parent->color = BLACK;       //made parent black
                z->parent->parent->color = RED; //made parent red
                rbtRightRotate(rbt, z->parent->parent);
            }
        }
        else
        {                                           //z.parent is the right child
            rbtNode_t *y = z->parent->parent->left; //uncle of z

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
                    z = z->parent; //marked z.parent as new z
                    rbtRightRotate(rbt, z);
                }
                z->parent->color = BLACK;       //made parent black
                z->parent->parent->color = RED; //made parent red
                rbtLeftRotate(rbt, z->parent->parent);
            }
        }
    }
    rbt->root->color = BLACK;
}

void rbtInsert(rbt_t *rbt, rbtNode_t *z)
{
    rbtNode_t *y = rbt->nil; //variable for the parent of the added node
    rbtNode_t *x = rbt->root;

    while (x != rbt->nil)
    {
        y = x;
        if (z->value < x->value)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;

    if (y == rbt->nil)
    { //newly added node is root
        rbt->root = z;
    }
    else if (z->value < y->value) //data of child is less than its parent, left child
        y->left = z;
    else
        y->right = z;

    z->right = rbt->nil;
    z->left = rbt->nil;
    z->color = RED; // MODIFICATO QUA
    rbtInsertFixup(rbt, z);

    rbt->size++; // mi serve incrementare la dimensione dell'albero per ogni nuovo nodo inserito
}

/* void inorder(rbt_t *t, rbtNode_t *n) // MODIFICA QUA
{
    if (n != t->nil)
    {
        inorder(t, n->left);
        printf("%d\n", n->data);
        inorder(t, n->right);
    }
} */

void rbtInOrder(rbt_t *rbt, rbtNode_t *x) // Visita InOrder
{
    if (x != rbt->nil)
    {
        rbtInOrder(rbt, x->left);
        printf("Nodo:\t%d\tcolore:\t%c\n", x->value, (x->color == RED) ? 'R' : 'B');
        rbtInOrder(rbt, x->right);
    }
}

// FUNZIONE DI RICERCA
// RICERCA
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
}

// FUNZIONI PER DEALLOCARE LA MEMORIA PER I NODI E PER L'ALBERO
void rbtFreeNodes(rbt_t *rbt, rbtNode_t *x)
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
void rbtFree(rbt_t *rbt)
{
    rbtFreeNodes(rbt, rbt->root); // Prima libero tutti i nodi ricorsivamente
    rbt->size = 0;                // Poi azzero la size
    rbt->root = NULL;             // Poi rendo invalidi i puntatori della struttura ad albero
    rbt->nil = NULL;
    free(rbt->nil);  // Libero il nodo rbt->nil
    free(rbt->root); // Libero il nodo rbt->root
}

// FUNZIONI AUSILIARIE
void clearScreen() // Procedura POSIX dell'analogo comando 'clear'
{
    const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
    write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}
rbtNode_t *rbtMinimum(rbt_t *rbt) // Ricerca del minimo
{
    rbtNode_t *x = rbt->root;
    while (x->left != rbt->nil)
        x = x->left;
    return x;
}
rbtNode_t *rbtMaximum(rbt_t *rbt) // Ricerca del massimo
{
    rbtNode_t *x = rbt->root;
    while (x->right != rbt->nil)
        x = x->right;
    return x;
}
int contaNeri(rbt_t *rbt, rbtNode_t *x)
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
// CALCOLO DELL'ALTEZZA NERA
/**
 * @brief Function that computes the black height of the RBT.
 * @param rbt The RBT.
 * @param x Current RBT node.
 * @return Black height if all paths have the same black height; otherwise, -1.
 */
int rbtComputeBlackHeightRicorsiva(rbt_t *rbt, rbtNode_t *x)
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

// ALTEZZA NERA ITERATIVA (ESAMINO SOLO DUE RAMI)
int rbtComputeBlackHeight /* _Iterativa */ (rbt_t *rbt, rbtNode_t *x) // Calcolo dell'altezza nera di un dato nodo x dell'rbt
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

// FUNZIONI PROPRIETÀ BST-RBT
//
/**
 * @brief Utilissima funzione la cui costruzione è ispirata dalla visita inOrder
 * @param rbt The RBT.
 * @param x Current RBT node.
 * @param Nodi Vettore di nodi su cui salvare i nodi incontrati durante la visita
 * @param i puntatore all'indice per tenere traccia del percorso
 */
void inorderToArray(rbt_t *rbt, rbtNode_t *x, rbtNode_t **Nodi, int *i)
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

bool rbtHasBstProperty_Iterativa(rbt_t *rbt)
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
    /* for (i = 0; i < rbt->size; i++)
    {
        // Se il nodo corrente è maggiore del suo figlio sinistro e minore o uguale al suo figlio destro
        //if ((Nodi[i]->value > Nodi[i]->left->value) && (Nodi[i]->value <= Nodi[i]->right->value))
        if (i + 1 == rbt->size)
            break;
        else
        {
            if (Nodi[i]->value < Nodi[i + 1]->value)
            {
                continue; // Allora ok, il sottoalbero formato da: nodo corrente, figlio sx del nodo corrente e
            }             // figlio dx del nodo corrente sta rispettando la Proprietà BST
            else
                return false;
        }
    } */
    // int max = Nodi[rbt->size];
    // Parto dall'ultimo e arrivo al primo --> Prova modifica
    if (Nodi[rbt->size]->value < Nodi[rbt->size - 1]->value) // Confronto l'ultimo col penultimo
        return false;                                        // Falso, perchè l'ultimo elemento dell'array deve essere maggiore del penultimo

    while ((i + 1 != rbt->size) && (Nodi[i + 1]->value > Nodi[i]->value))
    {
        /* if (!(Nodi[rbt->size]->value > Nodi[i]->value && i < rbt->size))
            return false; */
        i++;
        continue;
    }
    // Arrivato qui, ho soddisfatto la Proprietà BST
    return true;
}

// IDEA: Usare array di nodi in cui mi salvo la visita in order e controllo se per tutti vale la proprietà
bool rbtProprieta_1(rbt_t *rbt) // 1. Ogni nodo è rosso o nero.
{
    if (rbt)
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
        int contaNeriLeft, contaNeriRight = 0;    // Contatori di nodi neri a sinistra e a destra

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
{ // Provare con switch
    // 1. Ogni nodo è rosso o nero.
    bool p1 = rbtProprieta_1(rbt);
    // 2. La radice è nera
    bool p2 = rbtProprieta_2(rbt);
    // 3. Ogni foglia (NIL) è nera
    bool p3 = rbtProprieta_3;
    // 4. Se un nodo è rosso, allora entrambi i suoi figli sono neri
    bool p4 = rbtProprieta_4(rbt);
    // 5. Per ogni nodo, tutti i cammini semplici che vanno dal nodo alle foglie sue
    //    discendenti contengono lo stesso numero di nodi neri
    bool p5 = rbtProprieta_5(rbt);

    bool pbst = rbtHasBstProperty(rbt);
    if (pbst && p1 && p2 && p3 && p4 && p5) // and logico di tutte le proprietà
        return true;
    else
        return false;
}

int main()
{
    /* rbt_t *t = createRbt();

    rbtNode_t *a, *b, *c, *d, *e, *f, *g, *h, *i, *j, *k, *l, *m;
    a = createRbtNode(10);
    b = createRbtNode(20);
    c = createRbtNode(30);
    d = createRbtNode(100);
    e = createRbtNode(90);
    f = createRbtNode(40);
    g = createRbtNode(50);
    h = createRbtNode(60);
    i = createRbtNode(70);
    j = createRbtNode(80);
    k = createRbtNode(150);
    l = createRbtNode(110);
    m = createRbtNode(120);

    rbtInsert(t, a);
    rbtInsert(t, b);
    rbtInsert(t, c);
    rbtInsert(t, d);
    rbtInsert(t, e);
    rbtInsert(t, f);
    rbtInsert(t, g);
    rbtInsert(t, h);
    rbtInsert(t, i);
    rbtInsert(t, j);
    rbtInsert(t, k);
    rbtInsert(t, l);
    rbtInsert(t, m);

    inorder(t, t->root); */

    clearScreen(); // Ripulisco il terminale dai warnings
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
    //printf("\n");
    trovato = rbtSearch(T, chiave); // Versione iterativa (quella ricorsiva non mi veniva)
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
    free(T);
    if ((T->root == NULL) && (T->nil == NULL)) // Ok non ci sono più memory leaks
        printf("Ripulito completamente\n");
    else
        printf("C'è qualche altro nodo da ripulire\n");
    return 0;
}
