/*
 * This template is valid both in C and in C++,
 * so you can expand it with code from both languages.
 */

#include <assert.h>
#include <stdio.h>
#include <vector>
using namespace std;

// constraints
#define MAXN 1000000

// input data
int N, i;
int P[MAXN];
int G[MAXN];

pair<int,int> find_next(int N, vector<int>& P, vector<int>& G, int index){
    pair<int,int> result(0,0);
    for(result.second=index; result.second<N; result.second++){
        if(P[result.second] < P[index])
            return result;
        else{
            result.first += G[i];
        }
    }
    return result;
}

int gasoline(int N, vector<int>& P, vector<int>& G){
    pair<int,int> result(0,0);
    while(result.second<N)
        result = find_next(N, P, G, i);
    return result.first;
}

int main() {
  //  uncomment the following lines if you want to read/write from files
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);

  assert(1 == scanf("%d", &N));
  for (i = 0; i < N; i++) assert(1 == scanf("%d", &P[i]));
  for (i = 0; i < N; i++) assert(1 == scanf("%d", &G[i]));

  // insert your code here

  printf("%lld\n", 42LL);  // print the result
  return 0;
}
