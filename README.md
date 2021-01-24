# Algoritmi e Strutture Dati

In questo repository sono presenti i sorgenti dell'esercizio 2 di ASD a.a. 2020/2021.
L'esercizio consiste nel confrontare sperimentalmente, per input crescenti e casuali (uniformemente distribuiti) le operazioni di dizionario, eccetto l'eliminazione, che offrono le due strutture dati Hash Table e Red Black Tree.

In particolare, in questo repository si trovano le implementazioni di:

- Liste doppiamente concatenate.
- Hash Tables con conflitti risolti via chaining.
- Alberi Rosso Neri.

# Specifiche di progetto esercizio 2 algoritmi e strutture dati

Ho separato il codice in 4 file principali che servono per gestire l'esericizio:

- [main.c](): contenente il programma da cui far partire l'esercizio.
- [sercizio2.c](https://github.com/marcoBelt99/Algoritmi_e_Strutture_Dati/blob/main/esercizio2.c):       contenente la definizione delle funzioni richieste (eccetto quelle di test: "hashtableTest" e "rbtTest") ed altre mie funzioni aggiuntive.
- [esercizio2.h](https://github.com/marcoBelt99/Algoritmi_e_Strutture_Dati/blob/main/esercizio2.h):       contenente la dichiarazione di tali funzioni; sono presenti anche le definizioni dei tipi rappresentanti le strutture dati utilizzate.
- [testHashTable.c](https://github.com/marcoBelt99/Algoritmi_e_Strutture_Dati/blob/main/testHashTable.c):    contenente la definizione della funzione "hashtableTest".
- [testRedBlackTree.c](https://github.com/marcoBelt99/Algoritmi_e_Strutture_Dati/blob/main/testRedBlackTree.c): contenente la definizione della funzione "rbtTest".
- [Makefile](https://github.com/marcoBelt99/Algoritmi_e_Strutture_Dati/blob/main/Makefile): contenente istruzioni per la compilazione ed il linking. Genera un eseguibile di nome "Esercizio2".

Gli altri file:

- [listeCollegate.c](https://github.com/marcoBelt99/Algoritmi_e_Strutture_Dati/blob/main/listeCollegate.c)
- [hashTable.c](https://github.com/marcoBelt99/Algoritmi_e_Strutture_Dati/blob/main/hashTable.c)
- [rbt.c](https://github.com/marcoBelt99/Algoritmi_e_Strutture_Dati/blob/main/rbt.c)

contengono degli esempi di test per la verifica del corretto funzionamento degli algoritmi da applicare alle due strutture dati, tradotti in programmi.
In particolare, nel file [Esecuzione_e_Memcheck_con_Valgrind.txt](https://github.com/marcoBelt99/Algoritmi_e_Strutture_Dati/blob/main/Esecuzione_e_Memcheck_con_Valgrind.txt) sono presenti 3 esempi di esecuzione, rispettivamente per: liste concatenate, tabelle hash ed alberi rosso neri.
Ogni esecuzione è accompagnata dal "memcheck" effettuato da valgrid, avente lo scopo di assicurare la corretta gestione della memoria, evitando dunque la potenziale produzione di "memory leaks".

# Compilazione - linking - eseguibile
In prima istanza bisognerà assicurarsi di essere all'interno della propria directory di lavoro (quella contenente tutti i file sorgenti menzionati sopra).
Per compilare, effettuare il linking, e dunque ottenere il file eseguibile, digitare, da terminale, il comando: `make` .
Per eseguire il file, in ambiente Unix, digitare, da terminale: `./Esercizio2`.

