#ifndef LINKEDLIST_H
#define LINKEDLIST_H

//LLLIBRERIES
#include <stdlib.h>

//DEFINICIO DE CONSTANTS
#define LIST_NO_ERROR 0
#define LIST_ERROR_FULL 1
#define LIST_ERROR_EMPTY 2
#define LIST_ERROR_MALLOC 3
#define LIST_ERROR_END 4

#define MAX_CHAR 50

//CREACIO TYPEDEF STRUCT SYMPTOM PER GUARDAR ELS SINTOMES
typedef struct {

    char symptom[MAX_CHAR];
    int relevance;

} Symptom;

//REDEFINCIO DEL TYPEDEF STRCUCT ANTERIOR AMB ELEMENT
typedef Symptom Element;

//TYPEDEF STRUCT NODE PER ACCEDIR A TOTES LES VARIABLES ELEMENT
typedef struct _Node {	

	Element element;
	struct _Node * next;

} Node;

//TYPEDEF STRUCT LINKEDLIST PER ACCEDIR A TOTES LES VARIABLES NODE
typedef struct {

	int error;
	Node * head;
	Node * previous;

} LinkedList;

//DEFINICIÓ DE LES DIFERENTS LINKEDLISTS
LinkedList LINKEDLIST_create ();
void 	LINKEDLIST_add (LinkedList * list, Element element);
void 	LINKEDLIST_remove (LinkedList * list);
Element LINKEDLIST_get (LinkedList * list);
int 	LINKEDLIST_isEmpty (LinkedList list);
void 	LINKEDLIST_goToHead (LinkedList * list);
void 	LINKEDLIST_next (LinkedList * list);
int 	LINKEDLIST_isAtEnd (LinkedList list);
void 	LINKEDLIST_destroy (LinkedList * list);
int		LINKEDLIST_getErrorCode (LinkedList list);

#endif