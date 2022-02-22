#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <climits>
using namespace std;

#define IMP -1
typedef pair<int,int> ii;

FILE * in= fopen("input.txt","r");
FILE * out= fopen("output.txt","w");

//per l'algoritmo per trovare i LCA (lowest common ancestor) ho preso spunto dal video di Jalgs
//Link: https://www.youtube.com/watch?v=HeeyUZmaZg0
//per l'algoritmo per trovare gli articulation points e i bridges, ho preso ispirazione dal video di William Fiset:
//Link: https://youtu.be/aZXi1unBdJA

struct Clique{
    vector<int> nodes;
};

struct cmp{
    bool operator()(int a, int b){
        return a > b;
    }
};

struct RequestMinimumQuery{
    vector<int> log_table;
    vector<vector<int>> sparse_table;
    RequestMinimumQuery(){}

    void populate(vector<int> v){
        log_table.assign(v.size() + 1, 0);
        for(int i=2; i< log_table.size(); i++)
            log_table[i] = log_table[i/2] + 1;
        sparse_table.assign(log_table.back() +1, vector<int>(v.size()));
        sparse_table[0] = v;
        for(int i = 1; i < sparse_table.size(); i++){
            for(int j=0; j + (1 << i) <= v.size(); j++){
                sparse_table[i][j] = min(sparse_table[i-1][j], sparse_table[i-1][j + (1<<(i-1))]);
            }
        }
    }
    int minimum(int left, int right){
        int log = log_table[right-left];
        return min(sparse_table[log][left], sparse_table[log][right- (1<<log)]);
    }
};

void euler(unordered_map<int, vector<int>> &graph, vector<int> &euler_tour, unordered_map<int, int> &first_encounter, vector<int> &new_to_old, int source, int parent){
    int new_index = new_to_old.size();
    new_to_old.push_back(source);
    first_encounter[source] = euler_tour.size();
    euler_tour.push_back(new_index);
    for(int to : graph[source]){
        if(to != parent){
            euler(graph, euler_tour, first_encounter, new_to_old, to, source);
            euler_tour.push_back(new_index);
        }
    }
}

unordered_map<int, int> distance_from_root(unordered_map<int, vector<int>> &graph, int root){
    queue<int> q;
    unordered_map<int, int> distance;
    unordered_map<int, bool> visited;
    int level = 0;
    q.push(root);
    distance[root] = level;
    visited[root] = true;
    while(!q.empty()){
        int size = q.size();
        level++;
        for(int i=0; i<size; i++){
            int current = q.front(); q.pop();
            for(int to : graph[current]){
                if(!visited[to]){ //if not parent
                    q.push(to);
                    visited[to] = true;
                    distance[to] = level;
                } 
            }
        }
    }
    return distance;
}

struct Tree{
    int cc, root;
    unordered_map<int, vector<int>> tree;
    unordered_map<int, int> root_dist;
    vector<int> euler_tour;
    unordered_map<int, int> first_encounter;
    RequestMinimumQuery rmq;
    vector<int> new_to_old;
    Tree(int n, int r){
        cc = n;
        root = r;
    }

    void precompute(){
        root_dist = distance_from_root(tree, root);
        euler(tree, euler_tour, first_encounter, new_to_old, root, -1);
        rmq.populate(euler_tour);
    }

    int get_distance(int a, int b){
        int source = first_encounter[a];
        int target = first_encounter[b];
        if(source > target) swap(source, target);
        int new_index = rmq.minimum(source, target+1);
        int LCA = new_to_old[new_index];
        return root_dist[a] + root_dist[b] - 2*root_dist[LCA];
    }

};

int dfs_bridges(vector<vector<int>> &graph, vector<bool> &visited, vector<int> &id, vector<int> &low, int node, int parent, int curr_id, vector<ii> &bridges){
    
    visited[node] = true;
    low[node] = id[node] = ++curr_id;

    for(int adj : graph[node]){
        if(adj == parent) continue;
        if(!visited[adj]){
            curr_id = dfs_bridges(graph, visited, id, low, adj, node, curr_id, bridges);
            low[node] = min(low[node], low[adj]);
            if(id[node] < low[adj])
                bridges.push_back(make_pair(node, adj));
        }else{
            low[node] = min(low[node], id[adj]);
        }
    }
    return curr_id;
}

