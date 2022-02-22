#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

void top_order(vector<vector<int>> &graph, int source, vector<bool> &visited, stack<int> &dfs_stack);

void top_order(vector<vector<int>> &graph, int source, vector<bool> &visited, stack<int> &dfs_stack){
    visited[source] = true;
    for(int n : graph[source])
        if(!visited[n])
            top_order(graph, n, visited, dfs_stack);
    dfs_stack.push(source);
}

int main(int argc, char const *argv[]){
    int n,m;
    in >> n >> m;
    vector<vector<int>> graph(n);
    vector<bool> visited(n, false); 
    for(int i=0; i<m; i++){
        int a,b;
        in >> a >> b;
        graph[a].push_back(b);
    }
    stack<int> dfs_stack;
    for(int i=0; i<graph.size(); i++)
        if(!visited[i])
            top_order(graph, i, visited, dfs_stack);
    while(!dfs_stack.empty()){
        out << dfs_stack.top() << " ";
        dfs_stack.pop();
    }
    out << endl;
    return 0;
}
