# Algoritmi e Strutture Dati

In questo repository sono presenti i sorgenti dell'esercizio 2 di ASD a.a. 2020/2021.
L'esercizio consiste nel confrontare sperimentalmente, per input crescenti e casuali (uniformemente distribuiti) le operazioni di dizionario, eccetto l'eliminazione, che offrono le due strutture dati Hash Table e Red Black Tree.

In particolare, in questo repository si trovano le implementazioni di:

- Liste doppiamente concatenate.
- Hash Tables con conflitti risolti via chaining.
- Alberi Rosso Neri.

# Specifiche di progetto esercizio 2 algoritmi e strutture dati

Ho separato il codice in 4 file principali che servono per gestire l'esericizio:

- main.c: contenente il programma da cui far partire l'esercizio.
- esercizio2.c:       contenente la definizione delle funzioni richieste (eccetto le quelle di "test") ed altre mie funzioni aggiuntive.
- esercizio2.h:       contenente la dichiarazione di tali funzioni; sono presenti anche le definizioni dei tipi rappresentanti le strutture dati utilizzate.
- testHashTable.c:    contenente la definizione della funzione "hashtableTest".
- testRedBlackTree.c: contenente la definizione della funzione "rbtTest".
- Makefile: contenente istruzioni per la compilazione ed il linking. Genera un eseguibile di nome "Esercizio2".

Gli altri file:

- listeCollegate.c
- hashTable.c
- rbt.c

contengono degli esempi di test per la verifica del corretto funzionamento degli algoritmi da applicare alle due strutture dati, tradotti in programmi.
In particolare, nel file 'Esecuzione_e_Memcheck_con_Valgrind.txt' sono presenti 3 esempi di esecuzione, rispettivamente per: liste concatenate, tabelle hash ed alberi rosso neri.
Ogni esecuzione è accompagnata dal "memcheck" effettuato da valgrid, presente nel file "Esecuzione_e_Memcheck_con_Valgrind", allo scopo di assicurarmi di non aver commesso "memory leaks".

# Compilazione
Per compilare, effettuare il linking, dunque ottenere il file eseguibile, digitare il comando: `make` 

