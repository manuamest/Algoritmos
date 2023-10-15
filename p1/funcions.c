/*
*Jose Manuel Amestoy Lopez manuel.amestoy@udc.es
* María Riveiro Carballo m.riveiro.carballo@udc.es
*group 1.3
*/

#include "funcions.h"

char LetraTF (mode_t m)
{
	switch (m&S_IFMT) { /*and bit a bit con los bits de formato,0170000 */
		case S_IFSOCK: return ’s’; /*socket */
		case S_IFLNK: return ’l’; /*symbolic link*/
		case S_IFREG: return ’-’; /* fichero normal*/
		case S_IFBLK: return ’b’; /*block device*/
		case S_IFDIR: return ’d’; /*directorio */
		case S_IFCHR: return ’c’; /*char device*/
		case S_IFIFO: return ’p’; /*pipe*/
		default: return ’?’; /*desconocido, no deberia aparecer*/
	}
}
char * ConvierteModo (mode_t m, char *permisos)
{
	strcpy (permisos,"---------- ");

	permisos[0]=LetraTF(m);
	if (m&S_IRUSR) permisos[1]=’r’; /*propietario*/
	if (m&S_IWUSR) permisos[2]=’w’;
	if (m&S_IXUSR) permisos[3]=’x’;
	if (m&S_IRGRP) permisos[4]=’r’; /*grupo*/
	if (m&S_IWGRP) permisos[5]=’w’;
	if (m&S_IXGRP) permisos[6]=’x’;
	if (m&S_IROTH) permisos[7]=’r’; /*resto*/
	if (m&S_IWOTH) permisos[8]=’w’;
	if (m&S_IXOTH) permisos[9]=’x’;
	if (m&S_ISUID) permisos[3]=’s’; /*setuid, setgid y stickybit*/
	if (m&S_ISGID) permisos[6]=’s’;
	if (m&S_ISVTX) permisos[9]=’t’;
	return permisos;
}

char * ConvierteModo2 (mode_t m)
{
	static char permisos[12];

	strcpy (permisos,"---------- ");

	permisos[0]=LetraTF(m);
	if (m&S_IRUSR) permisos[1]=’r’; /*propietario*/
	if (m&S_IWUSR) permisos[2]=’w’;
	if (m&S_IXUSR) permisos[3]=’x’;
	if (m&S_IRGRP) permisos[4]=’r’; /*grupo*/
	if (m&S_IWGRP) permisos[5]=’w’;
	if (m&S_IXGRP) permisos[6]=’x’;
	if (m&S_IROTH) permisos[7]=’r’; /*resto*/
	if (m&S_IWOTH) permisos[8]=’w’;
	if (m&S_IXOTH) permisos[9]=’x’;
	if (m&S_ISUID) permisos[3]=’s’; /*setuid, setgid y stickybit*/
	if (m&S_ISGID) permisos[6]=’s’;
	if (m&S_ISVTX) permisos[9]=’t’;
	return (permisos);
}

char * ConvierteModo3 (mode_t m)
{
	char * permisos;
	permisos=(char *) malloc (12);
	strcpy (permisos,"---------- ");

	permisos[0]=LetraTF(m);
	if (m&S_IRUSR) permisos[1]=’r’; /*propietario*/
	if (m&S_IWUSR) permisos[2]=’w’;
	if (m&S_IXUSR) permisos[3]=’x’;
	if (m&S_IRGRP) permisos[4]=’r’; /*grupo*/
	if (m&S_IWGRP) permisos[5]=’w’;
	if (m&S_IXGRP) permisos[6]=’x’;
	if (m&S_IROTH) permisos[7]=’r’; /*resto*/
	if (m&S_IWOTH) permisos[8]=’w’;
	if (m&S_IXOTH) permisos[9]=’x’;
	if (m&S_ISUID) permisos[3]=’s’; /*setuid, setgid y stickybit*/
	if (m&S_ISGID) permisos[6]=’s’;
	if (m&S_ISVTX) permisos[9]=’t’;
	return (permisos);
}

/*prints a bug warning*/

void fun_error(){
	printf("\n error: invalid comand.\n");
}

int TrocearCadena(char * cadena, char * trozos[]){
	int i=1;

	if ((trozos[0]=strtok(cadena," \n\t"))==NULL)
	return 0;
	while ((trozos[i]=strtok(NULL," \n\t"))!=NULL)
	i++;
	return i;
}


/*Amosar autores*/

