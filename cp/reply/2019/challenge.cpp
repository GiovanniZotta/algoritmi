#include <bits/stdc++.h>
using namespace std;

#define WALL -1
#define WATER 800
#define JAM 200
#define DIRT 150
#define RAILCROSS 120
#define TERRAIN 100
#define HIGHWAY 70
#define RAILWAY 50
#define NONE -1
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef long long int lli;
ii NONE_PAIR = {NONE, NONE};
int W, H, C, R;

unordered_map<char, int> terrain_m = {
    {'#', 0},
    {'~', 1},
    {'*', 2},
    {'+', 3},
    {'X', 4},
    {'_', 5},
    {'H', 6},
    {'T', 7}
};
unordered_map<int, char> debug = {
    {WALL, '#'},
    {WATER, '~'},
    {JAM, '*'},
    {DIRT, '+'},
    {RAILCROSS, 'X'},
    {TERRAIN, '_'},
    {HIGHWAY, 'H'},
    {RAILWAY, 'T'}
};
vi terrain_cost = {WALL, WATER, JAM, DIRT, RAILCROSS, TERRAIN, HIGHWAY, RAILWAY};
int bonus_reward = 0;
int best_reward = 0;
int total_score = 0;
int local_score = 0;
struct Customer{
    ii pos;
    int reward;
};

struct Component{
    vector<ii> nodes;
    int customers;
    int customer_score;
    double average_distance;
};

struct Office{
    ii pos;
    vector<string> paths;
    int score;
};

struct Pq_node{
    ii current;
    ii parent;
    int cost;
};

struct cmp{
    bool operator()(Pq_node &a, Pq_node &b){
        return a.cost > b.cost;
    }
};

vector<Customer> customers;
vector<Component> components;
vector<vi> m;
vector<vector<bool>> is_customer;
vector<vector<bool>> used;
vector<vector<int>> customer_score;
vector<vector<double>> centrality;

double compute_distance(ii &c1, ii &c2){
    double x = c1.first - c2.first;
    double y = c1.second - c2.second;
    return sqrt(x * x + y * y);
}

double get_total_distance(Component &component, ii &cell){
    double distance = 0;
    // cerr << "ciaoo" << endl;
    for(ii &target : component.nodes){
        if(target != cell){
            distance += compute_distance(cell, target);
        }
    }
    return distance;
}


void compute_centrality(){
    centrality.resize(m.size());
    for(int i=0; i<m.size(); i++){
        centrality[i].resize(m[i].size());
        for(int j=0; j<m[i].size(); j++){
            centrality[i][j] = DBL_MAX;
        }
    }
    int progress = 0;
    for(Component &c : components){
        if(c.customers > 0){
            double total_component_distance = 0;
            for(ii &cell : c.nodes){
                if(progress % 1000 == 0)
                    cerr << progress/1000 << "/" << c.nodes.size()/1000 << " ";
                progress++;
                double cell_centrality = get_total_distance(c, cell) / c.nodes.size();
                centrality[cell.first][cell.second] = cell_centrality;
                total_component_distance += cell_centrality;
            }
            c.average_distance = total_component_distance / c.nodes.size();
        }
    }
    cerr << endl;
}


void print_component(Component &c){
    for(ii node : c.nodes)
        cerr << node.first << ", " << node.second << endl;
    cerr << endl;
}

void print_is_customer(){
    cerr << "=============================================" << endl;
    for(int i=0; i<is_customer.size(); i++){
        for(int j=0; j<is_customer[i].size(); j++){
            if(is_customer[i][j])
                cerr << "X";
            else
                cerr << "#";
        }
        cerr << endl;
    }
    cerr << "=============================================" << endl;
}

void read_customers(){
    is_customer.resize(H+2);
    customer_score.resize(H+2);
    for(int i=0; i<H+2; i++){
        is_customer[i].resize(W+2);
        customer_score[i].resize(W+2);
        for(int j=0; j<W+2; j++){
            is_customer[i][j] = false;
            customer_score[i][j] = 0;
        }
    }
    // print_is_customer();
    customers.resize(C);
    int x, y, r;
    for(int i=0; i<C; i++){
        cin >> x >> y >> r;
        // cerr << x+1 << " " << y+1 << endl;
        is_customer[y+1][x+1] = true;
        customer_score[y+1][x+1] = r;
        customers[i].pos = {y+1, x+1};
        customers[i].reward = r;
        best_reward = max(best_reward, r);
        bonus_reward += r;
    }

}

void print_customers(){
    for(Customer c : customers){
        cerr << "X: " << c.pos.first << ", Y: " << c.pos.second << ", reward: " << c.reward << endl;
    }
}

