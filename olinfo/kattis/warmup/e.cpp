#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;

int main(){
    long long int w, n;
    cin >> w >> n;
    long long int area=0;
    for(int i=0; i<n; i++){
        long long int wi, li;
        cin >> wi >> li;
        area += wi*li;
    }
    cout << area/w << endl;
}
