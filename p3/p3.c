/*
*Practica 3
*Grupo 1.3
Js Manuel Amestoy Lopez manuel.amestoy
*Maria Riveiro Carballo m.riveiro.carballo
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#define UMBRAL 100


void ord_ins (int v[],int n){
	int i;
	int x;
	int j;
	for(i=1;i<n;i++){
		x=v[i];
		j=i-1;
		while((j>=0) && (v[j]>x)){
			v[j+1]=v[j];
			j--;
		}
		v[j+1]=x;
	}
}
//***************************************************************

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
void mediana3(int v[],int i, int j){
	int k, s;
	 k=(i+j)/2; /*precondicion i<j*/
	 if(v[k]>v[j]){
	 	s=v[k];
	 	v[k]=v[j];
	 	v[j]=s;
	 }
	 if(v[k]>v[i]){
	 	s=v[k];
	 	v[k]=v[i];
	 	v[i]=s;
	 }
	 if(v[i]>v[j]){
	 	s=v[i];
	 	v[i]=v[j];
	 	v[j]=s;
	 }
}
//*************************************************************
void ordenarAux(int v[], int izq, int der){
	int pivote,i,j,aux;
	if((izq + UMBRAL)<= der){ /*UMBRAL <=1*/
		mediana3 (v,izq,der); /*el pivote esta en izq y en der habra 
						un valor mayor o igual que el pivote.*/
		pivote = v[izq];
		 i=izq+1;
		 j=der;
		while(i>j){
		 	while(v[i]<pivote){
		 		i++;
		 	}
		 	while(v[j]>pivote){
		 		j--;
		 	}
		 	aux =v[i];
		 	v[i]=v[j];
		 	v[j]=aux;
		}
		aux =v[i]; /* se deshace el ultimo intercambio.*/
	 	v[i]=v[j];
	 	v[j]=aux;
	 	aux =v[izq];
	 	v[izq]=v[j];
	 	v[j]=aux;
	 	ordenarAux(v,izq,j-1);
		ordenarAux(v,j+1,der);
	}
}
//*************************************************************
void ordenacionRapida (int v[],int n){
	ordenarAux(v,0,(n-1));
	if(UMBRAL>1){
		ord_ins(v,n);
	}
}
//*************************************************************

void test(void(*funcion)(int [], int)){

	int v1[17],v2[10];
	aleatorio(v1,17);
	descendente(v2,10);

	printf("---------------------------------------\n");
	printf("\nVector aleatorio\n");
	listarVector(v1,17);
	printf("\n");
	Ordenado(v1,17);
	printf("\n Una vez ordenado el vector: \n");
	funcion(v1,17);
	listarVector(v1,17);
	printf("\n");
	Ordenado(v1,17);
	printf("\n Vector descendente\n");
	listarVector(v2,10);
	printf("\n");
	Ordenado(v2,10);
	printf("\n Una vez ordenado el vector: \n");
	funcion(v2,10);
	listarVector(v2,10);
	printf("\n");
	Ordenado(v2,10);
}


//*************************************************************

