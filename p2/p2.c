/*
*Practica 2
*Grupo 1.4
*Sabela Pita Armada sabela.pita
*Maria Riveiro Carballo m.riveiro.carballo
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>


void ord_seleccion (int v[],int n){
	int i;
	int j;
	int minj, minx;
	for(i=0;i<n;i++){
		minj=i; minx=v[i];
		for(j=i+1;j<n+1;j++){
			if(v[j]<minx){
				minj=j; minx=v[j];
			}
		}
		v[minj]=v[i]; v[i]=minx;
	}
}

//***************************************************************

void ord_shell(int v[], int n){
	int incremento= n;
	int i,j;
	int tmp;
	bool seguir;

	while (incremento>1){
		incremento= incremento/2;
		for (i=incremento;i<n;i++){
			tmp=v[i];
			j=i;
			seguir=true;
			while(((j-incremento)>=0)&&
				(seguir)){
				if(tmp<v[j-incremento]){
					v[j]=v[j-incremento];
					j=j-incremento;
				}else {seguir=false;}
			}
		v[j]=tmp;
		}
	}	

}

//*************************************************************

double microsegundos() {
/* obtiene la hora del sistema en microsegundos */
	struct timeval t;
	if (gettimeofday(&t, NULL) < 0 )
		return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}

//***************************************************************

void inicializar_semilla(){
	srand(time(NULL));
}

//**************************************************************

void listarVector(int v[],int n){
	int i;
	for (i=0;i<n;i++){
		printf("%4d",v[i]);
	}
}

//**************************************************************

void aleatorio (int v [],int n){/*se generan numeros 
								pseudoaleatorios entre -n y +n*/
	int i, m=2*n+1;
	for (i=0;i < n;i++)
		v[i]=(rand() % m) - n;
}

//**************************************************************

void ascendente (int v[], int n){
	int i;
	for (i=0;i<n;i++)
		v[i]=i;
}

//**************************************************************

void descendente (int v[], int n){
	int i;
	int j=0;
	for (i=n;i>0;i--,j++){
		v[j]=i;
	}
}

//**************************************************************

void Ordenado(int v[],int n){
	int ord;
	int i=0;
	int j;
	for (j=0;j<(n-1)&&(i==0);j++){
		if (v[j]<=v[j+1]){
			i=i+0;
		} else {
		i=i+1;
		}
	}
	if (i==0){
		ord=1;
	} else {
		ord=0;
	}
	printf("¿Ordenado? %d\n",ord);
}

//*************************************************************

void test_seleccion(){

	int v1[17],v2[10];
	aleatorio(v1,17);
	descendente(v2,10);

	printf("\n TEST DE ORDENACION POR SELECCION \n");
	printf("---------------------------------------\n");
	printf("\nVector aleatorio\n");
	listarVector(v1,17);
	printf("\n");
	Ordenado(v1,17);
	printf("\n Una vez ordenado el vector: \n");
	ord_seleccion(v1,17);
	listarVector(v1,17);
	printf("\n");
	Ordenado(v1,17);
	printf("\n Vector descendente\n");
	listarVector(v2,10);
	printf("\n");
	Ordenado(v2,10);
	printf("\n Una vez ordenado el vector: \n");
	ord_seleccion(v2,10);
	listarVector(v2,10);
	printf("\n");
	Ordenado(v2,10);
}

//*************************************************************

void test_shell(){

	int v1[17],v2[10];
	aleatorio(v1,17);
	descendente(v2,10);

	printf("\n TEST DE ORDENACION POR SHELL \n");
	printf("---------------------------------------\n");
	printf("\nVector aleatorio\n");
	listarVector(v1,17);
	printf("\n");
	Ordenado(v1,17);
	printf("\n Una vez ordenado el vector: \n");
	ord_shell(v1,17);
	listarVector(v1,17);
	printf("\n");
	Ordenado(v1,17);
	printf("\n Vector descendente\n");
	listarVector(v2,10);
	printf("\n");
	Ordenado(v2,10);
	printf("\n Una vez ordenado el vector: \n");
	ord_shell(v2,10);
	listarVector(v2,10);
	printf("\n");
	Ordenado(v2,10);
}

//*************************************************************

