#include <iostream>
#include <vector>
#include "BoardGame_Classes.h"
#include <string>
#include<random>
using namespace std;
int dx[]={1,0,-1,0};
int dy[]={0,-1,0,1};
int scores[2] = { 0, 0 };
int num_moves=0;
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
    int calculate_score(int x, int y ) {
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
    ~SUSBoard() {
        for (int i = 0; i < rows; i++) {
            delete[] board[i];
        }
        delete[] board;
    }

    bool update_board(int x, int y, char symbol) override {
        if(n_moves==9)return 1;
        if (x < 1 || x > rows || y < 1 || y > columns || board[x - 1][y - 1] != ' ') {
            return false;
        }
        board[x - 1][y - 1] = symbol;
        n_moves++;
        num_moves=n_moves;
        x--,y--;
        int i=symbol=='U';
        scores[i] +=calculate_score(x,y);
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
        cout << "Player 1 Score: " << scores[0] << endl;
        cout << "Player 2 Score: " << scores[1] << endl;
    }

    bool is_win() override {
        return false; 
    }

    bool is_draw() override {
        return false;
    }
    bool is_full(){
        return n_moves==9;
    }
    bool game_is_over() override {
        return is_full();
    }



};
class HumanPlayer : public Player<char> {
public:
    HumanPlayer(string n, char s) : Player<char>(n, s) {}

    void getmove(int& x, int& y) override {
        if(num_moves==9)return;
        cout << name << " (" << symbol << "), enter your move (row and column): ";
        cin >> x >> y;
    }
};
class randomPlayer : public Player<char> {
public:
    randomPlayer(string n, char s) : Player<char>(n, s) {}

    void getmove(int& x, int& y) override {
        if(num_moves==9)return;
        x=rand()%3+1,y=rand()%3+1;
    }
};