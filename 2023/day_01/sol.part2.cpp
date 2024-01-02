/**            
 * author      minhnguyent546
 * created_at  Mon, 2024-01-01 22:04:31
 **/           
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "cp/debug.h"
#else
#define debug(...)
#endif

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MOD = (int) 1e9 + 7;
const int INF = 0x3f3f3f3f;


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    vector<string> digits = {
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine"
    };
    string s;
    long long sum = 0;
    while (cin >> s) {
        int n = (int) s.size();
        int x = 0;
        for (int t = 0; t < 2; ++t) {
            bool found = false;
            int num = 0;
            for (int i = 0; i < n && !found; ++i) {
                char ch = s[i];
                if ('0' <= ch && ch <= '9') {
                    num = ch - '0';
                    break;
                }
                for (int j = 0; j < (int) digits.size(); ++j) {
                    const string& digit = digits[j];
                    int sz = (int) digit.size();
                    if (i + sz - 1 < n && s.substr(i, sz) == digit) {
                        num = j + 1;
                        found = true;
                        break;
                    }
                }
            }
            x = x * 10 + num;
            reverse(s.begin(), s.end());
            for (string &digit : digits) { 
                reverse(digit.begin(), digit.end());
            }
        }
        sum += x;
    }
    cout << sum << '\n';    

    return 0;
}
