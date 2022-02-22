#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

int longestChain(vector<int> &x, vector<int> &y, int n){
    int maxSoFar = 0;
    int sum = 0;
    for(int i=0; i<n; i++){
        if(y[i] <= x[i+1])
            sum++;
        else
            sum = 0;
        maxSoFar = max(maxSoFar, sum);
    }
    return maxSoFar;
}

int main(int argc, char const *argv[]){
    int n;
    in >> n;
    vector<int> x(n);
    vector<int> y(n);
    for(int i=0; i<n; i++)
        in >> x[i];
    for(int i=0; i<n; i++)
        in >> y[i];

    cout << longestChain(x, y, 5);
    return 0;
}
