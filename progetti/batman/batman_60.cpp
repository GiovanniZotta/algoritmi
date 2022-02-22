#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

struct path{
    int without_enemies;
    int with_enemies;
};

ifstream in("input/input18.txt");
ofstream out("output.txt");

void top_order(vector<vector<int>> &graph, int source, vector<bool> &visited, stack<int> &dfs_stack);
void dfs(vector<vector<int>> &graph, int source, vector<int> &result);
vector<int> scc(vector<vector<int>> &graph);
int batman(vector<vector<int>> &graph, vector<vector<int>> &transposed, int source, int target);
path visit(vector<vector<int>> &graph, vector<bool> &visited, vector<int> &scc, vector<path> &paths, int source, int target);
path add(vector<int> &scc, path &path1, path &path2, int source, int edge);

void top_order(vector<vector<int>> &graph, int source, vector<bool> &visited, stack<int> &dfs_stack){
    visited[source] = true;
    for(int n : graph[source])
        if(!visited[n])
            top_order(graph, n, visited, dfs_stack);
    dfs_stack.push(source);
}


void dfs(vector<vector<int>> &graph, int source, vector<bool> &visited, vector<int> &result){
    visited[source] = true;
    for(int edge : graph[source])
        if(!visited[edge]){
            result.push_back(edge);
            dfs(graph, edge, visited, result);
        }
}

vector<int> scc(vector<vector<int>> &graph, vector<vector<int>> &transposed){
    stack<int> dfs_stack;
    vector<bool> visited(graph.size(), false);
    for(int i=0; i<graph.size(); i++)
        if(!visited[i])
            top_order(graph, i, visited, dfs_stack);

    visited.assign(visited.size(), false);
    vector<vector<int>> scc;
    while(!dfs_stack.empty()){
        if(!visited[dfs_stack.top()]){
            vector<int> result;
            result.push_back(dfs_stack.top());
            dfs(transposed, dfs_stack.top(), visited, result);
            scc.push_back(result);
        }
        dfs_stack.pop();
    }

    vector<int> result(graph.size());

    for(int i=0; i<scc.size(); i++)
        for(int c : scc[i])
            result[c] = i;

    return result;
}

path add(vector<int> &scc, path &path1, path &path2, int source, int edge){
    if(scc[source] != scc[edge]){ 
        // se nell'arco che sto attraversando c'è un nemico
        path1.with_enemies += path2.without_enemies + path2.with_enemies;
    }else{
        path1.with_enemies += path2.with_enemies;
        path1.without_enemies += path2.without_enemies;
    }
    return path1;
}

path visit(vector<vector<int>> &graph, vector<bool> &visited, vector<int> &scc, vector<path> &paths, int source, int target){
    visited[source] = true;
    for(int edge : graph[source])
        if(!visited[edge]){
            path tmp = visit(graph, visited, scc, paths, edge, target);
            paths[source] = add(scc, paths[source], tmp, source, edge);
        }else if(scc[source] != scc[edge])
            paths[source] = add(scc, paths[source], paths[edge], source, edge);
    // cout << "node: " << source << ", no_enemies: " << paths[source].without_enemies << ", with enemies: " << paths[source].with_enemies << endl;
    return paths[source];
}

int batman(vector<vector<int>> &graph, vector<vector<int>> &transposed, int source, int target){
    vector<int> components = scc(graph, transposed);
    vector<bool> visited(graph.size(), false);
    vector<path> paths(graph.size());
    for(path p : paths){
        p.with_enemies = 0;
        p.without_enemies = 0;
    }

    for(int vicino : transposed[target]){
        if(components[vicino] != components[target]) //se c'è un nemico
            paths[vicino].with_enemies += 1;
        else
            paths[vicino].without_enemies += 1;
    }

    visited[target] = true;
    
    return visit(graph, visited, components, paths, source, target).with_enemies;
}

int main(int argc, char const *argv[]){
    int n, m, s, d;
    in >> n >> m >> s >> d;

    vector<vector<int>> graph(n);
    vector<vector<int>> transposed(n);
    for(int i=0; i<m; i++){
        int a,b;
        in >> a >> b;
        graph[a].push_back(b);
        transposed[b].push_back(a);
    }
    
    out << batman(graph, transposed, s, d) << endl;

    return 0;
}
