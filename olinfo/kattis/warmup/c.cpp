#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;

int main(){
    unordered_map<int, int> map;
    int n,m;
    cin >> n >> m;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            int sum = i+j;
            map[sum]++;
        }
    }
    int max_number_of_times=0;
    for(auto el: map)
        max_number_of_times = max(max_number_of_times, el.second);

    vector<int> result;
    for(auto el: map)
        if(el.second == max_number_of_times)
            result.push_back(el.first);

    sort(result.begin(), result.end());
    for(int el : result)
        cout << el << endl;
}
