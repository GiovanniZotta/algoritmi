#include <vector>
using namespace std;

int countPaths(vector<vector<int>> &P, int n, int B){
    B = min(B, 10 * (2*n -2));

    int DP[n][n][B];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            for(int k = 0; k < B; k++)
                DP[i][j][k] = 0;

    for(int i = 0; i < B; i++)
        DP[0][0][i] = 1;

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            for(int k = 0; k < B; k++)
                if(k - P[i][j] >= 0){
                    if(i > 0)
                        DP[i][j][k] += DP[i - 1][j][k - P[i][j]];
                    if(j > 0)
                        DP[i][j][k] += DP[i][j - 1][k - P[i][j]];
                }

    return DP[n - 1][n - 1][B - 1];
}