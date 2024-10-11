#include <bits/stdc++.h>
#include <codecvt>
using namespace std;
#define endl '\n'
#define ll long long
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define all(x) (x).begin(), (x).end()

class InputValidator
{
public:
    bool isValidOption(int option, int min, int max)
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return false;
        }
        return option >= min && option <= max;
    }

    bool isValidPositiveInteger(int num)
    {
        if (cin.fail() || num < 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return false;
        }
        return true;
    }
    bool isValidFile(const string &filename)
    {
        ifstream file(filename);
        return file.good();
    }

    bool isValidMenu(int choice, const vector<int> &menu)
    {
        return find(all(menu), choice) != menu.end();
    }
};
void menu()
{
    cout << "Choose the number of the problem you want to solve." << endl;
    cout << "1. Problem 1" << endl;
    cout << "4. Problem 4" << endl;
    cout << "7. Problem 7" << endl;
    cout << "10. Problem 10" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
}
void problem1(string s)
{
    string x;
    bool space = true, upperCase = false;
    short n = s.length();
    for (int i = 0; i < n; ++i)
    {
        if (!upperCase && isalpha(s[i]))
        {
            x += toupper(s[i]);
            upperCase = true;
        }
        else
        {
            if (!space && (isspace(s[i]) || s[i] == '\n'))
            {
                x += ' ';
                space = true;
            }
            else if (!(isalpha(s[i]) || isspace(s[i])))
            {
                if (s[i] == '-' or s[i] == '\'')
                    x += s[i];
                else
                {
                    if (isspace(x.back()))
                        x.pop_back();
                    x += s[i];
                    x += ' ';
                    space = true;
                }
            }
            else if (isalpha(s[i]))
            {
                x += tolower(s[i]);
                space = false;
            }
        }
    }
    while (x.back() == ' ')
        x.pop_back();
    x.push_back('.');
    cout << x << endl;
}

