#ifndef _WORDAI_H
#define _WORDAI_H

#include <bits/stdc++.h>
#include "BoardGame_Classes.h"
#include "Word.cpp"
#define endl '\n'
#define ll long long
#define Template template <class T>

using namespace std;

Template
class Word_Ai_Player : public Player<T> , public Word<T>
{
private:
    string chosen_word;
public:
    Word_Ai_Player(T symbol, const set<string>& dictionary);
    void getmove(int& x, int& y) override;

private:
    int calculateMinMax(T s, bool isMaximizing);
    pair<int, int> getBestMove();
    bool isWinningMove(int x, int y, T symbol);
    bool isBlockingMove(int x, int y, T opponentSymbol);
};

//IMPLEMENTATION
Template
Word_Ai_Player<T>::Word_Ai_Player(T symbol, const set<string> &dictionary) : Player<T>(symbol) {
    this->name = "AI Player";
    vector<string> words(dictionary.begin(), dictionary.end());
    srand(time(0));
    int randomIndex = rand() % words.size();
    chosen_word = words[randomIndex];
}

// Method to get the best move for the player
Template
void Word_Ai_Player<T>::getmove(int& x, int& y) {
    pair<int, int> bestMove = getBestMove();
    x = bestMove.first;
    y = bestMove.second;
}

// Minimax algorithm to evaluate the board
Template
int Word_Ai_Player<T>::calculateMinMax(T s, bool isMaximizing) {
    if (this->boardPtr->is_win()) {
        return isMaximizing ? -1 : 1;
    } else if (this->boardPtr->is_draw()) {
        return 0;
    }

    int bestValue = isMaximizing ? numeric_limits<int>::min() : numeric_limits<int>::max();

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for(int l = 0; l < 26 ; l++)
            {
                char s = 'A' + l;
                if (this->boardPtr->update_board(i, j, s))
                {
                    int value = calculateMinMax(s, !isMaximizing);
                    this->boardPtr->update_board(i, j, ' '); // Undo move

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
    }

    return bestValue;
}

// Find the best move using the minimax algorithm
Template
pair<int, int> Word_Ai_Player<T>::getBestMove() {
    int bestValue = numeric_limits<int>::min();
    pair<int, int> bestMove = {-1, -1};

    // First, check if we can win in the next move
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for(auto s : chosen_word)
            {
                if (this->boardPtr->update_board(i, j, s))
                {
                    if (this->boardPtr->is_win())
                    {
                        this->boardPtr->update_board(i, j, ' '); // Undo move
                        return {i, j};                           // Winning move found
                    }
                    this->boardPtr->update_board(i, j, ' '); // Undo move
                }
            }
        }
    }

    // Second, check if the opponent can win in their next move and block them
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int l = 0; l < 26; l++)
            {
                char s = 'A' + l;
                if (this->boardPtr->update_board(i, j, s))
                {
                    if (this->boardPtr->is_win())
                    {
                        this->boardPtr->update_board(i, j, ' '); // Undo move
                        return {i, j};                           // Block opponent's winning move
                    }
                    this->boardPtr->update_board(i, j, ' '); // Undo move
                }
            }
            
        }
    }

    // If no immediate win or block, use MinMax to find the best move
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for(auto s : chosen_word)
            {
                if (this->boardPtr->update_board(i, j, s))
                {
                    int moveValue = calculateMinMax(s, false);
                    this->boardPtr->update_board(i, j, ' '); // Undo move

                    if (moveValue > bestValue)
                    {
                        bestMove = {i, j};
                        bestValue = moveValue;
                    }
                }
            }
        }
    }

    return bestMove;
}

// Check if the move is a winning move
Template
bool Word_Ai_Player<T>::isWinningMove(int x, int y, T symbol) {
    if (this->boardPtr->update_board(x, y, symbol)) {
        bool isWinning = this->boardPtr->is_win();
        this->boardPtr->update_board(x, y, ' '); // Undo move
        return isWinning;
    }
    return false;
}

// Check if the move is a blocking move
Template
bool Word_Ai_Player<T>::isBlockingMove(int x, int y, T opponentSymbol) {
    if (this->boardPtr->update_board(x, y, opponentSymbol)) {
        bool isBlocking = this->boardPtr->is_win();
        this->boardPtr->update_board(x, y, ' '); // Undo move
        return isBlocking;
    }
    return false;
}
#endif