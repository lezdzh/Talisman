#include<bits/stdc++.h>
typedef long long ll;
using std::min;

void read(int &digit)
{
	digit=0;
	char c;
	for (c=getchar();(c<'0' || c>'9') && c!='-';c=getchar());
	bool type=false;
	if (c=='-')
		type=true,c=getchar();
	for (;c>='0' && c<='9';digit=digit*10+c-'0',c=getchar());
	if (type==true)
		digit=-digit;
}

#define maxn 1010
const int INF=1<<30;
int n,m;
int S,T;
struct Edge
{
	int v,flow,next;
}	e[510010];
int g[maxn],tot=1;//tot初值必须赋为1 
void addedge(int x,int y,int flow)
{
	e[++tot].v=y;e[tot].flow=flow;e[tot].next=g[x];g[x]=tot;
	e[++tot].v=x;e[tot].flow=0;e[tot].next=g[y];g[y]=tot;
}
int w[maxn],hash[maxn],d[maxn];
int que[maxn],pre1[maxn],pre2[maxn],p[maxn];
bool vis[maxn];
int maxflow()
{
	for (int i=1;i<=n;i++)	hash[i]=0,d[i]=0,vis[i]=false;
	for (int i=1;i<=n;i++)	p[i]=g[i];
	//hash[0]=n;
	int l,r;
	l=r=1;
	que[1]=T;hash[0]=1;vis[T]=true;
	while (l<=r)
	{
		int u=que[l++];
		for (int i=g[u];i;i=e[i].next)
		if ((i&1) && !vis[e[i].v])
		{
			que[++r]=e[i].v;
			vis[e[i].v]=true;
			d[e[i].v]=d[u]+1;
			hash[d[e[i].v]]++;
		}
	}
	for (int i=1;i<=n;i++)
	if (!vis[i])	d[i]=n,hash[n]++;
	int flow=INF;
	int ans=0;
	int u=S;
	while (d[S]<n)
	{
		w[u]=flow;
		bool bo=true;
		for (int i=p[u];i;i=e[i].next)
		if (e[i].flow && d[e[i].v]==d[u]-1)
		{
			flow=min(flow,e[i].flow);
			p[u]=i;
			pre1[e[i].v]=u;
			pre2[e[i].v]=i;
			u=e[i].v;
			bo=false;
			if (u==T)
			{
				ans+=flow;
				while (u!=S)
				{
					e[pre2[u]].flow-=flow;
					e[pre2[u]^1].flow+=flow;
					u=pre1[u];
				}
				flow=INF;
			}
			break;
		}
		if (!bo)	continue;
		int minx=n,pos=0;
		for (int i=g[u];i;i=e[i].next)
		if (e[i].flow && d[e[i].v]<minx)	minx=d[e[i].v],pos=i;
		p[u]=pos;
		hash[d[u]]--;
		if (hash[d[u]]==0)	break;
		d[u]=minx+1;
		hash[d[u]]++;
		if (u!=S)	u=pre1[u],flow=w[u];
	}
	return ans;
}
int main()
{
	int n1,n2;
	read(n1),read(n2),read(m);
	n=n1+n2+2;
	S=n1+n2+1,T=n1+n2+2;
	tot=1;
	for (int i=1;i<=n1;i++)	addedge(S,i,1);
	for (int i=1;i<=n2;i++)	addedge(i+n1,T,1);
	while (m--)
	{
		int x,y;
		read(x),read(y);
		addedge(x,y+n1,1);
	}
	int mjy=maxflow();
	printf("%d\n",mjy);
	for (int i=1;i<=n1;i++)
	{
		bool bo=true;
		for (int j=g[i];j;j=e[j].next)
			if (!(j&1) && e[j].flow==0)	{bo=false;printf("%d ",e[j].v-n1);break;}
		if (bo)	printf("0 ");
	}
	printf("\n");
	return 0;
}

//求割的方案：从S开始，沿着非满流边bfs，能遍历到的地方为集合SS，其余为集合TT，横跨两个集合的边为割边 

