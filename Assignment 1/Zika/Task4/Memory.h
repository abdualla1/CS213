#ifndef MEMORY_H
#define MEMORY_H

#include <bits/stdc++.h>
using namespace std;

class Memory
{
public:
    string memory[256];
    const int size = 256;

    string getCell(int address) const
    {
        if (address < 0 || address >= size)
        {
            cerr << "Error! Memory access out of bounds at address " << address << endl;
            return "";
        }
        return memory[address];
    }

    void setCell(int address, const string &val)
    {
        if (address < 0 || address >= size)
        {
            cerr << "Error! Memory access out of bounds at address " << address << endl;
            return;
        }
        if (address < 10)
        {
            memory[address] = val;
            return;
        }
        memory[address] = val.substr(0, 2);
        memory[address + 1] = val.substr(2, 2);
    }

    void clear()
    {
        for (int i = 0; i < size; ++i)
        {
            memory[i].clear();
        }
    }
};
#endif