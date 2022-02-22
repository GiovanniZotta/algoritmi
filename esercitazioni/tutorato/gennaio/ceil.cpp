#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

int rec(vector<int> &a, int v, int start, int end){
    int mid = (start+end)/2;
    if(a[mid] == v){
        if(a[mid+1] != v)
            return a[mid+1];
        else
            return rec(a, v, mid+1, end);
    }
    if(a[mid] > v)
        return rec(a, v, start, mid-1);
    else{
        if(a[mid+1] > v)
            return a[mid+1];
        else
            return rec(a, v, mid+1, end);
    }
}

int ceil(vector<int> &a, int v){
    if(a[0] > v) return a[0];
    if(a[a.size()-1] <= v) return -1;
    return rec(a, v, 0, a.size()-1);
}

int main(int argc, char const *argv[])
{
    int n, v;
    in >> n >> v;
    vector<int> nums(n);
    for(int i=0; i<n; i++)
        in >> nums[i];
    
    cout << ceil(nums, v) << endl;
    return 0;
}
