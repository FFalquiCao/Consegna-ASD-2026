#include <bits/stdc++.h>
using namespace std;

const int LINES = 594924;
//const int LINES = 3;


vector<int> parent, value, dimen, ins;

void make_set(int v) {
    ins[v] = v;
    dimen[v] = 1;
}

int find_set(int v) {
    if (v == ins[v])
        return v;
    return v = find_set(ins[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (dimen[a] < dimen[b])
            swap(a, b);
        ins[b] = a;
        dimen[a] += dimen[b];
    }
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

    for(int i = 0; i<2*n; i++) {
        ins[i] = i;
        parent[i] = i;
    }

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
        union_sets(a,b);

    }

    for(int i = 0; i<20; i++) {
        cout << find_set(30*i) << " " << dimen[30*i] << "\n";
    }





    //int a, b; cin >> a >> b; //nodi di cui trovare il minmax path
    //a = NodiregToComp[a]; b = NodiregToComp[b]; 

    
    
    
    //cout << r;
    
}
