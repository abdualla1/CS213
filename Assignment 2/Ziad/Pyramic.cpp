#ifndef _PYRAMIC_H
#define _PYRAMIC_H

#include "BoardGame_Classes.h"
#define Template template <class T>
using namespace std;

Template
class Pyramic : public Board<T>
{
    public:
        Pyramic();
        bool update_board(int x, int y, T symbol);
        void display_board();
        bool is_win();
        bool is_draw();
        bool game_is_over();
};

Template
class Pyramic_Player : public Player<T>
{
    public:
        Pyramic_Player(string name, T symbol);
        void getmove(int& x, int& y);
};

Template
class Pyramic_Random_Player : public RandomPlayer<T>
{
    public:
        Pyramic_Random_Player(T symbol);
        void getmove(int &x, int &y);
};


#include <bits/stdc++.h>
#include "BoardGame_Classes.h"
#define endl '\n'
#define ll long long

Template
Pyramic<T> :: Pyramic()
{
    this->rows =3, this->columns = 5;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        int col = 2 * i + 1;
        this->board[i] = new char[col];
        for (int j = 0; j < col; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

Template
bool Pyramic<T> :: update_board(int x, int y, T symbol)
{
    if (x >= 0 && x < this->rows && y >= 0 && y <= (2 * x))
    {
        if (this->board[x][y] == 0 || symbol == 0)
        {
            if (symbol == 0)
            {
                this->n_moves--;
                this->board[x][y] = 0;
            }
            else
            {
                this->n_moves++;
                this->board[x][y] = toupper(symbol);
            }
            return true;
        }
    }
    return false;
}

Template
void Pyramic<T> :: display_board()
{
    for (int i = 0; i < this->rows; i++) {
        ll space = this->rows - i - 1;
        ll col = 2 * i + 1;
        cout << string(10 * space, ' ') << string(11 + (20 * i), '-') << endl;
        cout << string(10 * space, ' ');
        cout << "| ";
        for (int j = 0; j < col; j++) {
            string row = "";
            if(this ->board[i][j] == 0) {
                row += "(" + to_string(i) + "," + to_string(j) + ")" + " " + " | ";
            } 
            else row += "(" + to_string(i) + "," + to_string(j) + ")" + " " + char(this->board[i][j]) + " | "; 
            cout << setw(10) << row;
        }
        cout << endl;
    }
    cout << string(51, '-') <<endl;
}

Template
bool Pyramic<T>::is_win() {
    // Check column
    if(this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) {
        return true;
    }
    // Check rows
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < 2 * i + 1; j++)
        {
            if(this->board[i][j] == this->board[i][j+1] && this->board[i][j+1] == this->board[i][j+2] && this->board[i][j] != 0) {
                return true;
            }
        }
    }
    // Check diagonals
    if ((this->board[0][0] == this->board[1][2] && this->board[1][2] == this->board[2][4] && this->board[0][0] != 0) ||
        (this->board[0][0] == this->board[1][0] && this->board[1][0] == this->board[2][0] && this->board[0][0] != 0)) {
        return true;
    }

    return false;
}

Template
bool Pyramic<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

Template
bool Pyramic<T>::game_is_over() {
    return is_win() || is_draw();
}

Template
Pyramic_Player<T> :: Pyramic_Player(string name, T symbol) : Player<T>(name, symbol) {}

Template
void Pyramic_Player<T> :: getmove(int& x, int& y) {
    cout << this-> name << " enter your move (row and column) (0 t0 2) separated by spaces: ";
    cin >> x >> y;
}

Template
Pyramic_Random_Player<T> :: Pyramic_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->name = "Random Player";
    this->dimension = 5;
    srand(static_cast<unsigned int>(time(0)));
}

Template
void Pyramic_Random_Player<T> :: getmove(int &x, int &y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}

#endif