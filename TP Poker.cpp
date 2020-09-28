#include <iostream> 
#include <string.h> 
#include <cstring>
#include <cmath> 
#include <cstdlib>
#include <time.h>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
using namespace std;

struct Cartas{ 
	char palo[20];
	int numero;
	bool salio;
};

struct Ranking{
	int jug;
	int puntos;
	int rondas;
};

struct Nodo{
	Ranking info;
	Nodo* sgte;
};

void crearVectorDeMazo(Cartas[]);
void repartirCartas(Cartas[],Cartas[],int);
void reiniciarCartas(Cartas[]);
void mostrarYCambiarCartas(Cartas[], int, Cartas[], int, int, int);
void muestraCartas(Cartas[], int, Cartas[], int, int);
void mostrarResultados(int, int[][9], int);
void meterCartaEnMazo(Cartas[], int, Cartas[], int);
void reiniciarPuntaje(Cartas[], int, int[][9]);
void ordenarCartasPorNumero(Cartas[], int);
int escaleraReal(Cartas[], int);
int escalera(Cartas[], int);
int full(Cartas[], int);
int color(Cartas[], int);
int trio(Cartas[], int);
int doblePareja(Cartas[], int);
int pareja(Cartas[], int);
int poker(Cartas[], int);
void calcularResultados(Cartas[], int[][9], int);
Nodo* insertarOrdenado(Nodo*&, int);
void ranking(int[][9], int, Nodo*&, int);

int main() {
	int rondas, J, M, j=0;
	Nodo* lista=NULL;

	cout<<"BIENVENIDOS A POKER EN C++"<<endl;
	cout<<"Ingrese la cantidad de rondas que se jugaran por jugador"<<endl;
	cin>>rondas;
	cout<<"Ingrese la cantidad de jugadores con un tope maximo de 8 jugadores"<<endl;
	cin>>J;
	
	while(J>8){
		cout<<"NO pueden ser mas de 8 jugadores"<<endl;
		cout<<"Vuelva a ingresar la cantidad de jugadores con un tope maximo de 8"<<endl;
		cin>>J;
	}
	
	int jugadores[J][9];
	M=J*5;	
	Cartas mazo[52];
	Cartas cart[M];
	
	reiniciarPuntaje(cart, J, jugadores);
	crearVectorDeMazo(mazo);
	
	for(int l=0;l<rondas;l++){
		cout<<"-------"<<endl;
		cout<<"RONDA "<<l+1<<endl;
		cout<<"-------"<<endl;
		
		repartirCartas(mazo, cart, M);
		muestraCartas(cart, M, mazo, J, j);
		calcularResultados(cart, jugadores, J);
		cout<<"Si un jugador obtuvo un As en la mano, se le otorgan 10 puntos adicionales"<<endl;
		mostrarResultados(l, jugadores, J);
		reiniciarCartas(mazo);
	}
	
	ranking(jugadores, J, lista, rondas);
	
	return 0;
}

void crearVectorDeMazo(Cartas mazo[]) {
	int pica=1, diamante=1, trebol=1, corazon=1;
    for(int i=0; i<52; i++){
        if(i<=12){
            mazo[i].numero=pica;
            strcpy(mazo[i].palo, "pica");
            mazo[i].salio=false;
            pica++;
        }   else if(i>=13 && i<=25){
            mazo[i].numero=corazon;
            strcpy(mazo[i].palo, "corazon");
            mazo[i].salio=false;
            corazon++;
        }   else if(i>=26 && i<=38){
            mazo[i].numero=trebol;
            strcpy(mazo[i].palo, "trebol");
            mazo[i].salio=false;
            trebol++;
        } else {
            mazo[i].numero=diamante;
            strcpy(mazo[i].palo, "diamante");
            mazo[i].salio=false;
            diamante++;
        }
    }
}

void reiniciarCartas(Cartas mazo[]){
	for(int i=0;i<52;i++){
		mazo[i].salio=false;
	}
}

