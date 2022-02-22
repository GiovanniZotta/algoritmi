#include <bits/stdc++.h>
using namespace std;

int jamal(int x, int y, string &s){
    int res = 0;
    for(int i=0; i<s.size(); ){
        if(s[i] == '?'){
            int j=i;
            while(j<s.size() && s[j] == '?'){
                j++;
            }
            char left = i > 0 ? s[i-1] : 'X';
            char right = j < s.size() ? s[j] : 'X';
            char filler;
            if(left == right){
                if(left == 'X' && right == 'X'){
                    filler = 'C';
                } else { 
                    filler = left;
                }
            } else if (left == 'X') {
               filler = right; 
            } else if (right == 'X'){
               filler = left;
            } else {
               filler = 'C';
            } 
            while(i < j){
                s[i] = filler;
                i++;
            }
        } else {
            i++;
        }
    }
    cerr << s << endl;
    for(int i=1; i<s.size(); i++){
       if(s[i] != s[i-1]){
          res += s[i-1] == 'C' ? x : y;
       } 
    }
    return res;
}

int main(){
    int tests;
    cin >> tests;
    for(int i=1; i<=tests; i++){
        int x, y;
        string s;
        cin >> x >> y >> s;
        cout << "Case #" << i << ": " << jamal(x, y, s) << endl; 
    }    
}
