#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

typedef pair<int, int> ii;
struct cmp {
    bool operator()(ii a, ii b){
        return a.second > b.second;
    }
};

// ifstream in("input.txt");
// ofstream out("output.txt");

void pony(vector<vector<ii>> &graph, vector<int> &palline, int source, int target){
    priority_queue<ii, vector<ii>, cmp> q;
    vector<int> distance(graph.size(), INT_MAX);
    vector<int> mails(graph.size(), 0);
    ii start(source, 0);
    distance[source] = 0;
    mails[source] = palline[source];
    q.push(start);
    while(!q.empty()){
        ii current = q.top(); q.pop();
        if(distance[current.first] != current.second) continue;
        // cout << "current: " << current.first << endl;
        // cout << "mails: " << mails[current.first] << endl;
        // cout << "@@@@@@" << endl;
        for(ii to : graph[current.first]){
            if(distance[to.first] >= distance[current.first] + to.second){
                // mails[to.first] = max(mails[to.first], mails[current.first] + palline[to.first]);
                if(distance[current.first] + to.second < distance[to.first])
                    mails[to.first] = mails[current.first] + palline[to.first];
                else if(distance[current.first] + to.second == distance[to.first])
                    mails[to.first] = max(mails[to.first], mails[current.first] + palline[to.first]);
                distance[to.first] = distance[current.first] + to.second;
                q.push(ii(to.first, distance[to.first]));
            }
        }
    }

    if(distance[target] != INT_MAX)
        cout << distance[target] << " " << mails[target] << endl;
    else
        cout << "impossible" << endl;
}

int main(int argc, char const *argv[])
{
    int n, m;
    cin >> n;
    vector<vector<ii>> graph(n+1);  
    vector<int> palline(n+1);
    for(int i=1; i<=n; i++)
        cin >> palline[i];

    cin >> m;

    int a, b, c;
    for(int i=0; i<m; i++){
        cin >> a >> b >> c;
        graph[a].push_back(ii(b, c));
        graph[b].push_back(ii(a, c));
    }

    pony(graph, palline, 1, n);
    return 0;
}
