#include<cstdio>
#define N 100005
#define M 200005
using namespace std;
int last[N], ecnt = 1, cnt, ans[M], in_deg[N], out_deg[N];
bool vis[M];
struct edge{int next,to;}e[M<<1];
void addedge(int a, int b)
{
    e[++ecnt] = (edge){last[a], b};
    last[a] = ecnt;
}
void dfs(int x)
{
    for(int &i = last[x]; i; i = e[i].next)
    {
        int y = e[i].to, j = i;
        if(!vis[j>>1])
        {
            vis[j>>1] = 1;
            dfs(y);
            ans[++cnt] = j;
        } 
    }
}
int main()
{
    int t, n, m, a, b;
    scanf("%d%d%d",&t,&n,&m);
    for(int i = 1; i <= m; i++)
    {
        scanf("%d%d",&a,&b);
        addedge(a,b);
        if(t == 1)addedge(b,a), in_deg[a]++, in_deg[b]++;
        else ecnt++, in_deg[b]++, out_deg[a]++;
    }

    if(t == 1) // 无向
    {
        for(int i = 1; i <= n; i++)
            if((in_deg[i]+out_deg[i]) & 1)
                return !printf("NO\n");
    }
    else // 有向
    {
        for(int i = 1; i <= n; i++)
            if(in_deg[i] != out_deg[i])
                return !printf("NO\n");
    }   
    dfs(a);
    if(cnt != m)
    {
        puts("NO"); 
    } 
    else
    {
        puts("YES");
        for(int i = cnt; i; i--)
        {
            printf("%d ",ans[i]&1?-(ans[i]>>1):(ans[i]>>1));
        }
    }
}