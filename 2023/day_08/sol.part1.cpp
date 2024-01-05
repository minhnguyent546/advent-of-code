/**            
 * author      minhnguyent546
 * created_at  Wed, 2024-01-03 21:27:31
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
    string instruction;
    cin >> instruction;
    string bar;
    getline(cin, bar);
    map<string, pair<string, string>> which;
    while (getline(cin, bar)) {
        string cur = bar.substr(0, 3);
        string left = bar.substr(bar.find('(') + 1, 3);
        string right = bar.substr(bar.rfind(' ') + 1, 3);
        which[cur] = make_pair(left, right);
    }
    int step = 0;
    int n = (int) instruction.size();
    string cur = "AAA";
    while (cur != "ZZZ") {
        string ncur = (instruction[step % n] == 'L'
                ? which[cur].first
                : which[cur].second); 
        ++step;
        cur = ncur;
    }
    cout << step << '\n';
    return 0;
}
