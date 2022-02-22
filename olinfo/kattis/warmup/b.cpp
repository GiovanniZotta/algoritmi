#include <bits/stdc++.h>
using namespace std;

int main(){
    int king=1, queen=1, rooks=2, bishops=2, knights=2, pawns=8;
    int a,b,c,d,e,f;
    cin >>a>>b>>c>>d>>e>>f;
    cout << king-a << " " << queen-b << " " << rooks-c << " " << bishops-d << " " << knights-e << " " << pawns-f << endl;
}