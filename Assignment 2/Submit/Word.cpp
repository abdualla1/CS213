#ifndef _WORD_H
#define _WORD_H

#include <bits/stdc++.h>
#include "BoardGame_Classes.h"
#define endl '\n'
#define ll long long
#define Template template <class T>

using namespace std;

// Declaration of Classes
Template class Word : public Board<T>
{
private:
    set<string> dictionary;
    char mark;

public:
    Word();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    void load_dictionary(const string &filename = "dic.txt");
    bool is_word(const string &word);
};

Template class Word_Player : public Player<T>
{
public:
    Word_Player(string name, T symbol);
    void getmove(int &x, int &y);
};

Template class Word_Random_Player : public RandomPlayer<T>
{
public:
    Word_Random_Player(T symbol);
    void getmove(int &x, int &y);
};

// Implementation of Classes
Template
Word<T>::Word()
{
    this->rows = this->columns = 3;
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++)
    {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++)
        {
            this->board[i][j] = ' ';
        }
    }
    this->n_moves = 0;
    load_dictionary();
}

Template bool Word<T>::update_board(int x, int y, T symbol)
{
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && isalpha(symbol))
    {
        if (this->board[x][y] == ' ')
        {
            this->board[x][y] = symbol;
            this->n_moves++;
            return true;
        }
    }

    return false;
}

Template void Word<T>::display_board()
{
    for (int i = 0; i < this->rows; i++)
    {
        cout << string(31, '-') << endl;
        cout << "| ";
        for (int j = 0; j < this->columns; j++)
        {
            string row = "";
            if (this->board[i][j] == ' ')
            {
                row += "(" + to_string(i) + "," + to_string(j) + ")" + " " + " | ";
            }
            else
                row += "(" + to_string(i) + "," + to_string(j) + ")" + " " + char(this->board[i][j]) + " | ";
            cout << setw(10) << row;
        }
        cout << endl;
    }
    cout << string(31, '-') << endl;
}

Template void Word<T>::load_dictionary(const string &filename)
{
    ifstream file(filename);
    string word;
    while (file >> word)
    {
        dictionary.insert(word);
    }
    file.close();
}

Template bool Word<T>::is_word(const string &word)
{
    return dictionary.find(word) != dictionary.end();
}

Template bool Word<T>::is_win()
{
    // Check Rows
    for (int i = 0; i < this->rows; i++)
    {
        string word = "";
        for (int j = 0; j < this->columns; j++)
        {
            word += char(this->board[i][j]);
        }
        if (is_word(word))
        {
            return true;
        }
    }

    // Check Columns
    for (int i = 0; i < this->columns; i++)
    {
        string word = "";
        for (int j = 0; j < this->rows; j++)
        {
            word += char(this->board[j][i]);
        }
        if (is_word(word))
        {
            return true;
        }
    }

    // Check Diagonals
    string word1 = "", word2 = "";
    for (int i = 0; i < this->rows; i++)
    {
        word1 += char(this->board[i][i]);
        word2 += char(this->board[i][this->columns - i - 1]);
    }
    if (is_word(word1) || is_word(word2))
    {
        return true;
    }

    return false;
}

Template bool Word<T>::is_draw()
{
    return (this->n_moves == 9 && !is_win());
}

Template bool Word<T>::game_is_over()
{
    return is_win() || is_draw();
}

Template
Word_Player<T>::Word_Player(string name, T symbol) : Player<T>(name, symbol) {}

Template void Word_Player<T>::getmove(int &x, int &y)
{
    char c;
    cout << this->name << " enter your move (row and column) (0 to 2) separated by spaces: ";
    cin >> x >> y;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        x = -1;
        y = -1;
        return;
    }

    cout << "Enter a letter: ";
    cin >> c;
    this->symbol = toupper(c);
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

Template
Word_Random_Player<T>::Word_Random_Player(T symbol) : RandomPlayer<T>(symbol)
{
    this->name = "Random Player";
    this->dimension = 3;
    srand(static_cast<unsigned int>(time(0)));
}

Template void Word_Random_Player<T>::getmove(int &x, int &y)
{
    x = rand() % this->dimension;
    y = rand() % this->dimension;
    this->symbol = 'A' + rand() % 26;
}

#endif