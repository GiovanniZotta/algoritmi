#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

#define IMP -1
typedef pair<int,int> ii;

ifstream in("input.txt");
ofstream out("output.txt");
int mcd(int a, int b);

struct Tris{
    int a, b, c;
    Tris(){}
    Tris(int A, int B, int C):a(A), b(B), c(C) {}
    bool operator ==(Tris t1){
        return ((t1.b == b && t1.c == c) || (t1.b == c && t1.c == b));
    }
};

struct Graph{
    int dim;
    vector<vector<int>> graph;

    Graph(int n, int m): graph(n){
        dim = n;
        int a, b;
        for(int i=0; i<m; i++){
            in >> a >> b;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
    }

    int solve(int source){
        vector<bool> visited(dim, false);
        vector<ii> distance(dim);
        //first -> coming_from
        //second -> distance from source
        int count = 0;
        for(int edge : graph[source]){
            distance[edge].first = count++;
            distance[edge].second = 1;
        }
        return bfs(source, visited, distance);
    }

    int bfs(int source, vector<bool> &visited, vector<ii> &distance){
        int result = 0;
        Tris last;
        vector<Tris> cycles;
        queue<int> q;
        q.push(source);
        distance[source].second = 0;
        visited[source] = true;
        while(!q.empty()){
            int node = q.front(); q.pop();
            for(int edge : graph[node]){
                if(!visited[edge]){
                    if(distance[edge].second != 1)
                        distance[edge].first = distance[node].first;
                    distance[edge].second = distance[node].second + 1;
                    q.push(edge);
                    visited[edge] = true;
                }else if(edge != source){
                    if(distance[edge].first != distance[node].first){
                        int prev = result;
                        result = mcd(result, distance[edge].second + (distance[node].second + 1));
                        cycles.push_back(Tris(distance[edge].second + (distance[node].second + 1), distance[edge].first, distance[node].first));
                        if(result < prev)
                            last = cycles[cycles.size()-1];
                    }
                }
            }
        }
        if(cycles.size() != 0){
            for(int i=0; i<cycles.size()-1; i++)
                if(cycles[i].a % last.a == 0 && cycles[i] == last){
                    if(result % 2 != 0)
                        return 0;
                    else
                        return result/2;
                }
        }
        return result;
    }

    
};

int mcd(int m, int n){
	return n==0?m:mcd(n,m%n);
}

int pokemon(Graph g){

    int result = 0;

    for(int i=0; i<g.dim; i++)
        result = mcd(result, g.solve(i));

    return result;
    
}

int main(int argc, char const *argv[]){
    int n, m;
    in >> n >> m;
    Graph g(n, m);
    out << pokemon(g) << endl;
}


