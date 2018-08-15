const int MAXN,INF;// INF >= sum( W_ij )
int from[MAXN + 10][MAXN * 2 + 10],n,m,edge[MAXN + 10][MAXN * 2 + 10];
int sel[MAXN * 2 + 10],fa[MAXN * 2 + 10],vis[MAXN * 2 + 10];
int getfa(int x){if(x == fa[x]) return x; return fa[x] = getfa(fa[x]);}
void liuzhu(){ // 1-base: root is 1, answer = (sel[i], i) for i in [2..n]
	fa[1] = 1;
	for(int i = 2; i <= n; ++i){
		sel[i] = 1; fa[i] = i;
		for(int j = 1; j <= n; ++j) if(fa[j] != i)
			if(from[j][i] = i, edge[sel[i]][i] > edge[j][i]) sel[i] = j;
	}
	int limit = n;
	while(1){
		int prelimit = limit; memset(vis, 0, sizeof(vis)); vis[1] = 1;
		for(int i = 2; i <= prelimit; ++i) if(fa[i] == i && !vis[i]){
			int j = i; while(!vis[j]) vis[j] = i, j = getfa(sel[j]);
			if(j == 1 || vis[j] != i) continue; vector<int> C; int k = j;
			do C.push_back(k), k = getfa(sel[k]); while(k != j);
			++limit;
			for(int i = 1; i <= n; ++i){
				edge[i][limit] = INF, from[i][limit] = limit;
			}
			fa[limit] = vis[limit] = limit;
			for(int i = 0; i < int(C.size()); ++i){
				int x = C[i], fa[x] = limit;
				for(int j = 1; j <= n; ++j)
					if(edge[j][x] != INF && edge[j][limit] > edge[j][x] - edge[sel[x]][x]){
						edge[j][limit] = edge[j][x] - edge[sel[x]][x];
						from[j][limit] = x;
					}
			}
			for(int j=1;j<=n;++j) if(getfa(j)==limit) edge[j][limit] = INF;
			sel[limit] = 1;
			for(int j = 1; j <= n; ++j)
				if(edge[sel[limit]][limit] > edge[j][limit]) sel[limit] = j;
		}
		if(prelimit == limit) break;
	}
	for(int i = limit; i > 1; --i) sel[from[sel[i]][i]] = sel[i];
}
