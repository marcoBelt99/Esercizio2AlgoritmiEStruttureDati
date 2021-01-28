# Algoritmi e Strutture Dati

In questo repository sono presenti i sorgenti dell'esercizio 2 di ASD a.a. 2020/2021.
L'esercizio consiste nel confrontare sperimentalmente, per input crescenti e casuali (uniformemente distribuiti) le operazioni di dizionario, eccetto l'eliminazione, che offrono le due strutture dati Hash Table e Red Black Tree.
Riporto il testo integralmente:<br/>

*Realizzare un esperimento implementando sia una tabella hash con conflitti
risolti via chaining sia un albero red-black. Misurare il tempo medio per n
operazioni con n crescente, chiavi intere maggiori di zero casuali, su
entrambe le strutture, e confrontarlo. Realizzare il confronto per diversi
valori di m (dimensione fissata della tabella hash) e diverse proporzioni tra
numero di inserimenti e numero di ricerche*

In particolare, in questo repository si trovano le implementazioni di:

- Liste doppiamente concatenate.
- Hash Tables con conflitti risolti via chaining.
- Alberi Rosso Neri.

# Specifiche di progetto

Ho separato il codice in 6 file principali che servono per gestire l'esericizio:

- [main.c](https://github.com/marcoBelt99/Algoritmi_e_Strutture_Dati/blob/main/main.c): contenente il programma da cui far partire l'esercizio.
- [esercizio2.c](https://github.com/marcoBelt99/Algoritmi_e_Strutture_Dati/blob/main/esercizio2.c):       contenente la definizione delle funzioni richieste (eccetto quelle di test: "hashtableTest" e "rbtTest") ed altre mie funzioni aggiuntive.
- [esercizio2.h](https://github.com/marcoBelt99/Algoritmi_e_Strutture_Dati/blob/main/esercizio2.h):       contenente la dichiarazione di tali funzioni; sono presenti anche le definizioni dei tipi rappresentanti le strutture dati utilizzate.
- [testHashTable.c](https://github.com/marcoBelt99/Algoritmi_e_Strutture_Dati/blob/main/testHashTable.c):    contenente la definizione della funzione "hashtableTest".
- [testRedBlackTree.c](https://github.com/marcoBelt99/Algoritmi_e_Strutture_Dati/blob/main/testRedBlackTree.c): contenente la definizione della funzione "rbtTest".
- [Makefile](https://github.com/marcoBelt99/Algoritmi_e_Strutture_Dati/blob/main/Makefile): contenente istruzioni per la compilazione ed il linking. Genera un eseguibile di nome "Esercizio2".


Gli altri file:

- [listeCollegate.c](https://github.com/marcoBelt99/Algoritmi_e_Strutture_Dati/blob/main/listeCollegate.c)
- [hashTable.c](https://github.com/marcoBelt99/Algoritmi_e_Strutture_Dati/blob/main/hashTable.c)
- [rbt.c](https://github.com/marcoBelt99/Algoritmi_e_Strutture_Dati/blob/main/rbt.c)

contengono degli esempi di test interattivi (dotati di main e di richieste di input per l'utente) per accompagnare l'utente alla verifica del corretto funzionamento degli algoritmi da applicare alle due strutture dati, tradotti in programmi.

- [compilaListeHashTableRedBlackTree.sh](https://github.com/marcoBelt99/Algoritmi_e_Strutture_Dati/blob/main/compilaListeHashTableRedBlackTree.sh): contiene istruzioni per compilazione, linking e generazione degli eseguibili di questi file interattivi.

- [random.c](https://github.com/marcoBelt99/Algoritmi_e_Strutture_Dati/blob/main/random.c) è un semplice test per verificare la correttezza della generazione di numeri casuali.

In particolare, nel file [Esecuzione_e_Memcheck_con_Valgrind.txt](https://github.com/marcoBelt99/Algoritmi_e_Strutture_Dati/blob/main/Esecuzione_e_Memcheck_con_Valgrind.txt) sono presenti 3 esempi di esecuzione, rispettivamente per: liste concatenate, tabelle hash ed alberi rosso neri.
Ogni esecuzione è accompagnata dal "memcheck" effettuato da valgrid, avente lo scopo di assicurare la corretta gestione della memoria, evitando dunque la potenziale produzione di "memory leaks".


# Compilazione - linking - eseguibile
In prima istanza bisognerà assicurarsi di essere all'interno della propria directory di lavoro (quella contenente tutti i file sorgenti menzionati sopra).

- Per compilare, effettuare il linking, e dunque ottenere il file eseguibile dell'esercizio, digitare, da terminale, il comando: `make` .

- Per eseguire il file, in ambiente Unix, digitare, da terminale: `./Esercizio2`.

- Per rimuovere i file .o dal direttorio, dare il comando: `make clean`.

- Per vedere i grafici, una volta settato 'ONFILE' nel main e che Esercizio2 ha terminato,
aprire 'Grafici.m' ed eseguirlo (dentro matlab).

- Per compilare, effettuare il linking, e dunque ottenere i file eseguibili degli altri file 'interattivi' (quelli che accompagnano l'utente a testare la correttezza di una delle 3 strutture dati),<br/>dare il comando: `./compilaListeHashTableRedBlackTree.sh`.

# Aggiunte

- Ho aggiunto il file [Grafici.m](https://github.com/marcoBelt99/Algoritmi_e_Strutture_Dati/blob/main/Grafici.m) che permette di fare il plot dei risultati.

- Ho aggiunto alcuni file *.jpg prodotti dai grafici dello script matlab appena citato.
Notare che tali file sono nominati: 'numeroInsert_numeroHTsize.jpg'
