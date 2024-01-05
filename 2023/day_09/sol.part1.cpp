/**            
 * author      minhnguyent546
 * created_at  Thu, 2024-01-04 00:50:56
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

const int MOD = (int) 1e9 + 7;
const int INF = 0x3f3f3f3f;


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string line;
    long long res = 0;
    while (getline(cin, line)) {
        istringstream iss(line);
        vector<long long> arr = exact_numbers<long long>(str_split(line));
        int n = (int) arr.size();
        for (int i = n - 1; i > 0; --i) {
            for (int j = 0; j < i; ++j) {
                arr[j] = arr[j + 1] - arr[j];
            }
        }
        long long x = accumulate(arr.begin(), arr.end(), 0LL);
        res += x;
    }
    cout << res << '\n';

    return 0;
}
