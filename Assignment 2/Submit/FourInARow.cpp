#ifndef _FOUR_IN_A_ROW_H
#define _FOUR_IN_A_ROW_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <climits>
#include <random>
#include <vector>
#include <algorithm>

using namespace std;
bool check_direction(vector<vector<char>> &board, int x, int y, int dx, int dy)
{
    char symbol = board[x][y];
    for (int k = 1; k < 4; ++k)
    {
        int nx = x + k * dx, ny = y + k * dy;
        if (nx < 0 || nx >= 6 || ny < 0 || ny >= 7 || board[nx][ny] != symbol)
            return false;
    }
    return true;
}

bool iswin(vector<vector<char>> &board, char z)
{
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 7; ++j)
        {
            if (board[i][j] == z && (check_direction(board, i, j, 1, 0) ||
                                     check_direction(board, i, j, 0, 1) ||
                                     check_direction(board, i, j, 1, 1) ||
                                     check_direction(board, i, j, 1, -1)))
                return true;
        }
    }
    return false;
}

class FourInARowBoard : public Board<char>
{
public:
    FourInARowBoard()
    {
        rows = 6;
        columns = 7;
        n_moves = 0;
        board = new char *[rows];
        for (int i = 0; i < rows; ++i)
        {
            board[i] = new char[columns];
            fill(board[i], board[i] + columns, '.');
        }
    }
    void display_board() override
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        cout << string(columns * 2 - 1, '-') << endl;
        for (int j = 0; j < columns; ++j)
            cout << j << " ";
        cout << endl;
    }
    bool update_board(int row, int col, char symbol) override
    {
        if (col < 0 || col >= columns)
            return false;
        for (int r = rows - 1; r >= 0; --r)
        {
            if (board[r][col] == '.')
            {
                board[r][col] = symbol;
                n_moves++;
                return true;
            }
        }
        return false;
    }
    bool is_win() override
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                if (board[i][j] != '.' && (check_direction(i, j, 1, 0) ||
                                           check_direction(i, j, 0, 1) ||
                                           check_direction(i, j, 1, 1) ||
                                           check_direction(i, j, 1, -1)))
                    return true;
            }
        }
        return false;
    }
    bool is_draw() override
    {
        return n_moves == rows * columns;
    }
    bool game_is_over() override
    {
        return is_win() || is_draw();
    }
    int getRows() { return rows; }
    int getColumns() { return columns; }
    int get_cell(int i, int j) { return board[i][j]; }

private:
    bool check_direction(int x, int y, int dx, int dy)
    {
        char symbol = board[x][y];
        for (int k = 1; k < 4; ++k)
        {
            int nx = x + k * dx, ny = y + k * dy;
            if (nx < 0 || nx >= rows || ny < 0 || ny >= columns || board[nx][ny] != symbol)
                return false;
        }
        return true;
    }
};

class FourInARowHumanPlayer : public Player<char>
{
public:
    FourInARowHumanPlayer(string name, char symbol) : Player<char>(name, symbol) {}

    void getmove(int &x, int &y) override
    {
        cout << name << " (" << symbol << "), enter column: ";
        cin >> y;
        x = 0;
    }
};

class FourInARowRandomPlayer : public Player<char>
{
public:
    FourInARowRandomPlayer(string name, char symbol) : Player<char>(name, symbol) {}
    void getmove(int &x, int &y) override
    {
        y = rand() % 7;
        x = 0;
    }
};

class FourInARowMinimaxPlayer : public Player<char>
{
public:
    string name;
    char symbol;
    FourInARowBoard *boardPtr;
    FourInARowMinimaxPlayer(string name, char symbol) : Player<char>(name, symbol) {}
    void set_board(FourInARowBoard *board) { boardPtr = board; }
    void getmove(int &x, int &y) override
    {
        if (!boardPtr)
            throw runtime_error("Board pointer is null!");
        int rows = boardPtr->getRows();
        int columns = boardPtr->getColumns();
        vector<vector<char>> boardCopy(rows, vector<char>(columns));
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j)
                boardCopy[i][j] = boardPtr->get_cell(i, j);

        y = find_best_move(boardCopy, rows, columns);
        x = 0;
    }

