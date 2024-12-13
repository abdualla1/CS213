#ifndef MISERE_GAME_H
#define MISERE_GAME_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

template <typename T>
class MisereBoard : public Board<T> {
public:
    MisereBoard();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;

private:
    bool check_row(int row);
    bool check_column(int col);
    bool check_diagonals();

    T getCell(int x, int y) const;
};

template <typename T>
class MiserePlayer : public Player<T> {
public:
    MiserePlayer(std::string name, T symbol);
    void getmove(int& x, int& y) override;
};

template <typename T>
class MisereRandomPlayer : public RandomPlayer<T> {
public:
    MisereRandomPlayer(T symbol);
    void getmove(int& x, int& y) override;
};

//--------------------------------------- IMPLEMENTATION

template <typename T>
MisereBoard<T>::MisereBoard() {
    this->rows = this->columns = 3;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = '-';
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool MisereBoard<T>::update_board(int x, int y, T symbol) {
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != '-') {
        return false;
    }
    this->board[x][y] = symbol;
    this->n_moves++;
    return true;
}

template <typename T>
void MisereBoard<T>::display_board() {
    cout << "\n---Tic Tac Toe---\n";
    std::cout << "    0   1   2\n";
    for (int i = 0; i < this->rows; i++) {
        std::cout << " " << i << " ";
        for (int j = 0; j < this->columns; j++) {
            std::cout << std::setw(3) << (this->board[i][j] == '-' ? '.' : this->board[i][j]);
            if (j < this->columns - 1) std::cout << "|";
        }
        std::cout << "\n";
        if (i < this->rows - 1) {
            std::cout << "   ---+---+---\n";
        }
    }
}

template <typename T>
bool MisereBoard<T>::check_row(int row) {
    return this->board[row][0] != '-' && this->board[row][0] == this->board[row][1] && this->board[row][1] == this->board[row][2];
}

template <typename T>
bool MisereBoard<T>::check_column(int col) {
    return this->board[0][col] != '-' && this->board[0][col] == this->board[1][col] && this->board[1][col] == this->board[2][col];
}

template <typename T>
bool MisereBoard<T>::check_diagonals() {
    return (this->board[0][0] != '-' && this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2]) ||
           (this->board[0][2] != '-' && this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0]);
}

template <typename T>
bool MisereBoard<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
        if (check_row(i) || check_column(i)) return true;
    }
    return check_diagonals();
}

template <typename T>
bool MisereBoard<T>::is_draw() {
    return this->n_moves == 9 && !is_win();
}

template <typename T>
bool MisereBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

// Implementation of MiserePlayer

template <typename T>
MiserePlayer<T>::MiserePlayer(std::string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void MiserePlayer<T>::getmove(int& x, int& y) {
    bool valid_move = false;
    while (!valid_move) {
        std::cout << this->name << "'s turn (" << this->symbol << "). Enter row and column (0-2 for both): ";
        std::cin >> x >> y;
        if (x >= 0 && x < 3 && y >= 0 && y < 3) {
            valid_move = true;
        } else {
            std::cout << "Invalid coordinates. Please enter values between 0 and 2.\n";
        }
    }
}


template <typename T>
MisereRandomPlayer<T>::MisereRandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    std::srand(static_cast<unsigned int>(std::time(0)));
}

template <typename T>
void MisereRandomPlayer<T>::getmove(int& x, int& y) {
    x = std::rand() % 3;
    y = std::rand() % 3;
}

#endif // MISERE_GAME_H
