#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
typedef pair<int,int> ii;

class BridgeFinder{
    public:
    int n, id;
    vector<int> low, ids;
    vector<bool> visited;
    vector<vector<int>> graph;

    BridgeFinder(vector<vector<int>> graph, int n){
        this->graph = graph;
        this->n = n;
    }

    vector<ii> find_bridges(){
        id = 0;
        low.resize(n);
        ids.resize(n);
        visited.resize(n,false);

        vector<ii> bridges;

        for(int i=0; i<n; i++)
            if(!visited[i])
                dfs(i, -1, bridges);

        return bridges;
    }

    void dfs(int at, int parent, vector<ii> bridges){
        visited[at] = true;
        low[at] = ids[at] = ++id;

        for(int to : graph[at]){
            if(to == parent) continue;
            if(!visited[to]){
                dfs(to, at, bridges);
                low[at] = min(low[at], low[to]);
                if(ids[at] < low[to])
                    bridges.push_back(make_pair(at,to));
            }else
                low[at] = min(low[at], ids[to]);
        }
    }

};

int main(int argc, char const *argv[])
{
    ifstream in("input/input0.txt");
    int n, m;
    in >> n >> m;
    vector<vector<int>> graph(n);
    for(int i=0; i<m; i++){
        int a, b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    BridgeFinder finder(graph, n);
    vector<ii> result = finder.find_bridges();

    for(ii e : result)
        cout << e.first << " " << e.second << endl;

    return 0;
}
