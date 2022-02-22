#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N;
ifstream in("input.txt");
ofstream out("output.txt");

void print_intervals(vector<pair<int,int>>);
void output(vector<pair<int,int>>&);
int compare_pair(pair<int,int>, pair<int,int>);
void insert_order(vector<pair<int,int>>&);

int main(int argc, char const *argv[]) {
    in >> N;
    vector<pair<int, int>> intervals;
    // insert_order(intervals);
    for(int i=0;i<N; i++){
        int a,b;
        in >> a >> b;
        pair<int,int> newPair(a,b);
        intervals.push_back(newPair);
    }
    sort(intervals.begin(), intervals.end(), []
        (pair<int,int> pair1, pair<int,int> pair2){
            return pair1.first < pair2.first;
        }
    );
    output(intervals);
    return 0;
}

void insert_order(vector<pair<int,int>>& intervals){
    for(int i=0; i<N; i++){
        // print_intervals(intervals);
        int a,b,j, compare = 0;
        in >> a >> b;
        pair<int,int> newPair(a,b);
        for(j=0; j<intervals.size() && !compare; j++){
            compare = compare_pair(newPair, intervals[j]);
            if(compare && newPair.second > intervals[j-1].second)
                intervals.insert(intervals.begin() + j, newPair);
        }
        if(!compare)
            intervals.push_back(newPair);
    }
}
int compare_pair(pair<int,int> pair1, pair<int,int> pair2){
    return pair1.first < pair2.first;
}

void print_intervals(vector<pair<int,int>> intervals){
    for(pair<int,int> el: intervals)
        std::cout << "(" << el.first << "," << el.second << ") ";
    std::cout << '\n';
}

void output(vector<pair<int,int>>& intervals){
    int largest = 0, max_second=intervals[0].second;
    pair<int,int> output;
    for(int i=0; i<intervals.size()-1; i++){
        max_second = max(max_second, intervals[i].second);
        if(intervals[i+1].first - max_second > largest){
            largest = intervals[i+1].first - max_second;
            output = make_pair(max_second, intervals[i+1].first);
        }
    }
    if(output.first == 0 && output.second == 0)
        out << "0";
    else
        out << output.first << " " << output.second;
}
