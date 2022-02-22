#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

pair<char, int> *removeElem(pair<char, int> vect[], int dim, int pos){
    for(int i = pos; i < dim; i++)
        vect[i] = vect[i + 2];
    return vect;
}

void flatland(pair<char, int> vect[], bool supp[], int dim){
    if (dim > 3) {
        for(int i = 1; i < dim - 1; i++){
            pair<char, int> tmp[dim];
            for(int i = 0; i < dim; i++)
                tmp[i] = vect[i];
            if(vect[i].first == 's') // single quote needed
                flatland(removeElem(tmp, dim - 2, i - 1), supp, dim - 2);
            else
                flatland(removeElem(tmp, dim - 2, i), supp, dim - 2);
        }
    } else
        if(vect[1].first == 's') // single quote needed
            supp[vect[2].second] = true;
        else
            supp[vect[0].second] = true;
}

int main(){

    int dim = 0, cont = 0;

    ifstream in("input.txt");
    ofstream out("output.txt");

    in >> dim;

    pair<char, int> vect[dim];
    bool supp[dim];

    for (int i = 0; i < dim; i++) {
        in >> vect[i].first;
        vect[i].second = i;
        supp[i] = false;
    }

    flatland(vect, supp, dim);
    
    for (int i = 0; i < dim; i++)
        if (supp[i])
            cont++;

    out << cont << endl;
    cout << cont << endl;

    for (int i = 0; i < dim; i++) {
        if (supp[i]){
            out << i << " ";
            cout << i << " ";
        }
    }

    return 0;
}
