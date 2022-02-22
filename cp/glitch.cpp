#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

string str;

int conta(int ind1, int ind2){
    int count=0;
    while(str[ind1++] == str[ind2++])
        count++;
    return count;
}

int main(int argc, char const *argv[])
{
    int dim;
    cin >> dim;
    cin >> str;
    
    int count = 0;
    for(int i=0; i<dim; i++)
        for(int j=i+1; j<dim; j++)
            if(str[i] == str[j])
                count = max(count, conta(i,j));
    cout << count;
    return 0;
}
