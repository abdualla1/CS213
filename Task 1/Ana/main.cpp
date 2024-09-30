#include <bits/stdc++.h>

using namespace std;
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define endl '\n'
#define yes cout << "YES\n";
#define no cout << "NO\n";
#define ll long long
#define sz(x) (int)x.size()
#define EO(x) (x & 1 ? "ODD" : "EVEN")
#define YN(x) (x ? "YES" : "NO")
#define watch(x) cout << #x << " = " << x << endl

void zo7le2a() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
#ifdef Clion
    freopen("input.txt", "r", stdin);
    freopen("outputt.txt", "w", stdout);
#endif
}

class InputValidator {
public:
    InputValidator() = default;
};

void menu1() {
    cout << "-=*=-=*=-=*=-=*=-=*=-=*=-" << endl;
    cout << setw(26) << "AHLAN YA RO7E YA USER" << endl;
    cout << setw(26) << "E5tar your desired Problem HABIBI ( Number )" << endl;
    cout << "3- String Spilter" << endl; // input delimter or space by default
    cout << "6- Binary Print" << endl; // has a and b option;
    cout << "9- Teddy Bear Picnic" << endl;
    cout << "12- Phishing Scanner" << endl;
}

void StringSplit(string s, string delimiter) {
    string t = s;
    vector<string> ans;
    while (sz(t)) {
        auto x = t.find(delimiter);
        if (x != -1) {
            ans.push_back(t.substr(0, x));
            t.erase(0, x + 1);
        } else {
            ans.push_back(t);
            break;
        }
    }
    for (auto i: ans) cout << i << endl;
}

string BinaryPrintA(int n) {
    if (n == 0) return "0";
    return BinaryPrintA(n / 2) + to_string(n % 2);
}

void BinaryPrintB(string s, int k) {
    for (int i = 0; i < (1 << k); i++) {
        string t = s;
        for (int j = 0; j < k; j++) {
            t += ((i & (1 << j)) ? '1' : '0');
        }
        cout << t << endl;
    }
}

bool Teddy(int n) {
    if (n == 42) return true;
    if(n < 42) return false;
    if(n % 2 == 0 && Teddy(n / 2)) return true;
    if((n % 3 == 0 || n% 4 == 0) && Teddy(n - ((n%10) * ((n%100) / 10)))) return true;
    if(n % 5 == 0 && Teddy(n - 42)) return true;
    return false;
}

void solve() {
    int n;
    cin >> n;
    cout << YN(Teddy(n)) << endl;
}

signed main() {
    zo7le2a();
    int t = 1;
    cin >>t;
    while (t--) {
        solve();
    }
}