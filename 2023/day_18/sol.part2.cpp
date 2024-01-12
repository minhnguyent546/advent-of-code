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
};

struct Point {
    long long x;
    long long y;
};

const int DIRS = 4;
int dr[] = {0, 1, 0, -1};
int dc[] = {1, 0, -1, 0};
string DIRS_STR = "RDLU";

int idx(char ch) {
    return (int) DIRS_STR.find(ch);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    vector<Plan> plans; 
    string bar;
    while (getline(cin, bar)) {
        bar = bar.substr(bar.find('#') + 1);
        bar.pop_back();
        char dir = DIRS_STR[bar.back() - '0'];
        bar.pop_back();
        int level = stoi(bar, 0, 16);
        plans.emplace_back(dir, level);
    }
    long long cur_r = 0, cur_c = 0, boundary = 0;
    vector<Point> points;
    for (const Plan &plan : plans) {
        int t = idx(plan.dir);
        cur_r += plan.level * dr[t];
        cur_c += plan.level * dc[t];
        points.emplace_back(cur_r, cur_c);
        boundary += plan.level;
    }
    long long area = 0;
    int sz = (int) points.size();
    for (int i = 0; i < sz; ++i) {
       int ni = i + 1;
       if (ni >= sz) ni -= sz;
       area += points[i].x * points[ni].y - points[i].y * points[ni].x;
    }
    if (area < 0) area = -area;
    area /= 2;
    cout << area + boundary / 2 + 1 << '\n';

    /**
     * by Pick's theorem, we have:
     * area         = interior + boundary/2 - 1
     * interior     = area - boundary/2 + 1
     * total_point  = interior + boundary
     *              = area + boundary/2 + 1
     */
    return 0;
}
