#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int N;
ifstream in("input.txt");
ofstream out("output.txt");

int compare_pair(pair<int,int>, pair<int,int>);
bool contains(pair<int,int>, pair<int,int>);
void print_intervals(vector<pair<int,int>> intervals);
pair<int,int> calcola_output(vector<pair<int,int>>);
int main(int argc, char const *argv[]) {
    in >> N;
    vector<pair<int,int>> intervals;
    int a,b;
    in >> a >> b;
    intervals.push_back(make_pair(a,b));
    for (int i = 0; i < N-1; i++) {
        in >> a >> b;
        pair<int,int> newPair = make_pair(a,b);
        int comp = 1,j;
        for (j = 0; j < intervals.size() && comp != -1; j++) {
            comp = compare_pair(newPair, intervals[j]);
            if(comp == -1)
                intervals.insert(intervals.begin() + j, newPair);
        }
        if(comp == 0)
            intervals[j-1] = newPair;
        if(comp == 1)
            intervals.push_back(newPair);
    }
    print_intervals(intervals);
    pair<int,int> result = calcola_output(intervals);
    if(result.first == 0 && result.second == 0)
        out << "0";
    else
        out << result.first << " " << result.second;
    return 0;
}

bool contains(pair<int,int> pair1, pair<int,int> pair2){
    if(pair1.first <= pair2.first && pair1.second >= pair2.second)
        return true;
    return false;
}

int compare_pair(pair<int,int> pair1, pair<int,int> pair2){
    if(contains(pair1, pair2))
        return 0;
    if(pair1.first < pair2.first)
        return -1;
    return 1;
}

void print_intervals(vector<pair<int,int>> intervals){
    for(pair<int,int> el: intervals)
        std::cout << "(" << el.first << "," << el.second << ") ";
    std::cout << '\n';
}

pair<int,int> calcola_output(vector<pair<int,int>> intervals){
    int largest = 0;
    pair<int,int> output;
    for(int i=0; i<intervals.size()-1; i++){
        if(intervals[i+1].first - intervals[i].second > largest){
            largest = intervals[i+1].first - intervals[i].second;
            output = make_pair(intervals[i].second, intervals[i+1].first);
        }
    }
    return output;
}
