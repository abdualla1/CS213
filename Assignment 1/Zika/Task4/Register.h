#ifndef REGISTER_H
#define REGISTER_H

#include <bits/stdc++.h>
using namespace std;

class Register
{
private:
    int reg[16] = {0}; // 16 general-purpose registers
public:
    int getCell(int index) const
    {
        if (index < 0 || index >= 16)
        {
            cerr << "Error! Register access out of bounds at index " << index << endl;
            return 0;
        }
        return reg[index];
    }

    void setCell(int index, int value)
    {
        if (index < 0 || index >= 16)
        {
            cerr << "Error! Register access out of bounds at index " << index << endl;
            return;
        }
        reg[index] = value;
    }

    void clear()
    {
        for (int i = 0; i < 16; ++i)
        {
            reg[i] = 0;
        }
    }
};

#endif