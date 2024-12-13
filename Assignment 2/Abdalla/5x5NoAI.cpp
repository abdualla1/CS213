#ifndef _FIVE_BY_FIVE_TIC_TAC_TOE_H
#define _FIVE_BY_FIVE_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

template <typename T>
class FiveByFive_Board : public Board<T> {
public:
    FiveByFive_Board();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    int count_three_in_a_row(T symbol);
};

template <typename T>
class FiveByFive_Player : public Player<T> {
public:
    FiveByFive_Player(string name, T symbol);
    void getmove(int& x, int& y) override;
};

template <typename T>
class FiveByFive_RandomPlayer : public RandomPlayer<T> {
public:
    FiveByFive_RandomPlayer(T symbol);
    void getmove(int& x, int& y) override;
};

//----------------------------------- IMPLEMENTATION -----------------------------------

template <typename T>
FiveByFive_Board<T>::FiveByFive_Board() {
    this->rows = this->columns = 5;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; ++i) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; ++j) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool FiveByFive_Board<T>::update_board(int x, int y, T symbol) {
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

template <typename T>
void FiveByFive_Board<T>::display_board() {
    cout << "\n  ";
    for (int j = 0; j < this->columns; ++j) {
        cout << "  " << j << "  ";
    }
    cout << endl;
    cout << setfill('-') << setw(this->columns * 5 + 4) << "" << endl;
    for (int i = 0; i < this->rows; ++i) {
        cout << i << " |";
        for (int j = 0; j < this->columns; ++j) {
            cout << setw(3) << (this->board[i][j] == 0 ? ' ' : this->board[i][j]) << " |";
        }
        cout << endl << setfill('-') << setw(this->columns * 5 + 4) << "" << endl;
    }
}

template <typename T>
bool FiveByFive_Board<T>::is_win() {
    return false; // Winning depends on scoring and will be evaluated at the end of the game.
}

template <typename T>
bool FiveByFive_Board<T>::is_draw() {
    return this->n_moves == 25;
}

template <typename T>
bool FiveByFive_Board<T>::game_is_over() {
    return is_draw();
}

template <typename T>
int FiveByFive_Board<T>::count_three_in_a_row(T symbol) {
    int count = 0;
    // Check rows
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j <= this->columns - 3; ++j) {
            if (this->board[i][j] == symbol && this->board[i][j + 1] == symbol && this->board[i][j + 2] == symbol) {
                count++;
            }
        }
    }
    // Check columns
    for (int j = 0; j < this->columns; ++j) {
        for (int i = 0; i <= this->rows - 3; ++i) {
            if (this->board[i][j] == symbol && this->board[i + 1][j] == symbol && this->board[i + 2][j] == symbol) {
                count++;
            }
        }
    }
    // Check diagonals
    for (int i = 0; i <= this->rows - 3; ++i) {
        for (int j = 0; j <= this->columns - 3; ++j) {
            if (this->board[i][j] == symbol && this->board[i + 1][j + 1] == symbol && this->board[i + 2][j + 2] == symbol) {
                count++;
            }
        }
        for (int j = 2; j < this->columns; ++j) {
            if (this->board[i][j] == symbol && this->board[i + 1][j - 1] == symbol && this->board[i + 2][j - 2] == symbol) {
                count++;
            }
        }
    }
    return count;
}

template <typename T>
FiveByFive_Player<T>::FiveByFive_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void FiveByFive_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
    cin >> x >> y;
}

template <typename T>
FiveByFive_RandomPlayer<T>::FiveByFive_RandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    this->name = "Random Computer";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void FiveByFive_RandomPlayer<T>::getmove(int& x, int& y) {
        x = rand() % 5;
        y = rand() % 5;
}

#endif //_FIVE_BY_FIVE_TIC_TAC_TOE_H