void problem4(int n)
{
    vector<int> v(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        v[i] = i;
    }
    for (int i = 2; i <= n; i++)
    {
        if (!v[i])
            continue;
        for (int j = i + 1; j <= n; j++)
        {
            if (v[j] % v[i] == 0)
            {
                v[j] = 0;
            }
        }
    }
    cout << "Prime numbers from 1 to " << n << " are: ";
    for (int i = 2; i <= n; i++)
    {
        if(v[i]) cout << v[i] << " ";
    }
}
struct Domino
{
    short rightDots;
    short leftDots;
};
bool FormsDominoChain(vector<Domino> &dominos)
{
    static vector<Domino> chain;
    if (dominos.empty())
    {
        for (int i = 0; i < chain.size(); i++)
        {
            (i == chain.size() - 1) ? cout << chain[i].leftDots << "|" << chain[i].rightDots << endl : cout << chain[i].leftDots << "|" << chain[i].rightDots << " - ";
        }
        return true;
    }
    for (ll i = 0; i < dominos.size(); i++)
    {
        if (chain.empty() || chain.back().rightDots == dominos[i].leftDots)
        {
            chain.push_back(dominos[i]);
            Domino temp = dominos[i];
            dominos.erase(dominos.begin() + i);
            if (FormsDominoChain(dominos))
                return true;
            dominos.insert(dominos.begin() + i, chain.back());
            chain.pop_back();
        }
    }
    return false;
}
wstring trim(const wstring &str)
{
    auto start = str.begin();
    while (start != str.end() && isspace(*start))
    {
        ++start;
    }
    auto end = str.end();
    do
    {
        --end;
    } while (end != start && isspace(*end));
    return wstring(start, end + 1);
}
map<wstring, vector<wstring>> loadTable(wifstream &file)
{
    map<wstring, vector<wstring>> table;
    file.imbue(locale(file.getloc(), new codecvt_utf8<wchar_t>));
    if (!file.is_open())
    {
        cout << "Error opening file" << endl;
        return table;
    }
    wstring line;
    while (getline(file, line))
    {
        wistringstream lineStream(line);
        wstring word, key;
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == ',' || line[i] == '/' || line[i] == ':' || i == line.length() - 1)
            {
                if (key.empty())
                {
                    key = trim(word);
                }
                else
                {
                    if (i == line.length() - 1)
                        word += line[i];
                    table[key].push_back(trim(word));
                }
                word.clear();
            }
            else
            {
                word += line[i];
            }
        }
    }
    return table;
};
void problem10(string inputFileName, string tableFileName)
{
    wifstream inputFile(inputFileName);
    wifstream Table(tableFileName);
    inputFile.imbue(locale(inputFile.getloc(), new codecvt_utf8<wchar_t>));
    if (!inputFile.is_open())
    {
        cout << "Error opening file" << endl;
        return;
    }
    wstring line;
    wstring Text;
    while (getline(inputFile, line))
    {
        Text += line + L'\n';
    }
    vector<wstring> words;
    wstring word;
    wistringstream wordStream(Text);
    while (wordStream >> word)
    {
        words.push_back(word);
    }
    map<wstring, vector<wstring>> table = loadTable(Table);
    wofstream outputFile("output.txt");
    outputFile.imbue(locale(outputFile.getloc(), new codecvt_utf8<wchar_t>));
    if (!outputFile.is_open())
    {
        cout << "Error opening file" << endl;
        return;
    }
    for (int i = 0; i < words.size(); i++)
    {
        if (table.find(words[i]) != table.end())
        {
            outputFile << table[words[i]][rand() % table[words[i]].size()] << L" ";
        }
        else
        {
            outputFile << words[i] << L" ";
        }
    }
    inputFile.close();
    outputFile.close();
}
int main()
{
    cout << "AHLAN YA USER YA HABIBI." << endl;
    int choice;
    InputValidator validator;
    do
    {
        menu();
        while (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input!" << endl <<"Please enter a valid number: ";
            menu();
        }
        if (!validator.isValidOption(choice, 0, 10))
        {
            cout << "Invalid choice!" << endl <<"Please select a valid option from the menu." << endl;
            continue;
        }
        switch (choice)
        {
        case 1: {
            string s;
            cout << "Enter a string (must end with '.'): ";
            getline(cin, s, '.');
            problem1(s);
            break;
        }
        case 4: {
            int n;
            while (true)
            {
                cout << "Enter a positive integer: ";
                cin >> n;
                if (!validator.isValidPositiveInteger(n))
                {
                    cout << "Invalid input!" << endl << "Please enter a positive integer." << endl;
                }
                else
                {
                    problem4(n);
                    cout << endl;
                    break;
                }
            }
            break;
        }
        case 7: {
            int n;
            vector<Domino> dominos;
            do
            {
                cout << "Enter the number of dominos: ";
                cin >> n;
                if (!validator.isValidPositiveInteger(n))
                {
                    cout << "Invalid input!" << endl << "Please enter a positive integer." << endl;
                }
            } while (!validator.isValidPositiveInteger(n));
            cout << "Enter the left and right dots of each domino:" << endl;
            for (int i = 1; i <= n; i++)
            {
                Domino d;
                cin >> d.leftDots >> d.rightDots;
                if(d.leftDots < 0 || d.rightDots < 0){
                    cout << "Invalid input!" << endl << "Please enter a positive integer." << endl;
                    i--;
                    continue;
                }
                dominos.push_back(d);
            }
            if(!FormsDominoChain(dominos)){
                cout << "No solution exists." << endl;
            }
            break;
        }
        case 10: {
            cout << "Enter the input file name: ";
            string inputFileName;
            cin >> inputFileName;
            cout << "Enter the table file name: ";
            string tableFileName;
            cin >> tableFileName;
            if (validator.isValidFile(inputFileName) && validator.isValidFile(tableFileName))
            {
                problem10(inputFileName, tableFileName);
            }
            else
            {
                cout << "Error!" << endl << "Something wrong happened or invalid file name!." << endl;
            }
            break;
        }
        case 0:
            cout << "Exiting the program" << endl;
            return 0;
        default:
            cout << "Invalid Choice!" << endl << "Please select a valid choice." << endl;
        }
    } while (choice != 0);
}