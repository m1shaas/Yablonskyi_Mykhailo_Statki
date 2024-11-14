#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>
#include <set>
#include "Ship.h"
using namespace std;


class Board {
public:
    Board(); 

    void displayBoard() const; 
    bool isShipPlacementValid(int number, char letter, int size, bool horizontal); 
    bool deployShip(int number,char letter, int size, const std::string& name, bool horizontal);
    bool makeShot(char letter, int number); 
    bool areAllShipsSunk() const; 
    std::set<std::pair<int, int>> shotHistory;

private:
    char board[10][10]; 
    int shipCount; 
    vector<Ship> ships; 
};

#endif 
