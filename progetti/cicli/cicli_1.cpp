#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

#define IMP -1
typedef pair<int,int> ii;

ifstream in("input/input5.txt");
ofstream out("output.txt");

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

bool in_adj_target(vector<int> &adj_target, int node){
    for(int el : adj_target)
        if(node == el)
            return true;
    return false;
}

int compute_distance_only_arts(vector<vector<int>> &graph, vector<bool> &bool_points, int source, int target){
    queue<int> q;
    vector<bool> visited(graph.size(), false);
    vector<int> distance(graph.size(), IMP);
    visited[source] = true;
    distance[source] = 0;
    q.push(source);
    while(!q.empty()){
        int current = q.front(); q.pop();
        for(int to : graph[current]){
            if(bool_points[to] && !visited[to]){
                distance[to] = distance[current] + 1;
                if(to == target)
                    return distance[to];
                q.push(to);
                visited[to] = true;
            }
        }
    }
}

int compute_distance(vector<vector<int>> &graph, vector<bool> &bool_points, int source, vector<int> &adj_target){
    queue<int> q;
    vector<bool> visited(graph.size(), false);
    vector<int> distance(graph.size(), IMP);
    visited[source] = true;
    distance[source] = 0;
    q.push(source);
    while(!q.empty()){
        int current = q.front(); q.pop();
        for(int to : graph[current]){
            if(bool_points[to] && !visited[to]){
                distance[to] = distance[current] + 1;
                if(in_adj_target(adj_target, to))
                    return distance[to] + 1;
                q.push(to);
                visited[to] = true;
            }
        }
    }
}

bool are_adj(vector<vector<int>> &graph, int source, int target){
    for(int to : graph[source])
        if(to == target)
            return true;
    return false;
}

void cicli(vector<vector<int>> &graph, int q){

    vector<bool> bool_points = articulation_points(graph);
    vector<int> art_points;

    for(int i=0; i<bool_points.size(); i++)
        if(bool_points[i])
            art_points.push_back(i);

    int s, t;
    for(int i=0; i<q; i++){
        in >> s >> t;
        // cout << "from " << s << " to " << t;
        if(bool_points[s] && bool_points[t])
            out << compute_distance_only_arts(graph, bool_points, s, t) << endl;
        else{
            vector<int> adj_target;
            for(int adj : graph[t])
                if(bool_points[adj])
                    adj_target.push_back(adj);
            int res = compute_distance(graph, bool_points, s, adj_target);
            // cout << ", res: " << res << endl;
            if(i==8276)
                cout << "adj: " << are_adj(graph, s, t) << endl;
            if((res == 0 || res == 2) && are_adj(graph, s, t))
                out << 1 << endl;
            else
                out << res << endl;
            if(i==8276)
                cout << res << endl;
        }
        if(i==8276)
            cout << s << " " << t;
    }

}

int main(int argc, char const *argv[]){
    int n, m, q, a, b;
    in >> n >> m >> q;
    vector<vector<int>> graph(n);

    for(int i=0; i<m; i++){
        in >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    cicli(graph,q);

}