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