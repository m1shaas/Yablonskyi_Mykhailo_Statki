#include "Board.h"
#include <set>
#include <algorithm>
#include <iostream>
using namespace std;

Board::Board() : shipCount(0) {
    fill_n(&board[0][0], 100, '.');
}


void Board::displayBoard() const {
    std::cout << "  ";
    for (char letter = 'A'; letter <= 'J'; ++letter) {
        std::cout << letter << " ";
    }
    std::cout << "\n";

    for (int i = 0; i < 10; ++i) {
        std::cout << i << " ";
        for (int j = 0; j < 10; ++j) {
            std::cout << board[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void Board::displayBoards(const Board& opponentBoard) const {
    cout << "  ";
    for (char letter = 'A'; letter <= 'J'; ++letter) {
        cout << letter << " ";
    }
    cout << "      ";
    for (char letter = 'A'; letter <= 'J'; ++letter) {
        cout << letter << " ";
    }
    cout << "\n";

    for (int i = 0; i < 10; i++) {
        cout << i << " ";
        for (int j = 0; j < 10; j++) {
            cout << board[i][j] << " ";  
        }
        cout << "    " << i << " ";
        for (int j = 0; j < 10; j++) {
            char cell = opponentBoard.board[i][j];
            if (cell == 'X' || cell == 'O') {
                cout << cell << " ";  
            } else {
                cout << '.' << " ";  
            }
        }
        cout << "\n";
    }
}




bool Board::deployShip(int number, char letter, int size, const string& name, bool horizontal) {
    string errorMessage;

    
    Ship newShip(number, letter, size, name, horizontal);

    
    if (!isShipPlacementValid(newShip, errorMessage)) {
        std::cout << "Nie mozna umiescic statku: " << errorMessage << "\n";
        return false;
    }

    
    for (int i = 0; i < size; ++i) {
        int x = horizontal ? number : number + i;
        int y = horizontal ? letter - 'A' + i : letter - 'A';
        board[x][y] = name[0];
    }

    
    ships.push_back(newShip);
    return true;
}

bool Board::isShipPlacementValid(const Ship& ship, string& errorMessage) {
    
    if (ship.horizontal) {
        if (ship.letter - 'A' + ship.size > 10) {
            errorMessage = "Statek wystaje poza granice planszy w poziomie.";
            return false;
        }
    } else {
        if (ship.number + ship.size > 10) {
            errorMessage = "Statek wystaje poza granice planszy w pionie.";
            return false;
        }
    }

    
    for (int i = ship.number - 1; i <= ship.number + (ship.horizontal ? 0 : ship.size); ++i) {
        for (int j = ship.letter - 'A' - 1; j <= ship.letter - 'A' + (ship.horizontal ? ship.size : 1); ++j) {
            if (i >= 0 && i < 10 && j >= 0 && j < 10 && board[i][j] != '.') {
                errorMessage = "Statek znajduje sie zbyt blisko innego statku.";
                return false;
            }
        }
    }

    return true;
}



bool Board::makeShot(char letter, int number, Board& opponentBoard) {
    if (letter < 'A' || letter > 'J' || number < 0 || number >= 10) {
        return false; 
    }

    int x = number;
    int y = letter - 'A';

    if (shotHistory.find({x, y}) != shotHistory.end()) {
        cout << "Juz strzelano w tym miejscu. Wybierz inny.\n";
        return false;
    }

    shotHistory.insert({x, y});

    char& cell = opponentBoard.board[x][y];  

    
    if (cell == '.') {
        cell = 'O';  
        return false;
    } 
    
    else if (cell != 'O' && cell != 'X') {  
        cell = 'X'; 
        return true;
    }

    return false;
}



bool Board::areAllShipsSunk() const {
    for (const auto& ship : ships) {
        bool shipSunk = true;
        for (int j = 0; j < ship.size; ++j) {
            int x = ship.horizontal ? ship.number : ship.number + j;
            int y = ship.horizontal ? ship.letter - 'A' + j : ship.letter - 'A';
            if (board[x][y] != 'X') { 
                shipSunk = false;
                break;
            }
        }
        if (!shipSunk) {
            return false; 
        }
    }
    return true; 
}