vector<ii> find_bridges(vector<vector<int>> &graph){
    
    vector<ii> bridges;
    vector<int> id(graph.size(), 0);
    vector<int> low(graph.size(), 0);
    vector<bool> visited(graph.size(), false);

    int curr_id = -1;
    for(int i=0; i<graph.size(); i++)
        if(!visited[i])
            curr_id = dfs_bridges(graph, visited, id, low, i, -1, curr_id, bridges);

    return bridges;
}

ii dfs_points(vector<vector<int>> &graph, vector<bool> &visited, vector<int> &id, vector<int> &low, int root, int current, int parent, int curr_id, vector<bool> &art_points, ii &result){
    visited[current] = true;
    if(parent == root)
        result.second++;
    
    low[current] = id[current] = ++curr_id;
    result.first = curr_id;
    for(int edge : graph[current]){
        if(edge == parent) continue;
        if(!visited[edge]){
            result = dfs_points(graph, visited, id, low, root, edge, current, result.first, art_points, result);
            low[current] = min(low[current], low[edge]);
            if(id[current] <= low[edge])
                art_points[current] = true;
        }else
            low[current] = min(low[current], id[edge]);
    }
    return result;
}

vector<bool> articulation_points(vector<vector<int>> &graph){
    vector<bool> art_points(graph.size(), false);
    vector<int> id(graph.size(), 0);
    vector<int> low(graph.size(), 0);
    vector<bool> visited(graph.size(), false);

    for(int i=0; i<graph.size(); i++)
        if(!visited[i]){
            ii result(0,0);
            result = dfs_points(graph, visited, id, low, i, i, -1, result.first, art_points, result);
            art_points[i] = (result.second > 1);
        }
    
    return art_points;
}

bool in_adj_target(vector<int> &adj_target, int node){
    for(int el : adj_target)
        if(node == el)
            return true;
    return false;
}

int compute_distance_only_arts(vector<vector<int>> &graph, vector<bool> &bool_points, int source, int target){
    queue<int> q;
    vector<bool> visited(graph.size(), false);
    vector<int> distance(graph.size(), IMP);
    visited[source] = true;
    distance[source] = 0;
    q.push(source);
    while(!q.empty()){
        int current = q.front(); q.pop();
        for(int to : graph[current]){
            if(bool_points[to] && !visited[to]){
                distance[to] = distance[current] + 1;
                if(to == target)
                    return distance[to];
                q.push(to);
                visited[to] = true;
            }
        }
    }
}

int compute_distance(vector<vector<int>> &graph, vector<bool> &bool_points, int source, vector<int> &adj_target){
    queue<int> q;
    vector<bool> visited(graph.size(), false);
    vector<int> distance(graph.size(), IMP);
    visited[source] = true;
    distance[source] = 0;
    q.push(source);
    while(!q.empty()){
        int current = q.front(); q.pop();
        for(int to : graph[current]){
            if(bool_points[to] && !visited[to]){
                distance[to] = distance[current] + 1;
                if(in_adj_target(adj_target, to))
                    return distance[to] + 1;
                q.push(to);
                visited[to] = true;
            }
        }
    }
}

bool are_adj(vector<vector<int>> &graph, int source, int target){
    for(int to : graph[source])
        if(to == target)
            return true;
    return false;
}

void solve_graph(vector<vector<int>> &graph, int q){

    vector<bool> bool_points = articulation_points(graph);
    vector<int> art_points;

    for(int i=0; i<bool_points.size(); i++)
        if(bool_points[i])
            art_points.push_back(i);

    int s, t;
    for(int i=0; i<q; i++){
        fscanf(in, "%d %d", &s, &t);
        if(are_adj(graph, s, t))
            fprintf(out, "1\n");
        else if(bool_points[s] && bool_points[t])
            fprintf(out, "%d\n", compute_distance_only_arts(graph, bool_points, s, t));
        else{
            vector<int> adj_target;
            for(int adj : graph[t])
                if(bool_points[adj])
                    adj_target.push_back(adj);
            fprintf(out, "%d\n", compute_distance(graph, bool_points, s, adj_target));
        }
    }
}

void print_graph(vector<vector<int>> &graph){
    for(int i=0; i<graph.size(); i++){
        cout << "node: " << i << "\n\t";
        for(int j=0; j<graph[i].size(); j++)
            cout << graph[i][j] << " ";
        cout << endl;
    }
}

vector<vector<int>> create_tree_graph(vector<vector<int>> &graph, vector<ii> &bridges){
    vector<vector<int>> tree_graph(graph.size());
    for(ii el : bridges){
        tree_graph[el.first].push_back(el.second);
        tree_graph[el.second].push_back(el.first);
    }
    return tree_graph;
}

