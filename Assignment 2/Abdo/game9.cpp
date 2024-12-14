#include <iostream>
#include <vector>
#include "BoardGame_Classes.h"
#include <string>
#include<random>
using namespace std;
int dx[]={1,0,-1,0};
int dy[]={0,-1,0,1};
class SUSBoard : public Board<char> {
public:
    SUSBoard() {
        rows = 3;
        columns = 3;
        board = new char*[rows];
        for (int i = 0; i < rows; i++) {
            board[i] = new char[columns];
            for (int j = 0; j < columns; j++) {
                board[i][j] = ' ';
            }
        }
    }

    ~SUSBoard() {
        for (int i = 0; i < rows; i++) {
            delete[] board[i];
        }
        delete[] board;
    }

    bool update_board(int x, int y, char symbol) override {
        if (x < 1 || x > rows || y < 1 || y > columns || board[x - 1][y - 1] != ' ') {
            return false;
        }
        board[x - 1][y - 1] = symbol;
        n_moves++;
        return true;
    }

    void display_board() override {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                cout << " " << board[i][j] << " ";
                if (j < columns - 1) cout << "|";
            }
            cout << endl;
            if (i < rows - 1) cout << "---+---+---" << endl;
        }
    }

    bool is_win() override {
        return false; 
    }

    bool is_draw() override {
        return n_moves == 9;
    }

    bool game_is_over() override {
        return is_draw();
    }

    int calculate_score(int x, int y) {
    int score = 0;
    if (x >= 0 && x < 3) {
        if (board[x][0] == 'S' && board[x][1] == 'U' && board[x][2] == 'S') {
            score++;
        }
    }
    if (y >= 0 && y < 3) {
        if (board[0][y] == 'S' && board[1][y] == 'U' && board[2][y] == 'S') {
            score++;
        }
    }
    if (x == y) {
        if (board[0][0] == 'S' && board[1][1] == 'U' && board[2][2] == 'S') {
            score++;
        }
    }
    if (x + y == 2) {
        if (board[0][2] == 'S' && board[1][1] == 'U' && board[2][0] == 'S') {
            score++;
        }
    }

    return score;
}

};

class HumanPlayer : public Player<char> {
public:
    HumanPlayer(string n, char s) : Player<char>(n, s) {}

    void getmove(int& x, int& y) override {
        cout << name << " (" << symbol << "), enter your move (row and column): ";
        cin >> x >> y;
    }
};
class randomPlayer : public Player<char> {
public:
    randomPlayer(string n, char s) : Player<char>(n, s) {}

    void getmove(int& x, int& y) override {
        x=rand()%3+1,y=rand()%3+1;
    }
};
int main() {
    SUSBoard board;
    cout << "Select mode: \n(1) Two Players \n(2) Player vs random player: ";
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
    int scores[2] = { 0, 0 };
    board.display_board();
    while (!board.game_is_over()) {
        for (int i = 0; i < 2; i++) {
            if(board.game_is_over())break;
            int x, y;
            players[i]->getmove(x, y);
            while (!board.update_board(x, y, players[i]->getsymbol())) {
                cout << "Invalid move. Try again.\n";
                players[i]->getmove(x, y);
            }
            x--,y--;
            scores[i] += board.calculate_score(x,y);
            board.display_board();
            cout << "Player 1 Score: " << scores[0] << endl;
            cout << "Player 2 Score: " << scores[1] << endl;
        }
    }
    if (scores[0] > scores[1]) {
        cout << "Player 1 wins!" << endl;
    } else if (scores[0] < scores[1]) {
        cout << "Player 2 wins!" << endl;
    } else {
        cout << "It's a draw!" << endl;
    }

    return 0;
}
