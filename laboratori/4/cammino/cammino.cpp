#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

int cammino(vector<pair<vector<int>, int>> &graph, int source, vector<bool> &visited){
    visited[source] = true;
    for(int node : graph[source].first)
        if(!visited[node])
            graph[source].second = max(graph[source].second, 1 + cammino(graph, node, visited));
        else
            graph[source].second = max(graph[source].second, graph[node].second + 1);
    return graph[source].second;
}

int main(int argc, char const *argv[]){
    int n,m;
    in >> n >> m;
    vector<pair<vector<int>, int>> graph(n);
    vector<bool> visited(n, false); 
    for(int i=0; i<m; i++){
        int a,b;
        in >> a >> b;
        graph[a].first.push_back(b);
        graph[a].second = 0;
    }

    int result = 0;
    for(int i=0; i<graph.size(); i++)
        if(!visited[i])
            result = max(result, cammino(graph, i, visited));

    out << result << endl;
    return 0;
}
