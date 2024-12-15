#include <bits/stdc++.h>
#include "BoardGame_Classes.h"
#include "Word.cpp"
#include "WordAi.cpp"
#define endl '\n'
#define ll long long

using namespace std;

int main()
{
    int choice;
    Player<char> *players[2];
    Word<char> *B = new Word<char>();
    string player1, player2;

    cout << "Enter Player 1 Name: ";
    cin >> player1;
    cout << "What's Player 1 type: " << endl;
    cout << "1. Human" << endl;
    cout << "2. Random Computer" << endl;
    cout << "3. Ai Player" << endl;
    cin >> choice;

    switch (choice)
    {
    case 1:
        players[0] = new Word_Player<char>(player1, 'A');
        break;
    case 2:
        players[0] = new Word_Random_Player<char>('A');
        break;
    case 3:
        players[0] = new Word_Ai_Player<char>('A', B->getDictionary());
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
    cout << "3. Ai Player" << endl;
    cin >> choice;

    switch (choice)
    {
    case 1:
        players[1] = new Word_Player<char>(player2, 'B');
        break;
    case 2:
        players[1] = new Word_Random_Player<char>('B');
        break;
    case 3:
        players[1] = new Word_Ai_Player<char>('B', B->getDictionary());
        players[1]->setBoard(B);
        break;
    default:
        cout << "Invalid choice for Player 2. Exiting the game.\n";
        return 1;
    }

    GameManager<char> WordGame(B, players);
    WordGame.run();

    delete B;
    for (int i = 0; i < 2; i++)
    {
        delete players[i];
    }
    return 0;
}