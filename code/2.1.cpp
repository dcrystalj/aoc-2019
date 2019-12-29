#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
#define LL long long
#define ALL(x) x.begin(), x.end()
template<typename... Args>
void cline(Args... args){ ((cout << args << " "), ...);}

void solve() {
    LL n;
    char c;
    vector<LL> v;
    do {
        cin >> n;
        v.push_back(n);
    } while(cin >> c);
    for (LL i = 0; i < v.size(); i += 4) {
        if (v[i] == 99) break;
        if (v[i] == 1) v[v[i+3]] = v[v[i+1]] + v[v[i+2]];
        else if (v[i] == 2) v[v[i+3]] = v[v[i+1]] * v[v[i+2]];
    }
    for(auto i: v) cout << i <<",";
    cout << endl;
}


int main()
{  
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  solve();
  return 0;
}