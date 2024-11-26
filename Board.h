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
    void displayBoards(const Board& opponentBoard) const; 
    bool isShipPlacementValid(const Ship& ship, string& errorMessage); 
    bool deployShip(int number,char letter, int size, const std::string& name, bool horizontal);
    bool makeShot(char letter, int number,Board& opponentBoard); 
    bool areAllShipsSunk() const; 
    std::set<std::pair<int, int>> shotHistory;

private:
    char board[10][10]; 
    int shipCount; 
    vector<Ship> ships; 
};

#endif 
