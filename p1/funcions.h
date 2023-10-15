/*
*Jose Manuel Amestoy Lopez manuel.amestoy@udc.es
* María Riveiro Carballo m.riveiro.carballo@udc.es
*group 1.3
*/

#ifndef _FUNC
#define _FUNC

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <grp.h>
#include <sys/utsname.h>
#include <fcntl.h>
#include "arrayofpointers.h"
/*functions*/
void fun_error();//prints a bug warning
int TrocearCadena(char *cadena,char *trozos[]);
void fun_autores (char *comando); 
void fun_pid (char* comando);
void fun_carpeta (char* comando);
void fun_fecha (char* comando);
void fun_hist(char* comando, tList *l);
void fun_comando (char* comando, tList *l);
void fun_ayuda(char* comando);
void fun_infosis(char*comando);
/*P1*/
void fun_crear(char*comando, char *name);
int isDirectory(const char *comando); //Funcion auxiliar.
void fun_delete(char *trozos[]);
int borrar_dir(const char *directorio);//Funcion auxiliar.
void fun_recdelete(char *trozos[]);
void fun_salida(char* comando, tList *l);

#endif
