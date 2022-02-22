#include <vector>
#include <iostream>
#include <math.h>
using namespace std;
struct matrix{
    vector<vector<int>> mat;
    int N;
    matrix(vector<vector<int>> &m){
        if(m.size()!=m[0].size()){//sbagliato: non solo lo zero
            printf("input sbagliato");
        }else{
            N=m.size();
            mat=m;
        }
    }
    void exp(int n){
        matrix sup(mat);
        mat=vector<vector<int>>(N, vector<int>(N, 0));
        for(int i=0; i<N; i++)mat[i][i]=1;
        for(int k=1; n!=0; k<<=1, sup.exp2())
            if(n&k){
                mult(sup);
                n-=k;
            }
    }
    void exp2(){ //si può fare meglio
        vector<vector<int>> sup=mat;
        for(int i=0; i<N; i++)
            for(int j=0; j<N; j++){
                mat[i][j]=0;
                for(int z=0; z<N; z++)
                    mat[i][j] += sup[i][z]*sup[z][j];
            }
    }
    void mult(matrix &b){
        vector<vector<int>> sup=mat;
        for(int i=0; i<N; i++)
            for(int j=0; j<N; j++){
                mat[i][j]=0;
                for(int z=0; z<N; z++)
                    mat[i][j] += sup[i][z]*b.mat[z][j];
            }
    }
    void print(){
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++)
                printf("%d ", mat[i][j]);
            printf("\n");
        }
        printf("\n");
    }
};

int main(int argc, char const *argv[]){
    vector<vector<int>> vec={{1,1},{1,0}};
    matrix fib(vec), sup(vec);
    for(int i=2; i<20; i++){
        printf("mult:\n");
        fib.mult(sup);
        fib.print();
        matrix fib2(vec);
        fib2.exp(i);
        printf("exp:\n");
        fib2.print();
    }
    sup.exp(21);
    sup.print();
    return 0;
}
