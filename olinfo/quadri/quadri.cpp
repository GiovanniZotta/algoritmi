#include <vector>
#include <iostream>
#include <fstream>
using namespace std;


void printDP(vector<vector<int>>& DP){
    for(int i=0; i<DP[0].size(); i++){
        for(int j=0; j<DP.size(); j++)
            cout << DP[i][j] << " ";
        cout << endl;
    }
}

long long checkSum(int N, long long M, int V[]){
    long long sum = 0;
    for(int i=0; i<N; i++)
        sum += V[i];
    return sum;
}

int quadri60(int N, long long M, int V[]) {
    if(checkSum(N,M,V)<=M)
        return N;
    int B=N;
    for(int i=0; i<N; i++){
        long long curr = 0;
        for(int j=i, count=0; j<N && count < B; j++){
            if(curr + V[j] <= M){
                curr+=V[j];
                count++;
            }else
                B=count;
        }
    }
    return B;
}

int quadri(int N, long long M, int V[]) {
    if(checkSum(N,M,V)<=M)
        return N;
    int B=N;
    
}


int main(int argc, char const *argv[])
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    int N,M;
    in >> N >> M;
    int vect[N];
    for(int i=0; i<N; i++)
        in >> vect[i];
    cout << quadri(N,M,vect);
    return 0;
}
