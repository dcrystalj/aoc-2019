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

    vector<LL> serialize(LL i) {
        if (i==0) return {get<0>(pos), get<0>(speed)};
        else if (i == 1) return {get<1>(pos), get<1>(speed)};
        else return {get<2>(pos), get<2>(speed)};
    }
};

auto pointInTime (vector<Moon> &v, LL k) {
    vector<LL> pit;
    LL c = 0;
    for (LL i = 0; i < v.size(); i++) {
        for(auto j : v[i].serialize(k)) {
            pit.push_back(j);
        }
    }
    return pit;
}

LL lcm (LL a, LL b) {
    return ((a * b) / __gcd(a, b));
}

#define ddv(vec) for(auto &i: vec) { cout << i << " "; } cout << endl

void solve() {
    LL n = 4;
    LL a, b, c;
    vector<Moon> moons (n);
    for (LL i = 0; i < n; i++) {
        scanf("<x=%lld, y=%lld, z=%lld>\n", &a, &b, &c);
        moons[i] = Moon(a, b, c);
    }

    vector<vector<LL>> pits = {pointInTime(moons, 0), pointInTime(moons, 1), pointInTime(moons, 2)};
    vector<LL> iterations = {0, 0, 0};
    for (LL iter = 0; iter < 1e6; iter++) {
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
        for (LL i = 0; i < 3; i++) {
            if (iterations[i] == 0) {
                auto res = pointInTime(moons, i);
                if (res == pits[i]) {
                    iterations[i] = iter+1;
                }
            }
        }
    }
    LL res = 1;
    for(auto it : iterations) {
        res = lcm(res, it);
        cout << it << endl;
    }
    cout << res << endl;
}


int main()
{  
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  solve();
  return 0;
}