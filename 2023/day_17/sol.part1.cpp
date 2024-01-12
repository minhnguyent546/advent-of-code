/**            
 * author      minhnguyent546
 * created_at  Fri, 2024-01-12 14:11:20
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

const int MAX_CONSECUTIVE = 3;
const int DIRS = 4;
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};
vector<vector<int>> dist[DIRS][MAX_CONSECUTIVE + 1];

struct Vertex {
    int dist;
    int direction;
    int consecutive_count;
    int r;
    int c;
    bool operator>(const Vertex &other) const {
        return dist > other.dist;
    }
};

// directions
/*
        UP
        0
LEFT 3     1 RIGHT
        2
       DOWN
*/

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    vector<vector<int>> grid;
    string bar;
    while (cin >> bar) {
        grid.emplace_back(bar.size());
        for (int i = 0; i < (int) bar.size(); ++i) {
            grid.back()[i] = bar[i] - '0';
        }
    }
    int n = (int) grid.size(), m = (int) grid.back().size();

    auto valid = [&](int r, int c) -> bool {
        return (0 <= r && r < n && 0 <= c && c < m);
    };

    priority_queue<Vertex, vector<Vertex>, greater<>> pq;
    pq.emplace(0, 1, 0, 0, 0); // left dir
    pq.emplace(0, 0, 2, 0, 0); // downward

    for (int dir = 0; dir < DIRS; ++dir) {
        for (int cnt = 0; cnt <= MAX_CONSECUTIVE; ++cnt) {
            dist[dir][cnt].assign(n, vector<int>(m, INF));
        }
    }
    dist[1][0][0][0] = 0;
    dist[2][0][0][0] = 0;

    while (!pq.empty()) {
        auto [d, t, cnt, r, c] = pq.top(); pq.pop();
        if (d > dist[t][cnt][r][c]) continue;
        for (int dir = 0; dir < DIRS; ++dir) {
            if ((dir ^ t) == 2) {
                // can't go to the opposite direction
                continue;
            }
            if (cnt == MAX_CONSECUTIVE && dir == t) {
                continue;
            }
            int nr = r + dr[dir];
            int nc = c + dc[dir];
            if (!valid(nr, nc)) continue;
            int new_cnt = (dir == t ? cnt + 1 : 1);

            if (dist[dir][new_cnt][nr][nc] > dist[t][cnt][r][c] + grid[nr][nc]) {
                dist[dir][new_cnt][nr][nc] = dist[t][cnt][r][c] + grid[nr][nc];
                pq.emplace(dist[dir][new_cnt][nr][nc], dir, new_cnt, nr, nc);
            }
        }
    }
    int res = INF;
    for (int dir = 0; dir < DIRS; ++dir) {
        for (int cnt = 0; cnt <= MAX_CONSECUTIVE; ++cnt) {
            res = min(res, dist[dir][cnt][n - 1][m - 1]);
        }
    }
    cout << res << '\n';
    debug(elapsed_time());
    return 0;
}
