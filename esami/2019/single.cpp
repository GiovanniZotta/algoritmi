#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ifstream in("inputsingle.txt");

int single_rec(vector<int> &nums, int start, int end){
    if(start == end)
        return nums[start];
    int mid = (start+end)/2;
    cout << mid << endl;
    if(mid % 2 == 0)
        return single_rec(nums, mid, end);
    else
        return single_rec(nums, start, mid);

}

int single(vector<int> nums, int n){
    return single_rec(nums, 1, n);
}

int main(int argc, char const *argv[])
{
    int n;
    in >> n;
    vector<int> nums(n+1);
    for(int i=1; i<=n; i++)
        in >> nums[i];

    cout << single(nums, n);
    return 0;
}
