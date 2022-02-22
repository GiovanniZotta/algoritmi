#include <bits/stdc++.h>
using namespace std;

unordered_map<string, int> name2int;
unordered_map<int, string> int2name;

struct customer{
    unordered_set<int> like;
    unordered_set<int> dislike;
};

struct node{
    vector<int> adj;
    int degree;
};

typedef pair<int, int> ii;
int c, l, d, id=0, best_so_far = 0;
string s;
vector<customer> customers;
vector<node> graph;
vector<int> candidates;

void input(){
    cin >> c;
    customers.resize(c);
    for(int i=0; i<c; i++){
        cin >> l;
        for(int j=0; j<l; j++){
            cin >> s;
            if(name2int.find(s) == name2int.end()){
                int2name[id] = s;
                name2int[s] = id++;
            }
            customers[i].like.insert(name2int[s]);
        }
        cin >> d;
        for(int j=0; j<d; j++){
            cin >> s;
            if(name2int.find(s) == name2int.end()){
                int2name[id] = s;
                name2int[s] = id++;
            }
            customers[i].dislike.insert(name2int[s]);
        }
    }
}

bool conflict(int u, int v){
    for(int dislike : customers[u].dislike){
        if(customers[v].like.find(dislike) != customers[v].like.end()){
            return true;
        }
    }
    for(int dislike : customers[v].dislike){
        if(customers[u].like.find(dislike) != customers[u].like.end()){
            return true;
        }
    }
    return false;
}

void build_graph(){
    graph.resize(c);
    for(int i=0; i<c; i++){
        for(int j=i+1; j<c; j++){
            if(conflict(i, j)){
                graph[i].adj.push_back(j);
                graph[j].adj.push_back(i);
            }
        }
    }
}

void print_graph_size(){
    cerr << "nodes: " << graph.size() << endl;
    long long int edges = 0;
    for(int i=0; i<graph.size(); i++){
        edges += graph[i].adj.size();
    }
    cerr << "edges: " << edges << endl;
}

void print_graph_file(){
    int edges = 0;
    for(int i=0; i<graph.size(); i++){
        edges += graph[i].adj.size();
    }
    cout << graph.size() << " " << edges/2 << endl;
    for(int i=0; i<c; i++){
        for(int adj : graph[i].adj){
            if(i < adj){
                cout << i << " " << adj << endl;
            }
        }
    }
}

void prepare_solution(){
    for(int i=0; i<c; i++){
        graph[i].degree = graph[i].adj.size();
    }
}

void print_solution(vector<bool> &chosen){
    unordered_set<string> ings;
    for(int cus=0; cus<c; cus++){
        if(chosen[cus]){
            for(int ingredient: customers[cus].like){
                ings.insert(int2name[ingredient]);
            }
        }
    }

    cout << ings.size() << " ";
    for(string s: ings){
        cout << s << " ";
    }
    cout << endl;
}

int get_candidate(vector<bool> &forbidden){
    int min_so_far = c, min_index=-1;
    for(int i=0; i<c; i++){
        if((graph[i].degree) + (rand() % 5) < min_so_far && !forbidden[i]){
            min_so_far = graph[i].degree;
            min_index = i;
        }
    }
    return min_index;
}


ii get_swap(vector<bool> &chosen){
    int target = 0, best_swap = 0;
    for(int i=0; i<c; i++){
        unordered_set<int> freed_neighs;
        if(chosen[i]){
            for(int adj : graph[i].adj){
                bool would_be_free = true;
                for(int adj2 : graph[adj].adj){
                    if(adj2 != i && chosen[adj2]){
                        would_be_free = false;
                        break;
                    }
                }
                if(would_be_free)
                    freed_neighs.insert(adj);
            }
        }
        if(freed_neighs.size() > best_swap && (rand() % 100) < 30){
            best_swap = freed_neighs.size();
            target = i;
        }
    }

    return {target, best_swap};
}

int build_forbidden(vector<bool> &chosen, vector<bool> &forbidden){
    int forbidden_n = 0;
    for(int i=0; i<c; i++){
        if(chosen[i]){
            forbidden[i] = true;
            forbidden_n++;
            for(int adj : graph[i].adj){
                if(!forbidden[adj]){
                    forbidden_n++;
                    forbidden[adj] = true;
                }
            }
        }
    }
    return forbidden_n;
}

void improve_sol(vector<bool> &chosen, int iter){
    for(int i=0; i<iter*10000; i++){
        if(i%5000 == 0) cerr << i << " ";
        prepare_solution();
        vector<bool> forbidden(c, false);
        ii swap = get_swap(chosen); 
        int remove = swap.first;
        int freed = swap.second;
        chosen[remove] = false;
        int forbidden_n = build_forbidden(chosen, forbidden);
        //cerr << "best_swap is " << remove << " which frees " << freed << ". Expected forbidden_n: " << c - freed - 1 << ", forbidden_n: " << forbidden_n << endl;
        while(forbidden_n < c){
            int can = get_candidate(forbidden);
            if((rand() % 100) < 95 && can != -1){
                chosen[can] = true;
                forbidden[can] = true;
                forbidden_n++;
                for(int adj : graph[can].adj){
                    if(!forbidden[adj]){
                        forbidden_n++;
                        forbidden[adj] = true;
                        for(int adj2 : graph[adj].adj){
                            graph[adj2].degree--;
                        }
                    }
                }
            }
        }
        int chosen_n = 0;
        for(int i=0; i<c; i++){
            chosen_n += chosen[i];
        }

        if(chosen_n > best_so_far){
            best_so_far = chosen_n;
            cerr << "new solution: " << best_so_far << endl;
            print_solution(chosen);
        }
    }
    cerr << "trying out different sol" << endl;
}

void build_solution(){
    int iter=0;
    while(true){
        prepare_solution();
        vector<bool> forbidden(c, false);
        vector<bool> chosen(c, false);
        int forbidden_n = 0;
        while(forbidden_n < c){
            int can = get_candidate(forbidden);
            if((rand() % 100) < 95 && can != -1){
                chosen[can] = true;
                forbidden[can] = true;
                forbidden_n++;
                for(int adj : graph[can].adj){
                    if(!forbidden[adj]){
                        forbidden_n++;
                        forbidden[adj] = true;
                        for(int adj2 : graph[adj].adj){
                            graph[adj2].degree--;
                        }
                    }
                }
            }
        }
        
        int chosen_n = 0;
        for(int i=0; i<c; i++){
            chosen_n += chosen[i];
        }

        if(chosen_n > best_so_far){
            best_so_far = chosen_n;
            cerr << "new solution: " << best_so_far << endl;
            print_solution(chosen);
            improve_sol(chosen, ++iter);
        }
    }
    
}

int main(){
    input(); 
    build_graph();
    //print_graph();
    print_graph_size();
    //print_graph_file();

    build_solution();

}
