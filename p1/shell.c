/*
*Jose Manuel Amestoy Lopez manuel.amestoy@udc.es
* María Riveiro Carballo m.riveiro.carballo@udc.es
*group 1.3
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>

#include "funcions.h"
#include "arrayofpointers.h"


/*prints the prompt*/
void printPronpt (){
	printf("->");
}

void lerEntrada (char *input, tList *l){
	if(fgets(input, MAX, stdin)){
		insertElement(input,l);
	}else{
		printf("ERROR: input is not possible to read\n");
	}
}

void procesarEntrada(char *trozos[],tList *l){

	if(trozos[0]==NULL)
		return;
	if(!strcmp(trozos[0],"autores")){
		fun_autores(trozos[1]);
	}else
	if(!strcmp(trozos[0],"pid")){
		fun_pid(trozos[1]);
	}else
	if(!strcmp(trozos[0],"carpeta")){
		fun_carpeta(trozos[1]);
	}else
	if(!strcmp(trozos[0],"fecha")){
		fun_fecha(trozos[1]);
	}else
	if(!strcmp(trozos[0],"hist")){
		fun_hist(trozos[1],l);
	}else
	if(!strcmp(trozos[0],"comando")){
		fun_comando(trozos[1],l);
	}else
	if(!strcmp(trozos[0],"ayuda")){
		fun_ayuda(trozos[1]);
	}else
	if(!strcmp(trozos[0],"infosis")){
		fun_infosis(trozos[1]);
	}
	//P1.
	if(!strcmp(trozos[0],"crear")){
		fun_crear(trozos[1],trozos[2]);
	}
	if(!strcmp(trozos[0],"borrar")){
		fun_delete(trozos);
	}
	if(!strcmp(trozos[0],"borrarec")){
		fun_recdelete(trozos);
	}
	if ((!strcmp(trozos[0],"fin"))||(!strcmp(trozos[0],"salir"))
		||(!strcmp(trozos[0],"bye"))){
			fun_salida(trozos[1],l);
	} 
}	

int main(){
	char *trozos[MAX];
	char input [MAX];

	tList l;
	createList (&l);

	while(!0){
		printPronpt();
		lerEntrada(input,&l);
		TrocearCadena(input, trozos);
		procesarEntrada(trozos, &l);
	}

	return 0;
}

