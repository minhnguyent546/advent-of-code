/**            
 * author      minhnguyent546
 * created_at  Tue, 2024-01-09 17:12:07
 **/           
#include <bits/stdc++.h>
#include "../lib/functions.h"
using namespace std;

#ifdef LOCAL
#include "cp/debug.h"
#else
#define debug(...)
#endif

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int INF = 0x3f3f3f3f;

const int BASE = 17;
const int MOD = 256;

int encode(const string &s) {
    int res = 0;
    for (int i = 0; i < (int) s.size(); ++i) {
        if (s[i] == '\n' || s[i] == '\r') continue;
        res = (res + s[i]) * BASE % MOD;
    }
    return res;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    cin >> s;
    vector<string> sequences = str_split(s, ",");
    int sum = 0;
    for (const string &seq : sequences) {
        sum += encode(seq);
    }
    cout << sum << '\n';

    return 0;
}
