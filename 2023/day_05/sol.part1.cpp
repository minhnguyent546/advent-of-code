/**            
 * author      minhnguyent546
 * created_at  Tue, 2024-01-02 22:50:17
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
const long long INF_LL = 0x3f3f3f3f3f3f3f3f;

pair<string, string> exact_str_map(const string &s) {
    vector<string> ss = str_split(s, "-");
    assert((int) ss.size() == 3);
    return make_pair(ss[1], ss[0]);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string bar;
    getline(cin, bar);
    vector<string> seeds_str = str_split(bar.substr(7));
    vector<long long> seeds = exact_numbers<long long>(seeds_str);
   
    getline(cin, bar);
    while (getline(cin, bar)) {
        bar = str_split(bar)[0];
        auto[from, to] = exact_str_map(bar);
        string nums_str;
        map<long long, long long> new_seeds;
        while (getline(cin, nums_str)) {
            if (nums_str.empty()) break;
            vector<long long> nums = exact_numbers<long long>(str_split(nums_str));
            assert((int) nums.size() == 3);
            long long x = nums[0], y = nums[1], z = nums[2];
            for (auto seed : seeds) {
                if (y <= seed && seed < y + z) {
                    new_seeds[seed] = seed + x - y;
                }
            }
        }
        for (long long &seed : seeds) {
            if (new_seeds.count(seed)) {
                seed = new_seeds[seed];
            }
        }
    }   
    cout << *min_element(seeds.begin(), seeds.end()) << '\n';

    return 0;
}
