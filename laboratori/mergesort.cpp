#include <vector>
#include <fstream>
#include <iostream>

using namespace std;
ifstream in("media.txt");
ofstream out("output.txt");

void merge(vector<int> &vect, int start, int end){
    vector<int> tmp;
    int mid = (start+end)/2;
    int i = start, j = mid+1;

    while(i <= mid && j <= end)
        if(vect[i] < vect[j])
            tmp.push_back(vect[i++]);
        else
            tmp.push_back(vect[j++]);
    
    while(i <= mid)
        tmp.push_back(vect[i++]);
        
    while(j <= end)
        tmp.push_back(vect[j++]);

    for(int i = start; i <= end; i++)
        vect[i] = tmp[i - start];
    return;
}

void mergesort(vector<int> &vect, int i, int j){
    if(i >= j)
        return;
    else{
        int mid = (i+j)/2;
        mergesort(vect, i, mid);
        mergesort(vect, mid+1, j);
        merge(vect, i, j);
    }
}


int main(int argc, char const *argv[]){
    
    int n;
    in >> n;
    vector<int> vect(n);
    for(int i=0; i<n; i++)
        in >> vect[i];

    mergesort(vect, 0, vect.size() -1);

    for(int i=0; i<n; i++)
        out << vect[i] << " ";
    out << endl;
    return 0;
}
