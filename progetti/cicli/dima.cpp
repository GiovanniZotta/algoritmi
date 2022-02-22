using namespace std;
#include <bits/stdc++.h>

struct DTreeMin{
	#define p(k) (1<<(k))
	int **vec, *idTsha, N=0, K=0;
    DTreeMin(int n): vec(new int*[2*n]), idTsha(new int[n]){}
    
    void push(int a, int h){
		vec[N]=new int[p(K)&(N+1)?++K:K];
		vec[N][0]=h;
		static int k;
		for(k=1; k<K; k++)
			vec[N][k]=min(vec[N-p(k-1)][k-1], vec[N][k-1]);
    	idTsha[a]=N++;
    }		
    int distance(int a, int b){
    	static int diff, k, i;
    	a=idTsha[a], b=idTsha[b];
    	diff=abs(b-a)+1, k=K-1;

    	while(!(p(k)&diff)) k--;
    	i=min(vec[min(a,b)+p(k)-1][k], vec[max(a,b)][k]);

	    a=vec[a][0], b=vec[b][0];
    	return a/2+b/2-2*(i/2)-i%2*(i!=a && i!=b);
    }
};
struct Graph{
	vector<int> *adj, alt;
	DTreeMin tMin;
	int N;
	Graph(int n): N(n), adj(new vector<int>[n]), alt(n, INT_MAX), tMin(n){}
	int dfs(int u){
		int ret=-1, c=0;
		for(int v: adj[u])
			if(alt[v]==INT_MAX) alt[v]=-(alt[u]+1);
			else if(-alt[v]==alt[u]) ret=v;
			
		for(int v: adj[u])if(-alt[v]==alt[u]+1){
			if(c++)tMin.push(u, alt[u]*2);
			int c2=0;
			while(v!=-1){
				alt[v]=-alt[v];
				if(c2++ && c++)tMin.push(u, alt[u]*2+1);
				v=dfs(v);
			}
		}
		if(c<2) tMin.push(u, alt[u]*2);
		return ret;
	}
};

int main(int argc, char const *argv[]){
	FILE * in= fopen("input.txt","r");
	FILE * out= fopen("output.txt","w");

	int N,M,Q, u,v;
	fscanf(in, "%d %d %d", &N, &M, &Q);
	Graph g(N);
	for(int m=0; m<M; m++){
		fscanf(in, "%d %d", &u, &v);
		g.adj[u].push_back(v);
		g.adj[v].push_back(u);
	}
	g.alt[0]=0;
	g.dfs(0);
	for(int q=0; q<Q; q++){
		fscanf(in, "%d %d", &u, &v);
		fprintf(out, "%d\n", g.tMin.distance(u, v));
	}
	return 0;
}