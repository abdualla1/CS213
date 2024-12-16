#ifndef _PYRAMID_H
#define _PYRAMID_H

#include <bits/stdc++.h>
#include "BoardGame_Classes.h"
#define endl '\n'
#define ll long long
#define Template template <class T>

using namespace std;

// Declaration
Template class Pyramid : public Board<T>
{
public:
    Pyramid();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    ~Pyramid();
};

// Declaration to different types of players
Template class Pyramid_Player : public Player<T>
{
public:
    Pyramid_Player(string name, T symbol);
    void getmove(int &x, int &y);
};

Template class Pyramid_Random_Player : public RandomPlayer<T>
{
public:
    Pyramid_Random_Player(T symbol);
    void getmove(int &x, int &y);
};

Template class Pyramid_Ai_Player : public Player<T>
{
public:
    Pyramid_Ai_Player(T symbol);
    void getmove(int &x, int &y) override;

private:
    int calculateMinMax(T s, bool isMaximizing);
    pair<int, int> getBestMove();
};

// Implementation
Template
Pyramid<T>::Pyramid()
{
    this->rows = 3, this->columns = 5;
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++)
    {
        int col = 2 * i + 1;
        this->board[i] = new char[col];
        for (int j = 0; j < col; j++)
        {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}
Template
Pyramid<T>::~Pyramid()
{
    for (int i = 0; i < this->rows; i++)
    {
        delete[] this->board[i];
    }
    delete[] this->board;
}

Template bool Pyramid<T>::update_board(int x, int y, T symbol)
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

Template void Pyramid<T>::display_board()
{
    for (int i = 0; i < this->rows; i++)
    {
        ll space = this->rows - i - 1;
        ll col = 2 * i + 1;
        cout << string(10 * space, ' ') << string(11 + (20 * i), '-') << endl;
        cout << string(10 * space, ' ');
        cout << "| ";
        for (int j = 0; j < col; j++)
        {
            string row = "";
            if (this->board[i][j] == 0)
            {
                row += "(" + to_string(i) + "," + to_string(j) + ")" + " " + " | ";
            }
            else
                row += "(" + to_string(i) + "," + to_string(j) + ")" + " " + char(this->board[i][j]) + " | ";
            cout << setw(10) << row;
        }
        cout << endl;
    }
    cout << string(51, '-') << endl;
}

Template bool Pyramid<T>::is_win()
{
    // Check column
    if (this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0)
    {
        return true;
    }
    // Check rows
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < 2 * i + 1; j++)
        {
            if (this->board[i][j] == this->board[i][j + 1] && this->board[i][j + 1] == this->board[i][j + 2] && this->board[i][j] != 0)
            {
                return true;
            }
        }
    }
    // Check diagonals
    if ((this->board[0][0] == this->board[1][2] && this->board[1][2] == this->board[2][4] && this->board[0][0] != 0) ||
        (this->board[0][0] == this->board[1][0] && this->board[1][0] == this->board[2][0] && this->board[0][0] != 0))
    {
        return true;
    }

    return false;
}

Template bool Pyramid<T>::is_draw()
{
    return (this->n_moves == 9 && !is_win());
}

Template bool Pyramid<T>::game_is_over()
{
    return is_win() || is_draw();
}

// Players Implementation
Template
Pyramid_Player<T>::Pyramid_Player(string name, T symbol) : Player<T>(name, symbol) {}

Template void Pyramid_Player<T>::getmove(int &x, int &y)
{
    cout << this->name << " enter your move (row and column) (0 t0 2) separated by spaces: ";
    cin >> x >> y;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        x = -1;
        y = -1;
    }
}

Template
Pyramid_Random_Player<T>::Pyramid_Random_Player(T symbol) : RandomPlayer<T>(symbol)
{
    this->name = "Random Player";
    this->dimension = 5;
    srand(static_cast<unsigned int>(time(0)));
}

Template void Pyramid_Random_Player<T>::getmove(int &x, int &y)
{
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}

Template
Pyramid_Ai_Player<T>::Pyramid_Ai_Player(T symbol) : Player<T>(symbol)
{
    this->name = "AI Player";
}

Template void Pyramid_Ai_Player<T>::getmove(int &x, int &y)
{
    pair<int, int> bestMove = getBestMove();
    x = bestMove.first;
    y = bestMove.second;
}

// Minimax algorithm to evaluate the board
Template int Pyramid_Ai_Player<T>::calculateMinMax(T s, bool isMaximizing)
{
    if (this->boardPtr->is_win())
    {
        return isMaximizing ? -1 : 1;
    }
    else if (this->boardPtr->is_draw())
    {
        return 0;
    }

    int bestValue = isMaximizing ? numeric_limits<int>::min() : numeric_limits<int>::max();
    T opponentSymbol = (s == 'X') ? 'O' : 'X';

    for (int i = 0; i < 3; ++i)
    {
        int col = 2 * i + 1;
        for (int j = 0; j < col; ++j)
        {
            if (this->boardPtr->update_board(i, j, s))
            {
                int value = calculateMinMax(opponentSymbol, !isMaximizing);
                this->boardPtr->update_board(i, j, 0);

                if (isMaximizing)
                {
                    bestValue = max(bestValue, value);
                }
                else
                {
                    bestValue = min(bestValue, value);
                }
            }
        }
    }

    return bestValue;
}

Template
    pair<int, int>
    Pyramid_Ai_Player<T>::getBestMove()
{
    int bestValue = numeric_limits<int>::min();
    pair<int, int> bestMove = {-1, -1};
    T opponentSymbol = (this->symbol == 'X') ? 'O' : 'X';

    // First, check if we can win in the next move
    for (int i = 0; i < 3; ++i)
    {
        int col = 2 * i + 1;
        for (int j = 0; j < col; ++j)
        {
            if (this->boardPtr->update_board(i, j, this->symbol))
            {
                if (this->boardPtr->is_win())
                {
                    this->boardPtr->update_board(i, j, 0);
                    return {i, j};
                }
                this->boardPtr->update_board(i, j, 0);
            }
        }
    }

    // Second, check if the opponent can win in their next move and block them
    for (int i = 0; i < 3; ++i)
    {
        int col = 2 * i + 1;
        for (int j = 0; j < col; ++j)
        {
            if (this->boardPtr->update_board(i, j, opponentSymbol))
            {
                if (this->boardPtr->is_win())
                {
                    this->boardPtr->update_board(i, j, 0);
                    return {i, j};
                }
                this->boardPtr->update_board(i, j, 0);
            }
        }
    }

    // If no immediate win or block, use MinMax to find the best move
    for (int i = 0; i < 3; ++i)
    {
        int col = 2 * i + 1;
        for (int j = 0; j < col; ++j)
        {
            if (this->boardPtr->update_board(i, j, this->symbol))
            {
                int moveValue = calculateMinMax(this->symbol, false);
                this->boardPtr->update_board(i, j, 0);

                if (moveValue > bestValue)
                {
                    bestMove = {i, j};
                    bestValue = moveValue;
                }
            }
        }
    }

    return bestMove;
}

#endif