void fun_autores (char *comando){
	if (comando==NULL){
		printf("author1:Jose Manuel Amestoy Lopez. author2: Maria Riveiro Carballo.\n");
		printf("login1:manuel.amestoy .login2: m.riveiro.carballo\n");
	} else if (strcmp(comando,"-l")==0){
		printf("login1:manuel.amestoy .login2: m.riveiro.carballo\n");
	}else if (strcmp(comando, "-n")==0){
		printf("author1:Jose Manuel Amestoy Lopez. author2: Maria Riveiro Carballo.\n");
	} else {fun_error();}
}

/*prints the pid or the parent's pid of the process*/
void fun_pid (char* comando){
	if(comando==NULL){
		printf("\n pid ofshell:%d\n", getpid());
	}else if (strcmp(comando,"-p")==0){
		printf("\n pid of shell's parent process %d\n",getppid());
	}else fun_error();
}
 /*Changes de current working directory of the shell or
 * prints de current working directory
 */
void fun_carpeta (char* directorio){
	if(directorio==NULL){
		char cwd [MAX];

		if (getcwd(cwd,sizeof(cwd))!=NULL){
			printf("\n current working directory%s\n",cwd);
		} else {
			perror("ERROR: current directory not found\n");
		}
	}else if (chdir(directorio)!=-1){

		fun_carpeta(NULL);
	}else {perror("ERROR:directory doesn't exists");}
}

/*prints de date or/and the time*/
void fun_fecha (char* comando){
	if (comando==NULL){
		time_t d = time (0);
		struct tm * dia =localtime(&d);
		char tempo [128];
		strftime(tempo,128,"%d/%m/%y",dia);
		printf("%s\n",tempo); 

		time_t h= time (0);
		struct tm*hora= localtime(&h);
		strftime(tempo,128,"%H:%M:%S",hora);
		printf("%s\n",tempo);
		}else if (strcmp(comando,"-d")==0){
			time_t d = time (0);
			struct tm * dia =localtime(&d);
			char tempo [128];
			strftime(tempo,128,"%d/%m/%y",dia);
			printf("%s\n",tempo); 
		}else if (strcmp(comando,"-h")==0){
			time_t h = time (0);
			struct tm * hora =localtime(&h);
			char tempo [128];
			strftime(tempo,128,"%H:%M:%S",hora);
			printf("%s\n",tempo);
		}
}
/*shows/clears the historic of commands*/
void fun_hist(char*comando, tList *l){
	if(comando==NULL){
		showList(l);
	}else if(strcmp(comando,"-c")==0){
		clearList(l);
	}else if((atoi(comando))!=-1){
		int n=atoi(comando);
		for(int i=0;i<n;i++){
			printf("%d%s\n",i,l->nodo[i].comando);
		}
	}

}
/*shows the N command*/
void fun_comando(char *comando, tList *l){
	if (comando==NULL){
		printf("ERROR: few arguments for format.\n");
	}else if ((atoi(comando))!=-1){
		int n=atoi(comando);
		int i=0;
		while(i<n){
			i++;
		} 
		printf("%d%s\n",i,l->nodo[i].comando);
		}
}

/*displays a list of available commands*/
void fun_ayuda(char* comando){
    if (comando==NULL) {
        printf("'ayuda cmd' donde cmd es uno de los siguientes comandos:\n"
        " fin salir bye fecha pid autores hist comando carpeta infosis ayuda \n");
    }else if (strcmp(comando, "fin")==0){
            printf("'fin' termina la ejecución del shell.\n");
    }else if (strcmp(comando, "salir")==0){
            printf("'salir' termina la ejecución del shell.\n"); 
    }else if (strcmp(comando, "bye")==0){
            printf("'bye' termina la ejecución del shell.\n");
    }else if (strcmp(comando, "autores")==0){
            printf("autores [-n|-l]. Muestra los nombres y logins de los autores.\n");
    }else if (strcmp(comando, "pid")==0){
            printf("pid [-p]	Muestra el pid del shell o de su proceso padre.\n");
    }else if (strcmp(comando, "carpeta")==0){
            printf("carpeta [dir]	Cambia (o muestra) el directorio actual del shell.\n");
    }else if (strcmp(comando, "fecha")==0){
            printf("fecha [-d|.h	Muestra la fecha y o la hora actual.\n");
    }else if (strcmp(comando, "hist")==0){
            printf("hist [-c|-N]. Muestra el historico de comandos, con -c lo borra.\n");
    }else if (strcmp(comando, "comando")==0){
            printf("comando [-N]. Repite el comando N (del historico).\n");
    }else if (strcmp(comando, "infosis")==0){
            printf("infosis. Muestra informacion de la maquina donde corre el shell.\n");
    }else {fun_error();}
}

