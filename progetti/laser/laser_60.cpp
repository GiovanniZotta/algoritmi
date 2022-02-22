#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

#define NUM_FILE 5
#define NUM_PARAM 5
#define FILENAME "input/input"
#define IMPOSSIBLE -1

typedef pair<int,int> ii;

struct cmp{
    bool operator()(ii a, ii b){
        return a.second > b.second;
    }
};

struct edge{
    int to;
    int length;
    int offset;
    int off_time;
    int on_time;
};

void print_graph(vector<pair<vector<edge>, int>> &graph);
vector<pair<vector<edge>, int>> get_input(string filename);
int laser(string filename);
int main(int argc, char const *argv[]);
bool is_possible(int current_time, edge e);
int time_needed(int current_time, edge e);
int dijkstra(vector< pair<vector<edge>, int> > &graph, vector<int> parent, int source, int target);


int dijkstra(vector< pair<vector<edge>, int> > &graph, vector<int> parent, int source, int target){
    priority_queue<ii, vector<ii>, cmp> q;
    vector<bool> visited(graph.size(), false);
    q.push(make_pair(source,0));
    visited[source] = true;
    while(!q.empty()){
        ii node = q.top();
        q.pop();
        visited[node.first] = true;
        // cout << node.first << "\n\t";
        // cout << "current time: " << node.second << "\n\t";
        if(node.first == target)
            return node.second;
        else{
            for(edge &e : graph[node.first].first){
                if(!visited[e.to]){
                    int time = time_needed(node.second, e);
                    // cout << "time to go to " << e.to << " :" << time << "\n\t";
                    graph[e.to].second = time + node.second;
                    parent[e.to] = node.first;
                    q.push(make_pair(e.to, graph[e.to].second));
                }
            }
        }
        // cout << endl;
    }
    return IMPOSSIBLE;
}

int laser(string filename){
    vector<pair<vector<edge>, int>> graph = get_input(filename);
    int source = 0, target = graph.size()-1;
    // print_graph(graph);

    vector<int> result;
    vector<int> parent(graph.size(), IMPOSSIBLE);

    result.push_back(dijkstra(graph, parent, source, target));
    
    return result[0];
}

int time_needed(int current_time, edge e){
    if(current_time <= e.offset)
        return (e.offset - current_time) + e.length;
    int time_remaining = e.off_time - ((current_time - e.offset) % (e.on_time + e.off_time));
    if(time_remaining >= e.length)
        return e.length;
    else
        return time_remaining + e.on_time + e.length;
}


int main(int argc, char const *argv[]){
    // vector<vector<int>> result(NUM_FILE);
    // for (int i = 0; i < NUM_FILE; i++)
    // {
    //     string filename = FILENAME;
    //     filename += to_string(i) + ".txt";
    //     result[i] = laser(filename);
    //     cout << result[i][0] << endl;
    // }
    ofstream out("output.txt");
    out << laser("input.txt");

    return 0;
}

void print_graph(vector<pair<vector<edge>, int>> &graph){
    for(pair<vector<edge>,int> &node : graph)
        for(edge &e : node.first)
            cout <<
                e.to << " " <<
                e.length << " " <<
                e.offset << " " <<
                e.off_time << " " << e.on_time << endl;
    cout << endl;
}

vector<pair<vector<edge>, int>> get_input(string filename){
    ifstream in(filename);
    int n,m;
    in >> n >> m;
    vector<pair<vector<edge>, int>> graph(n);
    for(int i=0; i<m; i++){
        int s,t,w,f,y,n;
        in >> s >> t >> w >> f >> y >> n;
        edge e;
        e.to = t;
        e.length = w;        
        e.offset = f;
        e.off_time = y;
        e.on_time = n;
        if(e.length <= e.off_time){
            graph[s].first.push_back(e);
            graph[s].second = INT_MAX;
            e.to = s;
            graph[t].first.push_back(e);
            graph[t].second = INT_MAX;
        }
    }
    // print_graph(graph);
    return graph;
}