void repartirCartas(Cartas mazo[], Cartas cart[], int M){
	int num;
	srand(time(NULL));
	for(int i=0;i<M;i++){
		num=rand()%52;
		while(mazo[num].salio){
				num=rand()%M; //genera una posicion aleatoria para el vector
		}
		strcpy(cart[i].palo,mazo[num].palo);
		cart[i].numero=mazo[num].numero;
		
		mazo[num].salio=true; //la carta que ya salio se anula
	}
}

void meterCartaEnMazo(Cartas cart[], int b, Cartas mazo[], int i){
		int j=0;
		while(mazo[j].salio){
			j++;
		}
		mazo[j].numero=cart[(b-1)+(i*5)].numero;
		strcpy(mazo[j].palo,cart[(b-1)+(i*5)].palo);
		mazo[j].salio=false;
}

void mostrarYCambiarCartas(Cartas cart[], int M, Cartas mazo[], int J, int i, int j){
	int b, h=0, num;
	char a[2], t;
	while(h<5){
		if(cart[j+(i*5)].numero==11){
			t='J';
			cout<<t<<" de "<<cart[j+(i*5)].palo<<endl;
		} else {
			if(cart[j+(i*5)].numero==12){
				t='Q';
				cout<<t<<" de "<<cart[h].palo<<endl;
			} else {
				if(cart[j+(i*5)].numero==13){
					t='K';
					cout<<t<<" de "<<cart[h].palo<<endl;
				} else {
					cout<<cart[j+(i*5)].numero<<" de "<<cart[j+(i*5)].palo<<endl;
				}
			}
		}
		h++;
		j++;
	}
	cout<<"Quiere cambiar las cartas? Ingrese SI o NO"<<endl;
	cout<<"Recuerde que solo tiene 5 cambios posibles, uno por cada carta"<<endl;
	cin>>a;
	
	if(strcmp(a,"NO")==0 || strcmp(a,"no")==0){
		return;
	}
	while(strcmp(a,"SI")==0 || strcmp(a,"si")==0){
		cout<<"Ingrese el numero de carta que quiere cambiar. Ejemplo, '3' si quiere cambiar la tercera carta"<<endl;
		cin>>b;
		meterCartaEnMazo(cart, b, mazo, i);
		
		srand(time(NULL));
		num=rand()%52;
		while(mazo[num].salio){
				num=rand()%M;
		}
		strcpy(cart[(b-1)+(i*5)].palo,mazo[num].palo);
		cart[(b-1)+(i*5)].numero=mazo[num].numero;
		mazo[num].salio=true;

		cout<<"Desea cambiar otra carta? Ingrese SI o NO"<<endl;
		cin>>a;
	}
		j=j-5;
		h=0;
		cout<<"Las nuevas cartas del jugador "<<i+1<<" son:"<<endl;
		while(h<5){
			if(cart[j+(i*5)].numero==11){
			t='J';
			cout<<t<<" de "<<cart[j+(i*5)].palo<<endl;
			} else {
				if(cart[j+(i*5)].numero==12){
				t='Q';
				cout<<t<<" de "<<cart[h].palo<<endl;
				} else {
					if(cart[j+(i*5)].numero==13){
					t='K';
					cout<<t<<" de "<<cart[h].palo<<endl;
					} else {
						cout<<cart[j+(i*5)].numero<<" de "<<cart[j+(i*5)].palo<<endl;
					}
				}
			}
			h++;
			j++;
		}
}

void muestraCartas(Cartas cart[], int M, Cartas mazo[], int J, int j){
	for(int i=0;i<J;i++){ 
		cout<<"Las 5 cartas del jugador "<<i+1<<" son:"<<endl;
		mostrarYCambiarCartas(cart, M, mazo, J, i, j);
		if(i<(J-1)){
			cout<<"Presione ENTER para continuar"<<endl;
			getch();
			system("CLS");
		}
	}	
}