Tree cc_tree(vector<vector<int>> &graph, vector<bool> &visited, int source, int n, vector<int> &cc){
    Tree t(n, source);

    queue<int> q;
    visited[source] = true;
    q.push(source);
    while(!q.empty()){
        int current = q.front(); q.pop();
        cc[current] = n;
        for(int to : graph[current])
            if(!visited[to]){
                t.tree[current].push_back(to);
                t.tree[to].push_back(current);
                visited[to] = true;
                q.push(to);
            }
    }
    return t;
}

pair<vector<int>, vector<Tree>> get_trees(vector<vector<int>> &graph){
    vector<Tree> trees;
    vector<bool> visited(graph.size(), false);
    vector<int> cc(graph.size(), IMP);
    int count = 0;
    for(int i=0; i<graph.size(); i++){
        if(!visited[i]){
            if(graph[i].size() > 0){
                trees.push_back(cc_tree(graph, visited, i, count, cc));
                count++;
            }
        }
    }
    return make_pair(cc, trees);
}

vector<vector<int>> create_clique_graph(vector<vector<int>> &graph, unordered_map<int, unordered_map<int, bool>> &bool_bridges){
    vector<vector<int>> new_graph(graph.size());
    for(int i=0; i<graph.size(); i++)
        for(int adj : graph[i])
            if(!bool_bridges[i][adj]){
                new_graph[i].push_back(adj);
            }
    return new_graph;
}

Clique cc_clique(vector<vector<int>> &graph, unordered_map<int, unordered_map<int, bool>> &bool_bridges, vector<bool> &visited, int source, int n, vector<int> &cc){
    Clique clique;
    queue<int> q;
    visited[source] = true;
    q.push(source);
    while(!q.empty()){
        int current = q.front(); q.pop();
        cc[current] = n;
        clique.nodes.push_back(current);
        for(int to : graph[current]){
            if(!visited[to]){
                if(!(bool_bridges[to][current] && bool_bridges[current][to])){
                    visited[to] = true;
                    q.push(to);
                }
            }
        }
    }
    return clique;
}

pair<vector<int>, vector<Clique>> get_cliques(vector<vector<int>> &graph, unordered_map<int, unordered_map<int, bool>> &bool_bridges){
    vector<Clique> cliques;
    vector<bool> visited(graph.size(), false);
    vector<int> cc(graph.size(), IMP);
    int count = 0;
    for(int i=0; i<graph.size(); i++)
        if(!visited[i])
            if(graph[i].size() > 0){
                Clique tmp = cc_clique(graph, bool_bridges, visited, i, count, cc);
                if(tmp.nodes.size() > 1){
                    cliques.push_back(tmp);
                    count++;
                }
            }
    return make_pair(cc, cliques);
}

int query(vector<vector<int>> &graph, pair<vector<int>, vector<Tree>> &trees, pair<vector<int>, vector<Clique>> &cliques, vector<bool> &bool_gateways, vector<vector<int>> &tree_gateways, vector<vector<int>> &clique_gateways, int a, int b){
    //base case
    if(trees.first[a] == trees.first[b] && trees.first[a] != IMP)
        //they are in the same tree
        return trees.second[trees.first[a]].get_distance(a, b);
    if(cliques.first[a] == cliques.first[b] && cliques.first[a] != IMP)
        //they are in the same clique
        return 1;

    //dijkstra
    priority_queue<int, vector<int>, cmp> q;
    vector<bool> visited(graph.size(), false);
    vector<int> distance(graph.size(), INT_MAX);
    visited[a] = true;
    distance[a] = 0;
    q.push(a);
    while(!q.empty()){
        int current = q.top(); q.pop();
        //if it's the target
        if(current == b)
            return distance[current];
        if(trees.first[b] == trees.first[current] && trees.first[b] != IMP){
            //target is in my tree
            return trees.second[trees.first[current]].get_distance(current, b) + distance[current];
        }else{
            //target is not in my tree
            if(cliques.first[b] == cliques.first[current] && cliques.first[current] != IMP){
                //target is in my clique
                return distance[current] + 1;
            }
            //if i'm in a clique
            //push all the gateways of my clique
            if(cliques.first[current] != IMP){
                for(int g : clique_gateways[cliques.first[current]]){
                    if(!visited[g]){
                        if(tree_gateways[trees.first[g]].size() > 1){
                            distance[g] = distance[current] + 1;
                            visited[g] = true;
                            q.push(g);
                        }else if(trees.first[g] == trees.first[b]){
                            return distance[current] + 1 + trees.second[trees.first[g]].get_distance(g, b);
                        }
                    }
                }
            }
            //plus, if i'm a gateway or i am in a tree, push all the gateways of my tree
            if(bool_gateways[current] || trees.first[current] != IMP){
                for(int g : tree_gateways[trees.first[current]]){
                    if(!visited[g]){
                        distance[g] = distance[current] + trees.second[trees.first[current]].get_distance(current, g);
                        visited[g] = true;
                        q.push(g);
                    }
                }  
            }
        }
    }
}

