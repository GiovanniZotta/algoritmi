#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

typedef pair<int,int> ii;
vector<bool> articulation_points(vector<vector<int>> &graph);
ii dfs_points(vector<vector<int>> &graph, vector<bool> &visited, vector<int> &id, vector<int> &low, int root, int at, int parent, int curr_id, vector<bool> &art_points, ii &result);
pair<int, vector<int>> space(vector<vector<int>> &graph);
ii count_adj_articulations(vector<vector<int>> &graph, vector<bool> &visited, vector<bool> &art_points, vector<int> &adj_art_points, int source);
bool in_adj_art_points(vector<int> &adj_art_points, int node);

bool in_adj_art_points(vector<int> &adj_art_points, int node){
    for(int el : adj_art_points)
        if(el == node)
            return true;
    return false;
}

ii count_adj_articulations(vector<vector<int>> &graph, vector<bool> &visited, vector<bool> &art_points, vector<int> &adj_art_points, int source){
    ii count(0,source);
    visited[source] = true;
    for(int edge : graph[source])
        if(art_points[edge]){
            if(!in_adj_art_points(adj_art_points, edge)){
                adj_art_points.push_back(edge);
                count.first++;
            }
        }
        else if(!visited[edge])
            count.first += count_adj_articulations(graph, visited, art_points, adj_art_points, edge).first;
    return count;
}

ii dfs_points(vector<vector<int>> &graph, vector<bool> &visited, vector<int> &id, vector<int> &low, int root, int current, int parent, int curr_id, vector<bool> &art_points, ii &result){
    visited[current] = true;
    if(parent == root)
        result.second++;
    
    low[current] = id[current] = ++curr_id;
    result.first = curr_id;
    for(int edge : graph[current]){
        if(edge == parent) continue;
        if(!visited[edge]){
            result = dfs_points(graph, visited, id, low, root, edge, current, result.first, art_points, result);
            low[current] = min(low[current], low[edge]);
            if(id[current] <= low[edge])
                art_points[current] = true;
        }else
            low[current] = min(low[current], id[edge]);
    }
    return result;
}

vector<bool> articulation_points(vector<vector<int>> &graph){
    vector<bool> art_points(graph.size(), false);
    vector<int> id(graph.size(), 0);
    vector<int> low(graph.size(), 0);
    vector<bool> visited(graph.size(), false);

    for(int i=0; i<graph.size(); i++)
        if(!visited[i]){
            ii result(0,0);
            result = dfs_points(graph, visited, id, low, i, i, -1, result.first, art_points, result);
            art_points[i] = (result.second > 1);
        }
    
    return art_points;
}

pair<int, vector<int>> space(vector<vector<int>> &graph){
    pair<int, vector<int>> result;

    vector<bool> art_points = articulation_points(graph);

    vector<bool> visited(graph.size(), false);
    for(int i=0; i<graph.size(); i++)
        if(!visited[i] && !art_points[i]){
            vector<int> adj_art_points;
            ii tmp = count_adj_articulations(graph, visited, art_points, adj_art_points, i);
            if(tmp.first == 1){
                result.first++;
                result.second.push_back(tmp.second);
            }
        }

    return result;
}

int main(int argc, char const *argv[])
{
    int n, m;
    in >> n >> m;
    vector<vector<int>> graph(n);
    for(int i=0; i<m; i++){
        int a, b;
        in >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    pair<int, vector<int>> result = space(graph);
    out << result.first << endl;
    for(int node : result.second)
        out << node << " ";
    out << endl;

    return 0;
}
