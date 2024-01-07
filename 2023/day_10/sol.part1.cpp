/**            
 * author      minhnguyent546
 * created_at  Thu, 2024-01-04 10:42:26
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
    string pipes = "|-LJ7F";
    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};
    map<char, array<int, 2>> dirs;
    dirs['|'] = {0, 2};
    dirs['-'] = {1, 3};
    dirs['L'] = {0, 1};
    dirs['J'] = {0, 3};
    dirs['7'] = {2, 3};
    dirs['F'] = {1, 2};

    vector<string> grid;
    string bar;
    while (cin >> bar) {
        grid.emplace_back(bar);
    }
    int n = (int) grid.size(), m = (int) grid.back().size();
    pair<int, int> start_pos;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 'S') start_pos = make_pair(i, j);
        }
    }

    auto valid = [&](int r, int c) -> bool {
        return (0 <= r && r < n && 0 <= c && c < m && grid[r][c] != '.');
    };

    auto is_connect = [&](int r, int c, int rr, int cc) -> bool {
        for (int t : dirs[grid[rr][cc]]) {
            int nr = rr + dr[t];
            int nc = cc + dc[t];
            if (nr == r && nc == c) return true;
        }
        return false;
    };
    int res = -1;
    for (char start_pipe : pipes) {
        auto [r, c] = start_pos;
        int prev_r = -1, prev_c = -1;
        vector<vector<bool>> visited(n, vector<bool>(m));
        grid[r][c] = start_pipe;
        int step = 0;
        bool good = true;
        while (true) {
            for (int t : dirs[grid[r][c]]) {
                int nr = r + dr[t];
                int nc = c + dc[t];
                if (nr == prev_r && nc == prev_c) continue;
                if (!valid(nr, nc) || !is_connect(r, c, nr, nc)) {
                    good = false;
                    goto end_while;
                }
                prev_r = r; prev_c = c;
                r = nr; c = nc;
                ++step;
                break;
            }
            if (make_pair(r, c) == start_pos) break;
        }
        end_while:
        if (good) {
            res = max(res, step / 2);
        }
    }
    cout << res << '\n';
    return 0;
}
