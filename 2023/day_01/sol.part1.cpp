/**            
 * author      minhnguyent546
 * created_at  Mon, 2024-01-01 22:04:24
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
    string s;
    long long sum = 0;
    while (cin >> s) {
        int x = 0;
        for (int t = 0; t < 2; ++t) {
            for (char ch : s) {
                if ('0' <= ch && ch <= '9') {
                    x = x * 10 + (ch - '0');
                    break;
                }
            }
            reverse(s.begin(), s.end());
        }
        sum += x;
    }
    cout << sum << '\n';    

    return 0;
}
