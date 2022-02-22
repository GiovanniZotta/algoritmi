#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
#include <stack>
using namespace std;

#define NUM_FILE 5
#define NUM_PARAM 5
#define FILENAME "input/input"
#define IMPOSSIBLE -1

typedef pair<int, int> ii;

struct edge
{
    int to;
    int length;
    int offset;
    int off_time;
    int on_time;
};

void print_graph(vector<pair<vector<edge>, int>> &graph);
vector<pair<vector<edge>, int>> get_input(string filename);
pair<int, vector<int>> laser(string filename);
int main(int argc, char const *argv[]);
bool is_possible(int current_time, edge e);
int time_needed(int current_time, edge e);
int dijkstra(vector<pair<vector<edge>, int>> &graph, vector<int> &parent, int source, int target);

int dijkstra(vector<pair<vector<edge>, int>> &graph, vector<int> &parent, int source, int target)
{
    priority_queue<ii, vector<ii>, greater<ii>> q;
    vector<int> cost(graph.size(), INT_MAX);
    vector<bool> visited(graph.size(), false);
    // 0 -> current node, 1 -> cost, 2 -> parent
    parent[source] = source;
    q.push(ii(0, source));
    while (!q.empty())
    {
        pair<int, int> node = q.top();
        q.pop();
        if (visited[node.second])
            continue;
        visited[node.second] = true;
        if (node.second == target)
            return node.first;
        for (edge &e : graph[node.second].first)
            if (!visited[e.to])
            {
                int c = time_needed(node.first, e) + node.first;
                graph[e.to].second = c;
                if (cost[e.to] > c)
                {
                    cost[e.to] = c;
                    parent[e.to] = node.second;
                    q.push(ii(c, e.to));
                }
            }
        // cout << endl;
    }
    return IMPOSSIBLE;
}

pair<int, vector<int>> laser(string filename)
{
    vector<pair<vector<edge>, int>> graph = get_input(filename);
    int source = 0, target = graph.size() - 1;
    // print_graph(graph);
    pair<int, vector<int>> to_return;
    vector<int> parent(graph.size(), IMPOSSIBLE);

    to_return.first = dijkstra(graph, parent, source, target);
    to_return.second = parent;

    return to_return;
}

int time_needed(int current_time, edge e)
{
    if (current_time <= e.offset)
        return (e.offset - current_time) + e.length;
    int time_remaining = e.off_time - ((current_time - e.offset) % (e.on_time + e.off_time));
    if (time_remaining >= e.length)
        return e.length;
    else
        return time_remaining + e.on_time + e.length;
}

int main(int argc, char const *argv[])
{
    // vector<vector<int>> result(NUM_FILE);
    // for (int i = 0; i < NUM_FILE; i++)
    // {
    //     string filename = FILENAME;
    //     filename += to_string(i) + ".txt";
    //     result[i] = laser(filename);
    //     cout << result[i][0] << endl;
    // }
    ofstream out("output.txt");
    pair<int, vector<int>> result = laser("input/input10.txt");
    out << result.first << endl;

    if (result.first != IMPOSSIBLE)
    {
        int index = result.second.size() - 1;
        stack<int> path;
        while (index != 0)
        {
            path.push(result.second[index]);
            index = path.top();
        }
        // path.push(result.second[0]);
        while (!path.empty())
        {
            out << path.top() << endl;
            path.pop();
        }
        out << result.second.size() - 1;
    }

    return 0;
}

void print_graph(vector<pair<vector<edge>, int>> &graph)
{
    for (pair<vector<edge>, int> &node : graph)
        for (edge &e : node.first)
            cout << e.to << " " << e.length << " " << e.offset << " " << e.off_time << " " << e.on_time << endl;
    cout << endl;
}

vector<pair<vector<edge>, int>> get_input(string filename)
{
    ifstream in(filename);
    int n, m;
    in >> n >> m;
    vector<pair<vector<edge>, int>> graph(n);
    for (int i = 0; i < m; i++)
    {
        int s, t, w, f, y, n;
        in >> s >> t >> w >> f >> y >> n;
        edge e;
        e.to = t;
        e.length = w;
        e.offset = f;
        e.off_time = y;
        e.on_time = n;
        if (e.length <= e.off_time)
        {
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