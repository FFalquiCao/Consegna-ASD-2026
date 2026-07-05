#include <bits/stdc++.h>
using namespace std;

const int LINES = 594924;
//const int LINES = 3;

int main() {

    int n; cin >> n; // numero di nodi
    unordered_map<int,int> NodicompToReg;
    unordered_map<int,int> NodiregToComp;
    
    for(int i = 0; i<n; i++) {
        int reg, comp;
        cin >> reg >> comp;

        NodicompToReg[comp] = reg;
        NodiregToComp[reg] = comp;
    }

    int V; cin >> V; // valore del peso max: tutti i pesi w sono interi fra 1 e V
    
    int m; cin >> m; //numero di archi
    vector<vector<pair<int,int>>> adj(n, vector<pair<int,int>>(0));
    for(int i = 0; i<m; i++) {
        int w, ln, gn; cin >> w >> ln >> gn;
        ln = NodiregToComp[ln];
        gn = NodiregToComp[gn];

        if(gn >= n || gn >= n) {
            cerr << "Huh";
            return 0;
        }
        adj[ln].push_back(make_pair(gn, w));
        adj[gn].push_back(make_pair(ln, w));
    }

    //for(auto u : adj[0]) {
    //    cout << u.first << " " << u.second << "\n";
    //}

    int a = 480, b = 800; //cin >> a >> b; //nodi di cui trovare il minmax path
    //a = NodiregToComp[a]; b = NodiregToComp[b]; 

    vector<bool> visited(n);
    auto dfs = [&](int index, auto dfs) {
        if(visited[index]) return;
        visited[index] = true; 

        for(auto u : adj[index]) {
            if(u.second <= 25)
                dfs(u.first, dfs);
        }
    };

    dfs(a, dfs);
    
    cout << visited[b];
    
}
