#include <bits/stdc++.h>

using namespace std;

#define HAS(umap, key) (umap.find(key) != umap.end())
#define endl "\n"
#define LL long long
#define ALL(x) x.begin(), x.end()
template<typename... Args>
void cline(Args... args){ ((cout << args << " "), ...);}

struct DD {
    unordered_map<LL, LL> m;
    void set(LL i, LL val) { m[i] = val; }
    auto get(LL i, LL _default) {
        if (!HAS(m, i)) m[i] = _default;
        return &m[i];
    }
    auto get(LL i) { return get(i, 0); }
    auto size() { return m.size(); }
};


struct Program {
    DD instructions;
    list<LL> inputs;
    LL state = 0;
    LL lastOutput = 0;
    LL relative_base = 0;
    bool is_halt = false;
        

    Program(vector<LL> v, list<LL> in) {
        DD vm;
        for (LL i = 0; i < v.size(); i++) {
            vm.set(i, v[i]);
        }
        instructions = vm;
        inputs = in;
    }
};

auto param(Program &p, string s, LL i) {
    if(s[3-i] == '0') {
        return p.instructions.get(*p.instructions.get(p.state+i));
    } else if (s[3-i] == '2') {
        return p.instructions.get(p.relative_base + *p.instructions.get(p.state+i));
    } else {
        return p.instructions.get(p.state+i);
    }
}

void intprogram(Program &p) {
    while (p.state < p.instructions.size()) {
        if (*p.instructions.get(p.state) == 99) {
            p.is_halt = true;
            return;
        }
        string s = string(5, '0') + to_string(*p.instructions.get(p.state));
        s = s.substr(s.size()-5, 5);
        LL opcode = stoll(s.substr(3, 2));
        LL *par1 = param(p, s, 1);
        LL *par2 = param(p, s, 2);
        LL *par3 = param(p, s, 3);
        if (opcode == 3) {
            *par1 = p.inputs.front();
            p.inputs.pop_front();
            p.state += 2;
        } else if (opcode == 4) {
            p.state += 2;
            p.lastOutput = *par1;
            return;
        } else if(opcode == 1) {
            *par3 = *par1 + *par2;
            p.state += 4;
        } else if (opcode == 2) {
            *par3 = *par1 * *par2;
            p.state += 4;
        } else if (opcode == 5) {
            if (*par1 != 0) p.state = *par2;
            else p.state += 3;
        } else if (opcode == 6) {
            if (*par1 == 0) p.state = *par2;
            else p.state += 3;
        } else if (opcode == 7) {
            *par3 = *par1 < *par2;
            p.state += 4;
        } else if (opcode == 8) {
            *par3 = *par1 == *par2;
            p.state += 4;
        } else if (opcode == 9) {
            p.relative_base += *par1;
            p.state += 2;
        }
    }   
}

LL N = 50;

struct Screen {
    vector<vector<LL>> color {vector<vector<LL>>(N, vector<LL>(N))};
    LL blockCnt = 0;
    void paint(LL x, LL y, LL z) {
        color[x][y] = z;
        if (z == 2) blockCnt++;
    }
    void print() {
        vector<char> v = {'.', '|', '#', '-', '0'};
        for (LL i = 0; i < N/2; i++) {
            for (LL j = 0; j < N; j++) {
                cout << v[color[j][i]];
            }
            cout << endl;
        }
    }
};



void solve() {
    LL n;
    char c;
    vector<LL> v;
    do {
        cin >> n;
        v.push_back(n);
    } while(cin >> c);
    
    Program p (v, {});
    Screen s;
    LL x, y, z;
    do {
        intprogram(p); x = p.lastOutput;
        intprogram(p); y = p.lastOutput;
        intprogram(p); z = p.lastOutput;
        s.paint(x, y, z);
    } while(!p.is_halt);
    s.print();
    cline(s.blockCnt);
}


int main()
{  
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  solve();
  return 0;
}