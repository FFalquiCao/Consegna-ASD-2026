#include <bits/stdc++.h>
using namespace std;

const int LINES = 594924;

int main() {

    vector<vector<int>> paths(LINES, vector<int>(0));

    for(int path = 0; path < LINES; path++) {
        
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

                    paths[path].push_back((int) v);
                    cout << v << "\n";
                    
                }
            }
            
            cout.flush();
        }
    }

}
