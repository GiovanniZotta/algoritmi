#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;

int main(){
    int n;
    cin >> n;
    unordered_map<string, int> map1;
    unordered_map<string, int> map2;
    for(int i=0; i<n; i++){
        string s;
        cin >> s;
        map1[s]++;
    }
    for(int i=0; i<n; i++){
        string s;
        cin >> s;
        map2[s]++;
    }
    int result = 0;

    for(auto &el: map1)
        result += min(map1[el.first], map2[el.first]);
    cout << result << endl;
}
