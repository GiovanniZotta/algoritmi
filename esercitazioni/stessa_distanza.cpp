#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

#define IMP -1
ifstream in("input.txt");
ofstream out("output.txt");

vector<int> calcola_distanze(vector<vector<int>> &graph, int source){
    vector<bool> visited(graph.size(), false);
    vector<int> distance(graph.size(), IMP);
    queue<int> q;
    q.push(source);
    distance[source] = 0;
    while(!q.empty()){
        int node = q.front(); q.pop();
        visited[node] = true;
        for(int edge : graph[node])
            if(!visited[edge]){
                distance[edge] = distance[node] + 1;
                q.push(edge);
            }
    }
    return distance;
}

int stessa_distanza(vector<vector<int>> &graph, int s1, int s2){
    vector<int> distanza_1 = calcola_distanze(graph, s1);
    vector<int> distanza_2 = calcola_distanze(graph, s2);
    int result = 0;

    for(int i=0; i<graph.size(); i++)
        if(distanza_1[i] == distanza_2[i] && distanza_1[i] != IMP)
            result++;

    return result;
}

int main(int argc, char const *argv[])
{
    int n, m, s, t;
    in >> n >> m >> s >> t;
    vector<vector<int>> graph(n);
    for(int i=0; i<m; i++){
        int a,b;
        in >> a >> b;
        graph[a].push_back(b);
    }

    out << stessa_distanza(graph, s, t) << endl;
    return 0;
}