double tiemposejecucion(int v[], int n,void (*ordenado)(int [],int), 
	void (*funcion)(int [],int)){
	int i;
	int k=1000;
	double t,ta,tb,t1,t2;

	ordenado(v,n); //inicializar vector

	ta=microsegundos();
	ord_ins(v,n);
	tb=microsegundos();
	t=tb-ta;

	if (t<500){
		printf("*");
		ta=microsegundos();
		for (i=0;i<k;i++){
			ordenado(v,n); //inicializar vector
			funcion(v,n); //llamada a funcion
		}
		tb=microsegundos();
		t1=tb-ta;
		ta=microsegundos();
		for(i=0;i<k;i++){
			funcion(v,n); //inicializar vector
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

void cotasord_ins(int n,double t,void(*ordenado)(int[],int)){

	if (ordenado==aleatorio){
		printf("%6d",n);
		printf("%15.6f",t);
		printf("%15.6f",t/(pow(n,1.9))); //cota subestimada
		printf("%15.6f",t/(pow(n,0.5)));   //cota ajustada
		printf("%15.6f",t/(pow(n,2.1))); //cota sobreestimada
		printf("\n");
	}else if(ordenado==ascendente){
		printf("%6d",n);
		printf("%15.6f",t);
		printf("%15.6f",t/(pow(n,0.9))); //cota subestimada
		printf("%15.6f",t/(pow(n,1)));			  //cota ajustada
		printf("%15.6f",t/(pow(n,1.1)));  //cota sobreestimada
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

void cotasOrd_rapida(int n,double t,void(*ordenado)(int[],int)){

	if (ordenado==aleatorio){
		printf("%6d",n);
		printf("%15.6f",t);
		printf("%15.7f",t/(pow(n,1.8))); //cota subestimada
		printf("%15.7f",t/(pow(n,2))); //cota ajustada
		printf("%15.7f",t/(pow(n,2.1)));  //cota sobreestimada
		printf("\n");
	}else if(ordenado==ascendente){
		printf("%6d",n);
		printf("%15.f",t);
		printf("%15.6f",t/(pow(n,0.7)));
		printf("%15.6f",t/(pow(n,0.97)));
		printf("%15.6f",t/(pow(n,1.1)));
		printf("\n");
	}else {
		printf("%6d",n);
		printf("%15.6f",t);
		printf("%15.8f",t/(pow(n,1.9)));
		printf("%15.8f",t/(pow(n,2)));
		printf("%15.8f",t/(pow(n,2.1)));
		printf("\n");
	}

}

//*************************************************************
 void resultadosord_ins(void(*ordenado)(int[],int)){
	int n,k=32000,v[k];
	double t;

	if(ordenado==aleatorio){
		printf("\n***********************************************************");
		printf("\n COTAS ALGORITMO DE ORDENACION POR insercion\n");
		printf("\n Ordenación con inicialización aleatoria\n");
		printf("***********************************************************");
		printf("\n%6s%13s%18s%15s%16s\n","n","t(n)","t(n)/n^1.9"
			,"t(n)/n^2","t(n)/n^2.1");printf("\n");
		for(n=500;n<=k;n=n*2){
			t=tiemposejecucion(v,n,aleatorio, ord_ins);
			cotasord_ins(n,t,aleatorio);printf("\n");}
	}else if(ordenado==ascendente){
			printf("\n Ordenación con inicialización ascendente\n");
			printf("*******************************************************");
			printf("\n%6s%14s%19s%12s%17s\n","n","t(n)","t(n)/n^(0.9)"
			,"t(n)/n","t(n)/n^1.1");printf("\n");
			for(n=500;n<=k;n=n*2){
				t=tiemposejecucion(v,n,ascendente, ord_ins);
				cotasord_ins(n,t,ascendente);printf("\n");}
		}else{
			printf("\n Ordenación con inicialización descendente\n");
			printf("*******************************************************");
			printf("\n%6s%14s%18s%16s%16s\n","n","t(n)","t(n)/n^(1.9)"
			,"t(n)/n^(2)","t(n)/n^(2.1)");printf("\n");
			for(n=500;n<=k;n=n*2){
				t=tiemposejecucion(v,n,descendente,ord_ins);
				cotasord_ins(n,t,descendente);
				printf("\n");}
		}
}
//*************************************************************
void resultadosOrd_rapida(void(*ordenado)(int[],int)){
	int n,k=32000,v[k];
	double t;

	if(ordenado==aleatorio){
		printf("\n***********************************************************");
		printf("\n COTAS ALGORITMO DE ORDENACION POR QUICKSORT\n");
		printf("***********************************************************\n");
		printf("\n Ordenación por quicksort con inicialización aleatoria\n");
		printf("***********************************************************");
		printf("\n%6s%14s%16s%18s%16s\n","n","t(n)","t(n)/n^(1.8)"
			,"t(n)/n^(2)","t(n)/n^(2.1)");printf("\n");
		for(n=500;n<=k;n=n*2){
			t=tiemposejecucion(v,n,aleatorio,ordenacionRapida);
			cotasOrd_rapida(n,t,aleatorio);printf("\n");}
	}else if(ordenado==ascendente){
			printf("\n Ordenación por quicksort con inicialización ascendente\n");
			printf("*******************************************************");
			printf("\n%6s%14s%18s%16s%16s\n","n","t(n)","t(n)/n^(0.7)"
			,"t(n)/n^(0.97)","t(n)/n^(1.1)");printf("\n");
			for(n=500;n<=k;n=n*2){
				t=tiemposejecucion(v,n,ascendente,ordenacionRapida);
				cotasOrd_rapida(n,t,ascendente);printf("\n");}
		}else{
			printf("\n Ordenación por quicksort con inicialización descendente\n");
			printf("*******************************************************");
			printf("\n%6s%14s%18s%15s%17s\n","n","t(n)","t(n)/n^(1.9)"
			,"t(n)/n^(2)","t(n)/n^(2.1)");
			printf("\n");
			for(n=500;n<=k;n=n*2){
				t=tiemposejecucion(v,n,descendente,ordenacionRapida);
				cotasOrd_rapida(n,t,descendente);printf("\n");}
		}
}
//*************************************************************

int main(){
	inicializar_semilla();
	printf("\n TEST INSERCION.\n");
	test(ord_ins);
	printf("\n TEST QUICKSORT.\n");
	test(ord_ins);

	/*Empezan os tempos de insercion*/
	resultadosord_ins(aleatorio);
	resultadosord_ins(aleatorio);
	resultadosord_ins(aleatorio);
	resultadosord_ins(ascendente);
	resultadosord_ins(ascendente);
	resultadosord_ins(ascendente);
	resultadosord_ins(descendente);
	resultadosord_ins(descendente);
	resultadosord_ins(descendente);
	
	
	/*Empezan os tempos quicksort*/
	resultadosOrd_rapida(aleatorio);
	resultadosOrd_rapida(aleatorio);
	resultadosOrd_rapida(aleatorio);
	resultadosOrd_rapida(ascendente);
	resultadosOrd_rapida(ascendente);
	resultadosOrd_rapida(ascendente);
	resultadosOrd_rapida(descendente);
	resultadosOrd_rapida(descendente);
	resultadosOrd_rapida(descendente);


	

	return 0;
}