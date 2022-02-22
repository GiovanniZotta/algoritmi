#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

#define ND -1
#define OUT -1
ifstream in("input.txt");
ofstream out("output.txt");

int lcs(string& s1, string& s2, int i, int j, vector<vector<int>>& DP){
    if(i == OUT || j == OUT)
        return 0;
    if(DP[i][j] == ND)
        if(s1[i] == s2[j])
            DP[i][j] = 1 + lcs(s1, s2, i-1, j-1, DP);
        else
            DP[i][j] = max(lcs(s1, s2, i-1, j, DP), lcs(s1, s2, i, j-1, DP));
    return DP[i][j];
}

int main(int argc, char const *argv[])
{
    string s1, s2;
    in >> s1 >> s2;
    vector<vector<int>> DP(s1.length());
    for(int i=0; i < s1.length(); i++)
        DP[i].resize(s2.length(), ND);
    out << lcs(s1, s2, s1.length()-1, s2.length()-1, DP) << endl;
    return 0;
}
