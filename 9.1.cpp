#include <bits/stdc++.h>

using namespace std;

#define HAS(umap, key) (umap.find(key) != umap.end())
#define endl "\n"
#define LL long long
#define ALL(x) x.begin(), x.end()
template<typename... Args>
void cline(Args... args){ ((cout << args << " "), ...);}

struct VirtualMemory {
    vector<LL> memory;
    unordered_map<LL, LL> mapping;
    LL cnt = 0;

    auto getAddress(LL i) {
        if (!HAS(mapping, i)) {
            mapping[i] = cnt++;
            memory.push_back(0);
        }
        return mapping[i];
    }

    void setMemory(LL i, LL val) {
        LL internal_addr = getAddress(i);
        memory[internal_addr] = val;
    }

    auto getMemory(LL i) {
        LL internal_addr = getAddress(i);
        return &memory[internal_addr];
    }

    auto size() {
        return memory.size();
    }
};

struct Program {
    VirtualMemory instructions;
    list<LL> inputs;
    LL state = 0;
    LL lastOutput = 0;
    LL relative_base = 0;
    bool is_halt = false;
        

    Program(vector<LL> v, list<LL> in) {
        VirtualMemory vm;
        for (LL i = 0; i < v.size(); i++) {
            vm.setMemory(i, v[i]);
        }
        instructions = vm;
        inputs = in;
    }
};

auto param(Program &p, string s, LL i) {
    if(s[3-i] == '0') {
        return p.instructions.getMemory(*p.instructions.getMemory(p.state+i));
    } else if (s[3-i] == '2') {
        return p.instructions.getMemory(p.relative_base + *p.instructions.getMemory(p.state+i));
    } else {
        return p.instructions.getMemory(p.state+i);
    }
}

void intprogram(Program &p) {
    while (p.state < p.instructions.size()) {
        if (*p.instructions.getMemory(p.state) == 99) {
            p.is_halt = true;
            return;
        }
        string s = string(5, '0') + to_string(*p.instructions.getMemory(p.state));
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
void solve() {
    LL n;
    char c;
    vector<LL> v;
    do {
        cin >> n;
        v.push_back(n);
    } while(cin >> c);
    
    Program p (v, {1});
    intprogram(p);
    cout << p.lastOutput;
}


int main()
{  
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  solve();
  return 0;
}