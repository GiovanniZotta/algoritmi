#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
ifstream in("input.txt");
ofstream out("output.txt");

int N, C;

int zaino_it(int c, int n, vector<int>&p, vector<int>& v){
    vector<int> r1(c+1, 0);
    vector<int> r2(c+1, 0);

    for(int i=1; i<=n; i++){
        for(int j=1; j<r2.size(); j++)
            if(p[i] <= j)
                r2[j] = max(r1[j - p[i]] + v[i], r1[j]);
            else
                r2[j] = r1[j];
        r1 = r2;
    }
    return r2[c];
}

int main(int argc, char const *argv[])
{
    in >> C >> N;
    vector<int> p(N+1, 0), v(N+1, 0);

    for(int i=1; i< N + 1; i++)
        in >> p[i] >> v[i];

    out << zaino_it(C, N, p, v) << endl;

    return 0;
}
