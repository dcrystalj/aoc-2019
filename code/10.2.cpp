#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
#define LL long long
#define ALL(x) x.begin(), x.end()
template<typename... Args>
void cline(Args... args){ ((cout << args << " "), ...);}
#define HAS(umap, key) (umap.find(key) != umap.end())
#define PI 3.14159265358979323846

pair<LL, LL> tower = {26, 36};
map<pair<LL, LL>, pair<LL, LL>> map_polar;
pair<LL, LL> toPolar(double x, double y) {
    LL r = (pow(x, 2) + pow(y, 2)) * 1e6;
    LL phi = (atan2(y, x) + PI/2) * 1e6;
    return {r, phi};
}

void solve() {
    LL w = 42, h = 42;
    char c;
    vector<pair<LL, LL>> polars;
    for (LL i = 0; i < h; i++) {
        for (LL j = 0; j < w; j++) {
            cin >> c;
            if (c == '#' && (j != tower.first || i != tower.second)) {
                auto polar = toPolar(j - tower.first, i - tower.second);
                map_polar[polar] = {j, i};
                polars.push_back(polar);
            }
        }
    }

    sort(ALL(polars), [](auto &a, auto &b) {
        auto [ax, ay] = a;
        auto [bx, by] = b;
        if (ay >= 0 && by >= 0 && ay < by) return true;
        else if (ay >= 0 && by < 0) return true;
        else if (ay < 0 && by < 0 && ay < by) return true;
        else if (ay == by) {
            return a.first < b.first;
        }
        return false;
    });
    vector<LL> used_polars;
    unordered_set<LL> used_polars_set;
    while(used_polars_set.size() != polars.size()) {
        unordered_set<LL> s;
        for (LL i = 0; i < polars.size(); i++) {
            if (HAS(used_polars_set, i) || HAS(s, polars[i].second)) continue;
            s.insert(polars[i].second);
            used_polars.push_back(i);
            used_polars_set.insert(i);
        }
    }
    auto res = map_polar[polars[used_polars[199]]];
    cline(res.first*100 + res.second);
}


int main()
{  
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  solve();
  return 0;
}