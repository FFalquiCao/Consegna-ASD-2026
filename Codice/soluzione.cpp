#include <bits/stdc++.h>
using namespace std;

const int LINES = 594924;
//const int LINES = 3;


vector<int> parent, value, dimen, ins, root;

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
        //inoltre ogni insieme che inizia a puntare su un altro deve aggiornare l'albero parent
        if(value[root[a]] < value[root[b]]) {
            parent[root[a]] = root[b];
            root[a] = root[b];
        } else {
            parent[root[b]] = root[a];
        }
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
    root = vector<int> (2*n);

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
        if(value[root[a]] < w && value[root[a]] < w) {
            // si crea una nuova componente connessa

            value[newNode] = w;
            union_sets(a,newNode);
            union_sets(b,newNode);
            newNode++;
        } else {
            // non si crea una nuova componente connessa
            union_sets(a,b);
        } 
    }

    int j = find_set(0); 

    cout << root[j] << " " << value[root[j]];

    
    //int a, b; cin >> a >> b; //nodi di cui trovare il minmax path
    //a = NodiregToComp[a]; b = NodiregToComp[b]; 
    //cout << r;
    

    // 234 266 hanno percorso minimo 48776. Questo perché 234 si connette esclusivamente a 266, ma lo fa molto spesso.
}
