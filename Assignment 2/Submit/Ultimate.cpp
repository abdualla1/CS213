#ifndef ULTIMATE_H
#define ULTIMATE_H

#include <bits/stdc++.h>
#include "BoardGame_Classes.h"
#define endl '\n'
#define ll long long
#define Template template <class T>

using namespace std;

Template class Ultimate : public Board<T>
{
public:
    Ultimate();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    void is_mini_win();
};

Template class MainBoard : public Board<T>
{
public:
    MainBoard();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

Template class Ultimate_Player : public Player<T>, public Ultimate<T>
{
public:
    Ultimate_Player(string name, T symbol);
    void getmove(int &x, int &y);
};

Template class Ultimate_Random_Player : public RandomPlayer<T>, public Ultimate<T>
{
public:
    Ultimate_Random_Player(T symbol);
    void getmove(int &x, int &y);
};

// Implementation of Classes
Template
Ultimate<T>::Ultimate()
{
    this->rows = 9, this->columns = 12;
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++)
    {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++)
        {
            this->board[i][j] = ' ';
        }
    }
    this->n_moves = 0;
}

Template bool Ultimate<T>::update_board(int x, int y, T symbol)
{
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == ' '))
    {
        this->n_moves++;
        this->board[x][y] = symbol;
        return true;
    }

    return false;
}

Template void Ultimate<T>::display_board()
{
    is_mini_win();
    for (int i = 0; i < this->rows; i++)
    {
        if (i < 4)
            cout << string(91, '-') << string(11, ' ') << string(31, '-') << endl;
        else
            cout << string(91, '-') << endl;
        cout << "| ";
        for (int j = 3; j < this->columns; j++)
        {
            string row = "";
            if (this->board[i][j] == ' ')
            {
                row += "(" + to_string(i) + "," + to_string(j - 3) + ")" + " " + " | ";
            }
            else
                row += "(" + to_string(i) + "," + to_string(j - 3) + ")" + " " + char(this->board[i][j]) + " | ";
            cout << setw(10) << row;
        }
        if (i < 3)
        {
            cout << string(10, ' ') << "| ";
            for (int j = 0; j < 3; j++)
            {
                string row = "";
                if (this->board[i][j] == ' ')
                {
                    row += "(" + to_string(i) + "," + to_string(j) + ")" + " " + " | ";
                }
                else
                    row += "(" + to_string(i) + "," + to_string(j) + ")" + " " + char(this->board[i][j]) + " | ";
                cout << setw(10) << row;
            }
        }
        cout << endl;
    }
    cout << string(91, '-') << endl;
}

Template bool Ultimate<T>::is_win()
{
    // Check rows
    for (int i = 0; i < 3; i++)
    {
        if (this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != ' ')
        {
            return true;
        }
    }

    // Check columns
    for (int i = 0; i < 3; i++)
    {
        if (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != ' ')
        {
            return true;
        }
    }

    // Check diagonals
    if (this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != ' ')
    {
        return true;
    }
    else if (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != ' ')
    {
        return true;
    }

    return false;
}

Template void Ultimate<T>::is_mini_win()
{
    // Check rows;
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 3; j < this->columns - 2; j += 3)
        {
            if (this->board[i][j] == this->board[i][j + 1] && this->board[i][j + 1] == this->board[i][j + 2] && this->board[i][j] != ' ' && this->board[static_cast<int>(floor(i / 3))][static_cast<int>(floor((j - 3) / 3))] == ' ')
            {
                update_board(floor(i / 3), floor((j - 3) / 3), this->board[i][j]);
                return;
            }
        }
    }

    // Check columns
    for (int i = 3; i < this->columns; i++)
    {
        for (int j = 0; j < this->rows - 2; j += 3)
        {
            if (this->board[j][i] == this->board[j + 1][i] && this->board[j + 1][i] == this->board[j + 2][i] && this->board[j][i] != ' ' && this->board[static_cast<int>(floor(j / 3))][static_cast<int>(floor((i - 3) / 3))] == ' ')
            {
                update_board(floor(j / 3), floor((i - 3) / 3), this->board[j][i]);
                return;
            }
        }
    }
    // Check diagonals
    for (int i = 3; i < this->columns - 2; i += 3)
    {
        for (int j = 0; j < this->rows - 2; j += 3)
        {
            if (this->board[j][i] == this->board[j + 1][i + 1] && this->board[j + 1][i + 1] == this->board[j + 2][i + 2] && this->board[j][i] != ' ' && this->board[static_cast<int>(floor(j / 3))][static_cast<int>(floor((i - 3) / 3))] == ' ')
            {
                update_board(floor(j / 3), floor((i - 3) / 3), this->board[j][i]);
                return;
            }
        }
    }

    for (int i = 3; i < this->columns - 2; i += 3)
    {
        for (int j = 0; j < this->rows - 2; j += 3)
        {
            if (this->board[j][i + 2] == this->board[j + 1][i + 1] && this->board[j + 1][i + 1] == this->board[j + 2][i] && this->board[j][i + 2] != ' ' && this->board[static_cast<int>(floor(j / 3))][static_cast<int>(floor((i - 1) / 3))] == ' ')
            {
                update_board(floor(j / 3), floor((i - 1) / 3), this->board[j][i + 2]);
                return;
            }
        }
    }
}

Template bool Ultimate<T>::is_draw()
{
    return (this->n_moves == 81 && !is_win());
}

Template bool Ultimate<T>::game_is_over()
{
    return (is_draw() || is_win());
}

Template
Ultimate_Player<T>::Ultimate_Player(string name, T symbol) : Player<T>(name, symbol) {}

Template void Ultimate_Player<T>::getmove(int &x, int &y)
{
    cout << this->name << " enter your move: ";
    cin >> x >> y;
    y += 3;
}

Template
Ultimate_Random_Player<T>::Ultimate_Random_Player(T symbol) : RandomPlayer<T>(symbol)
{
    this->name = "Random Player";
    this->dimension = 9;
    srand(static_cast<unsigned int>(time(0)));
}

Template void Ultimate_Random_Player<T>::getmove(int &x, int &y)
{
    x = rand() % this->dimension;
    y = rand() % this->dimension + 3;
}
#endif