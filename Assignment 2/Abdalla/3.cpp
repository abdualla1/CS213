#include <iostream>
#include "5x5TicTacToe.h"
#include "5x5MinimaxPlayer.h"

using namespace std;

int main() {
    Player<char>* players[2];
    FiveByFive_Board<char>* board = new FiveByFive_Board<char>();
    string player1Name = "Player 1", player2Name = "Player 2";

    cout << "Welcome to 5x5 Tic Tac Toe!\n";
    cout << "Choose Your Mode:\n";
    cout << "1. Player vs Player\n";
    cout << "2. Player vs Smart Computer\n";
    cout << "3. Player vs Random Computer\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            players[0] = new FiveByFive_Player<char>(player1Name, 'X');
            players[1] = new FiveByFive_Player<char>(player2Name, 'O');
            break;
        case 2:
            players[0] = new FiveByFive_Player<char>(player1Name, 'X');
            players[1] = new FiveByFive_MinMax_Player<char>('O');
            players[1]->setBoard(board);
            break;
        case 3:
            players[0] = new FiveByFive_Player<char>(player1Name, 'X');
            players[1] = new FiveByFive_RandomPlayer<char>('O');
            players[1]->setBoard(board);
            break;
        default:
            cout << "Invalid choice! Exiting the game.\n";
            delete board;
            return 1;
    }

    GameManager<char> gameManager(board, players);
    gameManager.run();

    delete board;
    delete players[0];
    delete players[1];

    return 0;
}