void ordenarCartasPorNumero(Cartas cart[], int jug){
	int aux, i=0;
	char auxi[25];
	//burbujeo para ordenar cartas
	for(i; i<5; i++){
		for(int j=1;j<5-i;j++){
			if(cart[(jug*5)+j-1].numero>cart[jug*5+j].numero){
				aux=cart[jug*5+(j-1)].numero;
				strcpy(auxi,cart[jug*5+(j-1)].palo);
				cart[jug*5+(j-1)].numero=cart[jug*5+j].numero;
				strcpy(cart[jug*5+(j-1)].palo,cart[jug*5+j].palo);
				cart[jug*5+j].numero=aux;
				strcpy(cart[jug*5+j].palo,auxi);
			}
		}
	}
	i=0;
}

void reiniciarPuntaje(Cartas cart[], int J, int jugadores[][9]){
	for(int i=0;i<J;i++){
		for(int j=0;j<9;j++){
			jugadores[i][j]=0;
		}
	}
}

int escaleraReal(Cartas cart[], int jug){
	int j=1, k=1;
	for(j;j<5;j++){
		if(cart[(jug*5)+j-1].numero==cart[jug*5+j].numero-1 && strcmp(cart[(jug*5)+j-1].palo,cart[jug*5+j].palo)==0){
			k++;
			if(k==5){
				return 100;
			}
		}
	}
	return 0;
}

int escalera(Cartas cart[], int jug){
	int j=1, k=1;
	for(j;j<5;j++){
		if(cart[(jug*5)+j-1].numero==cart[jug*5+j].numero-1){
			k++;
			if(k==5 && escaleraReal(cart, jug)!=100){
				return 70;
			}
		}
	}
	return 0;
}

int poker(Cartas cart[], int jug){
	int k=1;
	for(int j=1;j<5;j++){
		if(cart[(jug*5)+j-1].numero==cart[(jug*5)+j].numero){
			k++;
		}
	}
	if(k==4 && escaleraReal(cart, jug)!=100 && escalera(cart, jug)!=70){
		return 60;
	}
	return 0;
}

int full(Cartas cart[], int jug){
	if(cart[(jug*5)].numero==cart[jug*5+1].numero-1==cart[jug*5+2].numero-2){
		if(cart[(jug*5)+3].numero==cart[jug*5+4].numero-1){
			if(escaleraReal(cart, jug)!=100 && escalera(cart, jug)!=70 && poker(cart, jug)!=60){
				return 50;
			}
		}
	}
	if(cart[(jug*5)].numero==cart[jug*5+1].numero-1){
		if(cart[(jug*5)+2].numero==cart[jug*5+3].numero-1==cart[jug*5+4].numero-2){
			if(escaleraReal(cart, jug)!=100 && escalera(cart, jug)!=70 && poker(cart, jug)!=60){
				return 50;	
			}
		} 
	}
	return 0;
}

int color(Cartas cart[], int jug){
	int j=1, k=1;
	for(j;j<5;j++){
		if (strcmp(cart[(jug*5)+j-1].palo,cart[jug*5+j].palo)==0){
			k++;
		}
	}
	if(k==5 && escaleraReal(cart, jug)!=100 && escalera(cart, jug)!=70 && poker(cart, jug)!=60){
		if(full(cart, jug)!=50){
			return 40;
		}
	}
	return 0;
	
}

int trio(Cartas cart[], int jug){
	int j=1,k=1;
	while(j<5){
		if(cart[(jug*5)+j-1].numero==cart[(jug*5)+j].numero){
			j++;
			if(cart[(jug*5)+j-1].numero==cart[(jug*5)+j].numero){
				k++;
			}
		} else {
			j++;
		}	
	}
	if(k==3 && escaleraReal(cart, jug)!=100 && escalera(cart, jug)!=70 && poker(cart, jug)!=60){
		if(full(cart, jug)!=50 && color(cart, jug)!=40){
			return 30;
		}
	}
	return 0;
}

