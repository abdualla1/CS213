#include <iostream>
#include "BoardGame_Classes.h"
#include "MisereTicTacToe.h"

using namespace std;
class BufferManip : public streambuf {
public:
    BufferManip(streambuf* originalBuffer) : originalBuffer(originalBuffer) {}

protected:
    virtual int overflow(int c) override {
        if (c != EOF) {
            char ch = static_cast<char>(c);
            buffer += ch;

            if (buffer.find("Player 1 wins") != string::npos) {
                buffer.replace(buffer.find("Player 1 wins"), 14, "Player 2 Wins!");
            }
            if (buffer.find("Player 2 wins") != string::npos) {
                buffer.replace(buffer.find("Player 2 wins"), 14, "Player 1 Wins!");
            }
        }

        originalBuffer->sputc(c);
        return c;
    }

public:
    string buffer;
    streambuf* originalBuffer;
};
int main() {
    Player<char>* players[2];
    Misere_Board<char>* board = new Misere_Board<char>();
    string player1Name = "Player 1", player2Name = "Player 2";

    cout << "Welcome to Misere Tic Tac Toe!\n";
    cout << "You are Player 1, and you will play as 'X'.\n";
    cout << "Choose Your Mode: " << endl;
    cout << "1. Player vs Player" << endl;
    cout << "2. Player vs Smart Computer" << endl;
    cout << "3. Player vs Random Computer" << endl;
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;

    if (choice < 1 || choice > 3) {
        cout << "Invalid choice. Exiting the game.\n";
        delete board;
        return 1;
    }

    // Player 1 is always human
    players[0] = new Misere_Player<char>(player1Name, 'X');
    players[0]->setBoard(board);

    switch (choice) {
        case 1: // Player vs Player
            players[1] = new Misere_Player<char>(player2Name, 'O');
            players[1]->setBoard(board);
            break;
        case 2: 
            players[1] = new Misere_SmartPlayer<char>('O');
            players[1]->setBoard(board);
            break;
        case 3: 
            players[1] = new Misere_RandomPlayer<char>('O');
            players[1]->setBoard(board);
            break;
    }

    streambuf* originalBuffer = cout.rdbuf();
    BufferManip interceptor(originalBuffer);
    cout.rdbuf(&interceptor);

    GameManager<char> gameManager(board, players);
    gameManager.run();

    cout.rdbuf(originalBuffer);
    cout << interceptor.buffer;

    delete board;
    delete players[0];
    delete players[1];

    return 0;
}

