#include <iostream>
#include <vector>
#include "sus.cpp"
#include <string>
#include<random>
using namespace std;

void game_9() {
    SUSBoard board;
    cout << "Select mode: \n(1) Two Players \n(2) Player vs random player : ";
    int chose; cin >> chose;
    HumanPlayer player1("Player 1", 'S');
    player1.setBoard(&board);
    Player<char>* player2 = nullptr;
    if(chose==1){
        player2 = new HumanPlayer("Player 2", 'U');
    }else{
        player2 = new randomPlayer("Player 2", 'U');
    }
    Player<char>* players[2] = { &player1, player2 };
    GameManager<char> gameManager(&board, players);
    gameManager.run();
    if (scores[0] > scores[1]) {
        cout << "Player 1 wins!" << endl;
    } else if (scores[0] < scores[1]) {
        cout << "Player 2 wins!" << endl;
    } else {
        cout << "It's a draw!" << endl;
    }
}
