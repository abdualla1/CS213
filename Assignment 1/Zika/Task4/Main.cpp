#include "Machine.h"
#include <bits/stdc++.h>
using namespace std;

class MainUI
{
private:
    Machine machine;

public:
    void LoadProgram()
    {
        string filename;
        cout << "Enter filename: ";
        cin >> filename;
        if (cin.fail())
        {
            cerr << "Invalid filename!" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
        machine.loadProgramFile(filename);
    }
    void RunProgram()
    {
        while (machine.processor.programCounter / 2 <= machine.instructions.size())
        {
            machine.processor.fetch(machine.memory);
            machine.processor.execute(machine.memory, machine.expectedOutput);
        }
    }

    void Reset()
    {
        machine.reset();
    }

    void DisplayOutput() const
    {
        machine.outputState();
    }

    void Execute()
    {
        while (true)
        {
            cout << "1. Load Program\n2. Reset\n3. Run Program\n4. Display Output\n5. Exit\n";
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number." << endl;
                continue;
            }
            switch (choice)
            {
            case 1:
                LoadProgram();
                break;
            case 2:
                Reset();
                break;
            case 3:
                RunProgram();
                break;
            case 4:
                DisplayOutput();
                break;
            case 5:
                cout << "Exiting program." << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        }
    }
};

int main()
{
    MainUI ui;
    ui.Execute();
    return 0;
}