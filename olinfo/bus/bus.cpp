#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

typedef pair<int, int> ii;
ifstream in("input.txt");
ofstream out("output.txt");

struct edge{
    int to;
    int start_time;
    int end_time;
    edge(int t, int s, int e){
        to = t;
        start_time = s;
        end_time = e;
    }
};

struct cmp {
    bool operator()(ii a, ii b){
        return a.second > b.second;
    }
};


void bus(vector<vector<edge>> &graph, int source, int target){
    // cout << "source: " << source << ", target: " << target << endl;
    priority_queue<ii, vector<ii>, cmp> q;
    vector<int> distance(graph.size(), INT_MAX);
    distance[source] = 0;
    q.push(ii(source, 0));
    while(!q.empty()){
        ii current = q.top(); q.pop();
        if(current.second > distance[current.first]) continue;
        for(edge e : graph[current.first]){
            // cout << "current.first: " << current.first << ", current.second: " << current.second << endl;
            // cout << "distance[current.first]: " << distance[current.first] << endl;
            // cout << "e.to: " << e.to << endl;
            if(e.start_time <= current.second){ //can take it
                int min_time = (e.start_time - current.second) + (e.end_time - e.start_time);
                if(current.second + min_time < distance[e.to]){
                    distance[e.to] = current.second + min_time;
                    q.push(ii(e.to, current.second + min_time));
                }
            }
        }
    }
    if(distance[target] != INT_MAX)
        out << distance[target] << endl;
    else
        out << "IMPOSSIBLE" << endl;

}

int main(int argc, char const *argv[])
{
    int n, m, source, target, s, t;
    in >> n >> source >> target >> m;
    vector<vector<edge>> graph(n);  

    int a, b;
    for(int i=0; i<m; i++){
        in >> a >> s >> b >> t;
        edge to(b,s,t);
        graph[a].push_back(to);
    }

    bus(graph, source, target);

    return 0;
}
