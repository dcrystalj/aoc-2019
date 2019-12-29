#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
#define LL long long
#define ALL(x) x.begin(), x.end()
#define HAS(umap, key) (umap.find(key) != umap.end())
template<typename... Args>
void cline(Args... args){ ((cout << args << " "), ...); cout << endl;}


struct DD {
    unordered_map<string, LL> m;
    void set(string i, LL val) { m[i] = val; }
    auto get(string i, LL _default) {
        if (!HAS(m, i)) m[i] = _default;
        return m[i];
    }
    void add(string i, LL val) { 
        if (HAS(m, i)) {
            m[i] += val;
        } else {
            m[i] = val; 
        }
    }
    auto get(string i) { return get(i, 0); }
    auto size() { return m.size(); }
};

auto splitRegex(string s, string regx) {
    vector<string> v;
    regex rgx(regx);  
    sregex_token_iterator it (s.begin(), s.end(), rgx, -1);
    sregex_token_iterator end;
    for ( ; it != end; ++it) v.push_back(*it);
    return v;
}

unordered_map<string, vector<pair<LL, string>>> g;

struct Warehouse {
    DD storage;
    DD min_quantity; // minimum production for items
    DD produced; // total produced

    void build(string s, LL q) {
        LL to_build = q - storage.get(s);
        LL produce_times = ceil(1.0 * to_build / min_quantity.get(s));
        if (produce_times > 0) {
            produced.add(s, produce_times);
            storage.set(s, produce_times * min_quantity.get(s) - to_build);
            if (!HAS(g, s)) return;
            for(auto v : g[s]) {
                build(v.second, v.first * produce_times);
            }
        } else {
            storage.add(s, -q);
        }
    }
};

void solve() {
    string s;
    LL cnt = 0;
    Warehouse w;
    while(getline(cin, s)) {
        auto split = splitRegex(s, "( => |, )+");
        auto key_split = splitRegex(split[split.size()-1], "\\s+");
        w.min_quantity.set(key_split[1], stoll(key_split[0]));
        for (LL i = 0; i < split.size()-1; i++) {
            auto rest_split = splitRegex(split[i], "\\s+");
            g[key_split[1]].push_back({stoll(rest_split[0]), rest_split[1]});
        }
    }
    w.build("FUEL", 1);
    LL ores = 0;
    for (auto &a : w.produced.m) {
        if (g[a.first].size() == 1 && g[a.first][0].second == "ORE") {
            ores += g[a.first][0].first * a.second;
        }
    }
    cout << ores;
}


int main()
{  
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  solve();
  return 0;
}