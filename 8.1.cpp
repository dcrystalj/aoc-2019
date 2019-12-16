#include <bits/stdc++.h>
    
using namespace std;
    
#define endl "\n"
#define LL long long
#define ULL unsigned long long
#define ALL(x) x.begin(), x.end() //handy for function like "sort()"
#define HAS(umap, key) (umap.find(key) != umap.end())
#define COUNTER(m, j) if (HAS(m, j)) { m[j]++; } else { m[j] = 1; }
template<typename... Args>
void cline(Args... args){ ((cout << args << " "), ...);}

 
void solve() {
    // vector<vector<LL>> v (25, vector<LL>(6));
    LL mod = 25 * 6;
    char c;
    LL cnt = 0;
    pair<LL, LL> multipliers = {0, 0};
    pair<LL,LL> res = {0, 0};
    LL mincnt = 2e9;
    for(LL i=0; i < 15000; i++) {
        cin >> c;
        if (c == '0') cnt++;
        if (c == '1') multipliers.first++;
        if (c == '2') multipliers.second++;
        if (i % mod == 0 && i > 0) {
            if (cnt < mincnt) {
                mincnt = min(mincnt, cnt);
                res = multipliers;
            }
            cnt = 0;
            multipliers = {0, 0};
        }
    }

    cout << res.first * res.second << endl;
}

int main()
{  
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}