void read_m(){
    m.resize(H+2);
    for(int i=0; i<H+2; i++){
        m[i].resize(W+2);
        if(i == 0 || i == H+1){
            for(int j=0; j<W+2; j++)
                m[i][j] = WALL;
        }else{
            string tmp;
            cin >> tmp;
            for(int j=0; j<W+2; j++){
                if(j == 0 || j == W+1){
                    m[i][j] = WALL;
                }else{
                    m[i][j] = terrain_cost[terrain_m[tmp[j-1]]];
                    // cerr << terrain_cost[terrain_m[tmp[j-1]]] << endl;
                    // m[i][j] = terrain_m[tmp[j-1]];
                }
            }
        }
    }
    // m.resize(W+2);
    // for(int i=0; i<W+2; i++){
    //     m[i].resize(H+2);
    //     if(i == 0 || i == W+2){
    //         for(int j=0; j<H+2; j++)
    //             m[i][j] = WALL;
    //     }else{
    //         string tmp;
    //         cin >> tmp;
    //         for(int j=0; j<H+2; j++){
    //             if(j == 0 || j == H+1){
    //                 m[i][j] = WALL;
    //             }else{
    //                 m[i][j] = terrain_cost[terrain_m[tmp[j-1]]];
    //             }
    //         }
    //     }

    // }
}



void print_m(){
    cerr << " ============ BEGIN MAP ============ " << endl;
    for(int i=0; i<m.size(); i++){
        for(int j=0; j<m[i].size(); j++){
            if(is_customer[i][j])
                cerr << "X";
            else
                cerr << debug[m[i][j]];
        }
        cerr << endl;
    }
    cerr << " ============ END MAP ============ " << endl;

}

void print_visited(vector<vector<bool>> &visited){
    cerr << " ============ BEGIN VISITED ============ " << endl;
    for(int i=0; i<visited.size(); i++){
        for(int j=0; j<visited[i].size(); j++){
            cerr << (visited[i][j] ? "X" : "O");
        }
        cerr << endl;
    }
    cerr << " ============ END VISITED ============ " << endl;
}

vector<ii> neighbours(ii cell){
    return  {
                {cell.first, cell.second - 1},
                {cell.first, cell.second + 1},
                {cell.first + 1, cell.second},
                {cell.first - 1, cell.second}
            };
}

void component_dfs(Component &component, vector<vector<bool>> &visited, ii cell){
    queue<ii> q;
    q.push(cell);
    while(!q.empty()){
        ii current = q.front(); q.pop();
        int x = current.first;
        int y = current.second;
        if(!visited[x][y]){
            visited[x][y] = true;
            component.nodes.push_back({x, y});
            if(is_customer[x][y]){
                component.customers++;
                component.customer_score += customer_score[x][y];
            }

            for(ii neighbour : neighbours(current)){
                if(m[neighbour.first][neighbour.second] != WALL){
                    if(!visited[neighbour.first][neighbour.second]){
                        q.push(neighbour);
                    }
                }
            }
        }
    }
}

Component find_component(vector<vector<bool>> &visited, ii cell){
    Component component;
    component.customers = 0;
    component.customer_score = 0;
    component_dfs(component, visited, cell);
    return component;
}

void find_components(){
    vector<vector<bool>> visited(m.size());
    for(int i=0; i<m.size(); i++){
        visited[i].resize(m[i].size());
        for(int j=0; j<m[i].size(); j++){
            visited[i][j] = false;
        }
    }
    for(int i=0; i<m.size(); i++){
        for(int j=0; j<m[i].size(); j++){
            if(m[i][j] != WALL){
                if(!visited[i][j]){
                    components.push_back(find_component(visited, {i, j}));
                }
            }
        }
    }
}

char get_direction(ii from, ii to){
    if(from.first + 1 == to.first)
        return 'D';
    if(from.first - 1 == to.first)
        return 'U';
    if(from.second + 1 == to.second)
        return 'R';
    if(from.second - 1 == to.second)
        return 'L';
}

