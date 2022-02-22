#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;

struct cmp{
    bool operator()(ii a, ii b){
        return a.second < b.second;
    }
};

void print_array(vector<int> &array){
    cout << "ARRAY" << endl;
    for(int el : array)
        cout << el << " ";
    cout << endl;
    cout << "END ARRAY" << endl;
}

int main(){
    int n = 0, b = 0;
    vector<int> results;
    while(n != -1 && b != -1){
        cin >> n >> b;
        if(n == -1 || b == -1)
            break;
        priority_queue<ii, vector<ii>, cmp> q;

        vector<int> cities(n);
        vector<int> assigned_boxes(n, 0);
        for(int i=0; i<n; i++){
            cin >> cities[i];
            q.push(make_pair(i, cities[i]));
            assigned_boxes[i]++;
        }

        for(int i=0; i<b-n; i++){
            ii city = q.top(); q.pop();
            int city_index = city.first;
            assigned_boxes[city_index]++;
            int people_per_box = cities[city_index] / assigned_boxes[city_index];
            if(cities[city_index] % assigned_boxes[city_index] != 0)
                people_per_box++;
            q.push(make_pair(city_index, people_per_box));
        }
        ii result = q.top();
        results.push_back(result.second);
    }
    for(int el : results){
        cout << el << endl;
    }
}
