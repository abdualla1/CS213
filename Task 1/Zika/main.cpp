#include <bits/stdc++.h>
#include <codecvt>
using namespace std;
#define endl '\n'
#define ll long long
#define fast ios_base::sync_with_stdio(0);cin.tie(0); cout.tie(0);

void problem1()
{
    string s, x;
    getline(cin, s, '.');
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
    while(x.back() == ' ')
        x.pop_back();
    x.push_back('.');
    cout << x << endl;
}

void problem4()
{
    fast 
    int n;
    cin >> n;
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
    for (int i = 2; i <= n; i++)
    {
        if (v[i])
            cout << v[i] << " ";
    }
}
struct Domino
{
    short rightDots;
    short leftDots;
};
bool FormsDominoChain(vector<Domino> &dominos)
{
    static vector <Domino> chain;
    if(dominos.empty()){
        for(int i = 0; i < chain.size(); i++)
        {
            (i == chain.size() - 1)? cout << chain[i].leftDots << "|" << chain[i].rightDots << endl : cout << chain[i].leftDots << "|" << chain[i].rightDots << " - "; 
        }
        return true;
    }
    for (ll i = 0; i < dominos.size(); i++)
    {
        if(chain.empty() || chain.back().rightDots == dominos[i].leftDots)
        {
            chain.push_back(dominos[i]); 
            Domino temp = dominos[i];  
            dominos.erase(dominos.begin() + i);
            if(FormsDominoChain(dominos))
                return true;
            dominos.insert(dominos.begin() + i, chain.back());
            chain.pop_back();
        }
    }
    return false;
}
void problem7()
{
    vector<Domino> dominos;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        Domino d;
        cin >> d.leftDots >> d.rightDots;
        dominos.push_back(d);
    }
    if(!FormsDominoChain(dominos))
        cout << "No solution" << endl;
}
map<wstring,vector<wstring>> loadTable(wifstream &file){
    map<wstring,vector<wstring>> table;
    file.imbue(locale(file.getloc(), new codecvt_utf8<wchar_t>));
    if(!file.is_open())
    {
        cout << "Error opening file" << endl;
        return table;
    }
    wstring line;
    while(getline(file, line))
    {
        wistringstream lineStream(line);
        wstring key;
        lineStream >> key;
        wstring value;
        while(lineStream >> value)
        {
            table[key].push_back(value);
        }
    }
    return table; 
};
void problem10()
{
    wifstream inputFile("input.txt");
    wifstream Table(L"Table.txt");
    inputFile.imbue(locale(inputFile.getloc(), new codecvt_utf8<wchar_t>));
    if(!inputFile.is_open())
    {
        cout << "Error opening file" << endl;
        return;
    }
    wstring line;
    wstring Text;
    while(getline(inputFile, line))
    {
        Text += line + L'\n';
    }
    vector<wstring> words;
    wstring word;
    wistringstream wordStream(Text);
    while(wordStream >> word)
    {
        words.push_back(word);
    }
    wofstream outputFile("output.txt");
    outputFile.imbue(locale(outputFile.getloc(), new codecvt_utf8<wchar_t>));
    if(!outputFile.is_open())
    {
        cout << "Error opening file" << endl;
        return;
    }
    map<wstring,vector<wstring>> table = loadTable(Table);
    for(int i = 0; i < words.size(); i++)
    {
        if(table.find(words[i]) != table.end())
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
    problem7();
}