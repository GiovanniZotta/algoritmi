#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long int ll;
typedef long long int ll;
vector<ll> perm;
vector<ll> weights;
unordered_set<ll> used;
int printed = 0;
int k, n;
struct partial_sol{
    ll res;
    vector<int> path;
    partial_sol(ll _res, int i){
        res = _res;
        path.push_back(i);
    }
};
inline bool operator<(const partial_sol& lhs, const partial_sol& rhs)
{
  return lhs.res < rhs.res;
}
map<ll, partial_sol> pq;
void insert_el(partial_sol &p){
    auto iter = pq.find(p.res);
    if (iter != pq.end()){
        if ((*iter).second.path[(*iter).second.path.size() - 1] > p.path[p.path.size() - 1]){
            (*iter).second.path = p.path;
        }
    } else {
        pq[p.res] = p;
    }
}
void backtrack(){
    while (printed < k){
        partial_sol sol = *pq.begin();
        pq.erase(pq.begin());
        
        cout << sol.res << ": ";
        for(int i : sol.path){
            cout << weights[i] << " ";
        }
        cout << endl;
        printed++;

        if(printed < k){
            int last = sol.path[sol.path.size() - 1];
            for(int j = last + 1; j < n; j++){
                sol.res += weights[j];
                sol.path.push_back(j);
                insert_el(sol);
                sol.path.pop_back();
                sol.res += weights[j];
                // cout << "Pushing sol " << new_sol.res << endl;
            }
        }
    }
}
int main(int argc, char const *argv[]){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> k;
    weights.resize(n);

    for(int i = 0; i < n; i++){
        cin >> weights[i];
    }
    sort(weights.begin(), weights.end());
    for(int i = 0; i < n; i++){
        partial_sol s({weights[i], i});
        insert_el(s);
        // cout << "pushing" << weights[i] << ", " << 0 << endl;
    }
    cout << "0: " << endl;
    printed++;
    backtrack();
    return 0;
}