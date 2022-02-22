#include <bits/stdc++.h>
using namespace std;

int solve(vector<bitset<10000>> &players){
    int max = 0, maxindex = 0;
    for(int i=1; i<=players.size(); i++){
        int partial = players[i-1].count();
        if(partial > max){
            max = partial;
            maxindex = i;
        }
    }
    return maxindex;    
}

int main(){
    int tests, p;
    cin >> tests >> p;
    for(int i=1; i<=tests; i++){
        vector<bitset<10000>> players;
        for(int j=0; j<100; j++){
            string tmp;
            cin >> tmp;
            bitset<10000> player(tmp);
            players.push_back(player); 
        }
        cout << "Case #" << i << ": " << solve(players) << endl;
    } 
}

