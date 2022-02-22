#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

struct node{
    vector<int> adj;
    bool visited = false;
};

int visita(vector<node>& graph, node& s){
    int sum = 1;
    s.visited = true;
    for(int n : s.adj)
        if(!graph[n].visited)
            sum += visita(graph,graph[n]);
    return sum;
}

int main(int argc, char const *argv[]){
    int n, m, s;
    in >> n >> m >> s;
    vector<node> graph(n);
    for(int i=0; i<m; i++){
        int a,b;
        in >> a >> b;
        graph[a].adj.push_back(b);
    }
    out << visita(graph, graph[s]);
    return 0;
}
