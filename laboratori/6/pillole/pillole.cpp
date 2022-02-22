#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
ifstream in("input.txt");
ofstream out("output.txt");

long long int pillole(int i, int m, vector<vector<int>>& DP){
    if(i == 0)
        return 1;
    else if(m > 0)
        return pillole(i-1, m+1, DP) + pillole(i, m-1, DP);
    else
        return pillole(i-1, m+1, DP);
}

long long int pillole_it(int n, vector<vector<int>>& DP){
    for(int j=0; j<DP[0].size(); j++)
        DP[0][j] = 1;

    // for(int i=0; i< DP.size(); i++){
    //     for(int j=0; j<DP[0].size(); j++)
    //         cout << DP[i][j] << " ";
    //     cout << endl;
    // }

    for(int i=1; i < DP.size(); i++)
        for(int m=0; m < DP[i].size(); m++)
            if(m > 0)
                DP[i][m] = DP[i-1][m+1] + DP[i][m-1];
            else
                DP[i][m] = DP[i-1][m+1];

    // for(int i=0; i< DP.size(); i++){
    //     for(int j=0; j<DP[0].size(); j++)
    //         cout << DP[i][j] << " ";
    //     cout << endl;
    // }

    return DP[n][0];

}

int main(int argc, char const *argv[])
{
    int n;
    in >> n;
    vector<vector<int>> DP(n+1);
    for(int i=0; i < n+1; i++)
        DP[i].resize((n*2) + 1, 0);
    out << pillole_it(n, DP) << endl;
    return 0;
}
