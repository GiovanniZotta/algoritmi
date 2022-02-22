#include <bits/stdc++.h>
using namespace std;

int sum_array(vector<int> &numbers, int to_avoid){
    int sum = 0;
    for(int i=0; i<numbers.size(); i++)
        if(i != to_avoid)
            sum += numbers[i];

    return sum;
}

int solve(vector<int> &numbers){
    for(int i=0; i<numbers.size(); i++)
        if(sum_array(numbers, i) == numbers[i])
            return numbers[i];
}

int main(){
    string s;
    while(getline(cin, s)){
        int n;
        vector<int> numbers;
        istringstream iss(s);
        while(iss >> n){
            numbers.push_back(n);
        }
        cout << solve(numbers) << endl;
    }
    
}
