#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;


#define IMP -1
ifstream in("input_wrestler.txt");
ofstream out("output.txt");


//is graph bipartite
bool wrestler(vector<vector<int>> &graph){
    queue<int> q;
    vector<int> color(graph.size(), IMP);
    color[0] = true;
    q.push(0);
    while(!q.empty()){
        int current = q.front(); q.pop();
        for(int to : graph[current]){
            if(color[to] == IMP){
                color[to] = !color[current];
                q.push(to);
            }else if(color[to] == color[current])
                return false;
        }
    }
    return true;
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
    }

    out << wrestler(graph) << endl;


    return 0;
}