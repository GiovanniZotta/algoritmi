#include <bits/stdc++.h>
using namespace std;

void print_array(vector<string> &array){
    for(string el : array)
        cout << el << " ";
    cout << endl;
}

void top_sort_dfs(unordered_map<string, vector<string>> &graph, unordered_map<string, bool> &visited, string source, stack<string> &sol){
    visited[source] = true;
    for(string adj : graph[source]){
        if(!visited[adj]){
            top_sort_dfs(graph, visited, adj, sol);
        }
    }
    sol.push(source);
}

void top_sort(unordered_map<string, vector<string>> &graph, string source){
    unordered_map<string, bool> visited;
    stack<string> s;
    top_sort_dfs(graph, visited, source, s);
    while(!s.empty()){
        cout << s.top() << endl;
        s.pop();
    }
}


int main(){
    int n;
    string s;
    getline(cin, s);
    istringstream iss(s);
    iss >> n;
    unordered_map<string, vector<string>> graph;
    for(int i=0; i<n; i++){
        string s, filename, rule;
        getline(cin, s);
        istringstream iss(s);
        iss >> filename;
        filename.pop_back();
        // cout << filename << endl;
        while(iss >> rule){
            graph[rule].push_back(filename);
        }
        // print_array(graph[filename]);
    }

    string s1, s2;
    getline(cin, s1);
    istringstream iss2(s1);
    iss2 >> s2;

    top_sort(graph, s2);

    
}
