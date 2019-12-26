#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
#define LL long long
#define ALL(x) x.begin(), x.end()
template<typename... Args>
void cline(Args... args){ ((cout << args << " "), ...); cout << endl;}

vector<LL> basePattern = {0, 1, 0, -1};

auto genPattern(LL step, LL n) {
    vector<LL> v;
    for (LL k = 0; k < ceil(n*1.0/(4*step)) + 1; k++) {
        for (LL i = 0; i < 4; i++) {
            for (LL j = 0; j < step; j++) {
                v.push_back(basePattern[i]);
            }
        }
    }
    return v;
}
void solve() {
    string s; 
    cin >> s;
    LL n = s.size();
    vector<LL> nums (n);
    vector<LL> res (n);
    for (LL i = 0; i < n; i++) {
        nums[i] = s[i] - '0';
    }
    vector<vector<LL>> pattern;
    for (LL i = 0; i < n; i++) {
        pattern.push_back(genPattern(i+1, n));
    }

    for (LL phase = 0; phase < 100; phase++) {    
        for (LL i = 0; i < n; i++) {
            for (LL j = 0; j < n; j++) {
                res[i] += pattern[i][j+1] * nums[j];
            }
            res[i] = abs(res[i]) % 10;
        }
        nums = res;
        for(auto & i : res) i = 0;
    }
    for(auto & i : nums) cout << i;
}


int main()
{  
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  solve();
  return 0;
}