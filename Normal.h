#include <iostream>
#include <string>
#ifndef Normal_h
#define Normal_h
#include "Casilla.h"
using namespace std;
class Normal : public Casilla{
    public:
        void print();

        Normal(int, int);
};

Normal::Normal(int pos, int type):Casilla(pos, type){
}

void Normal::print(){
    cout << "N";
    cout << ((pos+1) < 10 ? "0" : "");
    cout << (pos+1) << "     ";
}

#endif