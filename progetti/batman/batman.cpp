#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;

ifstream in("input/input18.txt");
ofstream out("output.txt");

void top_order(vector<vector<int>> &graph, int source, vector<bool> &visited, stack<int> &dfs_stack);
void dfs(vector<vector<int>> &graph, int source, vector<int> &result);
int batman(vector<vector<int>> &graph, vector<vector<int>> &transposed, int source, int target);
pair<vector<pair<vector<int>, int>>, pair<int,int>> scc(vector<vector<int>> &graph, vector<vector<int>> &transposed, int source, int target);

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

//first = graph (first -> adjacents, second -> paths )
//second = couple (first -> scc of source, second -> scc of target)
pair< vector<pair<vector<int>, int>>, pair<int,int> > scc(vector<vector<int>> &graph, vector<vector<int>> &transposed, int source, int target){
    
    //toporder
    stack<int> dfs_stack;
    vector<bool> visited(graph.size(), false);
    for(int i=0; i<graph.size(); i++)
        if(!visited[i])
            top_order(graph, i, visited, dfs_stack);

    //strongly connected components
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

    //create the collapsed graph
    vector<pair<vector<int>, int>> new_graph(scc.size());
    for(int i=0; i<new_graph.size(); i++)
        for(int c : scc[i])
            for(int edge : graph[c])
                if(result[edge] != result[c])
                    new_graph[i].first.push_back(result[edge]);

    //return the collapsed graph and which scc the source and the target belong to
    return make_pair(new_graph, make_pair(result[source], result[target]));
}

int visit(vector<pair<vector<int>, int>> &graph, vector<bool> &visited, int source, int target){
    visited[source] = true;
    if(source == target)
        return 1;
    for(int edge : graph[source].first)
        if(!visited[edge])
            graph[source].second += visit(graph, visited, edge, target);
        else
            graph[source].second += graph[edge].second;
    return graph[source].second;
}

int batman(vector<vector<int>> &graph, vector<vector<int>> &transposed, int source, int target){

    pair<vector<pair<vector<int>, int>>, pair<int,int>> res = scc(graph, transposed, source, target);
    
    //collapsed graph of strongly connected components
    vector<pair<vector<int>, int>> collapsed = res.first;

    //strongly connected component containing the source node
    int scc_of_source = res.second.first;
    //strongly connected component containing the target node
    int scc_of_target = res.second.second;


    collapsed[scc_of_target].second = 1;

    vector<bool> visited(graph.size(), false);

    return visit(collapsed, visited, scc_of_source, scc_of_target);

    return 0;
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
