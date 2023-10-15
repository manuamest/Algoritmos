/*
*Jose Manuel Amestoy Lopez manuel.amestoy@udc.es
* María Riveiro Carballo m.riveiro.carballo@udc.es
*group 1.3
*/

#ifndef _ARRAY
#define _ARRAY

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#define MAX 4096

/*struture of pointers*/

typedef struct input{
	char *comando;
}tInput;

/*structure of list*/

typedef struct list{
	tInput nodo [MAX];
	int count;	
}tList;

/*funciones*/

void createList (tList *l);
void insertElement (char *input, tList *l);
void clearList (tList *l);
void showList (tList *l);

#endif