#include <bits/stdc++.h>
#include "BoardGame_Classes.h"
#include "Pyramid.cpp"

#define endl '\n'
#define ll long long

using namespace std;

int main()
{
    int choice;
    Player<char> *players[2];
    Pyramid<char> *B = new Pyramid<char>();
    string player1, player2;
    cout << "Enter Player 1 Name: ";
    cin >> player1;
    cout << "What's Player 1 type: " << endl;
    cout << "1. Human" << endl;
    cout << "2. Random Computer" << endl;
    cout << "3. Smart Computer (AI)" << endl;
    cin >> choice;

    switch (choice)
    {
    case 1:
        players[0] = new Pyramid_Player<char>(player1, 'X');
        break;
    case 2:
        players[0] = new Pyramid_Random_Player<char>('X');
        break;
    case 3:
        players[0] = new Pyramid_Ai_Player<char>('X');
        players[0]->setBoard(B);
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
    cout << "3. Smart Computer (AI)" << endl;
    cin >> choice;

    switch (choice)
    {
    case 1:
        players[1] = new Pyramid_Player<char>(player2, 'O');
        break;
    case 2:
        players[1] = new Pyramid_Random_Player<char>('O');
        break;
    case 3:
        players[1] = new Pyramid_Ai_Player<char>('O');
        players[1]->setBoard(B);
        break;
    default:
        cout << "Invalid choice for Player 2. Exiting the game.\n";
        return 1;
    }

    GameManager<char> PyramidGame(B, players);
    PyramidGame.run();

    delete B;
    for (int i = 0; i < 2; i++)
    {
        delete players[i];
    }
    return 0;
}