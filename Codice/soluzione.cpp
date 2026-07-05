#include <bits/stdc++.h>
using namespace std;

const int LINES = 594924;
//const int LINES = 3;

int main() {

    int n; cin >> n; // numero di nodi
    unordered_map<int,int> NodiregToComp;
    vector<int> NodicompToReg(n);
    
    for(int i = 0; i<n; i++) {
        int reg;
        cin >> reg;

        NodicompToReg[i] = reg;
        NodiregToComp[reg] = i;
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

    int a, b; cin >> a >> b; //nodi di cui trovare il minmax path
    //a = NodiregToComp[a]; b = NodiregToComp[b]; 

    
    vector<bool> visited(n);
    auto dfs = [&](int index, auto dfs, int w) {
        if(visited[index]) return;
        visited[index] = true; 

        for(auto u : adj[index]) {
            if(u.second <= w)
                dfs(u.first, dfs, w);
        }
    };

    //cerchiamo il minimo v per cui visited[b]=true 
    int l = 1; int r = V;
    int mid;
    while(l != r) {
        mid = (l + r) / 2;
        visited = vector<bool>(n, false);
        dfs(a, dfs, mid);
        if (visited[b])
            r = mid;
        else 
            l = mid + 1;
   }
    
    cout << r;
    
}
