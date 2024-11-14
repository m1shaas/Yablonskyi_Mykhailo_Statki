#include "Ship.h"

Ship::Ship(int number, char letter, int size, const string& name, bool horizontal)
    : number(number), letter(letter), size(size), name(name), horizontal(horizontal) {}