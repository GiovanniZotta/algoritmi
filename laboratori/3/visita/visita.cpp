#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

int visita(vector<vector<int>> &graph, vector<bool> &visited, int node){
    visited[node] = true;
    int result = 1;
    for(int to : graph[node])
        if(!visited[to])
            result += visita(graph, visited, to);
    return result;
}

int main(int argc, char const *argv[]){
    
    int n, m, source, a, b;
    in >> n >> m >> source;
    vector<vector<int>> graph(n);
    vector<bool> visited(n, false);
    for(int i=0; i<m; i++){
        in >> a >> b;
        graph[a].push_back(b);
    }
    out << visita(graph, visited, source) << endl;
}
