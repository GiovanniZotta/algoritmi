#include <fstream>
#include <iostream>
using namespace std;

int N;
int arr[1000000];

int main(int argc, char const *argv[]) {
    ifstream in("input.txt");
    in >> N;
    for (int i = 0; i < N; i++) {
        in >> arr[i];
    }
    int max=0,somma=0;
    for (int i = 0; i < N; i++) {
        somma+=arr[i];
        if(somma<0){
            somma = 0;
        }
        if(somma>max)
            max=somma;
    }
    ofstream out("output.txt");
    out<<max<<endl;
    return 0;
}
