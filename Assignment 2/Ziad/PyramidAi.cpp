#ifndef _PYRAMIDAI_H
#define _PYRAMIDAI_H

#include <bits/stdc++.h>
#include "BoardGame_Classes.h"
#define endl '\n'
#define ll long long
#define Template template <class T>

using namespace std;

// Declaration
Template class Pyramid_Ai_Player : public Player<T>
{
public:
    Pyramid_Ai_Player(T symbol);
    void getmove(int &x, int &y) override;

private:
    int calculateMinMax(T s, bool isMaximizing);
    pair<int, int> getBestMove();
};

//Implementation
Template
Pyramid_Ai_Player<T>::Pyramid_Ai_Player(T symbol) : Player<T>(symbol)
{
    this->name = "AI Player";
}

// Method to get the best move for the player
Template
void Pyramid_Ai_Player<T>::getmove(int &x, int &y)
{
    pair<int, int> bestMove = getBestMove();
    x = bestMove.first;
    y = bestMove.second;
}

// Minimax algorithm to evaluate the board
Template
int Pyramid_Ai_Player<T>::calculateMinMax(T s, bool isMaximizing)
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
                this->boardPtr->update_board(i, j, 0); // Undo move

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

// Find the best move using the minimax algorithm
Template
pair<int, int> Pyramid_Ai_Player<T>::getBestMove()
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
                this->boardPtr->update_board(i, j, 0); // Undo move

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