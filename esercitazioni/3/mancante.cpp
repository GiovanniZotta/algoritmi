#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
ifstream in("input.txt");
ofstream out("output.txt");

int missing(vector<int> &vect){
    if(vect[vect.size()-1] == vect.size()-1)
        return vect.size();
    else
        return binary_search(vect, 0, vect.size()-1);
}
int binary_search(vector<int> &vect, int start, int end){
    int mid = (end-start)/2;
    if(start == end)
        return start;
    if(vect[mid] == mid)
        return binary_search(vect, mid+1, end);
    else
        return binary_search(vect, start, mid);
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