int doblePareja(Cartas cart[], int jug){
	int k=0;
	for(int j=1;j<5;j++){
		if(cart[(jug*5)+j-1].numero==cart[(jug*5)+j].numero){
			k++;
		}
	}
	if(k==2 && escaleraReal(cart, jug)!=100 && escalera(cart, jug)!=70 && poker(cart, jug)!=60){
		if(full(cart, jug)!=50 && color(cart, jug)!=40 && trio(cart, jug)!=30){
			return 20;	
		}
	} 
	return 0;
	
}

int pareja(Cartas cart[], int jug){
	for(int j=1;j<5;j++){
		if(cart[(jug*5)+j-1].numero==cart[(jug*5)+j].numero){
			if(escaleraReal(cart, jug)!=100 && escalera(cart, jug)!=70 && poker(cart, jug)!=60){
			if(full(cart, jug)!=50 && color(cart, jug)!=40 && trio(cart, jug)!=30 && doblePareja(cart, jug)!=20){
				return 10;	
			}
			}
		}
	}
	return 0;
}

void calcularResultados(Cartas cart[], int jugadores[][9], int J){
	for(int jug=0;jug<J;jug++){
		ordenarCartasPorNumero(cart,jug);
		
		jugadores[jug][0]+=escaleraReal(cart, jug);
		jugadores[jug][1]+=escalera(cart, jug);
		jugadores[jug][2]+=poker(cart, jug);
		jugadores[jug][3]+=full(cart, jug);
		jugadores[jug][4]+=color(cart, jug);
		jugadores[jug][5]+=trio(cart, jug);
		jugadores[jug][6]+=doblePareja(cart, jug);
		jugadores[jug][7]+=pareja(cart, jug);
		
		for(int i=0;i<5;i++){
			if(cart[(jug*5)+i].numero==1){
				jugadores[jug][8]+=10;
			}
		}	
	}
	
    for(int jug=0;jug<J;jug++){ //este casillero suma el total de puntajes, por jugador
		for(int i=0;i<8;i++){
			jugadores[jug][8]+=jugadores[jug][i];			
		}	
	}
}

void mostrarResultados(int l, int jugadores[][9], int J){
	cout<<"Los resultados de la ronda "<<l+1<<" son:"<<endl;
	cout<<"Jugador"<<"\t"<<"Puntos totales acumulados"<<endl;
	for(int b=0;b<J;b++){
		cout<<b+1<<"\t"<<jugadores[b][8]<<endl;
	}
}

Nodo* insertarOrdenado(Nodo*& lista, int k){
	Nodo* p=new Nodo();
	p->info.puntos=k;
	if(lista==NULL || k>lista->info.puntos){
		p->sgte=lista;
		lista=p;
	} else {
		Nodo* q=lista;
		while(q->sgte!=NULL && k<q->sgte->info.puntos){
			q=q->sgte;
		}
		p->sgte=q->sgte;
		q->sgte=p;
	}
	return p;
}

void ranking(int jugadores[][9], int J, Nodo*& lista, int rondas){
	Nodo* p=new Nodo();
	char a[2];

	for(int jug=0;jug<J;jug++){
		p=insertarOrdenado(lista, jugadores[jug][8]);
		p->info.puntos=jugadores[jug][8];	
		p->info.jug=jug;
		p->info.rondas=rondas;
	}
	Nodo* aux=lista;
	cout<<"Los resultados de esta partida fueron: "<<endl;
	cout<<"RANKING"<<endl;
	cout<<"-------"<< endl;
	
	cout<<"Jugador ganador: "<<(aux->info.jug)+1<<" con "<<aux->info.puntos<<" puntos"<<endl;
	aux=aux->sgte;
	cout<<"-------"<<endl;
	cout<<"Jugador"<<"\t"<<"Puntos"<<endl;
	while(aux!=NULL){
		cout<<(aux->info.jug)+1<<"\t"<<aux->info.puntos<<endl;
		aux=aux->sgte;
	}
}

