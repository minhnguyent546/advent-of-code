/**            
 * author      minhnguyent546
 * created_at  Wed, 2024-01-03 16:14:40
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
    string times, distances;
    getline(cin, times);
    getline(cin, distances);

    times = str_split(times, ":")[1];
    distances = str_split(distances, ":")[1];

    times = str_trim(times);
    distances = str_trim(distances);

    vector<int> time_numbers = exact_numbers(str_split(times, " "));
    vector<int> distance_numbers = exact_numbers(str_split(distances, " "));
    assert(time_numbers.size() == distance_numbers.size());
    int n = (int) time_numbers.size();
    
    long long res = 1;
    for (int i = 0; i < n; ++i) {
        int ways = 0;
        for (int t = 0; t <= time_numbers[i]; ++t) {
            if (1LL * t * (time_numbers[i] - t) > distance_numbers[i]) ++ways;
        }
        res *= ways;
    }
    cout << res << '\n';
    return 0;
}
