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
LL dfs(LL val, LL p, LL depth) {
    LL sum = depth;
    for (auto i : tree[val]) {
        if (i != p) {
            sum += dfs(i, val, depth + 1);
        }
    }
    return sum;
}

void solve() {
    string s, s1, s2;
    LL v1, v2;
    LL cnt = 0;
    unordered_map<string, LL> m;
    unordered_map<LL, LL> indegree;
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
        tree[v1].push_back(v2);
        COUNTER(indegree, v2);
    }
    for (LL i = 0; i < cnt; i++) {
        if (!HAS(indegree, i)) {
            cout << dfs(i, -1, 0) << endl;
            break;
        }
    }
}


int main()
{  
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  solve();
  return 0;
}