#include <iostream>
#include <fstream>
using namespace std;
#include <stdbool.h>
bool visita(int N, int A[]) {
    long long emil=0, gemma=0;
    for(int i=0, j=N-1; i<N && j>=0 && i>j; ){
        if(i==j && gemma == emil)
            return true;
        if(gemma < emil)
            gemma+=A[i++];
        else if(gemma > emil)
            emil += A[j--];
        else{
            gemma+=A[i++];
            emil+=A[j--];
        }
    }
    return false;
}

int main(int argc, char const *argv[])
{
    ifstream in("input.txt");
    int N;
    in >> N;
    int A[N];
    for(int i=0; i<N; i++)
        in >> A[i];
    if(visita(N,A))
        cout << "Emil";
    else
        cout << "Gemma";

    return 0;
}

