#include <bits/stdc++.h>
using namespace std;
int main(int argc, char const *argv[]){
    multiset<long long int> set;
    long long int N, S, p, max_min=1ll<<60;
    cin >> N >> S;
    vector<long long int> vec(N); 
    for(int i=0; i<N; i++){
        cin >> p;
        set.insert(p);
        vec[i]=p;
    }
    long long int SN=S*(N-1);
    long long int lm_i=0;
    long long int lm_v=vec[0];
    set.erase(set.begin());
    max_min=min(lm_v+SN, *(set.begin())-S);
    for(long long int n=1; n<N-1; n++){
        if(lm_v+SN - S*(n-lm_i) > vec[n]+SN){
            lm_i=n;
            lm_v=vec[n];
        }

        set.erase(set.begin());
        max_min=max(max_min, min(lm_v+SN - S*(n-lm_i), *(set.begin())-S*(n+1)));
    }
    cout << max_min << endl;
    return 0;
}
1,4,5,7;

M7: 5[1,4,5,7], (1,5)[4,7], (7)[1,4,5];
M7: 5[1,4,5,7], (1,5)[4,7], (7)[1,4,5];
M8: 5[1,4,5,7], (1,5)[4,7], (7)[1,4,5], (7,1)[4,5];
M9: 5[1,4,5,7], (1,5)[4,7], (7)[1,4,5], (7,1)[4,5], (5,4)[1,7], ;

