#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ifstream in("input_build_tree.txt");
ofstream out("output.txt");

bool is_valid(int val, vector<int> &nums){
    return !(val < 0 || val >= nums.size());
}

void build_tree(vector<vector<int>> &tree, vector<int> &nums, int start, int end){
    if(start <= end){
        int mid = (end-start)/2;

    }
}

int main(int argc, char const *argv[])
{
    int n;
    in >> n;
    vector<int> nums(n);
    for(int i=0; i<n; i++)
        in >> nums[i];

    vector<vector<int>> tree(n);
    build_tree(tree, nums, 0, nums.size()-1);

    return 0;
}
