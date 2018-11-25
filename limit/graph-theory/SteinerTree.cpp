//N点数, M边数, P关键点数
const int inf = 0x3f3f3f3f;
int n, m, p, status, idx[P], f[1 << P][N];
priority_queue<pair<int, int> > q; //int top, h[N];
void dijkstra(int dis[]) {}
void Steiner_Tree() {
	for (int i = 1; i < status; i++) {
		while (!q.empty()) q.pop(); //top = 0;
		memset(vis, 0, sizeof(vis));
		for (int j = 1; j <= n; j++) {
			for (int k = i & (i - 1); k; (--k) &= i)
				f[i][j] = min(f[i][j], f[k][j] + f[i ^ k][j]);
			if (f[i][j] != inf)
				q.push(make_pair(-f[i][j], j)); //h[++top] = j, vis[j] = 1;
		}
		dijkstra(f[i]); //SPFA(f[i]);
	}
}
int main() {
	scanf("%d%d%d", &n, &m, &p);
	status = 1 << p;
	tot = 0; memset(lst, 0, sizeof(lst));
	/*求最小生成森林
	  每棵生成树中至少选择一个点，点权为代价
	  新开一个空白关键点0作为源
	  Add(0, i, val[i]); Add(i, 0, val[i]);*/
	for (int i = 1; i <= p; i++) scanf("%d", &idx[i]);
	memset(f, 0x3f, sizeof(f));
	for (int i = 1; i <= n; i++) f[0][i] = 0;
	for (int i = 1; i <= p; i++) f[1 << (i - 1)][idx[i]] = 0;
	Steiner_Tree();
	int ans = inf;
	for (int i = 1; i <= n; i++) ans = min(ans, f[status - 1][i]);
}
