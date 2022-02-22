#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

void printDP(vector<long>& DP){
    for(int i=0; i<DP.size(); i++)
        cout << DP[i] << " ";
}

#define MODULO 1000000007

// int progetti(int N, int K) {
//     vector<long> DP(N + 1, 0);
//     DP[0] = DP[1] = 1;
//     for (int i = 2; i <= N; i++)
//         for (int j = 1; j <= K && j <= i; j++)
//             DP[i] += DP[(i - j)] % MODULO;
//     return DP[N] % MODULO;
// }



long progetti(int N, int K) {
    int mod = K + 1, pos = 1, i;
    vector<long> DP(mod + 1, 0);
    DP[0] = DP[1] = 1;
    for (i = 2; i <= N; i++) {
        pos = (pos + 1) % mod;
        DP[pos] = 0;
        for (int j = 1; j <= K && j <= i; j++) {
            DP[pos] += DP[(i - j) % mod];
        }
        DP[pos] %= MODULO;
    }
    return DP[pos];
}


int prova(){
    for(int i=1; i<=10; i++){
        for(int j=1; j<=5 && j <= i;j++){
            cout << "N: " << i << ", K: " << j << ", => " << progetti(i,j) << endl;
        }
        cout << endl;
    }
}

int main(int argc, char const *argv[]){
    cout << progetti(10,4) << endl;
    // cout << progetti3(100,2) << endl;
    // prova();
    return 0;
}
