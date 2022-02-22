#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

typedef pair<int,int> ii;

bool natale(vector<pair<vector<int>, int>> &tree, int root){
    queue<int> q;
    q.push(root);
    int brilliancy = tree[root].second;
    while(!q.empty()){
        int size = q.size();
        int sum = 0;
        for(int i=0; i<size; i++){
            int current = q.front();
            q.pop();
            sum += tree[current].second;
        }
        if(sum != brilliancy)
            return false;
    }
    return true;
}

int main(int argc, char const *argv[])
{
    int n, m;
    in >> n >> m;
    vector<pair<vector<int>, int>> tree(n);
    for(int i=0; i<m; i++){
        int a, b;
        in >> a >> b;
        tree[a].first.push_back(b);
    }
    for(int i=0; i<n; i++){
        int c;
        in >> c;
        tree[i].second = c;
    }

    out << natale(tree, 0) << endl;
    return 0;
}
