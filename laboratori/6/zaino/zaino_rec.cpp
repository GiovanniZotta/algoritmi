#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
ifstream in("input.txt");
ofstream out("output.txt");

int N, C;

int zaino(int c, int i, vector<int>& p, vector<int>& v, vector<vector<int>>& DP){
    if(c == 0 || i == 0)
        return 0;
    else if(DP[i][c] == 0)
        if(p[i] <= c)
            DP[i][c] = max( (zaino(c - p[i], i-1, p, v, DP) + v[i]),
                             zaino(c, i-1, p, v, DP) );
        else
            DP[i][c] = zaino(c, i-1, p, v, DP);
    return DP[i][c];
}

int zaino_no_dp(int c, int i, vector<int>& p, vector<int>& v, vector<vector<int>>& DP){
    if(c == 0 || i == 0)
        return 0;
    if(p[i] <= c)
        return max( (   zaino_no_dp(c - p[i], i-1, p, v, DP) + v[i]),
                        zaino_no_dp(c, i-1, p, v, DP) );
    else
        return zaino_no_dp(c, i-1, p, v, DP);
}

int main(int argc, char const *argv[])
{
    in >> C >> N;
    vector<int> p(N+1, 0), v(N+1, 0);
    vector<vector<int>> DP(N+1);

    for(int i=0; i < N+1; i++)
        DP[i].resize(C+1, 0);

    for(int i=1; i< N + 1; i++)
        in >> p[i] >> v[i];

    out << zaino(C, N, p, v, DP) << endl;
    out << zaino_no_dp(C, N, p, v, DP) << endl;
    

    return 0;
}
