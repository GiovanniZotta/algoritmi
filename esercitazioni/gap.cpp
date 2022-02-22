#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

int gap(vector<int> &nums, int start, int end){
    if(start >= end)
        return start;
    int mid = (end-start)/2;
    cout << mid << endl;
    if(nums[mid] < nums[end])
        return gap(nums, mid, end);
    else if(nums[mid] > nums[start])
        return gap(nums, start, mid);
}
int main(int argc, char const *argv[])
{
    int n, tmp;
    in >> n;
    vector<int> nums(n);
    for(int i=0; i<n; i++){
        in >> tmp;
        nums[i] = tmp;
    }
    out << gap(nums, 0, n-1);
    return 0;
}
