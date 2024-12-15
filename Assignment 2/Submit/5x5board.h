#ifndef _FIVE_BY_FIVE_TIC_TAC_TOE_H
#define _FIVE_BY_FIVE_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <limits>

using namespace std;

template <typename T>
class FiveByFive_Board : public Board<T>
{
public:
    FiveByFive_Board();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    int count_three_in_a_row(T symbol);

    int getRows() const { return this->rows; }
    int getColumns() const { return this->columns; }
    T **getBoard() const { return this->board; }
};

template <typename T>
class FiveByFive_Player : public Player<T>
{
public:
    FiveByFive_Player(string name, T symbol);
    void getmove(int &x, int &y) override;
};

template <typename T>
class FiveByFive_RandomPlayer : public RandomPlayer<T>
{
public:
    FiveByFive_RandomPlayer(T symbol);
    void getmove(int &x, int &y) override;
};

template <typename T>
FiveByFive_Board<T>::FiveByFive_Board()
{
    this->rows = this->columns = 5;
    this->board = new T *[this->rows];
    for (int i = 0; i < this->rows; ++i)
    {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; ++j)
        {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool FiveByFive_Board<T>::update_board(int x, int y, T symbol)
{
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || symbol == 0))
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
    return false;
}

template <typename T>
void FiveByFive_Board<T>::display_board()
{
    cout << "\n  ";
    for (int j = 0; j < this->columns; ++j)
    {
        cout << "  " << j << "  ";
    }
    cout << endl;
    cout << setfill('-') << setw(this->columns * 5 + 4) << "" << endl;
    for (int i = 0; i < this->rows; ++i)
    {
        cout << i << " |";
        for (int j = 0; j < this->columns; ++j)
        {
            cout << setw(3) << (this->board[i][j] == 0 ? '-' : this->board[i][j]) << " |";
        }
        cout << endl
             << setfill('-') << setw(this->columns * 5 + 4) << "" << endl;
    }
}

template <typename T>
bool FiveByFive_Board<T>::is_win()
{
    return false;
}

template <typename T>
bool FiveByFive_Board<T>::is_draw()
{
    if (this->n_moves == 24)
    {
        int X = count_three_in_a_row('X');
        int O = count_three_in_a_row('O');

        cout << "\nGame Over!\n";
        cout << "Player 1 (X) has " << X << " three-in-a-row(s).\n";
        cout << "Player 2 (O) has " << O << " three-in-a-row(s).\n";
        if (X > O)
            cout << "Player 1 (X) wins!\n";

        else if (O > X)
            cout << "Player 2 (O) wins!\n";

        else
            cout << "Draw!!\n";
    }
    return this->n_moves == 24;
}

template <typename T>
bool FiveByFive_Board<T>::game_is_over()
{
    return this->n_moves == 24;
}

template <typename T>
int FiveByFive_Board<T>::count_three_in_a_row(T symbol)
{
    int count = 0;
    for (int i = 0; i < this->rows; ++i)
    {
        for (int j = 0; j <= this->columns - 3; ++j)
        {
            if (this->board[i][j] == symbol &&
                this->board[i][j + 1] == symbol &&
                this->board[i][j + 2] == symbol)
            {
                count++;
            }
        }
    }
    for (int j = 0; j < this->columns; ++j)
    {
        for (int i = 0; i <= this->rows - 3; ++i)
        {
            if (this->board[i][j] == symbol &&
                this->board[i + 1][j] == symbol &&
                this->board[i + 2][j] == symbol)
            {
                count++;
            }
        }
    }
    for (int i = 0; i <= this->rows - 3; ++i)
    {
        for (int j = 0; j <= this->columns - 3; ++j)
        {
            if (this->board[i][j] == symbol &&
                this->board[i + 1][j + 1] == symbol &&
                this->board[i + 2][j + 2] == symbol)
            {
                count++;
            }
            if (this->board[i][j + 2] == symbol &&
                this->board[i + 1][j + 1] == symbol &&
                this->board[i + 2][j] == symbol)
            {
                count++;
            }
        }
    }
    return count;
}

template <typename T>
FiveByFive_Player<T>::FiveByFive_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void FiveByFive_Player<T>::getmove(int &x, int &y)
{
    while (true)
    {
        cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
        cin >> x >> y;
        if (cin.fail() || x < 0 || x > 4 || y < 0 || y > 4)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter numbers between 0 and 4.\n";
            continue;
        }
        break;
    }
}

template <typename T>
FiveByFive_RandomPlayer<T>::FiveByFive_RandomPlayer(T symbol) : RandomPlayer<T>(symbol)
{
    this->name = "Player 2";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void FiveByFive_RandomPlayer<T>::getmove(int &x, int &y)
{
    FiveByFive_Board<T> *currentBoard = dynamic_cast<FiveByFive_Board<T> *>(this->boardPtr);
    if (!currentBoard)
    {
        x = 0;
        y = 0;
        return;
    }
    vector<pair<int, int>> emptyCells;
    for (int i = 0; i < currentBoard->getRows(); ++i)
    {
        for (int j = 0; j < currentBoard->getColumns(); ++j)
        {
            if (currentBoard->getBoard()[i][j] == 0)
            {
                emptyCells.emplace_back(i, j);
            }
        }
    }
    if (!emptyCells.empty())
    {
        int randIndex = rand() % emptyCells.size();
        x = emptyCells[randIndex].first;
        y = emptyCells[randIndex].second;
    }
    else
    {
        x = -1;
        y = -1;
    }
}

#endif //_FIVE_BY_FIVE_TIC_TAC_TOE_H