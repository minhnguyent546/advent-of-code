/**            
 * author      minhnguyent546
 * created_at  Mon, 2024-01-08 12:48:35
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

inline vector<vector<char>> rotate(const vector<vector<char>> &grid) {
    int n = (int) grid.size(), m = (int) grid.back().size();
    vector<vector<char>> rotated(m, vector<char>(n));
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            rotated[c][n - r - 1] = grid[r][c];
        }
    }
    return rotated;
}

/**
 * @brief tilt the matrix in north direction
 * @return the number of rounded rocks that have position changed
 */
int tilt(vector<vector<char>> &grid) {
    int n = (int) grid.size(), m = (int) grid.back().size();
    int changed = 0;
    for (int c = 0; c < m; ++c) {
        for (int i = 0, k = 0; i < n; ++i) {
            if (grid[i][c] != 'O') {
                if (grid[i][c] == '#') {
                    k = i + 1;
                }
                continue;
            }
            if (i != k) {
                swap(grid[i][c], grid[k][c]);
                ++changed;
            }
            ++k;
        }
    }
    return changed;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    const int times = 1'000'000'000;

    string bar;
    vector<vector<char>> grid;
    while (cin >> bar) {
        grid.emplace_back(bar.size());
        for (int i = 0; i < (int) bar.size(); ++i) {
            grid.back()[i] = bar[i];
        }
    }
    int n = (int) grid.size(), m = (int) grid.back().size();
    int dir = 4;
    map<vector<vector<char>>, int> seen;
    int counter = 0;
    while (seen.find(grid) == seen.end()) {
        seen[grid] = counter++;
        for (int t = 0; t < dir; ++t) {
            tilt(grid);
            grid = rotate(grid);
        }
    }
    int start_loop = seen[grid];
    int x = start_loop;
    int y = (int) seen.size() - x;
    int z = (times - x) % y;
    vector<vector<char>> final_grid;
    for (auto &[g, idx] : seen) {
        if (idx == z + start_loop) {
            final_grid = g;
        }
    }
    n = (int) final_grid.size(), m = (int) final_grid.back().size();
    long long res = 0;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (final_grid[r][c] == 'O') res += n - r;
        }
    }
    cout << res << '\n';
    debug(elapsed_time());
    return 0;
}
