#include <vector>
#include <iostream>
using namespace std;

bool is_ordered(vector<int>& vect, int start){
    // std::cout << "checking starting from " << start << " vector: " << '\n';
    // stampa_vettore(vect);
    for(int i=start; i<vect.size(); i++)
        if(vect[i] > vect[i+1])
            return false;
    return true;
}

int main(int argc, char const *argv[]) {
    vector<int> vec = {2,3,1,4,5,6,7,8,9,10};
    std::cout << is_ordered(vec, 2) << '\n';
    return 0;
}