void dfs_spt(Office &o,vector<vector<bool>> &visited, vector<vector<vector<ii>>> &spt, ii source, vector<vector<int>> &distances, string &path, int thresh){
    int x = source.first;
    int y = source.second;
    visited[x][y] = true;
    // cerr << "in node " << source.first << ", " << source.second << endl;
    for(ii adj : spt[x][y]){
        if(m[adj.first][adj.second] != WALL && !visited[adj.first][adj.second]){
            visited[adj.first][adj.second] = true;
            path.push_back(get_direction({x,y}, adj));
            // cerr << "added " << get_direction({x,y}, adj) << " to path to get from " << "(" << x << ", " << y << ") to (" << adj.first << ", " << adj.second << ")" << endl;
            if(is_customer[adj.first][adj.second]){
                // cerr << "customer score: " << customer_score[adj.first][adj.second] << endl;
                // cerr << ", distance: " << distances[adj.first][adj.second] << endl;
                int score = customer_score[adj.first][adj.second] - distances[adj.first][adj.second];
                // cerr << "customer score: " << customer_score[adj.first][adj.second] << ", distance: " << distances[adj.first][adj.second] << ", score: " << score << endl;
                // cerr << "customer! adding path " << path << endl;
                if(score > thresh){
                    string x = path;
                    o.paths.push_back(x);
                    o.score += score;
                }
            }else{
                dfs_spt(o, visited, spt, adj, distances, path, thresh);
            }
            path.pop_back();
        }
    }
    // cerr << "end dfs of node " << source.first << ", " << source.second << endl;
}

void prepare_dfs_spt(Office &o, vector<vector<vector<ii>>> &spt, ii source, vector<vector<int>> &distances, string &path, int thresh){
    static vector<vector<bool>> visited(m.size());
    for(int i=0; i<m.size(); i++){
        visited[i].resize(m[i].size());
        for(int j=0; j<m[i].size(); j++){
            visited[i][j] = false;
        }
    }
    dfs_spt(o, visited, spt, source, distances, path, thresh);
}

Office compute_paths(ii cell, int thresh, bool bounded){
    static Office o;
    o.score = 0;
    o.pos = cell;
    o.paths.clear();
    static vector<vector<bool>> visited(m.size());
    static vector<vector<int>> distances(m.size());
    static vector<vector<vector<ii>>> spt(m.size());
    for(int i=0; i<m.size(); i++){
        visited[i].resize(m[i].size());
        distances[i].resize(m[i].size());
        spt[i].resize(m[i].size());
        for(int j=0; j<m[i].size(); j++){
            visited[i][j] = false;
            distances[i][j] = INT_MAX;
            spt[i][j].clear();
        }
    }
    // print_m();
    // print_visited(visited);
    // cerr << "starting dijkstra" << endl;
    distances[cell.first][cell.second] = 0;
    priority_queue<Pq_node, vector<Pq_node>, cmp> q;
    Pq_node to_push;
    to_push.current = cell;
    to_push.cost = 0;
    to_push.parent = NONE_PAIR;
    q.push(to_push);
    while(!q.empty()){
        Pq_node q_node = q.top(); q.pop();
        ii current = q_node.current;
        ii parent = q_node.parent;
        int cost = q_node.cost;
        // cerr << "parent " << parent.first << ", " << parent.second << endl;
        // cerr << "cost " << cost << endl;
        if(distances[current.first][current.second] == cost && parent != NONE_PAIR){
            // cerr << "current " << current.first << ", " << current.second << " can be reached with dist " << cost << endl;
            spt[parent.first][parent.second].push_back(current);
        }
        if(!visited[current.first][current.second]){
            visited[current.first][current.second] = true;
            for(ii neigh : neighbours(current)){
                // cerr << "neigh: " << neigh.first << ", " << neigh.second << endl;
                if(m[neigh.first][neigh.second] != WALL){
                    if(!visited[neigh.first][neigh.second]){
                        // cerr << "hi " << endl;
                        int new_dist = distances[current.first][current.second] + m[neigh.first][neigh.second];
                        int bound = (bounded ? best_reward : INT_MAX);
                        // cerr << "bound: " << bound << " ";
                        if(new_dist <= distances[neigh.first][neigh.second] && new_dist < bound){
                            distances[neigh.first][neigh.second] = new_dist;
                            Pq_node p;
                            p.current = neigh;
                            p.cost = new_dist;
                            p.parent = current;
                            q.push(p);
                        }
                    }
                }
            }
        }
    }
    // cerr << "spt done" << endl;
    string path = "";
    prepare_dfs_spt(o, spt, cell, distances, path, thresh);

    return o;
}

