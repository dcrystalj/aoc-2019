#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
#define LL long long
#define ALL(x) x.begin(), x.end()
template<typename... Args>
void cline(Args... args){ ((cout << args << " "), ...); cout << endl;}

vector<LL> basePattern = {0, 1, 0, -1};

void solve() {
    string is, s; 
    cin >> is;
    for (LL i = 0; i < 10000; i++) {
        s += is;
    }
    LL n = s.size();
    vector<LL> nums (n);
    vector<LL> res (n);
    for (LL i = 0; i < n; i++) {
        nums[i] = s[i] - '0';
    }

    LL offset = 0, p = 1;
    for (LL i = 6; i >= 0; i--) {
        offset += p*nums[i];
        p *= 10;
    }
    
    for (LL phase = 0; phase < 100; phase++) {    
        for (LL j = n-2; j >= 0; j--) {
            nums[j] = (nums[j] + nums[j+1]) % 10;
        }
    }

    for (LL i = 0; i < 8; i++) {
        cout << nums[offset + i];
    }
    cout << endl;
}


int main()
{  
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  solve();
  return 0;
}