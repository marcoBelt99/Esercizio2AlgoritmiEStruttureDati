Esercizio2: main.o esercizio2.o
	gcc -g -o Esercizio2 main.o esercizio2.o

main.o: main.c esercizio2.h
	gcc -g -c main.c

esercizio2: esercizio2.c esercizio2.h
	gcc -g -c esercizio2.c