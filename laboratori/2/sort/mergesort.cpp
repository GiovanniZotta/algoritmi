#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void mergesort(vector<int>&, int, int);
void merge(vector<int>&, int, int, int);
void stampa_vettore(vector<int>&, int, int);

int main(int argc, char const *argv[]) {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int N;
    in >> N;
    vector<int> vect;
    for(int i=0; i<N; i++){
        int a;
        in >> a;
        vect.push_back(a);
    }
    mergesort(vect, 0, N-1);
    for(int i=0; i<N; i++)
        out << vect[i] << " ";
    return 0;
}

void stampa_vettore(vector<int>& vect, int start, int end){
    for (int i = start; i <= end; i++)
        cout << vect[i] << " ";
    cout << '\n';
}

void mergesort(vector<int>& vect, int start, int end){
    int mid = (start+end)/2;
    if(end-start == 0)
        return;
    else if(end-start == 1){
        if(vect[start] > vect[end]){
            int tmp = vect[start];
            vect[start] = vect[end];
            vect[end] = tmp;
        }
    }else{
        mergesort(vect, start, mid);
        mergesort(vect, mid+1, end);
    }
    merge(vect, start, mid, end);
}

void merge(vector<int>& vect, int start, int mid, int end){

    if(end-start == 0)
        return;
    else if(end-start == 1){
        if(vect[start] > vect[end]){
            int tmp = vect[start];
            vect[start] = vect[end];
            vect[end] = tmp;
        }
    }else{
        vector<int> support;
        int i,j;
        for(i=start, j=mid+1; i<=mid && j<=end;){
            if(vect[i] < vect[j])
                support.push_back(vect[i++]);
            else
                support.push_back(vect[j++]);
        }
        while(i<=mid)
            support.push_back(vect[i++]);
        while(j<=end)
            support.push_back(vect[j++]);
        i=0;
        while(start<=end)
            vect[start++] = support[i++];
    }
}
