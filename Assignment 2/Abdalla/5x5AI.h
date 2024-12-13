#ifndef _FIVE_BY_FIVE_MINMAX_PLAYER_H
#define _FIVE_BY_FIVE_MINMAX_PLAYER_H

#include "BoardGame_Classes.h"
#include "5x5TicTacToe.h"
#include <limits>
#include <algorithm>

template <typename T>
class FiveByFive_MinMax_Player : public Player<T> {
public:
    FiveByFive_MinMax_Player(T symbol);

    void getmove(int& x, int& y) override;

private:
    int calculateMinMax(T s, bool isMaximizing);
    bool isWinningMove(int x, int y, T symbol);
    std::pair<int, int> getBestMove();
};

//----------------------------------- IMPLEMENTATION -----------------------------------

template <typename T>
FiveByFive_MinMax_Player<T>::FiveByFive_MinMax_Player(T symbol) : Player<T>(symbol) {
    this->name = "Smart Computer";
}

template <typename T>
void FiveByFive_MinMax_Player<T>::getmove(int& x, int& y) {
    std::pair<int, int> bestMove = getBestMove();
    x = bestMove.first;
    y = bestMove.second;
}

template <typename T>
bool FiveByFive_MinMax_Player<T>::isWinningMove(int x, int y, T symbol) {
    FiveByFive_Board<T>* board = dynamic_cast<FiveByFive_Board<T>*>(this->boardPtr);
    if (!board) return false;

    board->update_board(x, y, symbol);
    bool winning = board->is_win();
    board->update_board(x, y, 0); // Undo move
    return winning;
}

template <typename T>
int FiveByFive_MinMax_Player<T>::calculateMinMax(T s, bool isMaximizing) {
    FiveByFive_Board<T>* board = dynamic_cast<FiveByFive_Board<T>*>(this->boardPtr);
    if (!board) return 0;

    if (board->is_win()) {
        return isMaximizing ? -1 : 1; // Winning is bad for the maximizer
    } else if (board->is_draw()) {
        return 0; // Draw condition
    }

    int bestValue = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    T opponentSymbol = (s == 'X') ? 'O' : 'X';

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (this->boardPtr->update_board(i, j, s)) {
                int value = calculateMinMax(opponentSymbol, !isMaximizing);
                this->boardPtr->update_board(i, j, 0); // Undo move

                if (isMaximizing) {
                    bestValue = std::max(bestValue, value);
                } else {
                    bestValue = std::min(bestValue, value);
                }
            }
        }
    }

    return bestValue;
}

template <typename T>
std::pair<int, int> FiveByFive_MinMax_Player<T>::getBestMove() {
    int bestValue = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = {-1, -1};
    T opponentSymbol = (this->symbol == 'X') ? 'O' : 'X';

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (this->boardPtr->update_board(i, j, this->symbol)) {
                int moveValue = calculateMinMax(opponentSymbol, false);
                this->boardPtr->update_board(i, j, 0); // Undo move

                if (moveValue > bestValue) {
                    bestMove = {i, j};
                    bestValue = moveValue;
                }
            }
        }
    }

    return bestMove;
}

#endif //_FIVE_BY_FIVE_MINMAX_PLAYER_H
