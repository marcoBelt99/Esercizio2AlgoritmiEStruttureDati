Esercizio2: main.o esercizio2.o testHashTable.o testRedBlackTree.o # target: elenco delle dipendenze
	gcc -g -o Esercizio2 main.o esercizio2.o testHashTable.o testRedBlackTree.o

main.o: main.c esercizio2.h
	gcc -g -c main.c

esercizio2.o: esercizio2.c esercizio2.h
	gcc -g -c esercizio2.c

testHashTable.o: testHashTable.c esercizio2.h
	gcc -g -c testHashTable.c

testRedBlackTree.o: testRedBlackTree.c esercizio2.h
	gcc -g -c testRedBlackTree.c

clean: # Aggiungo il target clean, per ripulire il direttorio dai file oggetto
	rm *.o Esercizio2