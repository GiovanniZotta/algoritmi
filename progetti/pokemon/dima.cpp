using namespace std;
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <utility>
#include <ctime>

int mcd(int m, int n){
	return n==0?m:mcd(n,m%n);
}

struct Graph{
	vector<vector<int>> v;
    vector<bool> todo;
	int N;
	Graph(int n): N(n), v(n), todo(n){}
	int civ(int x, bool cros){
		vector<int> erdos(N, -1);
		vector<int> num(N, -1);
		queue<int> q;
		erdos[x]=0;
		int c=0;
		int ret=0;
		for(int u:v[x]){
			q.push(u);
			erdos[u]=1;
			num[u]=c++;
		}
		unordered_map<int, bool> mapu;
		int d=-1, s=-1;
        int last=-1;
		for(int t=q.front(); !q.empty(); q.pop(), t=q.front())
			for(int u:v[t]){
				if(erdos[u]==-1){
					erdos[u]=erdos[t]+1;
					num[u]=num[t];
					q.push(u);
                    last=u;
				}
				else if(num[t]!=num[u] && num[u]!=-1){ //radice = -1
					ret=mcd(ret, erdos[t]+erdos[u]+1);
					d=num[t];
					s=num[u];
					mapu[(erdos[t]+erdos[u]+1)*c*c+d*c+s]=true;
				}
			}

        todo[last]=true;
		if(ret>1)
		for(int a=ret*2; a<N; a+=ret)
			if(mapu[(a)*c*c+d*c+s])
				return ret%2==1?0:ret/2;
		return ret;
	}
};
int main(int argc, char const *argv[])
{
	clock_t t = clock();
    ifstream in("input/input19.txt");
	int N,M, primo,secondo;
	in>>N>>M;
	Graph g(N);
	for(int x=0; x<M; x++)
	{
		in>>primo>>secondo;
		g.v[primo].push_back(secondo);
		g.v[secondo].push_back(primo);
	}
    g.todo[0]=true;
	int min=0;
	int found=-1;
	for(int x=0; x<N; x++){
        int tmp;
        if(g.v[x].size()>2)
		    tmp=g.civ(x, true);
        else if(g.todo[x])
		    tmp=g.civ(x, false);
        else continue;
		//printf("%d\n", tmp);
		int save=min;
		min=mcd(min, tmp);
		if(save!=0 && save!=min)
			found=x;
		//break;
	}
	//g.place(x)
    ofstream out("output.txt");
    out << min;
	// printf("%d\n", min);
	//printf("%ld\n", (clock()-t)/1000);
	//cout << min;
	return 0;
}