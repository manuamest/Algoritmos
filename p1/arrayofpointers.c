/*
*Jose Manuel Amestoy Lopez manuel.amestoy@udc.es
* María Riveiro Carballo m.riveiro.carballo@udc.es
*group 1.3
*/


#include "arrayofpointers.h"

/*empty list*/

void createList (tList *l){
	l->nodo[0].comando=NULL;
	l->count=0;
}

/*insert an element in the list*/

void insertElement (char *input, tList *l){
	if (l==NULL){
		printf("ERROR: list doesn't.\n");
	}else 
		if ((l->count)<MAX){
			l->nodo [l->count].comando=strdup(input);
			l->count++;
		}else{
			printf("ERROR: the list is full. Press hist -c to free space\n");
		}
}

/*delet the content of the list*/

void clearList (tList *l){
	if (l!=NULL){
		for (int i=0;i<(l->count);i++){ //borrado en cascada
			free(l->nodo[i].comando);
		}
		l->count=0;
	}else {
		printf("ERROR: list doesn't exist.\n");
	}
}

/*prints the list*/

void showList (tList *l){
	if (l!=NULL){
		for (int i=0;i<(l->count);i++){
			printf("%d%s",i,l->nodo[i].comando);
		}
		printf("\n");
	}else {
		printf("ERROR: list doesn't exist.\n");
	}
}
