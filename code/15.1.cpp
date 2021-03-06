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

LL N = 100;

struct Surface {
    vector<vector<LL>> color {vector<vector<LL>>(N, vector<LL>(N))};
    pair<LL, LL> start = {N/2, N/2};
    pair<LL, LL> pos = {N/2, N/2};
    LL orientation = 1;
    Program p;
    unordered_map<char, LL> colors = {{'I', 0}, {'W', 1}, {'E', 2}, {'X', 3}, {'O', 4}};
    vector<LL> directions = {1, 2, 3, 4};
    vector<pair<LL, LL>> moves = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
    vector<LL> reverseDirection = {2, 1, 4, 3};

    LL bfs () {
        vector<vector<bool>> visited {vector<vector<bool>>(N, vector<bool>(N))};
        list<tuple<LL, LL, LL>> l = {{start.first, start.second, 1}};
        while(!l.empty()) {
            auto [y, x, len] = l.front(); l.pop_front();
            if (color[y][x] == colors['O']) return len;
            if (color[y][x] != colors['E'] || visited[y][x]) continue;
            visited[y][x] = true;
            for(auto &m: moves) {
                l.push_back({y + m.first, x + m.second, len + 1});
            }
        }
        return -1;
    }
    
    void scan() {
        auto [cury, curx] = pos;
        if (cury <= 0 || cury >= N -1 || curx <= 0 || curx >= N -1) return;
        for (LL i = 0; i < moves.size(); i++) {
            LL newY = cury + moves[i].first;  
            LL newX = curx + moves[i].second;
            if (color[newY][newX] == colors['I']) {
                pos = {newY, newX};
                p.inputs.push_front(directions[i]);
                intprogram(p);
                LL out = p.lastOutput;
                if (out == 0) {
                    color[newY][newX] = colors['W'];
                    if (color[cury][curx] != colors['O'])
                        color[cury][curx] = colors['E'];
                    pos = {cury, curx};
                    continue;
                } else if (out == 1) {
                    color[cury][curx] = colors['E'];
                } else if (out == 2) {
                    color[cury][curx] = colors['O'];
                }
                scan();
                p.inputs.push_front(reverseDirection[i]);
                intprogram(p);
                pos = {cury, curx};
            }
        }
    }

    Surface(Program &x) {
        p = x;
    }

    void print() {
        vector<char> v = {'=', '#', ' ',  'S', 'O'};
        auto [y, x] = pos;
        for (LL i = 0; i < N; i++) {
            for (LL j = N-1; j >= 0; j--) {   
                if (i == y && j == x) cout << "x";
                else cout << v[color[i][j]];
            }
            cout << endl;
        }
        cout << endl;
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
    Surface s (p);
    s.scan();
    s.print();
    cout << s.bfs() << endl;
}


int main()
{  
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  solve();
  return 0;
}