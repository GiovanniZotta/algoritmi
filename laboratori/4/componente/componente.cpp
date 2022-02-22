#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

void top_order(vector<vector<int>> &graph, int source, vector<bool> &visited, stack<int> &dfs_stack);
int dfs(vector<vector<int>> &graph, int source);
int scc(vector<vector<int>> &graph);

void top_order(vector<vector<int>> &graph, int source, vector<bool> &visited, stack<int> &dfs_stack){
    visited[source] = true;
    for(int n : graph[source])
        if(!visited[n])
            top_order(graph, n, visited, dfs_stack);
    dfs_stack.push(source);
}

int dfs(vector<vector<int>> &graph, int source, vector<bool> &visited){
    int count = 1;
    visited[source] = true;
    for(int edge : graph[source])
        if(!visited[edge])
            count += dfs(graph, edge, visited);
    return count;
}

int scc(vector<vector<int>> &graph, vector<vector<int>> &transposed){
    stack<int> dfs_stack;
    vector<bool> visited(graph.size(), false);
    for(int i=0; i<graph.size(); i++)
        if(!visited[i])
            top_order(graph, i, visited, dfs_stack);

    int result = 0;
    visited.assign(visited.size(), false);
    while(!dfs_stack.empty()){
        if(!visited[dfs_stack.top()])
            result = max(result, dfs(transposed, dfs_stack.top(), visited));
        dfs_stack.pop();
    }
    return result;
}

int main(int argc, char const *argv[]){
    int n,m;
    in >> n >> m;
    vector<vector<int>> graph(n);
    vector<vector<int>> transposed(n);
    vector<bool> visited(n, false); 
    for(int i=0; i<m; i++){
        int a,b;
        in >> a >> b;
        graph[a].push_back(b);
        transposed[b].push_back(a);
    }

    out << scc(graph, transposed) << endl;

    return 0;
}
