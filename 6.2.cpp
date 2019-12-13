#include <bits/stdc++.h>

using namespace std;

#define HAS(umap, key) (umap.find(key) != umap.end())
#define COUNTER(m, j) if (HAS(m, j)) { m[j]++; } else { m[j] = 1; }
#define endl "\n"
#define LL long long
#define ALL(x) x.begin(), x.end()
template<typename... Args>
void cline(Args... args){ ((cout << args << " "), ...);}

vector<vector<LL>> tree (2000, vector<LL>());
vector<bool> visited (2000);
unordered_map<string, LL> m;
LL santa, you, res;
void dfs(LL val, LL p, LL depth) {
    for (auto i : tree[val]) {
        if (i != p && !visited[i]) {
            dfs(i, val, depth+1);
        }
    }
    if (val == santa) {
        cout << "found santa " << depth - 2 << endl;;
    }
    visited[val] = true;
}

void solve() {
    string s, s1, s2;
    LL v1, v2;
    LL cnt = 0;
    
    while(cin >> s) {
        s1 = s.substr(0, 3);
        s2 = s.substr(4, 3);
        
        if (!HAS(m, s1)) {
            m[s1] = cnt++;
        }
        if (!HAS(m, s2)) {
            m[s2] = cnt++;
        }
        v1 = m[s1];
        v2 = m[s2];
        if (s1 == "YOU") you = v1;
        if (s2 == "YOU") you = v2;
        if (s1 == "SAN") santa = v1;
        if (s2 == "SAN") santa = v2;
        tree[v1].push_back(v2);
        tree[v2].push_back(v1);
    }
    dfs(you, -1, 0);
}


int main()
{  
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  solve();
  return 0;
}