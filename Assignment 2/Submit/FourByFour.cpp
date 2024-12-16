#ifndef _FOURBYFOUR_H
#define _FOURBYFOUR_H

#include <bits/stdc++.h>
#include "BoardGame_Classes.h"
#define endl '\n'
#define ll long long
#define Template template <class T>
using namespace std;

int new_x, new_y;

Template class FourByFour : public Board<T>
{
public:
    FourByFour();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

Template class FourByFour_Player : public Player<T>, public FourByFour<T>
{
public:
    FourByFour_Player(string name, T symbol);
    void getmove(int &x, int &y);
};

Template class FourByFour_Random_Player : public RandomPlayer<T>, public FourByFour<T>
{
public:
    FourByFour_Random_Player(T symbol);
    void getmove(int &x, int &y);
};

Template
FourByFour<T>::FourByFour()
{
    this->rows = this->columns = 4;
    new_x = new_y = 0;
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++)
    {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++)
        {
            if (i == 0)
            {
                if (j % 2 == 0)
                    this->board[i][j] = 'O';
                else
                    this->board[i][j] = 'X';
            }
            else if (i == 3)
            {
                if (j % 2 == 0)
                    this->board[i][j] = 'X';
                else
                    this->board[i][j] = 'O';
            }
            else
                this->board[i][j] = ' ';
        }
    }
    this->n_moves = 0;
}

Template bool FourByFour<T>::update_board(int x, int y, T symbol)
{
    if (new_x >= 0 && new_x < this->rows && new_y >= 0 && new_y < this->columns && this->board[new_x][new_y] == ' ' && this->board[x][y] == symbol && ((abs(new_x - x) == 1 && abs(new_y - y) == 0) || ((abs(new_x - x) == 0 && abs(new_y - y) == 1))) && x >= 0 && x < this->rows && y >= 0 && y < this->columns)
    {
        this->board[new_x][new_y] = symbol;
        this->board[x][y] = ' ';
        this->n_moves++;
        return true;
    }
    return false;
}

Template void FourByFour<T>::display_board()
{
    for (int i = 0; i < this->rows; i++)
    {
        cout << string(41, '-') << endl;
        cout << "| ";
        for (int j = 0; j < this->columns; j++)
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
        cout << endl;
    }
    cout << string(41, '-') << endl;
}

Template bool FourByFour<T>::is_win()
{
    // Check Rows
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            if (this->board[i][j] == this->board[i][j + 1] && this->board[i][j + 1] == this->board[i][j + 2] && this->board[i][j + 2] == this->board[i][j] && this->board[i][j] != ' ')
            {
                return true;
            }
        }
    }

    // Check Columns
    for (int i = 0; i < this->columns; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            if (this->board[j][i] == this->board[j + 1][i] && this->board[j + 1][i] == this->board[j + 2][i] && this->board[j + 2][i] == this->board[j][i] && this->board[j][i] != ' ')
            {
                return true;
            }
        }
    }

    // Check Right Skewed Diagonal
    if (this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != ' ')
    {
        return true;
    }
    else if (this->board[1][1] == this->board[2][2] && this->board[2][2] == this->board[3][3] && this->board[1][1] != ' ')
    {
        return true;
    }
    else if (this->board[1][0] == this->board[2][1] && this->board[2][1] == this->board[3][2] && this->board[1][0] != ' ')
    {
        return true;
    }
    else if (this->board[0][1] == this->board[1][2] && this->board[1][2] == this->board[2][3] && this->board[0][1] != ' ')
    {
        return true;
    }

    // Check Left Skewed Diagonal
    if (this->board[0][3] == this->board[1][2] && this->board[1][2] == this->board[2][1] && this->board[0][3] != ' ')
    {
        return true;
    }
    else if (this->board[1][2] == this->board[2][1] && this->board[2][1] == this->board[3][0] && this->board[1][2] != ' ')
    {
        return true;
    }
    else if (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != ' ')
    {
        return true;
    }
    else if (this->board[1][3] == this->board[2][2] && this->board[2][2] == this->board[3][1] && this->board[1][3] != ' ')
    {
        return true;
    }
    return false;
}

Template bool FourByFour<T>::is_draw()
{
    return (this->n_moves == 16 && !is_win());
}

Template bool FourByFour<T>::game_is_over()
{
    return is_win() || is_draw();
}

Template
FourByFour_Player<T>::FourByFour_Player(string name, T symbol) : Player<T>(name, symbol) {}

Template void FourByFour_Player<T>::getmove(int &x, int &y)
{
    cout << this->name << " enter your move (row and column) (0 to 3) separated by spaces: ";
    cin >> x >> y;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        x = -1;
        y = -1;
        return;
    }
    cout << "Enter new position (row and column) (0 to 3) separated by spaces: ";
    cin >> new_x >> new_y;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        new_x = -1;
        new_y = -1;
    }
}

Template
FourByFour_Random_Player<T>::FourByFour_Random_Player(T symbol) : RandomPlayer<T>(symbol)
{
    this->name = "Random Player";
    this->dimension = 4;
    srand(static_cast<unsigned int>(time(0)));
}

Template void FourByFour_Random_Player<T>::getmove(int &x, int &y)
{
    x = rand() % this->dimension;
    y = rand() % this->dimension;
    new_x = rand() % this->dimension;
    new_y = rand() % this->dimension;
}

#endif