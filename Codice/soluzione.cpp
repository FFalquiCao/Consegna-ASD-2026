#include <bits/stdc++.h>
using namespace std;

vector<int> parent, value, dimen, ins, root;
vector<vector<int>> adj;

const int lgmax = 20;
vector<int> level;
vector<vector<int>> anc(lgmax);

void make_set(int v) {
    ins[v] = v;
    dimen[v] = 1;
}

int find_set(int v) {
    if (v == ins[v])
        return v;
    return ins[v] = find_set(ins[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (dimen[a] < dimen[b])
            swap(a, b);
        ins[b] = a;
        dimen[a] += dimen[b];

        //ogni elemento terminale del find_set deve puntare ad un elemento di valore max nel suo sottoinsieme
        //inoltre ogni coppia di insiemi che si uniscono sono connessi nell'albero
        adj[root[a]].push_back(root[b]);
        adj[root[b]].push_back(root[a]);

        if(value[root[a]] < value[root[b]]) {
            parent[root[a]] = root[b];
            root[a] = root[b];
        } else {
            parent[root[b]] = root[a];
            root[b] = root[a];
        }
        
    }
}

int getLca(int x, int y) {

    if(level[x] < level[y]) swap(x, y);

    for(int h = lgmax; 0 <= h; h--) {
        if(level[y] + (1 << h) <= level[x])
            x = anc[h][x];
    }
    if(x == y) return x;

    for(int h = lgmax; 0 <= h; h--) {
        if(anc[h][x] != anc[h][y]) {
            x = anc[h][x];
            y = anc[h][y];
        }
    }
    return anc[0][x];
}

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

    value = vector<int> (2*n, 0);
    ins = vector<int> (2*n, 0);
    dimen = vector<int> (2*n, 1);
    parent = vector<int> (2*n);
    root = vector<int> (2*n);
    adj.resize(2*n);

    for(int i = 0; i<2*n; i++) {
        ins[i] = i;
        parent[i] = i;
        root[i] = i;
    }

    int newNode = n;
    
    for(int i = 0; i<m; i++) {
        int w, ln, gn; cin >> w >> ln >> gn;
        ln = NodiregToComp[ln];
        gn = NodiregToComp[gn];

        if(gn >= n || ln >= n) {
            cerr << "Huh";
            return 0;
        }

        int a = find_set(ln);
        int b = find_set(gn);

        if(a == b) continue;

        value[newNode] = w;
        union_sets(a,newNode);
        union_sets(b,newNode);
        newNode++;
    }

    //anc = vector<vector<int>> (lgmax, vector<int>(2*n));

    //for(int i = 0; i<2*n; i++) {
    //    anc[0][i] = parent[i];
    //}

    //int j = 0;
    //while (j <= 6000) {
    //    cout << j << ": ";
    //    for(auto u : adj[j]) cout << u << " ";
    //    cout << "\n";
    //    j = parent[j];
    //    
    //}
    /*vector<bool> visited(2*n);
    auto dfs = [&](int index, auto dfs, int depth) {
        if(visited[index]) return;
        visited[index] = true; 
        level[index] = depth;

        for(auto u : adj[index]) dfs(u, dfs, depth+1);
    };
    dfs(newNode-1, dfs, 1);

    for(int i = 0; i<100; i++) cout << level[i] << "\n";
    //int a, b; cin >> a >> b; //nodi di cui trovare il minmax path
    //a = NodiregToComp[a]; b = NodiregToComp[b]; 
    //cout << r;
    

    // 234 266 hanno percorso minimo 48776. Questo perché 234 si connette esclusivamente a 266, ma lo fa molto spesso.*/
}
