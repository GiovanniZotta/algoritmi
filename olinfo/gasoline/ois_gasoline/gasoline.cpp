#include <assert.h>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

// constraints
#define MAXN 1000000

// input data
int N, i;
vector<long long> P(MAXN);
vector<long long> G(MAXN);

long long gasoline(int N, vector<long long>& P, vector<long long>& G){
    long long result = 0, last_station = 0, passi=0;
    for(int i=0; i<N; i++){
        if(P[i] < P[last_station]){
            result += passi * P[last_station];
            last_station = i;
            passi = G[i];
        }else
            passi += G[i];
    }
    result += passi * P[last_station];
    return result;
}

int main() {
  //  uncomment the following lines if you want to read/write from files
  ifstream in("input.txt");
  ofstream out("output.txt");

  cin >> N;
  for(int i=0; i<N; i++) cin >> P[i];
  for(int i=0; i<N; i++) cin >> G[i];

  // insert your code here
  cout << gasoline(N, P, G);
  return 0;
}
