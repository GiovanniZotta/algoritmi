#include "tsp.h"
#include <bits/stdc++.h>
#include <random>
using namespace std;
std::random_device myRandomDevice;
unsigned seed = myRandomDevice();
std::default_random_engine myRandomEngine(seed);
typedef pair<int,int> ii;

ifstream in("input.txt");
ofstream out("output.txt");
int best_so_far = INT_MAX;
vector<int> sol;


void print_graph_first(vector<vector<ii>> &graph){
    for(int i=0; i<graph.size(); i++){
        for(int j=0; j<graph.size(); j++)
            cout << graph[i][j].first << " ";
        cout << endl;
    }
}

void print_graph_second(vector<vector<ii>> &graph){
    for(int i=0; i<graph.size(); i++){
        for(int j=0; j<graph.size(); j++)
            cout << graph[i][j].second << " ";
        cout << endl;
    }
}
bool cmp (ii a, ii b) { return (a.second < b.second); }

vector<vector<ii>> get_input(){
    int n;
    in >> n;
    vector<vector<ii>> graph(n, vector<ii>(n));
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            graph[i][j].first = j;

    graph[0][0].second = INT_MAX;
    for(int i = 1; i < n; i++){
        for(int j = 0; j <= i; j++){
            if(i == j){
                graph[i][j].second = INT_MAX;
                graph[j][i].second = INT_MAX;
            }else{
                int a;
                in >> a;
                graph[i][j].second = a;
                graph[j][i].second = a;
            }
        }
    }
    // print_graph_first(graph);
    // print_graph_second(graph);
    return graph;
}

int getRandInt(int min, int max){
    std::uniform_int_distribution<int> myUnifIntDist(min, max);
    return myUnifIntDist(myRandomEngine);
}

bool tsp(vector<vector<ii>> &graph){
    sol.resize(graph.size());
    vector<bool> visited(graph.size(), false);
    int cost = 0;
    int source = getRandInt(0, graph.size()-1);
    visited[source] = true;
    sol[0] = source;
    int i = 1;
    int current = source;
    while(!all_of(visited.begin(), visited.end(), [](bool v) { return v; })){
        vector<ii> tmp(graph[current]);
        sort(tmp.begin(), tmp.end(), cmp);
        bool found = false;
        while(!found){
            if(!visited[tmp[0].first]){
                found = true;
                current = tmp[0].first;
                cost += tmp[0].second;
                sol[i] = tmp[0].first;
                visited[tmp[0].first] = true;
                i++;
            }else{
                tmp.erase(tmp.begin());
            }
        }
    }
    cost += graph[current][source].second;
    if(cost < best_so_far){
        best_so_far = cost;
        return true;
    }else
        return false;
}

void print_solution(){
    for(int i=0; i<sol.size(); i++)
        out << sol[i] << " ";
    out << sol[0] << "#" << endl;
}

int main(){
    vector<vector<ii>> graph = get_input();
    while(true)
        if(tsp(graph))
            print_solution();
}

