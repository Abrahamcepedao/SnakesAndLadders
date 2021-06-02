#include <iostream>
#include <string>
#ifndef Casilla_h
#define Casilla_h
using namespace std;

class Casilla {
    protected:
        int pos; // posición
        int type; // 0 = normal, 1 = serpiente, 2 = escalera
    public:
        int getPos(){ return pos; };
        int  getType() {return type; };
        virtual void print() = 0;

        Casilla(int, int);
};

Casilla::Casilla(int pos, int type){
    this->pos = pos;
    this->type = type;
}

#endif