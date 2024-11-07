#ifndef CPU_H
#define CPU_H

#include "Register.h"
#include "Memory.h"
#include "ALU.h"
#include "CU.h"

#include <bits/stdc++.h>
using namespace std;

class CPU
{
public:
    int programCounter = 0;
    string instructionRegister;
    Register reg;
    ALU alu;
    CU cu;

    void fetch(Memory &mem)
    {
        if (programCounter < 0 || programCounter >= mem.size - 11)
        {
            cerr << "Error! Program counter out of bounds: " << programCounter << endl;
            cu.haltFlag = true;
            return;
        }
        string part1 = mem.getCell(programCounter + 10);
        string part2 = mem.getCell(programCounter + 11);
        instructionRegister = part1 + part2;
        programCounter += 2; // Increment by 2 since each instruction occupies two slots in memory
        if (instructionRegister.empty())
        {
            cu.haltFlag = true;
            return;
        }
    }

    vector<int> decode()
    {
        vector<int> result;
        if (instructionRegister.empty())
            return result;

        for (int i = 0; i < instructionRegister.size(); i++)
        {
            result.push_back(ALU ::hexToDec(instructionRegister.substr(i, 1)));
        }
        return result;
    }

    void execute(Memory &mem, vector<string> &expectedOutput)
    {
        if (cu.haltFlag)
            return;

        vector<int> instr = decode();
        int opcode = instr[0];
        switch (opcode)
        {
        case 0x1:
            cu.loadFromMemory(instr[1], instr[2] * 16 + instr[3], reg, mem);
            break;
        case 0x2:
            cu.loadImmediate(instr[1], instr[2] * 16 + instr[3], reg);
            break;
        case 0x3:
            cu.storeToMemory(instr[1], instr[2] * 16 + instr[3], reg, mem, expectedOutput);
            break;
        case 0x4:
            cu.copyRegister(instr[2], instr[3], reg);
            break;
        case 0x5:
            cu.addIntegers(instr[1], instr[2], instr[3], reg);
            break;
        case 0x6:
            cu.addFloats(instr[1], instr[2], instr[3], reg);
            break;
        case 0x7:
            cu.bitwiseOr(instr[1], instr[2], instr[3], reg);
            break;
        case 0x8:
            cu.bitwiseAnd(instr[1], instr[2], instr[3], reg);
            break;
        case 0x9:
            cu.bitwiseXor(instr[1], instr[2], instr[3], reg);
            break;
        case 0xA:
            cu.rotateRight(instr[1], instr[3], reg);
            break;
        case 0xB:
            cu.jumpIfEqual(instr[1], instr[2] * 16 + instr[3], reg, programCounter);
            break;
        case 0xC:
            cu.halt();
            break;
        case 0xD:
            cu.jumpIfGreater(instr[1], instr[2] * 16 + instr[3], reg, programCounter);
            break;
        default:
            cerr << "Error! Unknown operation code!" << endl;
        }
    }
};
#endif