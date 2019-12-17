#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
#define LL long long
#define ALL(x) x.begin(), x.end()
template<typename... Args>
void cline(Args... args){ ((cout << args << " "), ...);}
#define HAS(umap, key) (umap.find(key) != umap.end())


struct Point {
    LL x, y;
    Point(LL x, LL y) {
        this->x = x;
        this->y = y;
    }
};

// struct Line {
//     LL k, n;
//     Line(LL k, LL n) {
//         this->k = k;
//         this->n = n; 
//     }
// };

vector<vector<bool>> grid (1e2, vector<bool>(1e2, false));
double inf = 1e9;

double pround(double r) {
    return round(r * 1e3) / 1e3;
}
pair<double, double> getLine(Point p1, Point p2) {
    LL ydiff = p1.y - p2.y;
    LL kdiff = -p2.x + p1.x;
    if (kdiff == 0) return {inf, inf};
    double k = ydiff * 1.0 / kdiff;
    k = pround(k);
    double n = 1.0*p1.y - k * p1.x;
    n = pround(n);
    return {k, n};
}

LL countSteroids(LL x, LL y) {
    set<tuple<pair<double, double>, bool, bool>> s;
    LL cnt = 0;
    for (LL i = 0; i < grid.size(); i++) {
        for (LL j = 0; j < grid.size(); j++) {
            if (!grid[i][j] || (i == y && j == x)) continue; // empty or itself
            auto l = getLine(Point(x, y), Point(j, i));
            tuple<pair<double, double>, bool, bool> p = {l, i <= y, j <= x};
            if (!HAS(s, p)) {
                s.insert(p); cnt++;
            }
        }
    }
    return cnt;
}


void solve() {
    LL w = 42, h = 42;
    char c;
    for (LL i = 0; i < h; i++) {
        for (LL j = 0; j < w; j++) {
            cin >> c;
            if (c == '#') {
                grid[i][j] = true;    
            }
        }
    }
    LL res = 0;
    for (LL i = 0; i < h; i++) {
        for (LL j = 0; j < w; j++) {
            if (grid[i][j]) {
                res = max(res, countSteroids(j, i));
                // need for part 2
                if (countSteroids(j, i) == 347) {  
                    cline(i, j, endl);
                }
            }
        }
    }
    cout << res;

}


int main()
{  
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  solve();
  return 0;
}