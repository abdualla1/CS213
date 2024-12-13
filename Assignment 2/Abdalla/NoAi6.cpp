#include <iostream>
#include "BoardGame_Classes.h"
#include "MisereTicTacToe.h"

using namespace std;
class OutputInterceptor : public streambuf {
public:
    OutputInterceptor(streambuf* originalBuffer) : originalBuffer(originalBuffer) {}

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
    cout << "Choose Your Mode: " << endl;
    cout << "1. Player vs Player" << endl;
    cout << "2. Player vs Smart Computer" << endl;
    cout << "3. Player vs Random Computer" << endl;
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;

    // Validate choice
    if (choice < 1 || choice > 3) {
        cout << "Invalid choice. Exiting the game.\n";
        delete board;
        return 1;
    }

    // Player 1 is always human
    players[0] = new Misere_Player<char>(player1Name, 'X');
    players[0]->setBoard(board);

    // Configure Player 2 based on choice
    switch (choice) {
        case 1: // Player vs Player
            players[1] = new Misere_Player<char>(player2Name, 'O');
            players[1]->setBoard(board);
            break;
        case 2: // Player vs Smart Computer
            players[1] = new Misere_SmartPlayer<char>('O');
            players[1]->setBoard(board);
            break;
        case 3: // Player vs Random Computer
            players[1] = new Misere_RandomPlayer<char>('O');
            players[1]->setBoard(board);
            break;
    }

    // Redirect output for result swapping
    streambuf* originalBuffer = cout.rdbuf();
    OutputInterceptor interceptor(originalBuffer);
    cout.rdbuf(&interceptor);

    // Run the game
    GameManager<char> gameManager(board, players);
    gameManager.run();

    // Restore original buffer and print modified output
    cout.rdbuf(originalBuffer);
    cout << interceptor.buffer;

    // Clean up resources
    delete board;
    delete players[0];
    delete players[1];

    return 0;
}

