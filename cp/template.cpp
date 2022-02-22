#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

int main(int argc, char const *argv[]){

    return 0;
}


int progetti(int N, int K){
    vector<vector<int>> DP(N+1, vector<int>(K+1,-1));
    compute(N,K, DP);
    return DP[N][K];
}

int compute(int N, int K, vector<vector<int>>& DP){
    if(DP[N][K] != -1)
        return DP[N][K];
    for(int i=1; i<K; i++){
        
    }
}

