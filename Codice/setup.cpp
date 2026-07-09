#include <bits/stdc++.h>
using namespace std;

//const int LINES = 760447;
const int LINES = 594924;

int main() {
    vector<vector<int>> paths(LINES, vector<int>(0));

    int MaxV = 0;

    for(int p = 0; p < LINES; p++) {
        
        //una stringa di input è della forma routeviews/routeviews|5 3561|3847|6618 198.137.143.0/24 i 204.70.4.89
        //l'unica parte che ci interessa è 3561|3847|6618
        
        for(int i = 0; i<5; i++) {
            string s;
            cin >> s;
            
            if(i == 1) {
                int v = 0;
                for(int j = 0; j<s.size(); j++) {
                    if(s.at(j) == '|') {
                        paths[p].push_back(v);
                        v = 0;
                        continue;
                    }
                    v = v*10;
                    v += ((int)s.at(j)) - (int)'0'; 
                    MaxV = max(MaxV, v);
                }
                paths[p].push_back(v);
                /*while(!s.empty()) {
                    long unsigned int pos;
                    int v = stoi(s, &pos);
                    
                    s.erase(0,pos+1);

                    paths[p].push_back((int) v);
                    MaxV = max(MaxV, v);
                }*/         // asintoticamente più lento
            }
        }
    }

    int n = MaxV+1;

    //vector<vector<pair<int,int>>> adj(n, vector<pair<int,int>>(0));
    vector<unordered_map<int,int>> adj(n);
    int maxWeight = 0;

    for(int p = 0; p < LINES; p++) {
        int prev = paths[p][0];
        for(int i = 1; i<paths[p].size(); i++) {
            int curr = paths[p][i];

            adj[curr][prev]++;
            adj[prev][curr]++;
            maxWeight = max(maxWeight, adj[prev][curr]);

            prev = curr;
        }
    }

    int size_curr_comp = 0;

    vector<bool> visited(n);
    auto dfs = [&](int index, auto dfs) {
        if(visited[index]) return;
        visited[index] = true; 
        size_curr_comp++;

        for(auto u : adj[index]) dfs(u.first, dfs);
    };

    int connected_parts = 0;
    int max_size = 0;
    int max_size_index = 0;

    for(int i = 1; i < n; i++) {
        if(!visited[i]) {
            size_curr_comp = 0;
            dfs(i, dfs);
            if(size_curr_comp > max_size) {
                max_size = size_curr_comp;
                max_size_index = i;
            }
            connected_parts++;
        }
    }

    visited = vector<bool>(n,0); 
    
    //unordered_map<int,int> pesi;
    //int pesoCompresso = 0;

    vector<int> nodi;
    vector<pair<int,pair<int,int>>> archi; //contiene {peso, {nodo minore, nodo maggiore}}

    auto dfsNew = [&](int index, auto dfsNew) {
        if(visited[index]) return;
        visited[index] = true; 
        
        nodi.push_back(index);

        for(auto u : adj[index]) {
            if(u.first < index) {
                archi.push_back(make_pair(u.second, make_pair(u.first, index)));
            }

            //if(pesi.find(u.second) == pesi.end()) {
            //    pesi[u.second] = pesoCompresso;
            //    pesoCompresso++;
            //}

            dfsNew(u.first, dfsNew);
        }
    };

    dfsNew(max_size_index, dfsNew);

    sort(archi.begin(), archi.end());

    cout << nodi.size() << "\n";
    for(auto u : nodi) {
        cout << u << "\n";
    }

    cout << maxWeight << "\n";

    cout << archi.size() << "\n";
    for(auto u : archi) {
        cout << u.first << " " << u.second.first << " " << u.second.second << "\n";
    }

    //  Da runnare con il comando
    //  ./setup.exe < 19980101.all-paths > grafo.txt
}
