#include <bits/stdc++.h>
#include "BoardGame_Classes.h"
#include "Pyramid.cpp"
#include "Word.cpp"
#include "Ultimate.cpp"
#include "FourByFour.cpp"
#include "3x3board.h"
#include "5x5board.h"
#include "5x5minmax.h"
#include "Numerical.cpp"
#include "FourInARow.cpp"
#include "SUS.cpp"

using namespace std;

class FilteredBuffer : public streambuf
{
public:
    FilteredBuffer(streambuf *original)
        : originalBuffer(original), buffer(""), drawKeyword("Draw!") {}

protected:
    virtual int overflow(int c) override
    {
        if (c == EOF)
        {
            return !EOF;
        }
        else
        {
            char ch = static_cast<char>(c);
            buffer += ch;

            size_t pos;
            while ((pos = buffer.find(drawKeyword)) != string::npos)
            {
                buffer.erase(pos, drawKeyword.length());
            }

            size_t forwardLimit = buffer.size() > drawKeyword.length() ? buffer.size() - drawKeyword.length() : 0;
            for (size_t i = 0; i < forwardLimit; ++i)
            {
                originalBuffer->sputc(buffer[i]);
            }
            buffer.erase(0, forwardLimit);

            return ch;
        }
    }

    virtual int sync() override
    {
        for (char c : buffer)
        {
            originalBuffer->sputc(c);
        }
        buffer.clear();
        return originalBuffer->pubsync();
    }

private:
    streambuf *originalBuffer;
    string buffer;
    string drawKeyword;
};
class BufferManip : public streambuf
{
public:
    BufferManip(streambuf *originalBuffer) : originalBuffer(originalBuffer) {}

protected:
    virtual int overflow(int c) override
    {
        if (c != EOF)
        {
            char ch = static_cast<char>(c);
            buffer += ch;

            if (buffer.find("Player 1 wins") != string::npos)
            {
                buffer.replace(buffer.find("Player 1 wins"), 14, "Player 2 Wins!");
            }
            if (buffer.find("Player 2 wins") != string::npos)
            {
                buffer.replace(buffer.find("Player 2 wins"), 14, "Player 1 Wins!");
            }
        }

        originalBuffer->sputc(c);
        return c;
    }

public:
    string buffer;
    streambuf *originalBuffer;
};

