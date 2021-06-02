#include <iostream>
#include <string>
#ifndef Jugador_h
#define Jugador_h
using namespace std;
class Jugador{
    protected:
        int lastPos;
        int currentPos;
    public:
        int getLastPos(){ return lastPos; };
        int getCurrentPos() { return currentPos; };

        void setLastPos(int pos) { this->lastPos = pos; };
        void setCurrentPos(int pos){ this->currentPos = pos; };

        Jugador* operator+=(const int& num);

        Jugador();
        Jugador(int, int);
};
Jugador::Jugador(){
    this->lastPos = 0;
    this->currentPos = 0;
}
Jugador::Jugador(int last, int current){
    this->lastPos = last;
    this->currentPos = current;
}

Jugador* Jugador::operator+=(const int& num){
    /* int last = this->currentPos;
    int current = this->currentPos + num;
    Jugador jugador(last, current);
    return jugador; */
    cout << "operator += " << (this->currentPos+num) << endl;
    this->lastPos = this->currentPos;
    this->currentPos += num;
    cout << "operator += " << (this->currentPos) << endl;
    return this;
}

#endif