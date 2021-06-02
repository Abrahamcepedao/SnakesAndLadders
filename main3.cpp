#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <limits>
#include <ctime>
#include "Serpiente.h"
#include "Escalera.h"
#include "Normal.h"

using namespace std;

bool isIn(int arr[], int num, int size){
    bool flag = false;
    for(int i = 0; i < size; i++){
        if(arr[i] == num){
            flag = true;
        }
    }
    return flag;
}

void crearSerpientes(int serp[],int s, int n){
    int num;
    srand(time(NULL));
    for(int i = 0; i < s; i++){
        num = rand() % n + 5;
        while(isIn(serp, num, s)){
            num = rand() % n + 5;
        }
        serp[i] = num;
    }
}

void crearEscaleras(int esc[], int serp[], int e, int s, int n){
    int num;
    srand(time(NULL));
    for(int i = 0; i < e; i++){
        num = rand() % n + 5;
        while(isIn(serp, num, s) || isIn(esc, num, e)){
            num = rand() % n + 5;
        }
        esc[i] = num;
    }
}

bool hasTwo(int arr[], int num, int size){
    int count =0;
    for(int i = 0; i < size; i++){
        if(arr[i] == num){
            count++;
        }
    }
    return count >= 2;
}

void crearTablero(Casilla *tablero[], int serp[], int esc[], int n, int s, int e){
    int serpientes[s];
    int sCount = 0, eCount = 0;
    int escaleras[e];
    for(int i = 0; i < n; i++){
        if(isIn(serp, i, s)){
            //crear serpiente
            srand(time(0));
            int max = i - 2;
            int num = rand() % max;
            while(hasTwo(serpientes,num, s)){
                num = rand() % max;
            }
            serpientes[sCount] = num;
            sCount++;
            tablero[i] = new Serpiente(i, num, 1);
        } else if(isIn(esc, i, e)){
            //crear escalera
            srand(time(0));
            int min = i + 1;
            int max = n - 2;
            int num = (rand() % (max+1-min)) + min;
            while(hasTwo(escaleras,num, e)){
                num = (rand() % (max + 1 - min)) + min;
            }
            num = num > (n - 1) ? (n - 1) : num;
            escaleras[eCount] = num;
            eCount++;
            tablero[i] = new Escalera(i, num, 2);
        } else{
            //crear casilla
            tablero[i] = new Normal(i, 0);
        }
    }
}

void imprimirTablero(Casilla *tablero[], int size){
    cout << "-------Tablero inicial-------\n";
    for(int i = size-1; i >= 0; i--){
        if((i+1) % (size/10) == 0){
            cout << "\n";
        }
        tablero[i]->print();
    }
    cout << "\n";
}

int getPos(int jugadores[], int num, int size){
    for(int i = 0; i < size; i++){
        if(jugadores[i] == num){
            return i;
        }
    }
    return 0;
}

void imprimirTablero2(Casilla *tablero[], int size, int jugadores[], int jugSize){
    for(int i = size-1; i >= 0; i--){
        if((i+1) % (size/10) == 0){
            cout << "\n";
        }
        if(isIn(jugadores, i, jugSize)){
            int pos = getPos(jugadores, i, jugSize);
            cout << "J";
            cout << (pos < 10 ? "0" : "");
            cout << pos+1 << "     ";
        } else{
            tablero[i]->print();
        }
        
    }
    cout << "\n";
}

int tirar(){
    srand(time(NULL));
    return rand() % 6 + 1;
}

int getNewPos(int pos, Casilla *tablero[], int num){
    while(tablero[pos]->getType() != 0){
        if(tablero[pos]->getType() == 1){
            Serpiente *serpiente = (Serpiente *)(tablero[pos]);
            pos = serpiente->getTarget();
            cout << "Jugador " << num << " haz caído en una serpiente.. bajarás a la posición " << (pos+1) << "\n";
        } else{
            Escalera *escalera = (Escalera *)(tablero[pos]);
            pos = escalera->getTarget();
            cout << "Jugador " << num << " haz caído en una escalera.. subirás a la posición " << (pos + 1) << "\n";
        }
    }
    return pos;
}

void cambiarPos(int jugadores[], int num, int lastPos, int size){
    for(int i = 0; i < size; i++){
        if(jugadores[i] == jugadores[num] && i != num && jugadores[i] != 0){
            cout << "Jugador " << (i+1) << " te han alcanzado..tu nueva posición es: " << lastPos << "\n";
            jugadores[i] = lastPos;
        }
    }
}

int main(){
    int t, e, s, numJugadores;

    //Tamaño del tablero
    cout << "Tamaño del tablero (30,40,50 o 60): ";
    cin >> t;
    while(t != 30 && t != 40 && t != 50 && t != 60){
        cout << "Ingreso un tamaño válido (30,40,50 o 60): ";
        cin >> t;
    }

    //Número de serpientes y escaleras
    cout << "Número de serpientes: ";
    cin >> s;
    cout << "Número de escaleras: ";
    cin >> e;
    while((s+e) >  t){
        cout << "Ingrese número de serpientes y escaleras válido (" << t/2 << " max)\n";
        cout << "Número de serpientes: ";
        cin >> s;
        cout << "Número de escaleras: ";
        cin >> e;
    }

    //posiciones de serpientes y escaleras
    int serpientes[s];
    int escaleras[e];
    crearSerpientes(serpientes, s, t-1);
    crearEscaleras(escaleras, serpientes, e, s, t-5);

    //crear tablero
    Casilla *tablero[t];
    crearTablero(tablero, serpientes, escaleras, t, s, e);

    

    //crear jugadores
    cout << "Número de jugadores (min 2): ";
    cin >> numJugadores;
    while(numJugadores < 2){
        cout << "Ingrese un número válido de jugadores: ";
        cin >> numJugadores;
    }
    int jugadores[numJugadores];
    for(int i = 0; i < numJugadores; i++){
        jugadores[i] = 0;
    }

    //imprimir tablero
    imprimirTablero(tablero, t);

    //jugar
    bool terminar = false;
    string x;
    int partidas = 0, pos, type;
    while(!terminar && partidas < (t/2)){
        partidas++;
        cout << "\n\n--Partida (" << partidas << "/" << (t/2) << ")\n";
        for(int i = 0; i < numJugadores; i++){
            int num = tirar(); //tirar dado
            int lastPos = jugadores[i];
            cout << "\n--Turno jugador " << (i + 1) << "\n";
            cout << "--Posición actual: " << (jugadores[i]+1) << "\n";
            cout << "--Número tirado: " << num << "\n";
            pos = jugadores[i] + num;//nueva posición
            if(pos < t-1){
                //posición según serpientes y escaleras
                jugadores[i] = getNewPos(pos, tablero, i+1);
                cout << "Nueva posición: " << (jugadores[i] + 1) << "\n";

                //checar si jugador alcanzó a otro
                cambiarPos(jugadores, i, lastPos, numJugadores);

                imprimirTablero2(tablero, t, jugadores, numJugadores);
            } else{
                jugadores[i] = (t - 1);
            }
            if(jugadores[i] >= (t-1)){
                cout << "Felicidades jugador " << (i + 1) << " haz ganado!\n\n";
                terminar = true;
                i = numJugadores;
            } else{
                cout << "Oprime cualquier tecla para continuar: ";
                cin >> x;
            }
        }
    }
    if(partidas > (t/2)){
        cout << "Se ha terminado el juego por haber alcanzado el límite de partidas\n\n";
    } else{
        cout << "El juego ha terminado\n\n";
    }

    return 0;
}