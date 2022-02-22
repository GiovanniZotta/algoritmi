#include <bits/stdc++.h>
using namespace std;

int reverse(vector<int> &array, int i, int j){
    for(int low = i, high = j; low < high; low++, high--){
        swap(array[low], array[high]);
    }
    return j-i + 1;
} 

long long int reversort(vector<int> &array){
    long long int res = 0;
    for(int i=0; i<array.size()-1; i++){
        int j = min_element(array.begin() + i, array.end()) - array.begin();
        res += reverse(array, i, j);
    }
    return res;
}

void find(vector<int> &sol, int n, int c){
    for(int i=1; i<=n; i++){
        sol.push_back(i);
    }     
}

int main(){
    int tests;
    cin >> tests;
    for(int i=1; i<=tests; i++){
        int n, c;
        cin >> n >> c;
        cout << "Case #" << i << ": ";
        vector<int> sol;
        find(sol, n, c);
        if(sol.size() == 0){
            cout << "IMPOSSIBLE" << endl;
        } else{
            for(int el : sol){
                cout << el << " ";
            }
            cout << endl;
        }
    }
}

