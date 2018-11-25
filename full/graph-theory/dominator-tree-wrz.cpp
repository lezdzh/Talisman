int dfn[N],redfn[N],fa[N],sdom[N],idom[N],fo[N],vo[N],dtimer;
vector<int> pre[N],bkt[N];
int dom_find(int x)
{
	if(fo[x]==x) return x;
	int r = dom_find(fo[x]);
	if(sdom[vo[fo[x]]]<sdom[vo[x]]) vo[x] = vo[fo[x]];
	return fo[x] = r;
}
int dom_eval(int x){dom_find(x); return vo[x];}
void dom_dfs(int x)
{
	redfn[dfn[x]=++dtimer] = x, sdom[x] = dfn[x];
	for(int i=last[x];i;i=e[i].next) if(!dfn[e[i].to])
		dom_dfs(e[i].to), fa[e[i].to] = x;
}
void dom_build(int S)
{
	int i,x;
	dom_dfs(S);
	for(i = dtimer; i >=2; i--)
	{
		x = redfn[i];
		for(int i = 0, ii = pre[x].size(); i < ii; i++) 
		{
			int k = pre[x][i];
			if(dfn[k]) sdom[x] = min(sdom[x],sdom[dom_eval(k)]);
		} 
		bkt[redfn[sdom[x]]].push_back(x);
		int fp = fa[x]; fo[x] = fa[x];
		for(int i = 0, ii = bkt[fp].size(); i < ii; i++)
		{
			int v = bkt[fp][i];
			int u = dom_eval(v);
			idom[v] = sdom[u]==sdom[v]?fp:u;
		}
		bkt[fp].clear();
	}
	for(int i = 2;i <= dtimer; i++) x = redfn[i], idom[x] = idom[x]==redfn[sdom[x]]?idom[x]:idom[idom[x]];
	for(int i = 2;i <= dtimer; i++) x = redfn[i], sdom[x] = redfn[sdom[x]];
}
void dom_init()
{
	dtimer = 0;
	for(int i = 1; i <= n; i++)
	{
		dfn[i] = 0;
		fo[i] = vo[i] = i;
		pre[i].clear(), bkt[i].clear();
	}
	for(int x = 1; x <= n; x++) for(int i = last[x]; i; i = e[i].next) pre[e[i].to].push_back(x);
}
/*
	步骤：
	1.建好原图
	2.dom_init() // 必须保证原图上所有的边已经连好
	3.dom_build(S) // S为支配树的根结点标号
	4.得到idom数组 // idom[x]表示x在支配树上的父结点，别的数组用处不大
*/