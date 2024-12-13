#include <iostream>
#include <sstream>
#include "MisereBoard.h"

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
                buffer.replace(buffer.find("Player 1 wins"), 14, "Player 2 Wins");
            }
            if (buffer.find("Player 2 wins") != string::npos) {
                buffer.replace(buffer.find("Player 2 wins"), 14, "Player 1 Wins");
            }
        }

        originalBuffer->sputc(c);
        return c;
    }

public:
    string buffer;
    streambuf* originalBuffer;
};

void playMisereTicTacToe() {
    cout << "Choose game mode:\n";
    cout << "1. Player vs Player\n";
    cout << "2. Player vs Random Player\n";
    cout << "3. Player vs Smart AI\n";
    int choice;
    cin >> choice;

    MisereBoard<char> board;

    MiserePlayer<char> player1("Player 1", 'X');
    MiserePlayer<char> player2("Player 2", 'O');
    MisereRandomPlayer<char> randomPlayer('O');
//    MisereSmartPlayer<char> smartAI('O');

    player1.setBoard(&board);
    player2.setBoard(&board);
    randomPlayer.setBoard(&board);
//    smartAI.setBoard(&board);

    streambuf* originalBuffer = cout.rdbuf();

    OutputInterceptor interceptor(originalBuffer);
    cout.rdbuf(&interceptor);

    if (choice == 1) {
        Player<char>* players[2] = {&player1, &player2};
        GameManager<char> gameManager(&board, players);
        gameManager.run();
    } else if (choice == 2) {
        Player<char> *players[2] = {&player1, &randomPlayer};
        GameManager<char> gameManager(&board, players);
        gameManager.run();
//    } else if (choice == 3) {
//        // Player vs Smart AI
//        Player<char>* players[2] = {&player1, &smartAI};
//        GameManager<char> gameManager(&board, players);
//        gameManager.run();
//    }
    } else {
        cout << "Invalid choice.\n";
        return;
    }

    cout.rdbuf(originalBuffer);

    cout << interceptor.buffer;
}

int main() {
    cout << "Welcome to Misere Tic-Tac-Toe!\n";
    playMisereTicTacToe();
    return 0;
}
