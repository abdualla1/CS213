#ifndef ALU_H
#define ALU_H

#include "Register.h"

#include <bits/stdc++.h>
using namespace std;

class ALU
{
public:
    static int hexToDec(const string &hex)
    {
        return stoi(hex, nullptr, 16);
    }

    static string decToHex(int dec)
    {
        stringstream ss;
        ss << hex << dec;
        string result = ss.str();
        for (char &c : result)
        {
            if (isalpha(c))
            {
                c = toupper(c);
            }
        }
        return result;
    }

    static int add(int idx1, int idx2, Register &reg)
    {
        return reg.getCell(idx1) + reg.getCell(idx2);
    }

    static int bitwiseOr(int idx1, int idx2, Register &reg)
    {
        return reg.getCell(idx1) | reg.getCell(idx2);
    }

    static int bitwiseAnd(int idx1, int idx2, Register &reg)
    {
        return reg.getCell(idx1) & reg.getCell(idx2);
    }

    static int bitwiseXor(int idx1, int idx2, Register &reg)
    {
        return reg.getCell(idx1) ^ reg.getCell(idx2);
    }

    static int rotateRight(int value, int steps)
    {
        return ((value >> steps) | (value << (16 - steps))) % 256;
    }
};
#endif