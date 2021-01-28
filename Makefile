$(info *** Esercizio 2 Algoritmi e Strutture Dati ***)
$(info )

Esercizio2: main.o esercizio2.o testHashTable.o testRedBlackTree.o # target: elenco delle dipendenze
	gcc -g -Wall -Wextra -o Esercizio2 main.o esercizio2.o testHashTable.o testRedBlackTree.o

main.o: main.c esercizio2.h
	gcc -g -Wall -Wextra -c main.c

esercizio2.o: esercizio2.c esercizio2.h
	gcc -g -Wall -Wextra -c esercizio2.c

testHashTable.o: testHashTable.c esercizio2.h
	gcc -g -Wall -Wextra -c testHashTable.c

testRedBlackTree.o: testRedBlackTree.c esercizio2.h
	gcc -g -Wall -Wextra -c testRedBlackTree.c

clean: # Aggiungo il target clean, per ripulire il direttorio dai file oggetto
	rm *.o Esercizio2


$(info Digitare: 'make', per produrre l' eseguibile di nome: 'Esercizio2')
$(info Digitare: 'make clean', per rimuovere tutti i file di nome'*.o' all'interno del direttorio corrente)
$(info )


