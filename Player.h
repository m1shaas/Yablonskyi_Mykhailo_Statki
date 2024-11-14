#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"

using namespace std;

class Player {
private:
   
    Board board;
public:
    string nickname;
    Player(const string& name);
    void displayBoard() const;
    void deployShips(); 
    bool makeShoot(Player& opponent);
    bool allShipsSunk() const;
    string getNickname() const;
};

#endif 