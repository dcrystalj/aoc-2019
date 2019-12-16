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
    vector<LL> v (25 * 6, 2);
    char c;
    LL a = 0;
    LL mod = 25 * 6;
    LL cnt = 15000/mod + 1;
    while(cnt--> 0) {
        for (LL i=0; i < mod; i++) {
            if (!(cin >> c)) break;
            a = c - '0';
            if (v[i] == 2 && a < 2) { v[i] = a;}
        }
    }
    for (LL i = 0; i < 6; i++) {
        for (LL j = 0; j < 25; j++) {
            cout << ((v[i*25+j] == 1) ? 'X' : ' ');
        } cout << endl;
    }
}

int main()
{  
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}