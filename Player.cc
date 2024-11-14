#include "Player.h"
#include <iostream>
#include <limits>

Player::Player(const std::string& name) : nickname(name) {}

void Player::displayBoard() const {
    std::cout << "Plansza gracza " << nickname << ":\n";
    board.displayBoard(); 

}




void Player::deployShips() {
    int sizes[4] = {1, 2, 3, 4}; 
    int counts[4] = {4, 3, 2, 1}; 
    std::string names[4] = {"Jednopokladowy", "Dwupokladowy", "Trzypokladowy", "Czteropokladowy"};

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < counts[i]; ++j) {
            int number;
            char letter;
            bool horizontal;
            std::cout << "Gracz " << nickname << ", umiesc " << names[i] << " (rozmiar " << sizes[i] << "):\n";
            
            bool validInput = false;
            while (!validInput) {
                std::cout << "Podaj wspolrzedne (liczba, litera): ";
                
     
                while (!(std::cin >> number) || number < 0 || number >= 10) {
                    std::cout << "Bledna liczba, wprowadz liczbe od 0 do 9: ";
                    std::cin.clear(); 
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                }

                std::cin >> letter;
                if (letter >= 'A' && letter <= 'J') {
                    validInput = true;
                } else {
                    std::cout << "Bledny symbol, wprowadz literke od A do J.\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }

            if (sizes[i] > 1) {
                std::cout << "Czy statek jest poziomy? (1 - tak, 0 - nie): ";
                std::cin >> horizontal;
            }

            while (!board.deployShip(number, letter, sizes[i], names[i], horizontal)) {
                std::cout << "Nie mozna umiescic statku. Sprobuj ponownie.\n";
                std::cout << "Podaj wspolrzedne (liczba, litera): ";
                std::cin >> number >> letter;
                if (sizes[i] > 1) {
                    std::cout << "Czy statek jest poziomy? (1 - tak, 0 - nie): ";
                    std::cin >> horizontal;
                }
            }

            displayBoard();
        }
    }
}


bool Player::makeShoot(Player& opponent) {
    int number;
    char letter;
    while (true) {
        bool validInput = false;
        while (!validInput) {
            std::cout << nickname << ", wprowadz wspolrzedne (liczba, litera): ";
            
            while (!(std::cin >> number) || number < 0 || number >= 10) {
                std::cout << "Bledna liczba, wprowadz liczbe od 0 do 9: ";
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            }

            std::cin >> letter;
            if (letter >= 'A' && letter <= 'J') {
                validInput = true;
            } else {
                std::cout << "Bledny symbol, wprowadz literke od A do J.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        if (opponent.board.makeShot(letter, number)) { 
            std::cout << "Trafiles!\n";
            
            if (opponent.allShipsSunk()) {
                std::cout << opponent.nickname << " wszystkie statki zostały zatopione!\n";
                return false; 
            }
            continue; 
        } else {
            std::cout << "Nie trafiles.\n";
            break; 
        }
    }
    return true; 
}


bool Player::allShipsSunk() const {
    return board.areAllShipsSunk();
}

std::string Player::getNickname() const {
    return nickname;
}