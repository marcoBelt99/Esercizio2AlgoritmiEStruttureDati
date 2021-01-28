#!/bin/bash

# Questo semplice file compila, linka e genera l'eseguibile per i file 'interattivi' (provvisti main con gli appositi input da tastiera) 
# per testare la correttezza di Liste Doppiamente concatenate, Hash Table ed RBT.
# Se vogliamo, questo file Compila, linka e genera l'eseguibile dei i file esterni all'esercizio, non richiesti, ma opportunamente da me
# realizzati per effettuare tale 'test personale'.
echo "Compilo, link e creo gli eseguibili dei file interattivi (provvisti di main e istruzioni di input che ti guideranno nella verifica della correttezza delle 3 strutture dati")
gcc -g -Wall -Wextra listeCollegate.c -o listeCollegate
gcc -g -Wall -Wextra hashTable.c -o hashTable
gcc -g -Wall -Wextra rbt.c -o rbt