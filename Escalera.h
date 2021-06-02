#include <iostream>
#include <string>
#ifndef Escalera_h
#define Escalera_h
#include "Casilla.h"
using namespace std;
class Escalera : public Casilla{
    protected:
        int target; // target position
    public:
        int getTarget(){ return target; };
        void print();

        Escalera(int, int, int);
};

Escalera::Escalera(int pos, int target, int type):Casilla(pos, type){
    this->target = target;
}

void Escalera::print()
{
    cout << "E";
    cout << ((getPos() + 1) < 10 ? "0" : "");
    cout << (getPos() + 1);
    cout << ((target + 1) < 10 ? "-0" : "-");
    cout << (target + 1) << "  ";
}

#endif