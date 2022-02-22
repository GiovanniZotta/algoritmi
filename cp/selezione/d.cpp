#include <bits/stdc++.h>
using namespace std;






typedef unordered_map<string, vector<string>> mapgraph;

bool dfs(mapgraph &graph, unordered_map<string, bool> &ingredients, unordered_map<string, bool> &visited, bool previous_color, string source){
    visited[source] = true;
    ingredients[source] = !previous_color;
    for(auto &adj : graph[source]){
        if(!visited[adj]){
            if(!dfs(graph, ingredients, visited, !previous_color, adj)){
                return false;
            }
        }else if(ingredients[adj] == ingredients[source]){
            return false;
        }
    }
    return true;
}

bool is_bipartite(mapgraph &graph, unordered_map<string, bool> &ingredients){
    unordered_map<string, bool> visited;
    for(auto &node : graph){
        if(!visited[node.first]){
            if(!dfs(graph, ingredients, visited, false, node.first)){
                return false;
            }
        }
    }
    return true;
}

void print_array(vector<string> &array){
    for(string el : array)
        cout << el << " ";
    cout << endl;
}

void print_graph(mapgraph &graph){
    for(auto node : graph){
        cout << node.first << ": ";
        for(string adj : node.second){
            cout << adj << " ";
        }
        cout << endl;
    }
}


int main(){
    int n;
    string s;
    getline(cin, s);
    istringstream iss1(s);
    iss1 >> n;
    unordered_map<string, vector<string>> graph;
    unordered_map<string, bool> ingredients;
    for(int i=0; i<n; i++){
        string s, ingredient;
        getline(cin, s);
        istringstream iss(s);
        iss >> ingredient;
        ingredients[ingredient] = false;
    }

    int e;
    getline(cin, s);
    istringstream iss2(s);
    iss2 >> e;
    for(int i=0; i<e; i++){
        string from, to;
        getline(cin, s);
        istringstream iss3(s);
        iss3 >> from >> to;
        graph[from].push_back(to);
        graph[to].push_back(from);
    }

    if(!is_bipartite(graph, ingredients)){
        cout << "impossible" << endl;
    }else{
        for(auto el : ingredients){
            if(el.second == true)
                cout << el.first << " ";
        }
        cout << endl;
        for(auto el : ingredients){
            if(el.second == false)
                cout << el.first << " ";
        }
        cout << endl;
    }

}