vector<vector<int>> get_tree_gateways(pair<vector<int>, vector<Tree>> &trees, vector<int> &gateways, vector<bool> &bool_gateways){
    vector<vector<int>> tree_gateways(*max_element(trees.first.begin(), trees.first.end()) + 1);
    for(int i=0; i<trees.first.size(); i++)
        if(bool_gateways[i] && trees.first[i] != IMP)
            tree_gateways[trees.first[i]].push_back(i);
    return tree_gateways;
}

vector<vector<int>> get_cliques_gateways(pair<vector<int>, vector<Clique>> &cliques, vector<int> &gateways, vector<bool> &bool_gateways){
    vector<vector<int>> cliques_gateways(*max_element(cliques.first.begin(), cliques.first.end()) + 1);
    for(int i=0; i<cliques.first.size(); i++)
        if(bool_gateways[i] && cliques.first[i] != IMP)
            cliques_gateways[cliques.first[i]].push_back(i);
    return cliques_gateways;
}

bool old_alg(vector<vector<int>> &graph, int q, vector<vector<int>> &clique_graph){
    vector<bool> clique_only_arts = articulation_points(clique_graph);
    vector<int> clique_art_points;

    for(int i=0; i<clique_only_arts.size(); i++)
        if(clique_only_arts[i])
            clique_art_points.push_back(i);

    if(clique_art_points.size() > 0){
        solve_graph(graph, q);
        return true;
    }
    return false;
}

void solve(vector<vector<int>> &graph, unordered_map<int, unordered_map<int, bool>> &bool_bridges, int q){

    vector<ii> bridges = find_bridges(graph);
    for(ii b: bridges){
        bool_bridges[b.first][b.second] = true;
        bool_bridges[b.second][b.first] = true;
    }

    vector<vector<int>> tree_graph = create_tree_graph(graph, bridges);

    vector<vector<int>> clique_graph = create_clique_graph(graph, bool_bridges);

    if(old_alg(graph, q, clique_graph)) return;

    pair<vector<int>, vector<Tree>> trees = get_trees(tree_graph);

    for(int i=0; i<trees.second.size(); i++)
        trees.second[i].precompute();    

    pair<vector<int>, vector<Clique>>  cliques = get_cliques(clique_graph, bool_bridges);

    vector<int> gateways;
    vector<bool> bool_gateways(graph.size(), false);
    for(int i=0; i<graph.size(); i++)
        if(cliques.first[i] != IMP && trees.first[i] != IMP){
            gateways.push_back(i);
            bool_gateways[i] = true;
        }

    vector<vector<int>> tree_gateways = get_tree_gateways(trees, gateways, bool_gateways);
    vector<vector<int>> clique_gateways = get_cliques_gateways(cliques, gateways, bool_gateways);

    int a, b;
    for(int i=0; i<q; i++){
        fscanf(in, "%d %d", &a, &b);
        fprintf(out, "%d\n", query(graph, trees, cliques, bool_gateways, tree_gateways, clique_gateways, a, b));
    }

}

void cicli(vector<vector<int>> &graph, unordered_map<int, unordered_map<int, bool>> &bool_bridges, int n, int m, int q){
    solve(graph, bool_bridges, q);
}

int main(int argc, char const *argv[]){
    int n, m, q, a, b;
    fscanf(in, "%d %d %d", &n, &m, &q);
    vector<vector<int>> graph(n);
    unordered_map<int, unordered_map<int, bool>> edges;

    for(int i=0; i<m; i++){
        fscanf(in, "%d %d", &a, &b);
        graph[a].push_back(b);
        graph[b].push_back(a);
        edges[a][b] = false;
        edges[b][a] = false;
    }

    cicli(graph, edges, n, m, q);

}