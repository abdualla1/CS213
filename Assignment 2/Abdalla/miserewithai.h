#ifndef _MISERE_TIC_TAC_TOE_H
#define _MISERE_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <limits>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

// Misere Tic Tac Toe Board
template <typename T>
class Misere_Board : public Board<T> {
public:
    Misere_Board();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};

// Misere Tic Tac Toe Player
template <typename T>
class Misere_Player : public Player<T> {
public:
    Misere_Player(string name, T symbol);
    void getmove(int& x, int& y) override;
};

// Smart Computer Player for Misere Tic Tac Toe
template <typename T>
class Misere_SmartPlayer : public Player<T> {
public:
    Misere_SmartPlayer(T symbol);
    void getmove(int& x, int& y) override;

private:
    int calculateMinMax(T s, bool isMaximizing);
    std::pair<int, int> getBestMove();
};

//--------------------------------------- IMPLEMENTATION

// Constructor for Misere_Board
template <typename T>
Misere_Board<T>::Misere_Board() {
    this->rows = this->columns = 3;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; ++i) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; ++j) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

// Update the board for a move
template <typename T>
bool Misere_Board<T>::update_board(int x, int y, T symbol) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || symbol == 0)) {
        if (symbol == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        } else {
            this->n_moves++;
            this->board[x][y] = toupper(symbol);
        }
        return true;
    }
    return false;
}

// Display the board
template <typename T>
void Misere_Board<T>::display_board() {
    for (int i = 0; i < this->rows; ++i) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; ++j) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Check if there is a losing condition
template <typename T>
bool Misere_Board<T>::is_win() {
    for (int i = 0; i < this->rows; ++i) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {
            return true;
        }
    }

    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        return true;
    }

    return false;
}

// Check if the game is a draw
template <typename T>
bool Misere_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

// Check if the game is over
template <typename T>
bool Misere_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

// Constructor for Misere_Player
template <typename T>
Misere_Player<T>::Misere_Player(string name, T symbol) : Player<T>(name, symbol) {}

// Get the move from a player
template <typename T>
void Misere_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for Misere_SmartPlayer
template <typename T>
Misere_SmartPlayer<T>::Misere_SmartPlayer(T symbol) : Player<T>(symbol) {
    this->name = "Player 2";
}
template <typename T>
class Misere_RandomPlayer : public RandomPlayer<T> {
public:
    Misere_RandomPlayer(T symbol);
    void getmove(int& x, int& y) override;
};
template <typename T>
Misere_RandomPlayer<T>::Misere_RandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    this->name = "Player 2";
    srand(static_cast<unsigned int>(time(0)));  // Seed random number generator
}
template <typename T>
void Misere_RandomPlayer<T>::getmove(int& x, int& y) {
        x = rand() % 3;
        y = rand() % 3;
}
// Get the move using MinMax
template <typename T>
void Misere_SmartPlayer<T>::getmove(int& x, int& y) {
    std::pair<int, int> bestMove = getBestMove();
    x = bestMove.first;
    y = bestMove.second;
}

// MinMax algorithm for Misere Tic Tac Toe
// MinMax algorithm for Misere Tic Tac Toe
template <typename T>
int Misere_SmartPlayer<T>::calculateMinMax(T s, bool isMaximizing) {
    if (this->boardPtr->is_win()) {
        return isMaximizing ? 1 : -1; // Winning is bad, so penalize the maximizer
    } else if (this->boardPtr->is_draw()) {
        return 0; // Neutral value for a draw
    }

    int bestValue = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    T opponentSymbol = (s == 'X') ? 'O' : 'X';

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (this->boardPtr->update_board(i, j, s)) {
                int value = calculateMinMax(opponentSymbol, !isMaximizing);
                this->boardPtr->update_board(i, j, 0);

                if (isMaximizing) {
                    bestValue = std::max(bestValue, value); // Maximize losing potential
                } else {
                    bestValue = std::min(bestValue, value); // Minimize winning potential
                }
            }
        }
    }

    return bestValue;
}

// Get the best move using MinMax
template <typename T>
std::pair<int, int> Misere_SmartPlayer<T>::getBestMove() {
    int bestValue = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (this->boardPtr->update_board(i, j, this->symbol)) {
                int moveValue = calculateMinMax(this->symbol, false);
                this->boardPtr->update_board(i, j, 0);

                if (moveValue > bestValue) { // Favor moves that maximize losing chances
                    bestMove = {i, j};
                    bestValue = moveValue;
                }
            }
        }
    }

    return bestMove;
}

#endif //_MISERE_TIC_TAC_TOE_H
