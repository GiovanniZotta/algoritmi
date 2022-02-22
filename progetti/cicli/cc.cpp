#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

#define IMP -1
typedef pair<int,int> ii;

ifstream in("input/input1.txt");
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

vector<vector<int>> create_new_graph(vector<vector<int>> &graph, vector<int> &art_points, vector<bool> &bool_points){
  vector<vector<int>> new_graph(graph.size());
  for(int i=0; i<art_points.size(); i++){
      vector<int> tmp;
      for(int to : graph[art_points[i]])
          if(bool_points[to])
            tmp.push_back(to);
      new_graph[art_points[i]] = tmp;
  }
  return new_graph;
}

vector<int> bool_to_art(vector<bool> &bool_points){
  vector<int> art;
  for(int i=0;i<bool_points.size();i++)
    if(bool_points[i])
      art.push_back(i);
  return art;
}

void print_graph(vector<vector<int>> &graph){
  for(int i=0; i<graph.size(); i++){
    cout << "node: " << i << "\n\t";
    for(int j=0; j<graph[i].size(); j++)
      cout << graph[i][j] << " ";
    cout << endl;
  }
}

void cicli(vector<vector<int>> &graph){
  vector<vector<int>> tmp_graph;
  vector<bool> bool_points = articulation_points(graph);
  vector<int> art = bool_to_art(bool_points);
  vector<int> initial_art = bool_to_art(bool_points);

  while(art.size() != 0){
    tmp_graph = create_new_graph(graph, art, bool_points);
    vector<bool> tmp = articulation_points(tmp_graph);
    art = bool_to_art(tmp);
    // print_graph(tmp_graph);
    cout << art.size() << endl;
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
    /*for(int i=0; i<q; i++){
        in >> a >> b;
        out << erdos(graph, a, b) << endl;
    }*/

    cicli(graph);





}
