//时间复杂度：O(nm)
int N, m;
int pre[maxn], in[maxn], f[maxn], id[maxn];
struct node {int u, v, w;} a[maxm * 2]; //边表

int find(int x)
{
	return f[x] == x ? x : f[x] = find(f[x]);
}

int mst()
{
	long long res = 0;
	int root = 1;
	int n = N;
	while(true)
	{
		for(int i = 1; i <= n; i++) in[i] = INT_MAX, pre[i] = 0;
		for(int i = 1; i <= m; i++)
			if(a[i].u != a[i].v  && in[a[i].v] > a[i].w)
				in[a[i].v] = a[i].w, pre[a[i].v] = a[i].u;
		for(int i = 1; i <= n; i++)
			if(in[i] == INT_MAX && i != root) return 0;
		int cnt = 0;
		for(int i = 1; i <= n; i++) f[i] = i, id[i] = 0;
		for(int i = 1; i <= n; i++)
		{
			if(i == root) continue;
			res += in[i];
			if(find(i) != find(pre[i])) f[f[i]] = f[pre[i]];
			else
			{
				cnt++;
				for(int j = i; j && !id[j]; j = pre[j])
					id[j] = cnt;
			}
		}
		if(!cnt) break;
		for(int i = 1; i <= n; i++)
			if(!id[i]) id[i] = ++cnt;
		for(int i = 1; i <= m; i++)
		{
			if(id[a[i].u] != id[a[i].v]) a[i].w -= in[a[i].v];
			a[i].u = id[a[i].u];
			a[i].v = id[a[i].v];
		}
		n = cnt;
		root = id[root];
	}
    return res;
}