/*Shows information about the machine*/
void fun_infosis(char* comando){
    if (comando==NULL) {
        struct utsname unameData;

        uname(&unameData); // Might check return value here (non-0 = failure)

        printf("%s\n", unameData.nodename);
        printf("%s\n", unameData.sysname);
        printf("%s\n", unameData.release);
        printf("%s\n", unameData.version);
        printf("%s\n", unameData.machine);
    }else{
        fun_error();
    }
}
/*AQUI EMPEZAN AS FUNCIONS DA P1*/

/*Create a new file/directory*/
void fun_crear(char *comando, char* name){
	if((comando==NULL)&&(name==NULL)){
		char cwd [MAX];
		getcwd(cwd,sizeof(cwd));
		printf("\n current working directory: %s\n",cwd);
	}else if (comando==NULL&& name!=NULL){
		printf("Error invalid name.\n");
	}else if(strcmp(comando,"-f")==0){
		int archivo = open(name, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		if (archivo==-1){
			printf("File can not be created%s %s\n",comando, strerror(errno));
		}else close(archivo);
	}else{
		int directorio =mkdir(comando,S_IRWXU);
		if(directorio==-1){
			printf("Directory can not be created. %s %s\n",name, strerror(errno));
		}
	}
}
/*Funcion auxiliar*/
/*Shows if the file is a directory*/
int isDirectory(const char *comando){
	struct stat statbuf;
	if(stat(comando,&statbuf)!=0)
		return 0;
	return S_ISDIR(statbuf.st_mode);
}

/*Deletes files and/or empty directories*/
void fun_delete(char *trozos[]){
	if(trozos[1]==NULL){
		printf("Error invalid name.\n");
	}else{
		for(int i=1; trozos[i]; i++){
			if(isDirectory(trozos[i])){
				rmdir(trozos[i]);
			}else{
				remove(trozos[i]);
			}
		}
	}
}
/*Funcion auxiliar para borrar archivos ou directorios non vacios*/
int borrar_dir(const char *directorio){
	DIR *d=opendir(directorio);
	size_t dir_len=strlen(directorio);
	int r=-1;
	if(d){
		struct dirent *p;
		r=0;
		while(!r && (p=readdir(d))){
			int r2=-1;
			char *buf;
			size_t len;

			/* Skip the names "." and ".." as we don't want to recurse on them. */
			if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
    		continue;

    		len=dir_len+strlen(p->d_name)+2;
            buf=malloc(len);
            if(buf){
            	struct stat statbuf;
             	snprintf(buf,len,"%s/%s",directorio,p->d_name);
             	if(!stat(buf,&statbuf)){
             		if(S_ISDIR(statbuf.st_mode)){
             			r2= borrar_dir(buf);
             		}
             		else{
             			r2=unlink(buf);
             		}
             	}
             	free(buf);
        	}
        r=r2;
		}
	closedir(d);
	}
	if(!r){
		r=rmdir(directorio);

	}	
		
	return r;
}

/*Deletes files and/or non empty directories */
void fun_recdelete(char *trozos[]){
	
	if(trozos[1]==NULL){
		fun_carpeta(trozos[1]);
	}else{
		for(int i=1; trozos[i]; i++){
			borrar_dir(trozos[i]);
		}
	}
}

off_t lastAcces(char * nombre){
	struct stat fileStat;
	if(lstat(nombre, &fileStat) == -1) {
		return -1;
		} else {
			return fileStat.st_ino;
		}
}

off_t itemSize(char * nombre){
	struct stat fileStat;
	if(lstat(nombre, &fileStat) == -1) {
		return -1;
		} else {
			return fileStat.st_size;}
}

void fun_listfich(char *trozos[]){
	char cwd[MAX], aux[MAX];
	getcwd(cwd,sizeof(cwd));

	if (strcmp(trozos[1], "-long") == 0){
		for(int i = 2; trozos[i]; i++){
			printf("name %s ",string);
			printf("number of links %3d ",(int)fileStat.st_nlink);
			printf("owner %s ", getpwuid(fileStat.st_uid)->pw_name);
			printf("group %s ", getgrgid(fileStat.st_gid)->gr_name);
			printf("mode %s ", ConvierteModo(fileStat.st_mode,string));
			printf("size %5ld ", itemSize(trozos[i]));
			printf("number of links %3d ",(int)fileStat.st_nlink);
			printf("name %s\n", trozos[i])
		}
	}else if (strcmp(trozos[1], "-link") == 0){
		for(int i = 2; i < trozos[i]; i++){
			printf("name %s ",string);
			printf("number of links %3d ",(int)fileStat.st_nlink);
			printf("owner %s ", getpwuid(fileStat.st_uid)->pw_name);
			printf("group %s ", getgrgid(fileStat.st_gid)->gr_name);
			printf("mode %s ", ConvierteModo(fileStat.st_mode,string));
			printf("size %5ld ", itemSize(trozos[i]));
			printf("number of links %3d ",(int)fileStat.st_nlink);
			printf("name %s\n", trozos[i])

			if(!S_ISLNK(fileStat.st_mode)){
				continue;
		}else{
			readlink(trozos[i], aux, fileStat.st_size);
				aux[fileStat.st_size] = '\0';
				printf("%s\n", aux);}
		}
	}else if (strcmp(trozos[1], "-acc") == 0){
		for(int i = 2; i < trozos[i]; i++){
			printf("last access %ld ", lastAcces(trozos[i]));
		}
	}else {
		for(int i = 1; trozos[i] ; i++){
			fun_carpeta;
	}
}

void fun_listdir(char * trozos[]){
	char cwd[MAX];
	getcwd(cwd,sizeof(cwd));
	
	if (strcmp(comando, "-reca") == 0){
		for(int i = 2; trozos[i] ; i++){
			ultimo acceso
		}
	}else if (strcmp(comando, "-recb") == 0){
		for(int i = 2; trozos[i] ; i++){
			ultimo acceso
		}
	}else if (strcmp(comando, "-hid") == 0){
		for(int i = 2; trozos[i] ; i++){
			char * ocultos;
			strcpy(ocultos, trozos[i]);
			strcat(ocultos, "/");
			strcat(ocultos, entrada->d_name);
			
			printf("name %s ", ocultos);
			printf("number of links %3d ", (int)fileStat.st_nlink);
			printf("owner %s ", getpwuid(fileStat.st_uid)->pw_name);
			printf("group %s ", getgrgid(fileStat.st_gid)->gr_name);
			printf("mode %s ", ConvierteModo(fileStat.st_mode,string));
			printf("size %5ld ", itemSize(ocultos));
			printf("number of links %3d \n", (int)fileStat.st_nlink);

			if(!S_ISLNK(fileStat.st_mode)){
				continue;
			}else{
				readlink(trozos[i], aux, fileStat.st_size);
				aux[fileStat.st_size] = '\0';
				printf("%s\n", aux);
			}
		}
	}else if (strcmp(comando, "-long") == 0){
		for(int i = 2; trozos[i] ; i++){
			printf("name %s ", trozos[i]);
			printf("number of links %3d ", (int)fileStat.st_nlink);
			printf("owner %s ", getpwuid(fileStat.st_uid)->pw_name);
			printf("group %s ", getgrgid(fileStat.st_gid)->gr_name);
			printf("mode %s ", ConvierteModo(fileStat.st_mode,string));
			printf("size %5ld ", itemSize(trozos[i]));
			printf("number of links %3d \n", (int)fileStat.st_nlink);
		}
	}else if (strcmp(comando, "-link") == 0){
		for(int i = 2; trozos[i] ; i++){
			printf("name %s ", trozos[i]);
			printf("number of links %3d ", (int)fileStat.st_nlink);
			printf("owner %s ", getpwuid(fileStat.st_uid)->pw_name);
			printf("group %s ", getgrgid(fileStat.st_gid)->gr_name);
			printf("mode %s ", ConvierteModo(fileStat.st_mode,string));
			printf("size %5ld ", itemSize(trozos[i]));
			printf("number of links %3d \n", (int)fileStat.st_nlink);

			if(!S_ISLNK(fileStat.st_mode)){
				continue;
			}else{
				readlink(trozos[i], aux, fileStat.st_size);
				aux[fileStat.st_size] = '\0';
				printf("%s\n", aux);
			}
		}
	}else if (strcmp(comando, "-acc") == 0){
		for(int i = 2; trozos[i] ; i++){
			printf("last access %ld ", lastAcces(trozos[i]));
		}
	}else{
		for(int i = 1; trozos[i] ; i++){
			fun_carpeta;
		}
	}
}

/*ends the shell*/
void fun_salida(char *comando, tList *l){
	if(comando==NULL){
		clearList(l);
		exit(0);
	}else{
		fun_error();
	}
}