double tiemposejecucion_seleccion(int v[], int n,void (*ordenado)(int [],int)){
	int i;
	int k=1000;
	double t,ta,tb,t1,t2;

	ordenado(v,n); //inicializar vector

	ta=microsegundos();
	ord_seleccion(v,n);
	tb=microsegundos();
	t=tb-ta;

	if (t<500){
		printf("*");
		ta=microsegundos();
		for (i=0;i<k;i++){
			ordenado(v,n); //inicializar vector
			ord_seleccion(v,n); //llamada a funcion
		}
		tb=microsegundos();
		t1=tb-ta;
		ta=microsegundos();
		for(i=0;i<k;i++){
			ordenado(v,n); //inicializar vector
		}
		tb=microsegundos();
		t2=tb-ta;
		t=(t1-t2)/k;
	}else{
		printf(" ");
	}
	return t;
}
//*************************************************************

double tiemposejecucion_shell(int v[], int n,void (*ordenado)(int [],int)){
	int i;
	int k=1000;
	double t,ta,tb,t1,t2;

	ordenado(v,n); //inicializar vector

	ta=microsegundos();
	ord_shell(v,n);
	tb=microsegundos();
	t=tb-ta;

	if (t<500){
		printf("*");
		ta=microsegundos();
		for (i=0;i<k;i++){
			ordenado(v,n); //inicializar vector
			ord_shell(v,n); //llamada a funcion
		}
		tb=microsegundos();
		t1=tb-ta;
		ta=microsegundos();
		for(i=0;i<k;i++){
			ordenado(v,n); //inicializar vector
		}
		tb=microsegundos();
		t2=tb-ta;
		t=(t1-t2)/k;
	}else{
		printf(" ");
	}
	return t;
}
//*************************************************************

void cotasOrd_seleccion(int n,double t,void(*ordenado)(int[],int)){

	if (ordenado==aleatorio){
		printf("%6d",n);
		printf("%15.6f",t);
		printf("%15.6f",t/(pow(n,1.9))); //cota subestimada
		printf("%15.6f",t/(pow(n,2)));   //cota ajustada
		printf("%15.6f",t/(pow(n,2.1))); //cota sobreestimada
		printf("\n");
	}else if(ordenado==ascendente){
		printf("%6d",n);
		printf("%15.6f",t);
		printf("%15.6f",t/(pow(n,1.9))); //cota subestimada
		printf("%15.6f",t/(pow(n,2)));			  //cota ajustada
		printf("%15.6f",t/(pow(n,2.1)));  //cota sobreestimada
		printf("\n");
	}else {
		printf("%6d",n);
		printf("%15.6f",t);
		printf("%15.6f",t/(pow(n,1.9)));  //cota subestimada
		printf("%15.6f",t/(pow(n,2)));    //cota ajustada
		printf("%15.6f",t/(pow(n,2.1)));  //cota sobreestimada
		printf("\n");
	}

}

//*************************************************************

void cotasOrd_shell(int n,double t,void(*ordenado)(int[],int)){

	if (ordenado==aleatorio){
		printf("%6d",n);
		printf("%15.6f",t);
		printf("%15.6f",t/(pow(n,1.00))); //cota subestimada
		printf("%15.6f",t/(pow(n,1.2))); //cota ajustada
		printf("%15.6f",t/(pow(n,1.5)));  //cota sobreestimada
		printf("\n");
	}else if(ordenado==ascendente){
		printf("%6d",n);
		printf("%15.6f",t);
		printf("%15.6f",t/(pow(n,0.95)));
		printf("%15.6f",t/(pow(n,1.14)));
		printf("%15.6f",t/(pow(n,1.3)));
		printf("\n");
	}else {
		printf("%6d",n);
		printf("%15.6f",t);
		printf("%15.6f",t/(pow(n,0.95)));
		printf("%15.6f",t/(pow(n,1.13)));
		printf("%15.6f",t/(pow(n,1.3)));
		printf("\n");
	}

}

