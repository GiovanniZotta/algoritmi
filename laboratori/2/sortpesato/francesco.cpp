#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

pair<int,int> sortpesato(vector<int> & nums);


int main(int argc, char const *argv[]) {
    ifstream in("input.txt");
    ofstream out("output.txt");
    int n;
    in >> n;
    vector<int> nums(n+1);
    for (int i = 1; i < n+1; i++)
        in >> nums[i];

    pair<int, int> ret = sortpesato(nums);
    out << ret.first << " " << ret.second;

    return 0;
}

pair<int,int> sortpesato(vector<int> & nums){
    pair<int, int> ret(0,0);
    int pos, sum, m, numsNo;
    for (int i = 1; i < nums.size(); i++) {
        if(nums[i] != -1){
            pos = sum = nums[i];
            numsNo = 1;
            m = nums[i];
            nums[i] = -1;
            while(pos != i){
                sum += nums[pos];
                m = min(m, nums[pos]);
                int tmp = nums[pos];
                nums[pos] = -1;
                pos = tmp;
                numsNo++;
            }
            ret.first += numsNo -1;
            ret.second += min((sum - m + (numsNo - 1) * m),
                          ((m + 1) * 2 + (sum - m) + numsNo -1 ));
        }
    }
    return ret;
}
