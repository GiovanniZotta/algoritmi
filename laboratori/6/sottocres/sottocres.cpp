#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
ifstream in("input.txt");
ofstream out("output.txt");

typedef pair<long long int, int> ii;

long long int sottocres(vector<int>& nums){
    vector<ii> DP(nums.size());
    for(int i=0; i<nums.size(); i++)
        DP[i] = make_pair(0, nums[i]);

    DP[0].first = nums[0];

    for(int i=1; i<DP.size(); i++){
        long long int best = 0;
        for(int j=0; j < i; j++)
            if(DP[j].second <= DP[i].second)
                best = max(best, DP[j].first);
        DP[i].first = nums[i] + best;
    }

    long long int ret = 0;
    for(ii el : DP)
        ret = max(ret, el.first);

    return ret;
}

int main(int argc, char const *argv[])
{
    int n;
    in >> n;
    vector<int> nums(n);
    for(int i=0; i<n; i++)
        in >> nums[i];
    
    out << sottocres(nums) << endl;
    return 0;
}
