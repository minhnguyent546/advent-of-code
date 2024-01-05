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

inline long long sqr(int x) { return 1LL * x * x; }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string times, distances;
    getline(cin, times);
    getline(cin, distances);

    times = str_split(times, ":")[1];
    distances = str_split(distances, ":")[1];
    
    times = str_trim(times);
    distances = str_trim(distances);

    vector<string> time_numbers = str_split(times, " ", true);
    vector<string> distance_numbers = str_split(distances, " ", true);
    assert(time_numbers.size() == distance_numbers.size());
    int n = (int) time_numbers.size();

    string actual_time_str = "", actual_distance_str = "";
    for (int i = 0; i < n; ++i) {
        actual_time_str += time_numbers[i];
        actual_distance_str += distance_numbers[i];
    }
    assert(stoi(actual_time_str) && stoll(actual_distance_str));
    int T = stoi(actual_time_str);
    long long D = stoll(actual_distance_str);
    int tl = (T - sqrt(sqr(T) - 4 * D)) / 2;
    int tr = (T + sqrt(sqr(T) - 4 * D)) / 2;
    while (sqr(tl) - 1LL * T * tl + D < 0) --tl;
    while (sqr(tl) - 1LL * T * tl + D >= 0) ++tl;

    while (sqr(tr) - 1LL * T * tr + D < 0) ++tr;
    while (sqr(tr) - 1LL * T * tr + D >= 0) --tr;
    assert(0 <= tl && tl <= tr && tr <= T);
    cout << tr - tl + 1 << '\n';

    return 0;
}