private:
    static const int MAX_DEPTH = 5;
    int evaluate_board(const vector<vector<char>> &board, char AI, char opponent)
    {
        int score = 0;
        int central_weight[] = {3, 4, 5, 7, 5, 4, 3};
        for (int i = 0; i < board.size(); ++i)
        {
            for (int j = 0; j < board[i].size(); ++j)
            {
                if (board[i][j] == AI)
                    score += central_weight[j];
                if (board[i][j] == opponent)
                    score -= central_weight[j];
            }
        }
        auto count_in_line = [](const vector<char> &line, char symbol) -> int
        {
            return count(line.begin(), line.end(), symbol);
        };
        auto evaluate_window = [&](const vector<char> &window) -> int
        {
            int AI_count = count_in_line(window, AI);
            int opp_count = count_in_line(window, opponent);

            if (AI_count == 4)
                return 100000;
            if (opp_count == 4)
                return -100000;
            if (AI_count == 3 && opp_count == 0)
                return 100;
            if (AI_count == 2 && opp_count == 0)
                return 10;
            if (opp_count == 3 && AI_count == 0)
                return -100;
            if (opp_count == 2 && AI_count == 0)
                return -10;

            return 0;
        };
        for (int i = 0; i < board.size(); ++i)
        {
            for (int j = 0; j <= board[i].size() - 4; ++j)
            {
                vector<char> window(board[i].begin() + j, board[i].begin() + j + 4);
                score += evaluate_window(window);
            }
        }
        for (int j = 0; j < board[0].size(); ++j)
        {
            for (int i = 0; i <= board.size() - 4; ++i)
            {
                vector<char> window = {board[i][j], board[i + 1][j], board[i + 2][j], board[i + 3][j]};
                score += evaluate_window(window);
            }
        }
        for (int i = 0; i <= board.size() - 4; ++i)
        {
            for (int j = 0; j <= board[i].size() - 4; ++j)
            {
                vector<char> window = {board[i][j], board[i + 1][j + 1], board[i + 2][j + 2], board[i + 3][j + 3]};
                score += evaluate_window(window);
            }
        }
        for (int i = 3; i < board.size(); ++i)
        {
            for (int j = 0; j <= board[i].size() - 4; ++j)
            {
                vector<char> window = {board[i][j], board[i - 1][j + 1], board[i - 2][j + 2], board[i - 3][j + 3]};
                score += evaluate_window(window);
            }
        }
        return score;
    }
    int minimax(vector<vector<char>> &board, int depth, bool isMaximizing, int alpha, int beta, char AI, char opponent, int rows, int columns)
    {
        if (depth == 0)
            return evaluate_board(board, AI, opponent);

        if (isMaximizing)
        {
            int maxEval = INT_MIN;
            for (int col = 0; col < columns; ++col)
            {
                if (is_valid_move(board, col, rows))
                {
                    make_move(board, col, AI, rows);
                    int eval = minimax(board, depth - 1, false, alpha, beta, AI, opponent, rows, columns);
                    undo_move(board, col, rows);
                    maxEval = max(maxEval, eval);
                    alpha = max(alpha, eval);
                    if (beta <= alpha)
                        break;
                }
            }
            return maxEval;
        }
        else
        {
            int minEval = INT_MAX;
            for (int col = 0; col < columns; ++col)
            {
                if (is_valid_move(board, col, rows))
                {
                    make_move(board, col, opponent, rows);
                    int eval = minimax(board, depth - 1, true, alpha, beta, AI, opponent, rows, columns);
                    undo_move(board, col, rows);
                    minEval = min(minEval, eval);
                    beta = min(beta, eval);
                    if (beta <= alpha)
                        break;
                }
            }
            return minEval;
        }
    }
    bool is_valid_move(const vector<vector<char>> &board, int col, int rows)
    {
        return board[0][col] == '.';
    }
    void make_move(vector<vector<char>> &board, int col, char symbol, int rows)
    {
        for (int r = rows - 1; r >= 0; --r)
        {
            if (board[r][col] == '.')
            {
                board[r][col] = symbol;
                break;
            }
        }
    }
    void undo_move(vector<vector<char>> &board, int col, int rows)
    {
        for (int r = 0; r < rows; ++r)
        {
            if (board[r][col] != '.')
            {
                board[r][col] = '.';
                break;
            }
        }
    }
    int find_best_move(vector<vector<char>> &board, int rows, int columns)
    {
        int bestMove = -1;
        int bestValue = INT_MIN;
        for (int col = 0; col < columns; ++col)
        {
            if (is_valid_move(board, col, rows))
            {
                make_move(board, col, 'O', rows);
                if (iswin(board, 'O'))
                {
                    undo_move(board, col, rows);
                    return col;
                }
                undo_move(board, col, rows);
            }
        }
        for (int col = 0; col < columns; ++col)
        {
            if (is_valid_move(board, col, rows))
            {
                make_move(board, col, 'O', rows);
                int moveValue = minimax(board, MAX_DEPTH, false, INT_MIN, INT_MAX, this->symbol, 'X', rows, columns);
                undo_move(board, col, rows);
                if (moveValue > bestValue)
                {
                    bestValue = moveValue;
                    bestMove = col;
                }
            }
        }
        return bestMove;
    }
};

#endif