vector<Office> place_offices(Component &component, int offices_to_place){
    used.resize(m.size());
    for(int i=0; i<m.size(); i++){
        used[i].resize(m[i].size(), false);
    }
    vector<Office> offices;
    local_score = 0;
    for(int i=0; i<offices_to_place; i++){
        ii cell;
        Office o;
        o.score = 0;
        for(int tries=0; tries < 100; tries++){
            if(tries%10 == 0)
                cerr << tries/10 << " ";
            int node = rand() % component.nodes.size();
            cell = component.nodes[node];
            while(is_customer[cell.first][cell.second] || used[cell.first][cell.second]){
                node = rand() % component.nodes.size();
                cell = component.nodes[node];
            }
            Office tmp = compute_paths(cell, 0, true);
            if(tmp.score > o.score){
                o = tmp;
            }
        }
        // cell = {7,5};
        // cerr << "office placed in " << cell.first << ", " << cell.second << endl;
        offices.push_back(o);
        total_score += o.score;
        used[o.pos.first][o.pos.second] = true;
        cerr << i+1 << " out of " << offices_to_place << " placed" << endl;
    }

    for(Office &o : offices){
        // cerr << "paths: " << o.paths.size() << endl;
        if(o.paths.size() > 0){
            for(string &path : o.paths){
                cout << o.pos.second - 1 << " " << o.pos.first - 1 << " " << path << endl;
            }
        }
    }
    return offices;
}

void find_sol(){
    find_components();
    cerr << "there are " << components.size() << " components" << endl;
    for(Component &c : components){
        // print_component(c);
        if(c.customers > 0){
            int ratio = (int)((double)(100.0 *c.customers / C));
            cerr << "size: " << c.nodes.size() << ", customers: " << c.customers << ", offices to place: " << max((R * ratio) / 100, 1) << endl;
            cerr << "customer_score: " << c.customer_score << ", rate: " << ((double)(100.0 *c.customer_score / bonus_reward)) << endl;
            place_offices(c, max((R * ratio) / 100, 1));
        }
    }
}

void alternative_sol(){
    find_components();
    compute_centrality();
    vector<Office> offices;
    for(Component &c : components){
        if(c.customers > 0){
            cerr << "COMPONENT AVERAGE DISTANCE: " << c.average_distance << endl;
            int count = 0;
            for(ii node : c.nodes){
                // cerr << centrality[node.first][node.second]*2 << " ";
                // cerr << !is_customer[node.first][node.second] << " ";
                // cerr << m[node.first][node.second] << endl;
                if(centrality[node.first][node.second]*(0.0) < c.average_distance && !is_customer[node.first][node.second] && m[node.first][node.second] != WATER){
                    count++;
                }
            }
            cerr << count << " nodes will be considered out of " << c.nodes.size() << endl;
        }
    }
    for(Component &c : components){
        if(c.customers > 0){
            cerr << "COMPONENT AVERAGE DISTANCE: " << c.average_distance << endl;
            int count = 0;
            for(ii node : c.nodes){
                // cerr << centrality[node.first][node.second]*2 << " ";
                // cerr << !is_customer[node.first][node.second] << " ";
                // cerr << m[node.first][node.second] << endl;
                if(centrality[node.first][node.second]*(0.0) < c.average_distance && !is_customer[node.first][node.second] && m[node.first][node.second] != WATER){
                    if(count % 100 == 0)
                        cerr << count << " ";
                    count++;
                    Office tmp = compute_paths(node, 0, true);
                    // cerr << tmp.score << ", ";
                    offices.push_back(tmp);
                }
            }
            cerr << count << " nodes were considered out of " << c.nodes.size() << endl;
        }
    }

    // for(int i=0; i<m.size(); i++){
    //     cerr << i+1 << "/" << m.size() << "   ";
    //     for(int j=0; j<m[i].size(); j++){
    //         if(m[i][j] != WALL && m[i][j] != WATER && !is_customer[i][j]){
    //             Office tmp = compute_paths({i, j}, 0, true);
    //             // cerr << tmp.score << ", ";
    //             offices.push_back(tmp);
    //         }
    //     }
    // }
    sort(offices.begin(), offices.end(), [] (Office &o1, Office &o2){
        return o1.score > o2.score;
    });
    cerr << endl;
    for(int i=0; i<R; i++){
        // cerr << offices[i].score << ", (" << offices[i].pos.second -1 << ", " << offices[i].pos.first -1 << ")" << endl;
        if(offices[i].paths.size() > 0){
            // cerr << offices[i].score << ", (" << offices[i].pos.second -1 << ", " << offices[i].pos.first -1 << ")" << endl;
            total_score += offices[i].score;
            for(string &path : offices[i].paths){
                cout << offices[i].pos.second - 1 << " " << offices[i].pos.first - 1 << " " << path << endl;
            }
        }
    }
}

int main(int argc, char* argv[]){
    srand(atoi(argv[1]));
    cin >> W >> H >> C >> R;
    read_customers();
    // print_customers();
    read_m();
    // print_m();
    // print_is_customer();
    // find_sol();
    alternative_sol();
    cerr << "TOTAL SCORE: " << total_score << endl;
    cerr << "BONUS REWARD WOULD BE " << bonus_reward << endl;
    return 0;
}
