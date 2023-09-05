#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
using namespace std;

class Boxer {
    public:
        int boxerSkill;

        Boxer() {
            this -> boxerSkill = rand() % 10;
        }
};

int main() {
    srand(time(NULL));
    char enter;

    // game stats
    int playerAlive = true;
    int playerSkill = rand() % 20;
    int playerScore = 1;
    string playerName = "";
    int boxerCount = 0;
    int boxersDefeated = 0;

    // title
    cout << "Welcome to Punchout." << endl << "Press [ENTER] to start.";
    cin.get();

    // player name
    cout << "Please enter your name: ";
    cin >> playerName;

    // ask how many boxers
    cout << "How many boxers do you wish to fight? ";
    cin >> boxerCount;

    // inform skill level
    cout << "Your skill level out of 20 is " << playerSkill << endl;
    cout << "Get ready to fight for the championship, " << playerName << "!" << endl;
    sleep(2);

    // main game loop
    while (playerAlive && boxersDefeated < boxerCount) {
        // create a random boxer
        Boxer opponent;

        // battle sequence
        if (opponent.boxerSkill > 10) {
            cout << endl << "Here comes a huge boxer! His skill level is " << opponent.boxerSkill << endl;
        }
        else {
            cout << endl << "Here comes boxer " << boxersDefeated + 1 << ". His skill level is " << opponent.boxerSkill << endl;
        }

        cout << "Fighting..." << endl;
        sleep(2);

        // player lost
        if (playerSkill < opponent.boxerSkill) {
            playerAlive = false;
            cout << "You have been knocked out." << endl;
        }

        // player won
        else {
            if (playerSkill - opponent.boxerSkill > 5) {
                cout << "You knocked him out!" << endl;
                playerScore = playerScore * 2;
            }

            else if (playerSkill - opponent.boxerSkill > 0) {
                cout << "You won on a points decision!" << endl;
                playerScore = playerScore * 2;
            }

            else {
                playerSkill = playerSkill - 1;
                cout << "You won, but suffered injuries. Your new skill level is " << playerSkill << endl;
            }

            boxersDefeated++;
        }

        cout << endl;
        sleep(1);
    }

    // end game
    if (boxersDefeated == boxerCount) {
        // victory
        cout << "You have won the championship!" << endl;
    }
    else {
        // lost
        cout << "You were knocked out of the tournament." << endl;
    }

    cout << "Boxers defeated: " << boxersDefeated << endl;
    cout << "Final score: " << playerScore << endl << endl;
}