/*
*Practica 4
*Grupo 1.3
Jose Manuel Amestoy Lopez manuel.amestoy
*Maria Riveiro Carballo m.riveiro.carballo
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
// Number of vertices in the graph

#define TAM_MAX 1600
#define inf 100000

typedef int ** matriz;

typedef struct {
	int x, y, peso;
}arista;

typedef arista tipo_elemento;

typedef struct {
	int cabeza, final, tam;
	tipo_elemento vector [TAM_MAX];
}cola;



void crear_cola (cola *c){
	c->tam=0;
	c->cabeza=0;
	c->final=-1;
}

int cola_vacia (cola c){
	return (c.tam ==0);
}

void incrementar (int *x){
	if(++(*x)==TAM_MAX){
        *x=0;
    }
}
void insertar (tipo_elemento x, cola* c){
	if(c->tam==TAM_MAX){
        printf("Error: La cola está llena: %d\n",c->tam);
        exit (EXIT_FAILURE);
    }
    c->tam++;
    incrementar (&(c->final));
    c->vector[c->final] =x;
}
tipo_elemento quitar_primero (cola* c){
    tipo_elemento x;
	if(cola_vacia(*c)){
		printf("Error : Cola vacia.\n");
        exit (EXIT_FAILURE);
	}else{
        c->tam=-1;
        x=c->vector[c->cabeza];
        incrementar (&(c->cabeza));
        return x;
    }
}
tipo_elemento primero (cola c){
    if(cola_vacia(c)==c.tam){
        printf("Error: Cola vacia.\n");
        exit (EXIT_FAILURE);
    }else{
        return c.vector[c.cabeza];
    }
}
void mostrar_cola (cola c){
    int i, peso = 0;
    for(i = 0 ; i < c.tam -1 ; i++){
        printf("(%2d,%2d), "
        ,c.vector[i].x,c.vector[i].y);
        peso += c.vector[i].peso;
    }
    printf("Peso : %2d \n\n", peso);
}
//FUNCIONES PARA CREAR GRAFOS ALEATORIOS
matriz crear_matriz(int n) {
    int i;
    matriz aux;
    if ((aux = malloc(n*sizeof(int *))) == NULL)
        return NULL;
    for (i=0; i<n; i++)
        if ((aux[i] = malloc(n*sizeof(int))) == NULL)
            return NULL;
    return aux;
}

void asignar_matriz(matriz m, int n, int aux[][n]){
	int i;
	int j;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			m[i][j] = aux[i][j];
		}
	}

}
void mostrar_matriz(matriz m, int n){
	int i;
	int j;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			printf("\t%d", m[i][j]);
		}
		printf("\n");
	}
}
void inicializar_matriz(matriz m, int n) {
/* Crea un grafo completo no dirigido con valores aleatorios entre 1 y n */
    int i, j;
    for (i=0; i<n; i++)
        for (j=i+1; j<n; j++)
            m[i][j] = rand() % n + 1;
    for (i=0; i<n; i++)
        for (j=0; j<=i; j++)
            if (i==j)
                m[i][j] = 0;
            else
                m[i][j] = m[j][i];
}
void liberar_matriz(matriz m, int n) {
    int i;
    for (i=0; i<n; i++)
        free(m[i]);
    free(m);
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
cola Prim (matriz M , int n){
	cola *T;
	crear_cola(T);
	int min, i, j, k=0,l=0;
	int *masProximo = (int *) malloc(n*sizeof(int));
	int *distanciaMinima = (int *) malloc(n*sizeof(int));
	distanciaMinima[0] = -1;
	for (i=1; i<n; i++){
		masProximo[i]=0;
		distanciaMinima[i] = M[i][0];
	}
	do{
		min=inf;
		for (j=1;j<n; j++){
			if((0<=distanciaMinima[j])&&(distanciaMinima[j]<min)){
				min=distanciaMinima[j];
				k=j;
			}
		}
		T= T+ masProximo[k];
		distanciaMinima[k]=-1;
		for(j=1;j<n;j++){
			if(M[j][k]< distanciaMinima[j]){
				distanciaMinima [j]= M[j][k];
				masProximo[j]=k;
			}
		}
		l++;
	}while(l==n-1);
	free(masProximo);
	free(distanciaMinima);
	return *T;
}

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void prim(matriz m, int nodos, cola *aristas) {
	/* calcular el árbol de recubrimiento mínimo devolviendo
	las aristas del arbol en la cola ’aristas’ */
	int min, i, j, w, k=0;
	arista a;
	int *masProximo = (int *) malloc(nodos*sizeof(int));
	int *distanciaMinima = (int *) malloc(nodos*sizeof(int));
	crear_cola(aristas);
	distanciaMinima[0] = -1;
	for(i = 1; i < nodos; i++) {
		masProximo[i] = 0;
		distanciaMinima[i] = m[i][0];
	}
	for(w=0;w<nodos;w++){
		min = inf;
		for(j=1;j<nodos;j++){
			if((distanciaMinima[j]>=0)&&(distanciaMinima[j]<min)){
				min=distanciaMinima[j];
				k=j;
			}
		}
		a.x = masProximo[k];
		a.peso=min;
		a.y=k;
		insertar(a,aristas);
		distanciaMinima[k]=-1;
		for(j=1;j<nodos;j++){
			if(m[j][k] < distanciaMinima[j]){
				distanciaMinima[j] = m[j][k];
				masProximo[j] = k;
			}
		}
	}
	free(masProximo);
	free(distanciaMinima);
}
//FUNCIONES TIEMPOS

double microsegundos() {
/* obtiene la hora del sistema en microsegundos */
	struct timeval t;
	if (gettimeofday(&t, NULL) < 0 )
		return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}

double tiemposejecucion(matriz m, int n){
	int i;
	int k=1000;
	double t,ta,tb,t1,t2;
	cola T;
	
	inicializar_matriz(m, n);
	crear_cola(&T);
	ta=microsegundos();
	prim(m, n, &T);
	tb=microsegundos();
	t=tb-ta;
	
	
	if (t < 500){
		ta=microsegundos();
		for (i=0;i<k;i++){
			inicializar_matriz(m, n);
			prim(m, n, &T); //llamada a funcion
		}
		tb=microsegundos();
		t1=tb-ta;
		ta=microsegundos();
		for(i=0;i<k;i++){
			prim(m, n, &T); //inicializar matriz
		}
		tb=microsegundos();
		t2=tb-ta;
		t=(t1-t2)/k;
	}
	return t;
}

//FUNCION RESULTADOS
void resultados_Prim(){
	int n;
	double t = 1;
	matriz m;
	
    	printf("\n*******************************************************************");
	printf("\n COTAS ALGORITMO  DE PRIM\n");
	printf("*******************************************************************\n");
	printf("\n%6s%14s%16s%18s%16s\n","n","t(n)","t(n)/n^(1.95)","t(n)/n^(2.10)","t(n)/n^(2.30)\n");//cotas
	
	for(n = 25; n <= TAM_MAX ; n *= 2){
		m = crear_matriz(n);
		inicializar_matriz(m, n);
    		t = tiemposejecucion(m, n);
    		printf("%s", (t<500)? "*" : " ");
    		printf("%6d",n);
		printf("%15.6f",t);
		printf("%15.7f",t/(pow(n,1.95))); //cota subestimada
		printf("%15.7f",t/(pow(n,2.10))); //cota ajustada
		printf("%15.7f",t/(pow(n,2.30)));  //cota sobreestimada
		printf("\n");
		liberar_matriz(m, n);
	}
}

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void test() {
	cola T;
	crear_cola(&T);
	matriz m1 = crear_matriz(5);
	matriz m2 = crear_matriz(4);
	matriz m3 = crear_matriz(7);

	int aux[4][4] = {{0,1,4,7},{1,0,2,8},{4,2,0,3},{7,8,3,0}};
	
	int aux2[5][5] = {{0,1,8,4,7}, {1,0,2,6,5}, {8,2,0,9,5}, {4,6,9,0,3}, {7,5,5,3,0}};
	
	int aux3[7][7] = {{0,7,99,5,99,99,99}, {7,0,8,9,7,99,99}, {99,8,0,99,5,99,99},
					{5,9,99,0,15,6,99}, {99,7,5,15,0,8,9}, {99,99,99,6,8,0,11},
					{99,99,99,99,9,11,0}};

	asignar_matriz(m1,5,aux2);
	asignar_matriz(m2,4,aux);
	asignar_matriz(m3,7,aux3);
	//PrimerGrafo
	printf("Figura 1\n");
	mostrar_matriz(m1,5);
	prim(m1,5,&T);
	mostrar_cola(T);
	
	liberar_matriz(m1, 5);
		
	//SegundoGrafo
	printf("Figura 2\n");
	mostrar_matriz(m2,4);
	prim(m2,4,&T);
	mostrar_cola(T);
	
	liberar_matriz(m2, 4);
		
	//TercerGrafo
	printf("Figura 3\n");
	mostrar_matriz(m3,7);
	prim(m3,7,&T);
	mostrar_cola(T);

	liberar_matriz(m3, 7);
}
//RANDOM
void inicializar_semilla(){
	srand(time(NULL));
}
int main(){
    inicializar_semilla();
    printf("\n TEST PRIM. \n\n");
    test();
    printf("\nPRIMERA INTERACION\n");
    resultados_Prim();
    printf("\nSEGUNDA INTERACION\n");
    resultados_Prim();
    printf("\nTERCERA INTERACION\n");
    resultados_Prim();
    return 0;
}
