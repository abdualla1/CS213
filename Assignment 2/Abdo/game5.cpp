#include "BoardGame_Classes.h"
#include <iostream>
#include<limits>
#include <vector>
#include <numeric>
#include <unordered_map>
#include <algorithm>
#include <set>
using namespace std;
pair<bool,int> last={0,0};
class NumericalTicTacToeBoard : public Board<int> {
public:
    NumericalTicTacToeBoard() {
        rows = 3;
        columns = 3;
        n_moves = 0;
        board = new int*[rows];
        for (int i = 0; i < rows; ++i) {
            board[i] = new int[columns];
            fill(board[i], board[i] + columns, 15);
        }
    }
    void display_board() override {
        cout << "      0   1   2   (Columns)\n";
        cout << "    +---+---+---+\n";
        for (int i = 0; i < rows; ++i) {
            cout << " " << i << "  |";
            for (int j = 0; j < columns; ++j) {
                if (board[i][j] == 15)
                    cout << "   |";
                else
                    cout << " " << board[i][j] << " |";
            }
            cout << "\n    +---+---+---+\n";
        }
        cout << "(Rows)\n";
    }
    bool update_board(int row, int col, int number) override {
        last.first=(number%2);
        if (row < 0 || row >= rows || col < 0 || col >= columns || board[row][col] != 15)
            return false;
        board[row][col] = number;
        n_moves++;
        
        return true;
    }
    bool is_win() override {
        for (int i = 0; i < rows; ++i) {
            if (accumulate(board[i], board[i] + columns, 0) == 15) return true; 
        }
        for (int j = 0; j < columns; ++j) {
            int col_sum = 0;
            for (int i = 0; i < rows; ++i) col_sum += board[i][j];
            if (col_sum == 15) return true; 
        }
        if (board[0][0] + board[1][1] + board[2][2] == 15) return true;
        if (board[0][2] + board[1][1] + board[2][0] == 15) return true;
        return false;
    }
    bool is_draw() override {
        return n_moves == rows * columns && !is_win();
    }
    bool game_is_over() override {
        return is_win() || is_draw();
    }
    int get_rows()  { return rows; }
    int get_columns() { return columns; }
    int get_cell(int row, int col) { return board[row][col]; }

};

class NumericalHumanPlayer : public Player<int> {
public:
    NumericalHumanPlayer(string name, const set<int>& allowedNumbers) 
        : Player<int>(name, 0), allowedNumbers(allowedNumbers) {}
    void getmove(int& x, int& y) override {
        bool validMove = false;
        while (!validMove) {
            cout << name << ", enter your move (row and column): ";
            cin >> x >> y;
            cout << "Enter the number you want to place (symbol): ";
            cin >> symbol;
            if (allowedNumbers.count(symbol) == 0) {
                cout << "Invalid number. You can only use your allowed numbers, and it must not be used already. Try again.\n";
                continue;
            }
            if((last.first%2 && symbol%2) || (last.first%2==0 && symbol%2==0)){
                usedNumbers.erase(last.second);
            }
            if (usedNumbers.count(symbol) != 0) {
                cout << "Number already used. Try again.\n";
                continue;
            }
            validMove = true;
            last.second=symbol;
        }
        usedNumbers.insert(symbol);
    }
private:
    const set<int> allowedNumbers; 
    static set<int> usedNumbers;   
};
class randomPlayer : public Player<int> {
public:
    randomPlayer(string name, const set<int>& allowedNumbers) 
        : Player<int>(name, 0), allowedNumbers(allowedNumbers) {}
    void getmove(int& x, int& y) override {
        bool validMove = false;
        while (!validMove) {
            x=rand()%3+1,y=rand()%3+1;
            symbol=rand()%10;
            if (allowedNumbers.count(symbol) == 0) {
                continue;
            }
            if((last.first%2 && symbol%2) || (last.first%2==0 && symbol%2==0)){
                usedNumbers.erase(last.second);
            }
            if (usedNumbers.count(symbol) != 0) {
                continue;
            }
            validMove = true;
            last.second=symbol;
        }
        usedNumbers.insert(symbol);
    }
private:
    const set<int> allowedNumbers; 
    static set<int> usedNumbers;   
};
set<int> NumericalHumanPlayer:: usedNumbers;
set<int> randomPlayer:: usedNumbers;
int main() {
    cout << "Welcome to Numerical Tic-Tac-Toe!" << endl;
    cout << "Select mode: \n(1) Two Players \n(2) Player vs random player : ";
    int choice;
    cin >> choice;
    NumericalTicTacToeBoard board;
    Player<int>* player1;
    Player<int>* player2;
    if (choice == 1) {
        player1 = new NumericalHumanPlayer("Player 1 (Odd)", {1, 3, 5, 7, 9});
        player2 = new NumericalHumanPlayer("Player 2 (Even)", {2, 4, 6, 8});
    }
    else {
        player1 = new NumericalHumanPlayer("Player 1 (Odd)", {1, 3, 5, 7, 9});
        player2 = new randomPlayer("Player 2 (Even)", {2, 4, 6, 8});
    }
    player1->setBoard(&board);
    player2->setBoard(&board);
    Player<int>* players[] = {player1, player2};
    GameManager<int> gameManager(&board, players);
    gameManager.run();
    delete player1;
    delete player2;
    
    return 0;
}

