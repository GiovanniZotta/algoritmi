#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <algorithm>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

int bfs(vector<vector<int>> graph, int start){
    queue<int> q;
    q.push(start);
    vector<bool> visited(graph.size(),false);
    vector<int> distances(graph.size(),0);
    visited[start] = true;
    while(!q.empty()){
        int nodo = q.front(); q.pop();
        for(int edge: graph[nodo])
            if(!visited[edge]){
                distances[edge] = distances[nodo] +1;
                q.push(edge);
                visited[edge] = true;
            }
    }
    return *max_element(distances.begin(),distances.end());
}

int diametro(vector<vector<int>> graph){
    int diametro = 0;
    for(int i=0; i<graph.size(); i++)
        diametro = max(diametro, bfs(graph, i));
    return diametro;
}

int main(int argc, char const *argv[]){
    int n, m;
    in >> n >> m;
    vector<vector<int>> graph(n);

    for(int i=0; i<m; i++){
        int a,b;
        in >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    out << diametro(graph);

    return 0;
}
