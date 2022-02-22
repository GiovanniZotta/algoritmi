#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;


// void print_matrix(vector<vector<int>> &matrix){
//     for(int i=0; i<matrix.size(); i++){
//         for(int j=0; j<matrix[i].size(); j++){
//             out << matrix[i][j];
//         }
//         out << endl;
//     }
// }

// void print_array(vector<int> &array){
//     for(int el : array)
//         out << el << " ";
//     out << endl;
// }

void dfs(vector<vector<int>> &matrix, vector<vector<int>> &visited, int i, int j){
    // cout << "ciaoo, " << "i: " << i << ", j: " << j << endl;
    visited[i][j] = true;
    if(i-1 >= 0)
        if(!visited[i-1][j] && matrix[i-1][j] == 1)
            dfs(matrix, visited, i-1, j);
    if(i+1 < matrix.size())
        if(!visited[i+1][j] && matrix[i+1][j] == 1)
            dfs(matrix, visited, i+1, j);
    if(j-1 >= 0)
        if(!visited[i][j-1] && matrix[i][j-1] == 1)
            dfs(matrix, visited, i, j-1);
    if(j+1 < matrix[i].size())
        if(!visited[i][j+1] && matrix[i][j+1] == 1)
            dfs(matrix, visited, i, j+1);
}

int countcc(vector<vector<int>> &matrix){
    vector<vector<int>> visited(matrix.size());
    for(int i=0; i<matrix.size(); i++){
        visited[i].resize(matrix[i].size(), false);
    }
    int cc = 0;
    for(int i=0; i<matrix.size(); i++){
        for(int j=0; j<matrix[i].size(); j++){
            if(!visited[i][j]){
                if(matrix[i][j] == 1){
                    dfs(matrix, visited, i, j);
                    cc++;
                }else{
                    visited[i][j] = true;
                }
            }
        }
    }
    return cc;
}


int solve(int m, int n){
    //cout << m << " " << n << endl;
    vector<vector<int>> matrix(m);
    for(int i=0; i<m; i++){
        string row;
        cin >> row;
        for(int j=0; j<n; j++){
            if(row[j] == '#')
                matrix[i].push_back(0);
            else    
                matrix[i].push_back(1);
        }
    }
    return countcc(matrix);

}

int main(){
    vector<int> sol;
    int m, n;
    while(cin >> m >> n){
        sol.push_back(solve(m, n));
    }

    for(int i=1; i<=sol.size(); i++){
        cout << "Case " << i << ": " << sol[i-1] << endl;
    }
}

