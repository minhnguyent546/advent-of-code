/**            
 * author      minhnguyent546
 * created_at  Fri, 2024-01-12 01:08:21
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
int dir = 4;
int dr[] = {-1, 0, 1, 0}; // clockwise direction
int dc[] = {0, 1, 0, -1};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    vector<vector<char>> grid;
    string bar;
    while (cin >> bar) {
        grid.emplace_back(bar.size());
        for (int i = 0; i < (int) bar.size(); ++i) {
            grid.back()[i] = bar[i];
        }
    }   
    int n = (int) grid.size();
    int m = (int) grid.back().size();

    auto in_grid = [&](int r, int c) -> bool {
        return (0 <= r && r < n && 0 <= c && c < m);
    };

    auto idx = [&](int r, int c) -> int {
        return r * m + c;
    };

    vector<pair<int, int>> que;
    vector<vector<array<bool, 4>>> vis(n, vector<array<bool, 4>>(m));
    auto Push = [&](int r, int c, int t) {
        if (in_grid(r, c) && !vis[r][c][t]) {
            vis[r][c][t] = true;
            que.emplace_back(idx(r, c), t);
        }
    };

    auto bfs = [&](int start_r, int start_c, int start_dir) -> int {
        Push(start_r, start_c, start_dir);
        for (int k = 0; k < (int) que.size(); ++k) {
            auto [u, t] = que[k];
            int r = u / m, c = u - r * m;
            char ch = grid[r][c];
            if (ch == '.') {
                int nr = r + dr[t];
                int nc = c + dc[t];
                Push(nr, nc, t);
            }
            else if (ch == '|') {
                if (t == 0 || t == 2) {
                    int nr = r + dr[t];
                    int nc = c + dc[t];
                    Push(nr, nc, t);
                }
                else {
                    Push(r - 1, c, 0);
                    Push(r + 1, c, 2);
                }
            }
            else if (ch == '-') {
                if (t == 1 || t == 3) {
                    int nr = r + dr[t];
                    int nc = c + dc[t];
                    Push(nr, nc, t);
                }
                else {
                    Push(r, c - 1, 3);
                    Push(r, c + 1, 1);
                }
            }
            else if (ch == '/') {
                if (t == 0)      Push(r, c + 1, 1);   
                else if (t == 1) Push(r - 1, c, 0);
                else if (t == 2) Push(r, c - 1, 3);
                else if (t == 3) Push(r + 1, c, 2);
            }
            else if (ch == '\\') {
                if (t == 0)      Push(r, c - 1, 3);   
                else if (t == 1) Push(r + 1, c, 2);
                else if (t == 2) Push(r, c + 1, 1);
                else if (t == 3) Push(r - 1, c, 0);
            }
            else assert(false);
        }
        int energized = 0;
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                energized += vis[r][c][0] |
                             vis[r][c][1] | 
                             vis[r][c][2] |
                             vis[r][c][3];
            }
        }
        // reset for the next call
        que.clear();
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                for (int t = 0; t < 4; ++t) vis[r][c][t] = false;
            }
        }
        return energized;
    };
    int res = -1;
    for (int r = 0; r < n; ++r) {
        res = max(res, bfs(r, 0, 1));
        res = max(res, bfs(r, m - 1, 3));
    }

    for (int c = 0; c < m; ++c) {
        res = max(res, bfs(0, c, 2));
        res = max(res, bfs(n - 1, c, 0));
    }
    cout << res << '\n';
    return 0;
}
