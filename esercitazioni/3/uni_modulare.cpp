#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
ifstream in("input.txt");
ofstream out("output.txt");

int binary_search(vector<int> &vect, int start, int end){
    int mid = (end-start)/2;
    if(end-start <=3){
        int result = vect[start];
        while(start<=end)
            result = min(result, vect[start++]);
        return result;
    }
    if(vect[mid-1] > vect[mid] && vect[mid] > vect[mid+1])
        return binary_search(vect, mid, end);
    else if(vect[mid-1] < vect[mid] && vect[mid] < vect[mid+1])
        return binary_search(vect, start, mid);
    else
        return vect[mid];
}

int main(int argc, char const *argv[])
{
    int N;
    in >> N;
    vector<int> vect(N);
    for(int i=0; i<N; i++)
        in >> vect[i];

    out << binary_search(vect, 0, vect.size()-1) << endl;
    return 0;
}