//*************************************************************
 void resultadosOrd_seleccion(void(*ordenado)(int[],int)){
	int n,k=32000,v[k];
	double t;

	if(ordenado==aleatorio){
		printf("\n***********************************************************");
		printf("\n COTAS ALGORITMO DE ORDENACION POR SELECCION\n");
		printf("\n Ordenación con inicialización aleatoria\n");
		printf("***********************************************************");
		printf("\n%6s%13s%18s%15s%16s\n","n","t(n)","t(n)/n^1.9"
			,"t(n)/n^2","t(n)/n^2.1");printf("\n");
		for(n=500;n<=k;n=n*2){
			t=tiemposejecucion_seleccion(v,n,aleatorio);
			cotasOrd_seleccion(n,t,aleatorio);printf("\n");}
	}else if(ordenado==ascendente){
			printf("\n Ordenación con inicialización ascendente\n");
			printf("*******************************************************");
			printf("\n%6s%14s%19s%12s%17s\n","n","t(n)","t(n)/n^(1.9)"
			,"t(n)/n^2","t(n)/n^2.1");printf("\n");
			for(n=500;n<=k;n=n*2){
				t=tiemposejecucion_seleccion(v,n,ascendente);
				cotasOrd_seleccion(n,t,ascendente);printf("\n");}
		}else{
			printf("\n Ordenación con inicialización descendente\n");
			printf("*******************************************************");
			printf("\n%6s%14s%18s%16s%16s\n","n","t(n)","t(n)/n^(0.95)"
			,"t(n)/n^(1.13)","t(n)/n^(1.3)");printf("\n");
			for(n=500;n<=k;n=n*2){
				t=tiemposejecucion_seleccion(v,n,descendente);
				cotasOrd_seleccion(n,t,descendente);
				printf("\n");}
		}
}
//*************************************************************
void resultadosOrd_shell(void(*ordenado)(int[],int)){
	int n,k=32000,v[k];
	double t;

	if(ordenado==aleatorio){
		printf("\n***********************************************************");
		printf("\n COTAS ALGORITMO DE ORDENACION POR SHELL\n");
		printf("***********************************************************\n");
		printf("\n Ordenación por shell con inicialización aleatoria\n");
		printf("***********************************************************");
		printf("\n%6s%14s%16s%18s%16s\n","n","t(n)","t(n)/n"
			,"t(n)/n^(1.2)","t(n)/n^(1.5)");printf("\n");
		for(n=500;n<=k;n=n*2){
			t=tiemposejecucion_shell(v,n,aleatorio);
			cotasOrd_shell(n,t,aleatorio);printf("\n");}
	}else if(ordenado==ascendente){
			printf("\n Ordenación por shell con inicialización ascendente\n");
			printf("*******************************************************");
			printf("\n%6s%14s%18s%16s%16s\n","n","t(n)","t(n)/n^(0.95)"
			,"t(n)/n^(1.14)","t(n)/n^(1.3)");printf("\n");
			for(n=500;n<=k;n=n*2){
				t=tiemposejecucion_shell(v,n,ascendente);
				cotasOrd_shell(n,t,ascendente);printf("\n");}
		}else{
			printf("\n Ordenación por shell con inicialización descendente\n");
			printf("*******************************************************");
			printf("\n%6s%14s%18s%15s%17s\n","n","t(n)","t(n)/n^(0.95)"
			,"t(n)/n^(1.14)","t(n)/n^(1.3)");
			printf("\n");
			for(n=500;n<=k;n=n*2){
				t=tiemposejecucion_shell(v,n,descendente);
				cotasOrd_shell(n,t,descendente);printf("\n");}
		}
}
//*************************************************************

int main(){
	inicializar_semilla();
	test_seleccion();
	test_shell();

	/*Empezan os tempos de seleccion*/
	resultadosOrd_seleccion(aleatorio);
	resultadosOrd_seleccion(aleatorio);
	resultadosOrd_seleccion(ascendente);
	resultadosOrd_seleccion(ascendente);
	resultadosOrd_seleccion(ascendente);
	resultadosOrd_seleccion(descendente);
	resultadosOrd_seleccion(descendente);
	resultadosOrd_seleccion(descendente);
	
	/*Empezan os tempos do shell*/
	resultadosOrd_shell(aleatorio);
	resultadosOrd_shell(aleatorio);
	resultadosOrd_shell(aleatorio);
	resultadosOrd_shell(ascendente);
	resultadosOrd_shell(ascendente);
	resultadosOrd_shell(descendente);
	resultadosOrd_shell(descendente);
	resultadosOrd_shell(descendente);


	return 0;
}