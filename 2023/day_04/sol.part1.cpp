/**            
 * author      minhnguyent546
 * created_at  Tue, 2024-01-02 20:22:35
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

const char minchar = '0';
const int V = (int) 1e3;
int freq[V];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string winning, have;
    long long res = 0;
    while (getline(cin, winning) && getline(cin, have)) {
        vector<int> winning_numbers = exact_numbers(str_split(winning));
        vector<int> have_numbers = exact_numbers(str_split(have));
        int matches = 0;
        for (int num : have_numbers) {
            freq[num]++;
        }
        for (int num : winning_numbers) {
            if (freq[num] > 0) {
                ++matches;
            }
        }
        for (int num : have_numbers) {
            freq[num]--;
        }
        if (matches > 0) {
            res += (1LL << (matches - 1));
        }
    }
    cout << res << '\n';

    return 0;
}
