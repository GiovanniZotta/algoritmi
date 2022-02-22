#include <iostream>
#include <vector>
using namespace std;

void Colora(int N, int Q, vector <int> &A, vector <int> &B, vector <int> &C, vector <int> &murale){
    murale.assign(murale.size(), -1);
    for(int i = Q - 1; i >= 0; i--)
        for(int j = A[i]; j <= B[i]; j++)
            if (murale[j] == -1)
                murale[j] = i;
            else 
                j = B[murale[j]];
 
    for(int i = 0; i < N; i++)
        if (murale[i] == -1)
            murale[i] = 0;
        else 
            murale[i] = C[murale[i]];
    
}

void colora_murale(int N, int Q, vector <int> &A, vector <int> &B, vector <int> &C, vector <int> murale){
    for(int i=0; i<Q; i++)
        for(int j=A[i]; j<= B[i]; j++)
            murale[j] = C[i];
    cout << "GIUSTO: ";
    for(int i=0; i<N; i++)
        cout << murale[i] << " ";
    cout << endl;
    return;
}

int main(int argc, char const *argv[]){
    int n,q;
    cin >> n >> q;
    vector<int> A(q,0), B(q,0), C(q,0), murale(n,0);
    for(int i=0; i<q; i++)
        cin >> A[i] >> B[i] >> C[i];
    colora_murale(n,q,A,B,C,murale);
    Colora(n,q,A,B,C,murale);
    for(int i=0; i<n; i++)
        cout << murale[i] << " ";
    cout << endl;
    return 0;
}
