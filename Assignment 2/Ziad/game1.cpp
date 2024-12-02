#include <bits/stdc++.h>
#include "BoardGame_Classes.h"
#include "Pyramic.cpp"
#define endl '\n'
#define ll long long

using namespace std;

int main() {
    int choice;
    Player<char> *players[2];
    Pyramic<char> *B = new Pyramic<char>();
    string player1, player2;
    cout << "Enter Player 1 Name: ";
    cin >> player1;
    cout << "What's Player 1 type: " << endl;
    cout << "1. Human" << endl;
    cout << "2. Random Computer" << endl;
    cin >> choice;

    switch(choice)
    {
        case 1:
            players[0] = new Pyramic_Player<char>(player1, 'X');
            break;
        case 2:
            players[1] = new Pyramic_Random_Player<char>('X');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return 1;
    }
    cout << "Enter Player 2 name: ";
    cin >> player2;
    cout << "Choose Player 2 type: " << endl;
    cout << "1. Human" << endl;
    cout << "2. Random Computer" << endl;
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new Pyramic_Player<char>(player2, 'O');
            break;
        case 2:
            players[1] = new Pyramic_Random_Player<char>('O');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return 1;
    }

    GameManager<char> PyramicGame(B, players);
    PyramicGame.run();
    
    delete B;
    for (int i = 0; i < 2; i++)
    {
        delete players[i];
    }
    return 0;
}