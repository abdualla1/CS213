#ifndef CU_H
#define CU_H

#include "Register.h"
#include "Memory.h"
#include "ALU.h"

#include <bits/stdc++.h>
using namespace std;

class CU
{
public:
    bool haltFlag = false; // Flag to indicate halt without exiting the program

    void loadFromMemory(int idxReg, int idxMem, Register &reg, Memory &mem)
    {
        reg.setCell(idxReg, ALU::hexToDec(mem.getCell(idxMem)));
    }

    void loadImmediate(int idxReg, int value, Register &reg)
    {
        reg.setCell(idxReg, value);
    }

    void storeToMemory(int idxReg, int idxMem, Register &reg, Memory &mem, vector<string> &expectedOutput)
    {
        mem.setCell(idxMem, ALU::decToHex(reg.getCell(idxReg)));
        if (idxMem == 0)
        {
            expectedOutput.push_back((mem.getCell(idxMem)));
        }
    }

    void copyRegister(int idxReg1, int idxReg2, Register &reg)
    {
        reg.setCell(idxReg2, reg.getCell(idxReg1));
    }

    void addIntegers(int idxR, int idxS, int idxT, Register &reg)
    {
        int valueS = reg.getCell(idxS);
        int valueT = reg.getCell(idxT);
        int result = (valueS + valueT) % 256;
        reg.setCell(idxR, result);
    }

    void bitwiseOr(int idxR, int idxS, int idxT, Register &reg)
    {
        reg.setCell(idxR, ALU::bitwiseOr(idxS, idxT, reg));
    }

    void bitwiseAnd(int idxR, int idxS, int idxT, Register &reg)
    {
        reg.setCell(idxR, ALU::bitwiseAnd(idxS, idxT, reg));
    }

    void bitwiseXor(int idxR, int idxS, int idxT, Register &reg)
    {
        reg.setCell(idxR, ALU::bitwiseXor(idxS, idxT, reg));
    }

    void rotateRight(int idxR, int steps, Register &reg)
    {
        reg.setCell(idxR, ALU::rotateRight(reg.getCell(idxR), steps));
    }

    void jumpIfEqual(int idxR, int idxMem, Register &reg, int &PC)
    {
        if (reg.getCell(idxR) == reg.getCell(0))
        {
            PC = idxMem - 10;
        }
    }

    void jumpIfGreater(int idxR, int idxMem, Register &reg, int &PC)
    {
        if (reg.getCell(idxR) > reg.getCell(0))
        {
            PC = idxMem;
        }
    }

    void halt()
    {
        haltFlag = true; // Set the flag to stop the current program but stay in the main menu
    }
};
#endif