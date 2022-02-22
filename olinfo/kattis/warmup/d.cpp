#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;

int main(){
    int n;
    cin >> n;
    int result=0;
    for(int i=0; i<n; i++){
        int t;
        cin >> t;
        if(t < 0)
            result++;
    }
    cout << result << endl;
}
