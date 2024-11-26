#include "Player.h"
#include <iostream>
#include <limits>
#include "Ship.h"

Player::Player(const std::string& name) : nickname(name) {}

void Player::displayBoards(const Board& opponentBoard) const {
    std::cout << "Plansza gracza " << nickname << "\n";
    board.displayBoards(opponentBoard); 
}

void clearConsole() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
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

            bool validInput = false;
            while (!validInput) {
                std::cout << "Gracz " << nickname << ", umiesc " << names[i] << " (rozmiar " << sizes[i] << "):\n";

                std::cout << "Podaj wspolrzedne aby umiescic statek (liczba(0-9), litera(A-J)): ";
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
                std::cout << "Podaj wspolrzedne (liczba, litera): ";
                std::cin >> number >> letter;
                if (sizes[i] > 1) {
                    std::cout << "Czy statek jest poziomy? (1 - tak, 0 - nie): ";
                    std::cin >> horizontal;
                }
            }

            
            clearConsole();
            board.displayBoard();
        }
    }


    clearConsole();
}


bool Player::makeShoot(Player& opponent) {
    int number;
    char letter;
    bool miss = false;
    clearConsole();

    
    board.displayBoards(opponent.getBoard());

    while (true) {
        bool validInput = false;
        while (!validInput) {
            std::cout << nickname << ", wprowadz wspolrzedne dla strzalu (liczba(0-9), litera(A-J)): ";

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

        
        bool hit = opponent.board.makeShot(letter, number, opponent.getBoard());
        
        
        clearConsole();

        
        board.displayBoards(opponent.getBoard());

        if (hit) { 
            std::cout << "Trafiles!\n";
            if (opponent.allShipsSunk()) {
                std::cout << opponent.nickname << " wszystkie statki zostaly zatopione!\n";
                return false; 
            }
            continue; 
        } else {
            std::cout << "Nie trafiles.\n";

            std::cout << "Wcisnij Enter, aby przekazac ture drugiemu graczowi...\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            miss = true;
            break; 
        }
    }

    if (miss)
    {
        clearConsole();
    }
    
    std::cout << "Czy nastepny gracz jest gotowy? Wcisnij Enter, aby kontynuowac...\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();

    
    clearConsole();

    return true;
}




bool Player::allShipsSunk() const {
    return board.areAllShipsSunk();
}

std::string Player::getNickname() const {
    return nickname;
}
Board& Player::getBoard() {
    return board;
}