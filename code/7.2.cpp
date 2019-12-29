#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
#define LL long long
#define ALL(x) x.begin(), x.end()
template<typename... Args>
void cline(Args... args){ ((cout << args << " "), ...);}
LL HALT = -1e9;

struct Program {
    vector<LL> instructions;
    list<LL> inputs;
    LL state = 0;
    LL lastOutput = 0;
    bool is_halt = false;
};

void intprogram(Program & p) {
    for (LL i = p.state; i < p.instructions.size();) {
        if (p.instructions[i] == 99) {
            p.is_halt = true;
            return;
        }
        string s = string(5, '0') + to_string(p.instructions[i]);
        s = s.substr(s.size()-5, 5);
        LL opcode = stoll(s.substr(3, 2));
        LL *par1 = (s[2] == '0') ? &p.instructions[p.instructions[i+1]] : &p.instructions[i+1];
        LL *par2 = (s[1] == '0') ? &p.instructions[p.instructions[i+2]] : &p.instructions[i+2];
        LL *par3 = (s[0] == '0') ? &p.instructions[p.instructions[i+3]] : &p.instructions[i+3];
        if (opcode == 3) {
            *par1 = p.inputs.front();
            p.inputs.pop_front();
            i += 2;
        } else if (opcode == 4) {
            i += 2;
            p.lastOutput = *par1;
            p.state = i;
            return;
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
    do {
        cin >> n;
        v.push_back(n);
    } while(cin >> c);
    vector<LL> combinations = {5, 6, 7, 8, 9};
    LL max_thruster = 0;
    do {
        vector<Program> programs (5);
        for (LL i = 0; i < 5; i++) {
            programs[i].instructions = v;
            programs[i].inputs = {combinations[i]};
        }
        programs[0].inputs.push_back(0);
        LL amplifier = 0;
        while(true) {
            intprogram(programs[amplifier]);
            if (programs[amplifier].is_halt) break;
            programs[(amplifier+1) % 5].inputs.push_back(programs[amplifier].lastOutput);
            amplifier++; amplifier %= 5;
        }
        max_thruster = max(max_thruster, programs[4].lastOutput);

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