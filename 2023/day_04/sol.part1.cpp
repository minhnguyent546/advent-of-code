/**            
 * author      minhnguyent546
 * created_at  Tue, 2024-01-02 20:22:35
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

const char minchar = '0';
const int V = (int) 1e3;
int freq[V];

vector<int> str_split(const string &str, char delimiter = ' ') {
    vector<int> numbers;
    int n = (int) str.size();
    for (int i = 0; i < n; ++i) {
        if (str[i] == delimiter) continue;
        int j = i - 1;
        int num = 0;
        while (j + 1 < n && str[j + 1] != delimiter) {
            num = num * 10 + (str[++j] - minchar);
        }
        numbers.push_back(num);
        i = j;
    }
    return numbers;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string winning, have;
    long long res = 0;
    while (getline(cin, winning) && getline(cin, have)) {
        vector<int> winning_numbers = str_split(winning, ' ');
        vector<int> have_numbers = str_split(have, ' ');
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
            cerr << (1LL << (matches - 1)) << '\n';
        }
    }
    cout << res << '\n';

    return 0;
}
