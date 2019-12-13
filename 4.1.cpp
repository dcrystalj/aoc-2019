#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
#define LL long long
#define ALL(x) x.begin(), x.end()
template<typename... Args>
void cline(Args... args){ ((cout << args << " "), ...);}

bool meetCriteria(LL a) {
    string s = to_string(a);
    bool two_same = false;
    for (LL i = 1; i < 6; i++) {
        if (s[i] < s[i-1]) return false;
        if (s[i] == s[i-1]) two_same = true;
    }
    return two_same;
}

void solve() {
    LL a = 156218;
    LL b = 652527;
    LL cnt = 0;
    while(a < b) {
        cnt += meetCriteria(a++);
    }
    cout << cnt << endl;
}


int main()
{  
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  solve();
  return 0;
}