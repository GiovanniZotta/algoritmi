#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
#include <stack>
using namespace std;

#define NUM_FILE 20
#define FILENAME "input/input"
#define IMPOSSIBLE -1
#define CURRENT 0
#define COST 1
#define PARENT 2

typedef pair<int,int> ii;

struct cmp{
    bool operator()(vector<int> a, vector<int> b){
        return a[1] > b[1];
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
pair<int,vector<int>> laser(string filename);
int main(int argc, char const *argv[]);
int time_needed(int current_time, edge e);
int dijkstra(vector< pair<vector<edge>, int> > &graph, vector<int> &parent, int source, int target);


int dijkstra(vector< pair<vector<edge>, int> > &graph, vector<int> &parent, int source, int target){
    priority_queue<vector<int>, vector<vector<int>>, cmp> q;
    vector<bool> visited(graph.size(), false);
    vector<int> s = {source, 0, 0};
    // 0 -> current node, 1 -> cost, 2 -> parent
    q.push(s);
    while(!q.empty()){
        vector<int> node = q.top();
        q.pop();
        if(!visited[node[CURRENT]]){
            visited[node[CURRENT]] = true;
            parent[node[CURRENT]] = node[PARENT];
            if(node[CURRENT] == target)
                return node[COST];
            else
                for(edge &e : graph[node[CURRENT]].first)
                    if(!visited[e.to]){
                        int time = time_needed(node[COST], e);
                        graph[e.to].second = time + node[COST];
                        vector<int> n = {e.to, graph[e.to].second, node[CURRENT]};
                        q.push(n);
                    }
        }
    }
    return IMPOSSIBLE;
}

pair<int, vector<int>> laser(string filename){
    vector<pair<vector<edge>, int>> graph = get_input(filename);
    int source = 0, target = graph.size()-1;

    pair<int, vector<int>> to_return;
    vector<int> parent(graph.size(),IMPOSSIBLE);

    to_return.first = dijkstra(graph, parent, source, target);
    to_return.second = parent;
    
    return to_return;
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
    vector<pair<int,vector<int>>> result(NUM_FILE);
    ofstream out("output.txt");
    for (int i = 0; i < NUM_FILE; i++)
    {
        string filename = FILENAME;
        filename += to_string(i) + ".txt";
        result[i] = laser(filename);
        out << result[i].first << endl;
        if(result[i].first != IMPOSSIBLE){
            int index = result[i].second.size()-1;
            stack<int> path;
            while(index != 0){
                path.push(result[i].second[index]);
                index = path.top();
            }
            // path.push(result[i].second[0]);
            while(!path.empty()){
                out << path.top() << endl;
                path.pop();
            }
            out << result[i].second.size()-1;
        }
        cout << i << " done" << endl;
    }
    // pair<int,vector<int>> result = laser("input/input.txt");
    // out << result.first << endl;
    

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