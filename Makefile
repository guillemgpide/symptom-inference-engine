all: programa
linkedlist.o: linkedlist.c linkedlist.h
	gcc -c linkedlist.c
main.o: main.c linkedlist.h
	gcc -c main.c
programa: main.o linkedlist.o
	gcc main.o linkedlist.o -o programa