void runGame1()
{
    int choice;
    Player<char> *players[2];
    Pyramid<char> *B = new Pyramid<char>();
    string player1 = "Player 1", player2 = "Player 2";

    cout << "Welcome to Pyramid Tic Tac Toe!\n";
    cout << "Choose Your Mode:\n";
    cout << "1. Player vs Player\n";
    cout << "2. Player vs Smart Computer\n";
    cout << "3. Player vs Random Computer\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        players[0] = new Pyramid_Player<char>(player1, 'X');
        players[1] = new Pyramid_Player<char>(player2, 'O');
        break;
    case 2:
        players[0] = new Pyramid_Player<char>(player1, 'X');
        players[1] = new Pyramid_Ai_Player<char>('O');
        players[1]->setBoard(B);
        break;
    case 3:
        players[0] = new Pyramid_Player<char>(player1, 'X');
        players[1] = new Pyramid_Random_Player<char>('O');
        break;
    default:
        cout << "Invalid choice for Player 1. Exiting the game.\n";
        return;
    }

    GameManager<char> PyramidGame(B, players);
    PyramidGame.run();

    delete B;
    for (int i = 0; i < 2; i++)
    {
        delete players[i];
    }
}
void runGame2()
{
    int choice;
    Player<char> *players[2];
    FourInARowBoard B;
    string player1 = "Player 1", player2 = "Player 2";

    cout << "Welcome Connect Four!\n";
    cout << "Choose Your Mode:\n";
    cout << "1. Player vs Player\n";
    cout << "2. Player vs Smart Computer\n";
    cout << "3. Player vs Random Computer\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        players[0] = new FourInARowHumanPlayer(player1, 'X');
        players[1] = new FourInARowHumanPlayer(player2, 'O');
        players[1]->setBoard(&B);
        break;
    case 2:
        players[0] = new FourInARowHumanPlayer(player1, 'X');
        players[1] = new FourInARowMinimaxPlayer(player2, 'O');
        dynamic_cast<FourInARowMinimaxPlayer *>(players[1])->set_board(&B);
        break;
    case 3:
        players[0] = new FourInARowHumanPlayer(player1, 'X');
        players[1] = new FourInARowRandomPlayer(player2, 'O');
        players[1]->setBoard(&B);
        break;
    default:
        cout << "Invalid choice for Player 1. Exiting the game.\n";
        return;
    }
    players[0]->setBoard(&B);

    GameManager<char> PyramidGame(&B, players);
    PyramidGame.run();

    for (int i = 0; i < 2; i++)
    {
        delete players[i];
    }
}
void runGame3()
{
    Player<char> *players[2];
    FiveByFive_Board<char> *board = new FiveByFive_Board<char>();
    string player1Name = "Player 1", player2Name = "Player 2";
    streambuf *originalCoutBuffer = cout.rdbuf();

    FilteredBuffer filtBuf(originalCoutBuffer);

    cout.rdbuf(&filtBuf);
    cout << "Welcome to 5x5 Tic Tac Toe!\n";
    cout << "Choose Your Mode:\n";
    cout << "1. Player vs Player\n";
    cout << "2. Player vs Smart Computer\n";
    cout << "3. Player vs Random Computer\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    switch (choice)
    {
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
        return;
    }

    GameManager<char> gameManager(board, players);
    gameManager.run();
    cout.rdbuf(originalCoutBuffer);
    delete board;
    delete players[0];
    delete players[1];
}
void runGame4()
{
    int choice;
    Player<char> *players[2];
    Word<char> *B = new Word<char>();
    string player1 = "Player 1", player2 = "Player 2";

    cout << "Welcome to Word Tic Tac Toe!\n";
    cout << "Choose Your Mode:\n";
    cout << "1. Player vs Player\n";
    cout << "2. Player vs Random Computer\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        players[0] = new Word_Player<char>(player1, 'A');
        players[1] = new Word_Player<char>(player2, 'B');
        break;
    case 2:
        players[0] = new Word_Player<char>(player1, 'A');
        players[1] = new Word_Random_Player<char>('B');
        break;
    default:
        cout << "Invalid choice for Player 1. Exiting the game.\n";
        return;
    }

    GameManager<char> WordGame(B, players);
    WordGame.run();

    delete B;
    for (int i = 0; i < 2; i++)
    {
        delete players[i];
    }
}
void runGame5()
{
    int choice;
    Player<int> *players[2];
    NumericalTicTacToeBoard B;
    string player1 = "Player 1", player2 = "Player 2";

    cout << "Welcome to Numerical Tic Tac Toe!\n";
    cout << "Choose Your Mode:\n";
    cout << "1. Player vs Player\n";
    cout << "2. Player vs Random Computer\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        players[0] = new NumericalHumanPlayer(player1, {1, 3, 5, 7, 9});
        players[1] = new NumericalHumanPlayer(player2, {2, 4, 6, 8});
        break;
    case 2:
        players[0] = new NumericalHumanPlayer(player1, {1, 3, 5, 7, 9});
        players[1] = new NumericalRandomPlayer(player2, {2, 4, 6, 8});
        break;
    default:
        cout << "Invalid choice for Player 1. Exiting the game.\n";
        return;
    }

    players[0]->setBoard(&B);
    players[1]->setBoard(&B);
    GameManager<int> NumericalGame(&B, players);
    NumericalGame.run();

    for (int i = 0; i < 2; i++)
    {
        delete players[i];
    }
}
void runGame6()
{
    int choice;
    Player<char> *players[2];
    Misere_Board<char> *board = new Misere_Board<char>();
    string player1Name = "Player 1", player2Name = "Player 2";

    cout << "Welcome to Misere Tic Tac Toe!\n";
    cout << "Choose Your Mode: " << endl;
    cout << "1. Player vs Player" << endl;
    cout << "2. Player vs Smart Computer" << endl;
    cout << "3. Player vs Random Computer" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    players[0] = new Misere_Player<char>(player1Name, 'X');
    players[0]->setBoard(board);

    switch (choice)
    {
    case 1:
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

    streambuf *originalBuffer = cout.rdbuf();
    BufferManip interceptor(originalBuffer);
    cout.rdbuf(&interceptor);

    GameManager<char> gameManager(board, players);
    gameManager.run();

    cout.rdbuf(originalBuffer);
    cout << interceptor.buffer;

    delete board;
    delete players[0];
    delete players[1];
}
void runGame7()
{
    int choice;
    Player<char> *players[2];
    FourByFour<char> *B = new FourByFour<char>();
    string player1 = "Player 1", player2 = "Player 2";

    cout << "Welcome to 4x4 Tic Tac Toe!\n";
    cout << "Choose Your Mode:\n";
    cout << "1. Player vs Player\n";
    cout << "2. Player vs Random Computer\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        players[0] = new FourByFour_Player<char>(player1, 'X');
        players[1] = new FourByFour_Player<char>(player2, 'O');
        break;
    case 2:
        players[0] = new FourByFour_Player<char>(player1, 'X');
        players[1] = new FourByFour_Random_Player<char>('O');
        break;
    default:
        cout << "Invalid choice for Player 1. Exiting the game.\n";
        return;
    }

    GameManager<char> FourByFourGame(B, players);
    FourByFourGame.run();

    delete B;
    for (int i = 0; i < 2; i++)
    {
        delete players[i];
    }
}
void runGame8()
{
    int choice;
    Player<char> *players[2];
    Ultimate<char> *B = new Ultimate<char>();
    string player1 = "Player 1", player2 = "Player 2";

    cout << "Welcome to Ultimate Tic Tac Toe!\n";
    cout << "Choose Your Mode:\n";
    cout << "1. Player vs Player\n";
    cout << "2. Player vs Random Computer\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        players[0] = new Ultimate_Player<char>(player1, 'X');
        players[1] = new Ultimate_Random_Player<char>('O');
        break;
    case 2:
        players[0] = new Ultimate_Player<char>(player1, 'X');
        players[1] = new Ultimate_Random_Player<char>('O');
        break;
    default:
        cout << "Invalid choice for Player 1. Exiting the game.\n";
        return;
    }

    GameManager<char> UltimateGame(B, players);
    UltimateGame.run();
    delete B;
    for (int i = 0; i < 2; i++)
    {
        delete players[i];
    }
}
void runGame9()
{
    int choice;
    Player<char> *players[2];
    SUSBoard B;
    string player1 = "Player 1", player2 = "Player 2";

    cout << "Welcome to SUS Tic Tac Toe!\n";
    cout << "Choose Your Mode:\n";
    cout << "1. Player vs Player\n";
    cout << "2. Player vs Random Computer\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        players[0] = new SUSHumanPlayer(player1, 'S');
        players[1] = new SUSHumanPlayer(player2, 'U');
        break;
    case 2:
        players[0] = new SUSHumanPlayer(player1, 'S');
        players[1] = new SUSRandomPlayer(player2, 'U');
        break;
    default:
        cout << "Invalid choice for Player 1. Exiting the game.\n";
        return;
    }

    players[0]->setBoard(&B);
    players[1]->setBoard(&B);
    GameManager<char> SUSGame(&B, players);
    SUSGame.run();

    if (scores[0] > scores[1])
    {
        cout << "Player 1 wins!" << endl;
    }
    else if (scores[0] < scores[1])
    {
        cout << "Player 2 wins!" << endl;
    }
    else
    {
        cout << "It's a draw!" << endl;
    }
    for (int i = 0; i < 2; i++)
    {
        delete players[i];
    }
}

int main()
{
    cout << "Welcome to Tic Tac Toe Game!\n";
    cout << "Choose Your Game:\n";
    cout << "1. Pyramid Tic Tac Toe\n";
    cout << "2. Connect Four\n";
    cout << "3. 5x5 Tic Tac Toe\n";
    cout << "4. Word Tic Tac Toe\n";
    cout << "5. Numerical Tic Tac Toe\n";
    cout << "6. Misere Tic Tac Toe\n";
    cout << "7. 4x4 Tic Tac Toe\n";
    cout << "8. Ultimate Tic Tac Toe\n";
    cout << "9. SUS Tic Tac Toe\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
        runGame1();
        break;
    case 2:
        runGame2();
        break;
    case 3:
        runGame3();
        break;
    case 4:
        runGame4();
        break;
    case 5:
        runGame5();
        break;
    case 6:
        runGame6();
        break;
    case 7:
        runGame7();
        break;
    case 8:
        runGame8();
        break;
    case 9:
        runGame9();
        break;
    default:
        cout << "Invalid choice. Exiting the game.\n";
        break;
    }
    
    return 0;
}