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

struct Range {
    long long l, r;
    friend ostream& operator<<(ostream &os, const Range &range) {
        return os << "(" << range.l << ", " << range.r << ")";
    }
};

/**
 * @brief return a pair with `first` is `true` if there is an intersection,
 * otherwise `false`, and `second` is ranges belong to `x`.
 */
pair<bool, vector<Range>> intersect(Range x, Range y) {
    long long l = max(x.l, y.l);
    long long r = min(x.r, y.r);
    bool has_intersection = (l <= r);
    vector<Range> ranges;
    if (has_intersection) {
        ranges.emplace_back(l, r);
        if (x.l < l) {
            ranges.emplace_back(x.l, l - 1);
        }
        if (x.r > r) {
            ranges.emplace_back(r + 1, x.r);
        }
    }
    else {
        ranges.emplace_back(x);
    }
    return make_pair(has_intersection, ranges);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string bar;
    getline(cin, bar);
    vector<string> seeds_str = str_split(bar.substr(7));
    vector<long long> initial_seeds = exact_numbers<long long>(seeds_str);
    assert((int) initial_seeds.size() % 2 == 0);
    vector<Range> ranges;
    for (int i = 0; i < (int) initial_seeds.size(); i += 2) {
        ranges.emplace_back(
            initial_seeds[i],
            initial_seeds[i] + initial_seeds[i + 1] - 1
        );
    }
    getline(cin, bar); // ignore empty line
    while (getline(cin, bar)) {
        bar = str_split(bar)[0];
        string nums_str;
        vector<Range> nranges;
        while (getline(cin, nums_str)) {
            if (nums_str.empty()) break;
            vector<long long> nums = exact_numbers<long long>(str_split(nums_str));
            assert((int) nums.size() == 3);
            Range y = Range{nums[1], nums[1] + nums[2] - 1};
            long long new_value = nums[0];
            vector<Range> remain;
            for (Range x : ranges) {
                assert(x.l <= x.r);
                auto [has_intersection, rs] = intersect(x, y);
                if (!has_intersection) {
                    remain.emplace_back(x);
                }
                else {
                    Range common = rs[0];
                    nranges.emplace_back(
                        new_value + common.l - y.l,
                        new_value + common.r - y.l
                    );
                    copy(rs.begin() + 1, rs.end(), back_inserter(remain));
                }
            }
            ranges.swap(remain);
        }
        move(nranges.begin(), nranges.end(), back_inserter(ranges));
    }   
    long long res = INF_LL;
    for (Range x : ranges) {
        res = min(res, x.l);
    }
    cout << res << '\n';

    return 0;
}
