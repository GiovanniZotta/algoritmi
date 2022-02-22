#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[])
{
    int K,N, p, tot=0;
    cin >> N >> K;
    vector<int> v(N);

    for(int n=0; n<N; n++)
        cin >> v[n];
    sort(v.begin(), v.end());
    for(int i=0; i<K; i++)
        tot+=v[N-i-1];
    cout << tot;
    return 0;
}