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

vector<pair<string, int>> _hashmap[MOD];

int encode(const string &s) {
    int res = 0;
    for (int i = 0; i < (int) s.size(); ++i) {
        if (s[i] == '\n' || s[i] == '\r') continue;
        res = (res + s[i]) * BASE % MOD;
    }
    return res;
}

void assign(const string &key, int value) {
    int bucket = encode(key);
    for (auto &[_key, _value] : _hashmap[bucket]) {
        if (_key == key) {
            _value = value;
            return;
        }
    }
    _hashmap[bucket].emplace_back(key, value);
}

void remove(const string &key) {
    int bucket = encode(key);
    auto it = _hashmap[bucket].begin();
    while (it != _hashmap[bucket].end() && it->first != key) ++it;
    if (it != _hashmap[bucket].end()) {
        _hashmap[bucket].erase(it);
    }
}   

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    cin >> s;
    vector<string> sequences = str_split(s, ",");
    for (const string &seq : sequences) {
        if (seq.find('=') != seq.npos) {
            string key = seq.substr(0, seq.find('='));
            int value = stoi(seq.substr(seq.find('=') + 1));
            assign(key, value);
        }
        else {
            assert(seq.back() == '-');
            string key = seq;
            key.pop_back();
            remove(key);
        }
    }
    long long res = 0;
    for (int i = 0; i < MOD; ++i) {
        long long cur = 0;
        for (int j = 0; j < (int) _hashmap[i].size(); ++j) {
            cur += (j + 1) * _hashmap[i][j].second;
        }
        cur *= (i + 1);
        res += cur;
    }
    cout << res << '\n';
    return 0;
}
