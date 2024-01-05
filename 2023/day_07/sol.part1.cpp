/**            
 * author      minhnguyent546
 * created_at  Wed, 2024-01-03 20:56:24
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
    string labels = "AKQJT98765432";
    auto idx = [&](char ch) -> int {
        auto i = labels.find(ch);
        assert(i != string::npos);
        return (int) i;
    };
    auto encode = [&](const string &s) -> string {
        map<char, int> f;
        for (char ch : s) f[ch]++;
        string res = "";    
        for (auto [ch, cnt] : f) {
            res += to_string(cnt);
        }
        sort(res.begin(), res.end(), greater<>());
        return res;
    };
    vector<pair<string, int>> arr;
    arr.emplace_back();
    while (cin >> arr.back().first >> arr.back().second) {
        arr.emplace_back();
    }
    arr.pop_back(); 
    sort(arr.begin(), arr.end(), [&encode, &idx](const auto &lhs, const auto &rhs) -> bool {
        string left = encode(lhs.first);
        string right = encode(rhs.first);
        if (left == right) {
            for (int i = 0; i < (int) lhs.first.size(); ++i) {
                char x = lhs.first[i];
                char y = rhs.first[i];
                if (x != y) return idx(x) > idx(y);
            }
            return false;
        }
        return left < right;
    });
    long long res = 0;
    for (int i = 0; i < (int) arr.size(); ++i) {
        res += 1LL * arr[i].second * (i + 1);
    }
    cout << res << '\n';
    return 0;
}
