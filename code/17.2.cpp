#include <bits/stdc++.h>

using namespace std;

#define HAS(umap, key) (umap.find(key) != umap.end())
#define endl "\n"
#define LL long long
#define ALL(x) x.begin(), x.end()
template<typename... Args>
void cline(Args... args){ ((cout << args << " "), ...);}

struct DD {
    map<LL, LL> m;
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

    Program() {}
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

struct Surface {
    vector<vector<LL>> s;
    vector<LL> tmp;
    vector<LL> commands;
    LL W;
    LL H;
    LL posx = 36;
    LL posy = 16;
    LL direction = 0; // 0-up, 1-right, 2-down, 3 left
    LL moved = 0;

    void addNew(LL o) {
        if (o == 10) {
            s.push_back(tmp);
            tmp.clear();
        } else {
            tmp.push_back(o);
        }
    }

    void print() {
        for (LL i = 0; i < s.size(); i++) {
            for (LL j = 0; j < s[i].size(); j++) {
                cout << char(s[i][j]);
            }
            cout << endl;
        }
    }

    bool hasNextMove() {
        if (direction == 0 && posy - 1 >= 0 && s[posy-1][posx] == 35) return true;
        if (direction == 1 && posx + 1 < W && s[posy][posx+1] == 35) return true;
        if (direction == 2 && posy + 1 < H && s[posy+1][posx] == 35) return true;
        if (direction == 3 && posx - 1 >= 0 && s[posy][posx-1] == 35) return true;
        return false;
    }

    void move() {
        if (direction == 0) posy -= 1;
        if (direction == 1) posx += 1;
        if (direction == 2) posy += 1;
        if (direction == 3) posx -= 1;
        moved++;
    }

    void newDirection() {
        if (moved > 0) {
            if (moved > 9) {
                moved -= 10;
                commands.push_back('1');
            }
            commands.push_back(moved+'0');
            commands.push_back(',');
            moved = 0;
        }
        if (direction == 0) {
            if (posx + 1 < W && s[posy][posx+1] == 35) {
                direction = 1;
                commands.push_back('R');
                commands.push_back(',');
                return;
            } else if (posx - 1 >= 0 && s[posy][posx-1] == 35) {
                direction = 3;
                commands.push_back('L');
                commands.push_back(',');
                return;
            }
        } else if (direction == 1) {
            if (posy + 1 < H && s[posy+1][posx] == 35) {
                direction = 2;
                commands.push_back('R');
                commands.push_back(',');
                return;
            } else if (posy - 1 >= 0 && s[posy-1][posx] == 35) {
                direction = 0;
                commands.push_back('L');
                commands.push_back(',');
                return;
            }
        } else if (direction == 2) {
            if (posx + 1 < W && s[posy][posx+1] == 35) {
                direction = 1;
                commands.push_back('L');
                commands.push_back(',');
                return;
            } else if (posx - 1 >= 0 && s[posy][posx-1] == 35) {
                direction = 3;
                commands.push_back('R');
                commands.push_back(',');
                return;
            }
        } else if (direction == 3) {
            if (posy + 1 < H && s[posy+1][posx] == 35) {
                direction = 2;
                commands.push_back('L');
                commands.push_back(',');                
                return;
            } else if (posy - 1 >= 0 && s[posy-1][posx] == 35) {
                direction = 0;
                commands.push_back('R');
                commands.push_back(',');                
                return;
            }
        } 
        direction = -1;
    }


    void findPathHome() {
        while (direction != -1) {
            while(hasNextMove()) {
                move();
            }
            newDirection();
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
    Surface s;
    do {
        intprogram(p);
        s.addNew(p.lastOutput);
    } while (!p.is_halt);
    s.s.pop_back(); s.s.pop_back();
    s.H = s.s.size();
    s.W = s.s[0].size();
    s.print();
    s.findPathHome();
    for(auto &i: s.commands) cout << i << ", ";
    cout << endl;
    vector<LL> mainRoutine = {'A', ',', 'B', ',', 'A', ',', 'B', ',', 'C', ',', 'C', ',', 'B', ',', 'A', ',', 'B', ',', 'C', '\n'};
    vector<LL> funa = {76, 44, 52, 44, 82, 44, 56, 44, 76, 44, 54, 44, 76, 44, 49, 48,'\n'};
    vector<LL> funb = {76, 44, 54, 44, 82, 44, 56, 44, 82, 44, 49, 48, 44, 76, 44, 54, 44, 76, 44, 54, '\n'};
    vector<LL> func = {76, 44, 52, 44, 76, 44, 52, 44, 76, 44, 49, 48,'\n'};
    v[0] = 2;
    p = Program(v, {});
    for(auto &i: mainRoutine) p.inputs.push_back(i);
    for(auto &i: funa) p.inputs.push_back(i);
    for(auto &i: funb) p.inputs.push_back(i);
    for(auto &i: func) p.inputs.push_back(i);
    p.inputs.push_back('n');
    p.inputs.push_back('\n');
    do {
        intprogram(p);
        cout << char(p.lastOutput);   
    } while (!p.is_halt);

    cout << endl << p.lastOutput << endl;
}


int main()
{  
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  solve();
  return 0;
}