#include <bits/stdc++.h>
using namespace std;

const int LINES = 594924;
//const int LINES = 3;

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
                while(!s.empty()) {
                    long unsigned int pos;
                    int v = stoi(s, &pos);
                    
                    s.erase(0,pos+1);

                    paths[p].push_back((int) v);
                    MaxV = max(MaxV, v);
                }
            }
        }
    }

    cout << "MaxV: " << MaxV << "\n"; //dovrebbe essere 9999
    int n = MaxV+1;

    vector<vector<pair<int,int>>> adj(n, vector<pair<int,int>>(0));
    int maxWeight = 0;

    for(int p = 0; p < LINES; p++) {
        int prev = paths[p][0];
        for(int i = 1; i<paths[p].size(); i++) {
            int curr = paths[p][i];
            
            bool found = false;
            for(int j = 0; j<adj[curr].size(); j++) {
                if(adj[curr][j].first == prev) {
                    (adj[curr][j].second)++;
                    found = true; 
                    break;
                }
            }
            if(found) {
                for(int j = 0; j<adj[prev].size(); j++) {
                    if(adj[prev][j].first == curr) {
                        (adj[prev][j].second)++; 
                        maxWeight = max(maxWeight, adj[prev][j].second);
                        break;
                    }
                }
            } else {
                adj[prev].push_back(make_pair(curr, 1));
                adj[curr].push_back(make_pair(prev, 1));
            }

            prev = curr;
        }
    }

    cout << "MAX PESO: " << maxWeight << "\n";

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

    cout << "Parti connesse: " << connected_parts << "\n";
    cout << "Max size: " << max_size << "\n";
    cout << "Max size index: " << max_size_index << "\n";
}
