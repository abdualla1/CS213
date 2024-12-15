#ifndef _FIVE_BY_FIVE_MINIMAX_PLAYER_H
#define _FIVE_BY_FIVE_MINIMAX_PLAYER_H

#include "BoardGame_Classes.h"
#include "5x5TicTacToe.h"
#include <limits>
#include <algorithm>
#include <utility>

using namespace std;

template <typename T>
class FiveByFive_MinMax_Player : public Player<T> {
public:
    FiveByFive_MinMax_Player(string name, T symbol);
    FiveByFive_MinMax_Player(T symbol);

    void getmove(int& x, int& y) override;

private:
    int calculateMinMax(FiveByFive_Board<T>* board, T currentSymbol, bool isMaximizing, int alpha, int beta, int depth);

    int evaluate(FiveByFive_Board<T>* board);

    bool isGameOver(FiveByFive_Board<T>* board);

    T getOpponentSymbol();

    pair<int, int> findBestMove(FiveByFive_Board<T>* board, int depth);
};

template <typename T>
FiveByFive_MinMax_Player<T>::FiveByFive_MinMax_Player(string name, T symbol)
        : Player<T>(name, symbol) {}

template <typename T>
FiveByFive_MinMax_Player<T>::FiveByFive_MinMax_Player(T symbol)
        : Player<T>(symbol) {
    this->name = "MinMax Computer";
}

template <typename T>
T FiveByFive_MinMax_Player<T>::getOpponentSymbol() {
    return (this->symbol == 'X') ? 'O' : 'X';
}

template <typename T>
bool FiveByFive_MinMax_Player<T>::isGameOver(FiveByFive_Board<T>* board) {
    return board->is_win() || board->is_draw();
}

template <typename T>
int FiveByFive_MinMax_Player<T>::evaluate(FiveByFive_Board<T>* board) {
    int myScore = board->count_three_in_a_row(this->symbol);
    int oppScore = board->count_three_in_a_row(getOpponentSymbol());
    return myScore - oppScore;
}

template <typename T>
int FiveByFive_MinMax_Player<T>::calculateMinMax(FiveByFive_Board<T>* board, T currentSymbol, bool isMaximizing, int alpha, int beta, int depth) {
    if (isGameOver(board) || depth == 0) {
        return evaluate(board);
    }

    if (isMaximizing) {
        int maxEval = numeric_limits<int>::min();
        for (int i = 0; i < board->getRows(); ++i) {
            for (int j = 0; j < board->getColumns(); ++j) {
                if (board->getBoard()[i][j] == 0) {
                    board->update_board(i, j, currentSymbol);
                    int eval = calculateMinMax(board, getOpponentSymbol(), false, alpha, beta, depth - 1);
                    board->update_board(i, j, 0);
                    maxEval = max(maxEval, eval);
                    alpha = max(alpha, eval);
                    if (beta <= alpha)
                        break;
                }
            }
            if (beta <= alpha)
                break;
        }
        return maxEval;
    }
    else {
        int minEval = numeric_limits<int>::max();
        for (int i = 0; i < board->getRows(); ++i) {
            for (int j = 0; j < board->getColumns(); ++j) {
                if (board->getBoard()[i][j] == 0) {
                    board->update_board(i, j, currentSymbol);
                    int eval = calculateMinMax(board, getOpponentSymbol(), true, alpha, beta, depth - 1);
                    board->update_board(i, j, 0);
                    minEval = min(minEval, eval);
                    beta = min(beta, eval);
                    if (beta <= alpha)
                        break;
                }
            }
            if (beta <= alpha)
                break;
        }
        return minEval;
    }
}

template <typename T>
pair<int, int> FiveByFive_MinMax_Player<T>::findBestMove(FiveByFive_Board<T>* board, int depth) {
    int bestVal = numeric_limits<int>::min();
    pair<int, int> bestMove = { -1, -1 };

    for (int i = 0; i < board->getRows(); ++i) {
        for (int j = 0; j < board->getColumns(); ++j) {
            if (board->getBoard()[i][j] == 0) {
                board->update_board(i, j, this->symbol);
                int moveVal = calculateMinMax(board, getOpponentSymbol(), false, numeric_limits<int>::min(), numeric_limits<int>::max(), depth - 1);
                board->update_board(i, j, 0);
                if (moveVal > bestVal) {
                    bestMove = { i, j };
                    bestVal = moveVal;
                }
            }
        }
    }

    return bestMove;
}

template <typename T>
void FiveByFive_MinMax_Player<T>::getmove(int& x, int& y) {
    FiveByFive_Board<T>* currentBoard = dynamic_cast<FiveByFive_Board<T>*>(this->boardPtr);
    if (!currentBoard) {
        FiveByFive_RandomPlayer<T> randomPlayer(this->symbol);
        randomPlayer.setBoard(this->boardPtr);
        randomPlayer.getmove(x, y);
        return;
    }

    pair<int, int> bestMove = findBestMove(currentBoard, 3);

    if (bestMove.first != -1 && bestMove.second != -1) {
        x = bestMove.first;
        y = bestMove.second;
    }
    else {
        FiveByFive_RandomPlayer<T> randomPlayer(this->symbol);
        randomPlayer.setBoard(this->boardPtr);
        randomPlayer.getmove(x, y);
    }
}

#endif //_FIVE_BY_FIVE_MINIMAX_PLAYER_H
