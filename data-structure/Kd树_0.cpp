#include <cstdio>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;

typedef long long ll;

#define Abs(x)  ((x)>0?(x):(-(x)))
#define min(a,b)  ((a)<(b)?(a):(b))
#define max(a,b)  ((a)>(b)?(a):(b))

const int maxn=1e6+5;
const int inf=0x3f3f3f3f;
int n,m,cnt,root,ans;
struct point {int x,y;};
struct node
{
    point p;
    int ch[2],l,r,u,d;
}a[maxn];

bool cmp0(point a,point b)  {return a.x<b.x;}
bool cmp1(point a,point b)  {return a.y<b.y;}
bool Cmp0(node a,node b)  {return cmp0(a.p,b.p);}
bool Cmp1(node a,node b)  {return cmp1(a.p,b.p);}

void maintain(int x)
{
    for(int i=0;i<2;i++)
    {
	a[x].l=min(a[x].l,a[a[x].ch[i]].l);
	a[x].u=min(a[x].u,a[a[x].ch[i]].u);
	a[x].r=max(a[x].r,a[a[x].ch[i]].r);
	a[x].d=max(a[x].d,a[a[x].ch[i]].d);
    }
}

int dis(int u,point x)
{
    int res=0;
    if(x.x<a[u].l)  res+=a[u].l-x.x;
    if(x.x>a[u].r)  res+=x.x-a[u].r;
    if(x.y<a[u].u)  res+=a[u].u-x.y;
    if(x.y>a[u].d)  res+=x.y-a[u].d;
    return res;
}

int build(int l,int r,int f)
{
    if(l>r)  return 0;
    int x=(l+r)>>1;
    if(f==0)  nth_element(a+l,a+x,a+r+1,Cmp0);
    else  nth_element(a+l,a+x+1,a+r+1,Cmp1);
    a[x].l=a[x].r=a[x].p.x;
    a[x].u=a[x].d=a[x].p.y;
    a[x].ch[0]=build(l,x-1,f^1);
    a[x].ch[1]=build(x+1,r,f^1);
    maintain(x);
    return x;
}

void insert(int &u,int f,point x)
{
    if(!u)
    {
	u=++cnt;
	a[cnt].p=x;
	a[cnt].l=a[cnt].r=a[cnt].p.x;
	a[cnt].u=a[cnt].d=a[cnt].p.y;
	return;
    }
    int d;
    if(f==0)  d=cmp0(a[u].p,x);
    else  d=cmp1(a[u].p,x);
    insert(a[u].ch[d],f^1,x);
    maintain(u);
}

bool check(int u,point x)
{
    if(x.x<a[u].l && a[u].l-x.x<=ans)  return 1;
    if(x.x>a[u].r && x.x-a[u].r<=ans)  return 1;
    if(x.y<a[u].u && a[u].u-x.y<=ans)  return 1;
    if(x.y>a[u].d && x.y-a[u].d<=ans)  return 1;
    return 0;
}

void query(int u,point x)
{
    if(!u)  return;
    ans=min(ans,Abs(x.x-a[u].p.x)+Abs(x.y-a[u].p.y));
    int d=(dis(a[u].ch[0],x)>dis(a[u].ch[1],x));
    query(a[u].ch[d],x);
    if(dis(a[u].ch[d^1],x)<ans)  query(a[u].ch[d^1],x);
}

int main()
{
    int o,x,y;
    scanf("%d%d",&n,&m);cnt=n;
    for(int i=0;i<=n+m;i++)
	a[i].l=a[i].u=inf,a[i].r=a[i].d=-inf;
    for(int i=1;i<=n;i++)
	scanf("%d%d",&a[i].p.x,&a[i].p.y);
    root=build(1,n,0);
    while(m--)
    {
	scanf("%d%d%d",&o,&x,&y);
	if(o==1)
	    insert(root,0,(point){x,y});
	else
	{
	    ans=INT_MAX;
	    query(root,(point){x,y});
	    printf("%d\n",ans);
	}
    }
    return 0;
}
