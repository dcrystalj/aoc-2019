#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
#define LL long long
#define ALL(x) x.begin(), x.end()
template<typename... Args>
void cline(Args... args){ ((cout << args << " "), ...); cout << endl;}

struct Moon {
    tuple<LL, LL, LL> pos = {0, 0, 0};
    tuple<LL, LL, LL> speed = {0, 0, 0};
    Moon () {}
    Moon (LL x, LL y, LL z) {
        pos = {x, y, z};
    }
    void applyGravity(Moon m) {
        auto [x, y, z] = pos;
        auto [mx, my, mz] = m.pos;
        auto [sx, sy, sz] = speed;
        if (mx > x) sx++;
        if (mx < x) sx--;
        if (my > y) sy++;
        if (my < y) sy--;
        if (mz > z) sz++;
        if (mz < z) sz--;
        speed = {sx, sy, sz};
    }

    void applyVelocity() {
        auto [x, y, z] = pos;
        auto [sx, sy, sz] = speed;
        x += sx; y += sy; z += sz;
        pos = {x, y, z};
    }

    LL energy () {
        auto [x, y, z] = pos;
        auto [sx, sy, sz] = speed;
        return (abs(x) + abs(y) + abs(z)) * (abs(sx) + abs(sy) + abs(sz)); 
    }

    vector<LL> serialize() {
        auto [x, y, z] = pos;
        auto [sx, sy, sz] = speed;
        return {x, y, z, sx, sy, sz};
    }
};

void solve() {
    LL n = 4;
    LL a, b, c;
    vector<Moon> moons (n);
    for (LL i = 0; i < n; i++) {
        scanf("<x=%lld, y=%lld, z=%lld>\n", &a, &b, &c);
        moons[i] = Moon(a, b, c);
    }

    for (LL iter = 0; iter < 1000; iter++) {
        vector<Moon> newMoons = moons;    
        for (LL i = 0; i < n; i++) {
            for (LL j = i+1; j < n; j++) {
                newMoons[i].applyGravity(moons[j]);
                newMoons[j].applyGravity(moons[i]);
            }
        }
        for (LL i = 0; i < n; i++) {
            newMoons[i].applyVelocity();
        }
        moons = newMoons;
    }
    LL totalE = accumulate(ALL(moons), 0, [](LL sum, Moon b){ return sum + b.energy();});
    cout << totalE << endl;
}


int main()
{  
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  solve();
  return 0;
}