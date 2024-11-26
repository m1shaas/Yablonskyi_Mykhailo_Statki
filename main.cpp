#include "Player.cc"
#include "Board.cc"
#include "Ship.cc"
#include <iostream>
#include <ctime>

using namespace std;

const int MAX_GAMES = 100; 

struct GameHistory {
    string player1;
    string player2;
    string winner;
    time_t timestamp;
    double duration; 
};

GameHistory gameHistory[MAX_GAMES];
int gameCount = 0;

bool hasAHistory = false;

void displayMenu() {
    cout << "\n**************************************\n";
    cout << "**           BATTLE SHIP           **\n";
    cout << "**************************************\n\n";
    cout << "1. Graj 1 na 1\n";
    cout << "2. Historia gier\n";
    cout << "3. Wyjscie\n";
    cout << "Wybierz opcje: ";
}


void displayGameHistory() {
    cout << "\n**************************************\n";
    cout << "**          Historia gier          **\n";
    cout << "**************************************\n\n";
    if(hasAHistory){
        for (int i = 0; i < gameCount; ++i) {
        cout << "Gracz 1: " << gameHistory[i].player1 
            << ", Gracz 2: " << gameHistory[i].player2
             << ", Zwycięca: " << gameHistory[i].winner
             << ", Czas: " << ctime(&gameHistory[i].timestamp)
             << ", Dlugosc gry: " << gameHistory[i].duration << " sekund.\n";
        }
    } else {
        cout  << "Brak zapisanych gier.\n";

    }
 
}

int main() {
    

    while (true) {
        displayMenu();
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string player1Name, player2Name;
                cout << "Podaj imie gracza 1: ";
                cin >> player1Name;
                cout << "Podaj imie gracza 2: ";
                cin >> player2Name;

                Player player1(player1Name);
                Player player2(player2Name);

                player1.deployShips();
                player2.deployShips();
   

                time_t startTime = time(0); 
                bool gameActive = true;
                while (gameActive) {
                    player1.displayBoards(player2.getBoard());
                    if (!player1.makeShoot(player2)) {
                        gameActive = false; 
                        break;
                    }

                    player2.displayBoards(player1.getBoard());
                    if (!player2.makeShoot(player1)) {
                        gameActive = false; 
                        break;
                    }
                }

                time_t endTime = time(0); 
                double duration = difftime(endTime, startTime); 

                
                if (player1.allShipsSunk()) {
                    cout << player2.getNickname() << " wygral!\n";
                    cout << "Gratulacje " << player2.getNickname() << "!\n";
                    if (gameCount < MAX_GAMES) {
                        gameHistory[gameCount++] = {player1Name, player2Name, player2.getNickname(), time(0), duration};
                        hasAHistory = true;
                    }
                } else {
                    cout << player1.getNickname() << " wygral!\n";
                    cout << "Gratulacje " << player1.getNickname() << "!\n";
                    if (gameCount < MAX_GAMES) {
                        gameHistory[gameCount++] = {player1Name, player2Name, player1.getNickname(), time(0), duration};
                        hasAHistory = true;
                    }
                }

                cout << "Czas trwania gry: " << duration << " sekund.\n";
                break;
            }
            case 2:
                displayGameHistory();
                break;
            case 3:
                cout << "Dzieki za gre!\n";
                return 0;
            default:
                cout << "Niewlasciwy wybor. Prosze sprobować ponownie.\n";
                break;
        }
    }

    return 0;
}
