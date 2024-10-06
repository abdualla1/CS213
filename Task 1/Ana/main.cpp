#include <bits/stdc++.h>

using namespace std;
#define all(x) (x).begin(), (x).end()
#define endl '\n'

class InputValidator {
public:
    bool isValidOption(int option, int min, int max) {
        if (cin.fail()) {
            cin.clear(); // clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            return false;
        }
        return option >= min && option <= max;
    }

    bool isValidPositiveInteger(int num) {
        if (cin.fail() || num < 0) {
            cin.clear(); // clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            return false;
        }
        return true;
    }

    bool isValidFile(const string& filename) {
        ifstream file(filename);
        return file.good();
    }

    bool isValidMenu(int choice, const vector<int>& menu) {
        return find(all(menu), choice) != menu.end();
    }
};

void menu1() {
    cout << "-=*=-=*=-=*=-=*=-=*=-=*=-" << endl;
    cout << setw(26) << "AHLAN YA RO7E YA USER" << endl;
    cout << setw(26) << "E5tar your desired Problem HABIBI ( Number )" << endl;
    cout << "3- String Splitter ( Delimiter is space by default )" << endl;
    cout << "6- Binary Print" << endl;
    cout << "9- Teddy Bear Picnic" << endl;
    cout << "12- Phishing Scanner" << endl;
    cout << "0 - Exit" << endl;
    cout << "Enter the number corresponding to your choice: ";
}

void StringSplit(string s, string delimiter) {
    vector<string> ans;
    size_t pos = 0;
    while ((pos = s.find(delimiter)) != string::npos) {
        ans.push_back(s.substr(0, pos));
        s.erase(0, pos + delimiter.size());
    }
    ans.push_back(s);

    for (const auto& i : ans)
        cout << i << endl;
}

string BinaryPrintA(int n) {
    if (n == 0) return "0";
    return BinaryPrintA(n / 2) + to_string(n % 2);
}

void BinaryPrintB(const string& prefix, int k) {
    for (int i = 0; i < (1 << k); i++) {
        string t = prefix;
        for (int j = 0; j < k; j++) {
            t += ((i & (1 << j)) ? '1' : '0');
        }
        cout << t << endl;
    }
}

bool Teddy(int n) {
    if (n == 42) return true;
    if (n < 42) return false;
    if (n % 2 == 0 && Teddy(n / 2)) return true;
    if ((n % 3 == 0 || n % 4 == 0) && ((n % 10) * ((n % 100) / 10)) != 0 && Teddy(n - ((n % 10) * ((n % 100) / 10)))) return true;
    if (n % 5 == 0 && Teddy(n - 42)) return true;
    return false;
}

void PhishingScanner(const string& filename) {
    vector<pair<string, int>> phishingKeywords = {
            {"password", 3}, {"login", 3}, {"credit card", 3}, {"bank", 3},
            {"social security", 3}, {"verify", 2}, {"click", 2}, {"urgent", 2},
            {"account", 2}, {"update", 2}, {"limited time", 2}, {"confirm", 2},
            {"secure", 1}, {"sensitive", 1}, {"pay now", 1}, {"threat", 1},
            {"unauthorized", 2}, {"failure", 1}, {"risk", 2}, {"support", 2},
            {"paypal", 3}, {"ebay", 3}, {"amazon", 3}, {"transaction", 1},
            {"alert", 1}, {"congratulations", 1}, {"offer", 2}, {"request", 1},
            {"dear customer", 1}, {"free", 1}
    };

    ifstream file(filename);
    if (!file) {
        cerr << "Error: Could not open the file!" << endl;
        return;
    }

    string line;
    int totalScore = 0;
    map<string, int> keywordCounts;
    while (getline(file, line)) {
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        for (const auto& [keyword, score] : phishingKeywords) {
            size_t pos = line.find(keyword);
            while (pos != string::npos) {
                keywordCounts[keyword]++;
                totalScore += score;
                pos = line.find(keyword, pos + 1);
            }
        }
    }
    file.close();

    cout << "Phishing Report:" << endl;
    for (const auto& [keyword, count] : keywordCounts) {
        cout << "Keyword: " << keyword << ", Count: " << count << ", Total Points: " << count * phishingKeywords[0].second << endl;
    }
    cout << "Total Phishing Score: " << totalScore << endl;
    cout << (totalScore >= 10 ? "Warning: This email appears highly suspicious!" : "This email seems legitimate.") << endl;
}

void solve() {
    int choice;
    InputValidator validator;

    do {
        menu1();

        // Validate input to ensure it's a number
        while (!(cin >> choice)) {
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid input! Please enter a valid number: ";
        }

        // Ensure the choice is a valid option in the menu
        if (!validator.isValidOption(choice, 0, 12)) {
            cout << "Invalid option! Please select a valid option from the menu." << endl;
            continue;
        }

        switch (choice) {
            case 3: {
                cout << "Enter the string to split: ";
                string s;
                cin.ignore();
                getline(cin, s);
                cout << "Enter the delimiter (or press enter to use space): ";
                string delim;
                getline(cin, delim);
                if (delim.empty()) delim = " ";
                StringSplit(s, delim);
                break;
            }
            case 6: {
                int option;
                cout << "Choose option A (1) or B (2): ";
                cin >> option;

                if (!validator.isValidOption(option, 1, 2)) {
                    cout << "Invalid option for Binary Print!" << endl;
                    break;
                }

                if (option == 1) {
                    cout << "Enter an integer to convert to binary: ";
                    int n;
                    cin >> n;
                    if (validator.isValidPositiveInteger(n)) {
                        cout << stoll(BinaryPrintA(n)) << endl;
                    } else {
                        cout << "Invalid input. Please enter a positive integer." << endl;
                    }
                } else {
                    cout << "Enter the prefix: ";
                    string prefix;
                    cin >> prefix;
                    cout << "Enter the number of binary digits: ";
                    int k;
                    cin >> k;
                    if (validator.isValidPositiveInteger(k)) {
                        BinaryPrintB(prefix, k);
                    } else {
                        cout << "Invalid input for k." << endl;
                    }
                }
                break;
            }
            case 9: {
                cout << "Enter the number of bears: ";
                int n;
                cin >> n;
                if (validator.isValidPositiveInteger(n)) {
                    cout << (Teddy(n) ? "YES" : "NO") << endl;
                } else {
                    cout << "Invalid input. Please enter a positive number of bears." << endl;
                }
                break;
            }
            case 12: {
                cout << "Enter the filename to scan for phishing terms: ";
                string filename;
                cin >> filename;
                if (validator.isValidFile(filename)) {
                    PhishingScanner(filename);
                } else {
                    cout << "Error: Invalid file name or file does not exist." << endl;
                }
                break;
            }
            case 0: {
                cout << "Exiting the program..." << endl;
                exit(0);
            }
            default:
                cout << "Invalid option! Please select a valid option from the menu." << endl;
        }
    } while (choice != 0);
}

int main() {
    solve();
    return 0;
}
