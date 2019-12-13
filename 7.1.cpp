#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
#define LL long long
#define ALL(x) x.begin(), x.end()
template<typename... Args>
void cline(Args... args){ ((cout << args << " "), ...);}

LL intprogram(vector<LL> v, list<LL> &inputs) {
    for (LL i = 0; i < v.size();) {
        if (v[i] == 99) break;
        string s = string(5, '0') + to_string(v[i]);
        s = s.substr(s.size()-5, 5);
        LL opcode = stoll(s.substr(3, 2));
        LL *par1 = (s[2] == '0') ? &v[v[i+1]] : &v[i+1];
        LL *par2 = (s[1] == '0') ? &v[v[i+2]] : &v[i+2];
        LL *par3 = (s[0] == '0') ? &v[v[i+3]] : &v[i+3];
        if (opcode == 3) {
            *par1 = inputs.front();
            inputs.pop_front();
            i += 2;
        } else if (opcode == 4) {
            return *par1;
            i += 2;
        } else if(opcode == 1) {
            *par3 = *par1 + *par2;
            i += 4;
        } else if (opcode == 2) {
            *par3 = *par1 * *par2;
            i += 4;
        } else if (opcode == 5) {
            if (*par1 != 0) i = *par2;
            else i += 3;
        } else if (opcode == 6) {
            if (*par1 == 0) i = *par2;
            else i += 3;
        } else if (opcode == 7) {
            *par3 = *par1 < *par2;
            i += 4;
        } else if (opcode == 8) {
            *par3 = *par1 == *par2;
            i += 4;
        }
    }
}

void solve() {
    LL n;
    char c;
    vector<LL> v;
    cin >> n;
    v.push_back(n);
    while(cin >> c) {
        cin >> n;
        v.push_back(n);
    }
    vector<LL> combinations = {0, 1, 2, 3, 4};    
    LL max_thruster = 0;
    do {
        LL res = 0;
        list<LL> inputs = {};
        for (LL i = 0; i < 5; i++) {
            inputs = {combinations[i], res};
            res = intprogram(v, inputs);
        }
        max_thruster = max(max_thruster, res);

    } while (next_permutation(combinations.begin(), combinations.end()));

    cout << max_thruster << endl;
}


int main()
{  
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  solve();
  return 0;
}