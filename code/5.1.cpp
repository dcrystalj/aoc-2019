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
    for (LL i = 0; i < v.size();) {
        if (v[i] == 99) break;
        string s = string(5, '0') + to_string(v[i]);
        s = s.substr(s.size()-5, 5);
        LL opcode = stoll(s.substr(3, 2));
        LL *par1 = (s[2] == '0') ? &v[v[i+1]] : &v[i+1];
        LL *par2 = (s[1] == '0') ? &v[v[i+2]] : &v[i+2];
        LL *par3 = (s[0] == '0') ? &v[v[i+3]] : &v[i+3];
        if (opcode == 3) {
            *par1 = 1;
            cout << "opcode3" << endl;
            i += 2;
        } else if (opcode == 4) {
            cout << "opcode " << *par1 << endl;
            i += 2;
        } else if(opcode == 1) {
            *par3 = *par1 + *par2;
            i += 4;
        } else if (opcode == 2) {
            *par3 = *par1 * *par2;
            i += 4;
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