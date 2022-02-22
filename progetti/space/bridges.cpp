#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
typedef pair<int,int> ii;

ifstream in("input/input0.txt");
ofstream out("output.txt");
int dfs_bridges(vector<vector<int>> &graph, vector<bool> &visited, vector<int> &id, vector<int> &low, int at, int parent, int curr_id, vector<ii> &bridges){
    
    visited[at] = true;
    low[at] = id[at] = ++curr_id;

    for(int to : graph[at]){
        if(to == parent) continue;
        if(!visited[to]){
            curr_id = dfs_bridges(graph, visited, id, low, to, at, curr_id, bridges);
            low[at] = min(low[at], low[to]);
            if(id[at] < low[to])
                bridges.push_back(make_pair(at, to));
        }else{
            low[at] = min(low[at], id[to]);
        }
    }
    return curr_id;
}

vector<ii> find_bridges(vector<vector<int>> &graph){
    
    vector<ii> bridges;
    vector<int> id(graph.size(), 0);
    vector<int> low(graph.size(), 0);
    vector<bool> visited(graph.size(), false);

    int curr_id = -1;
    for(int i=0; i<graph.size(); i++)
        if(!visited[i])
            curr_id = dfs_bridges(graph, visited, id, low, i, -1, curr_id, bridges);

    return bridges;
}

int main(int argc, char const *argv[]){

    int n, m;
    in >> n >> m;
    vector<vector<int>> graph(n);
    for(int i=0; i<m; i++){
        int a, b;
        in >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<ii> bridges = find_bridges(graph);
    for(ii el : bridges)
        cout << el.first << " " << el.second << endl;
}
