#include <iostream>
#include <string>
#ifndef Serpiente_h
#define Serpiente_h
#include "Casilla.h"
using namespace std;
class Serpiente : public Casilla{
    protected:
        int target; // target position
    public:
        int getTarget(){ return target; };
        void print();

        Serpiente(int, int, int);
};

Serpiente::Serpiente(int pos, int target, int type):Casilla(pos, type){
    this->target = target;
}

void Serpiente::print(){
    cout << "S";
    cout << ((getPos() + 1) < 10 ? "0" : "" );
    cout << (getPos() + 1);
    cout << ((target+1) < 10 ? "-0" : "-");
    cout << (target+1) << "  ";
}

#endif