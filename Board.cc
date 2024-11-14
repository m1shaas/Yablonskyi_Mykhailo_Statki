#include "Board.h"
#include <set>
#include <algorithm>
#include <iostream>
using namespace std;

Board::Board() : shipCount(0) {
    fill_n(&board[0][0], 100, '.');
}

void Board::displayBoard() const {
    cout << "  ";
    for (char letter = 'A'; letter <= 'J'; ++letter) {
        cout << letter << " ";
    }
    cout << "\n";

    for (int i = 0; i < 10; i++) {
        cout << i << " ";
        for (int j = 0; j < 10; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

bool Board::deployShip(int number, char letter, int size, const string& name, bool horizontal) {
    if (!isShipPlacementValid(number, letter, size, horizontal)) {
        return false;
    }
    for (int i = 0; i < size; ++i) {
        board[horizontal ? number : number + i][horizontal ? letter - 'A' + i : letter - 'A'] = name[0];
    }

    ships.push_back(Ship(number, letter, size, name, horizontal));

    return true;
}

bool Board::isShipPlacementValid(int number, char letter, int size, bool horizontal) {
    if (horizontal) {
        if (letter - 'A' + size > 10) return false;
    } else {
        if (number + size > 10) return false;
    }

    for (int i = number - 1; i <= number + (horizontal ? 0 : size); ++i) {
        for (int j = letter - 'A' - 1; j <= letter - 'A' + (horizontal ? size : 1); ++j) {
            if (i >= 0 && i < 10 && j >= 0 && j < 10 && board[i][j] != '.') {
                return false; 
            }
        }
    }

    return true;
}

bool Board::makeShot(char letter, int number) {
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

    char& cell = board[x][y];

    if (cell == '.') {
        cell = 'O'; 
        return false;
    } else if (cell != 'O' && cell != 'X') { 
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

