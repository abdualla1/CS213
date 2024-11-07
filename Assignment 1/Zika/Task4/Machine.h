#ifndef MACHINE_H
#define MACHINE_H

#include "CPU.h"
#include "Memory"

#include <bits/stdc++.h>
using namespace std;

class Machine
{
public:
    CPU processor;
    Memory memory;
    vector<pair<int, string>> instructions;
    vector<string> expectedOutput;
    void loadProgramFile(const string &filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cerr << "Could not open the file!" << endl;
            return;
        }
        string line;
        int address = 10;
        while (file >> line)
        {
            if (!regex_match(line, regex("^[0-9A-Fa-f]+$")))
            {
                cerr << "Invalid instruction: " << line << endl;
                return;
            }
            instructions.push_back({address, line});
            memory.setCell(address, line);
            address += 2;
        }
        file.close();
    }

    void outputState() const
    {
        cout << "Program Counter: " << processor.programCounter << endl;
        for (int i = 0; i < 16; i++)
        {
            cout << "Register " << i << ": " << ALU::decToHex(processor.reg.getCell(i)) << endl;
        }
        cout << "Memory Contents:" << endl;
        for (int row = 0; row < memory.size; row += 16)
        {
            for (int col = 0; col < 16; ++col)
            {
                int index = row + col;
                if (index < memory.size)
                {
                    if (!memory.getCell(index).empty())
                    {
                        cout << setw(3) << memory.getCell(index) << " ";
                    }
                    else
                    {
                        cout << " 00 ";
                    }
                }
            }
            cout << endl;
        }
        cout << "Expected output: ";
        for (auto &i : expectedOutput)
        {
            cout << ALU ::hexToDec(i) << " ";
        }
        cout << endl;
    }

    void reset()
    {
        memory.clear();
        processor.reg.clear();
        processor.programCounter = 0;
        processor.cu.haltFlag = false;
        cout << "Machine reset completed." << endl;
    }
};
#endif