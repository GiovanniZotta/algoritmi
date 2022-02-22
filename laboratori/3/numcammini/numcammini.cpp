#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

void print_distances(vector<int> distances)
{
    for (int i = 0; i < distances.size(); i++)
        cout << distances[i] << " ";
    cout << endl;
}

void print_graph(vector<vector<int>> &graph){
    for(int i=0; i<graph.size(); i++){
        for(int j=0; j<graph[i].size(); j++){
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
}

int visit_transposed(vector<vector<int>> &graph, vector<int> &distances, int source, int target){
    queue<int> q;
    q.push(source);
    int result = 0;
    while(!q.empty()){
        int nodo = q.front();
        q.pop();
        for(int v : graph[nodo]){
            if(distances[v] == distances[nodo]-1)
                q.push(v);
            if(v==target)
                result++;
        }
    }
    return result;
}

pair<int, int> numcammini(vector<vector<int>> &graph, vector<vector<int>> &transposed, int source, int target){
    queue<int> q;
    q.push(source);
    vector<bool> visited(graph.size(), false);
    vector<int> distances(graph.size(), 0);
    visited[source] = true;
    while (!q.empty()){
        int nodo = q.front();
        q.pop();
        for(int v : graph[nodo])
            if (!visited[v]){
                distances[v] = distances[nodo] + 1;
                visited[v] = true;
                q.push(v);
            }
    }
    pair<int,int> result;
    result.first = distances[target];
    result.second = visit_transposed(transposed, distances, target, source);
    return result;
}

int main(int argc, char const *argv[])
{
    int n, m, s, t;
    in >> n >> m >> s >> t;
    vector<vector<int>> graph(n);
    vector<vector<int>> transposed(n);
    int a, b;

    for (int i = 0; i < m; i++)
    {
        in >> a >> b;
        graph[a].push_back(b);
        transposed[b].push_back(a);
    }
    pair<int, int> result = numcammini(graph, transposed, s, t);
    out << result.first << " " << result.second;

    return 0;
}
