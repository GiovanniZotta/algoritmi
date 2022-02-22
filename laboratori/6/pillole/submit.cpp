#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
ifstream in("input.txt");
ofstream out("output.txt");

long long int pillole(int n){
    vector<vector<long long int>> DP(n+1);
    for(int i=0; i < n+1; i++)
        DP[i].resize((n*2) + 1, 0);

    for(int j=0; j<DP[0].size(); j++)
        DP[0][j] = 1;

    for(int i=1; i < DP.size(); i++)
        for(int m=0; m < DP[i].size(); m++)
            if(m > 0)
                DP[i][m] = DP[i-1][m+1] + DP[i][m-1];
            else
                DP[i][m] = DP[i-1][m+1];

    return DP[n][0];
}

int main(int argc, char const *argv[])
{
    int n;
    in >> n;
    out << pillole(n) << endl;
    return 0;
}
