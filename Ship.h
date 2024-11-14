#ifndef SHIP_H
#define SHIP_H

#include <string>

using namespace std;

class Ship {
public:
    int number;
    char letter;
    int size; 
    string name; 
    bool horizontal; 
    
    Ship(int number, char letter, int size, const string& name, bool horizontal);
};

#endif 