#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

int mincover(int source, vector<bool>& visited, vector<vector<int>>& tree){
    // queue<int> q1, q2;
    // q1.push(source);
    // visited[source] = true;
    // int result = 1;
    // while(!q1.empty()){
    //     int size1 = q1.size();
    //     for(int i=0; i<size1; i++){
    //         int node = q1.front(); q1.pop();
    //         for(int adj : tree[node])
    //             if(!visited[adj])
    //                 q2.push(adj);
    //     }
    //     int size2 = q2.size();
    //     for(int i=0; i<size2; i++){
            
    //     }

    // }

}

int main(int argc, char const *argv[]){
    int n, a, b;
    in >> n;
    vector<vector<int>> tree(n);
    vector<bool> visited(n, false);
    for(int i=0; i<n-1; i++){
        in >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    out << mincover(0, visited, tree) << endl;
    return 0;
}
