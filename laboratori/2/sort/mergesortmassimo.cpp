#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

vector<int> mergesort(vector<int>);
vector<int> merge(vector<int> vect1, vector<int> vect2);
vector<int> slice(vector<int>, int, int);

int main(int argc, char const *argv[]) {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int dim;
    in >> dim;
    vector<int> vect(dim,0);
    for (int i = 0; i < dim; i++)
        in >> vect[i];
    vector<int> res = mergesort(vect);
    for (int i = 0; i < dim; i++)
        out << res[i] << " ";
    return 0;
}

vector<int> mergesort(vector<int> vect){
    return (vect.size()>1)?merge(mergesort(slice(vect, 0, vect.size()/2)), mergesort(slice(vect, vect.size()/2, vect.size()))):vect;
}

vector<int> merge(vector<int> vect1, vector<int> vect2){
    int i = 0, j = 0;
    vector<int> res;
    while (i < vect1.size() && j < vect2.size()){
        if(vect1[i] < vect2[j])
            res.push_back(vect1[i++]);
        else
            res.push_back(vect2[j++]);
    }
    while(i<vect1.size())
        res.push_back(vect1[i++]);
    while(j<vect2.size())
        res.push_back(vect2[j++]);
    return res;
}

vector<int> slice(vector<int> vect, int i, int j){
    vector<int> result;
    while(i<j)
        result.push_back(vect[i++]);
    return result;
}
