#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int main(int argc, char const *argv[]){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    int res = INT_MAX;
    for(int i=0; i<N; i++){
        int a,b;
        cin >> a >> b;
        res = min(res, b/a);
    }
    cout << res << endl;
    return 0;
}