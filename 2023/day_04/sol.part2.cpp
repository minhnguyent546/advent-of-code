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
const int N = (int) 1e5;
const int V = (int) 1e3;
int freq[V];

template<typename T = int>
struct FenwickTree {
    int n;
    vector<T> tree;
    FenwickTree() {}
    FenwickTree(int _n): n(_n) {
        tree.resize(n);
    }
    void __add(int i, T v) {
        while (i < n) {
            tree[i] += v;
            i |= (i + 1);
        }
    }
    T __pref(int i) {
        T res{};
        while (i >= 0) {
            res += tree[i];
            i = (i & (i + 1)) - 1;
        }
        return res;
    }
    void add(int l, int r, T v) {
        if (l > r) return;
        __add(l, v);
        __add(r + 1, -v);
    }
    T get(int i) {
        return __pref(i);
    }
};

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
    FenwickTree<int> coeff(N);
    coeff.add(0, N - 1, 1);
    long long res = 0;
    int idx = 0;
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
        int cur_coeff = coeff.get(idx);
        res += cur_coeff;
        coeff.add(idx + 1, idx + matches, cur_coeff);
        ++idx;
    }
    cout << res << '\n';

    return 0;
}
