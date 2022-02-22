#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct piatto{
    int instant;
    int fill;
    int time;
};

vector<int> computePredecessor(vector<int> a, vector<int> b, int n){
    vector<int> pred(n);
    pred[0] = 0;
    for(int i=1; i<n; i++){
        int j = i-1;
        while(j>0 && b[j] > a[i])
            j = j-1;
        pred[i] = j;
    }
    return pred;
}

int main(int argc, char const *argv[])
{
    int dim;
    cin >> dim;
    vector<piatto> piatti;
    for(int i=0; i<dim; i++)
        cin >> piatti[i].instant >> piatti[i].fill >> piatti[i].time;
    vector<int> a,b,c;
    for(int i=0; i<dim; i++){
        a.push_back(piatti[i].instant);
        b.push_back(piatti[i].fill);
        c.push_back(piatti[i].time);
    }
    vector<int> pred = computePredecessor(a,b,dim);

    return 0;
}
