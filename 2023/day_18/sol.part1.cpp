/**            
 * author      minhnguyent546
 * created_at  Fri, 2024-01-12 21:21:34
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

struct Plan {
    char dir;
    int level;
    string hex_color;
};

const int DIRS = 4;
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};
string DIRS_STR = "URDL";

int idx(char ch) {
    return (int) DIRS_STR.find(ch);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    vector<Plan> plans; 
    string bar;
    while (getline(cin, bar)) {
        vector<string> z = str_split(bar, " ");
        plans.emplace_back(z[0][0], stoi(z[1]), z[2].substr(1, z[2].find(')')));
    }
    int cnt_l = 0, cnt_r = 0, cnt_u = 0, cnt_d = 0;
    for (const auto &plan : plans) {
        if (plan.dir == 'U') {
            cnt_u += plan.level;
        }
        else if (plan.dir == 'R') {
            cnt_r += plan.level;
        }
        else if (plan.dir == 'D') {
            cnt_d += plan.level;
        }
        else if (plan.dir == 'L') {
            cnt_l += plan.level;
        }
    }
    int max_x = max(cnt_l, cnt_r);
    int max_y = max(cnt_u, cnt_d);
    int n = max_x * 2, m = 2 * max_y;
    int offset_x = max_x, offset_y = max_y;
    vector<vector<bool>> visited(n, vector<bool>(m));
    int cur_r = 0, cur_c = 0;
    for (const Plan &plan : plans) {
        int t = idx(plan.dir);
        for (int k = 0; k < plan.level; ++k) {
            cur_r += dr[t];
            cur_c += dc[t];
            assert(0 <= cur_r + offset_x && cur_r + offset_x < n);
            assert(0 <= cur_c + offset_y && cur_c + offset_y < m);
            visited[cur_r + offset_x][cur_c + offset_y] = true;
        }
    }

    vector<pair<int, int>> que;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (r == 0 || r == n - 1 || c == 0 || c == m - 1) {
                if (!visited[r][c]) {
                    visited[r][c] = true;
                    que.emplace_back(r, c);
                }
            }
        }
    }

    for (int k = 0; k < (int) que.size(); ++k) {
        auto [r, c] = que[k];
        for (int t = 0; t < DIRS; ++t) {
            int nr = r + dr[t];
            int nc = c + dc[t];
            if (0 <= nr && nr < n && 0 <= nc && nc < m && !visited[nr][nc]) {
                visited[nr][nc] = true;
                que.emplace_back(nr, nc);
            }
        }
    }
    cout << n * m - (int) que.size() << '\n';
    debug(elapsed_time());
    return 0;
}
