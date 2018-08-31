#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 2147482647;
int n,m,a[500001],x = 3;
int random0(){return x = abs(215314*23+(x-31)&1001*97127);}
struct node
{
    int w, rem, size, sum, maxl, maxr, maxall, change;
    bool swp; node *ls, *rs;
    node(int v = 0): w(v)
    {
        change = -maxn; size = 1, swp = false, sum = maxall = w;
        maxl = maxr = (w > 0 ? w : 0); ls = rs = NULL;
    }
} *root;
void maintain(node *rt)
{
    rt->size = (rt->ls?rt->ls->size:0) + (rt->rs?rt->rs->size:0) + 1;
    if(rt->change == -maxn)
    {
        rt->sum = (rt->ls?rt->ls->sum:0) + (rt->rs?rt->rs->sum:0) + rt->w;
        rt->maxl = max((rt->ls?rt->ls->maxl:0), (rt->ls?rt->ls->sum:0) + rt->w + (rt->rs?rt->rs->maxl:0));
        rt->maxr = max((rt->rs?rt->rs->maxr:0), (rt->rs?rt->rs->sum:0) + rt->w + (rt->ls?rt->ls->maxr:0));
        rt->maxall = max(max((rt->ls?rt->ls->maxall:-maxn),(rt->rs?rt->rs->maxall:-maxn)),(rt->ls?rt->ls->maxr:0) + (rt->rs?rt->rs->maxl:0) + rt->w);
        if(rt->swp) swap(rt->maxl,rt->maxr);
    }
    else
    {
        rt->w=rt->change;rt->sum=rt->maxall=rt->change*rt->size;
        if(rt->change>0)rt->maxl=rt->maxr=rt->size*rt->change;
        else rt->maxl=rt->maxr=0;
    }
}
void build(node *&rt, int l, int r)
{
    if(l > r) return;
    rt = new node(a[l + r >> 1]);
    build(rt->ls,l,(l + r >> 1) - 1);
    build(rt->rs,(l + r >> 1) + 1, r);
    maintain(rt);
}
void pushdown(node *rt)
{
    if(rt -> swp)
    {
        swap(rt->ls, rt->rs);
        if(rt->ls)rt->ls->swp ^= 1;
        if(rt->rs)rt->rs->swp ^= 1;
        rt->swp = false;
    }
    if(rt -> change != -maxn)
    {
        if(rt->ls)rt->ls->change = rt->change;
        if(rt->rs)rt->rs->change = rt->change;
        rt->change = -maxn;
    }
    if(rt->ls) maintain(rt->ls);
    if(rt->rs) maintain(rt->rs);
}
node *merge(node *a, node *b)
{
    if(a == NULL) return b;
    if(b == NULL) return a;
    pushdown(a), pushdown(b);
    if(random0()%(a->size + b->size) < a->size) 
        {a->rs = merge(a->rs,b); maintain(a); return a;}
    else {b->ls = merge(a,b->ls);maintain(b); return b;}
}
pair<node*,node*>split(node *a,int num)
{
    if(!a || !num) return pair<node*, node*>(NULL,a);
    pushdown(a); pair<node*, node*>re;
    if(a->ls && a->ls->size >= num)
    {
        re = split(a->ls, num);a->ls = re.second;
        re.second=a;maintain(a);return re;
    }
    else
    {
        re = split(a->rs,num-(a->ls?a->ls->size:0)-1);a->rs=re.first;
        re.first=a;maintain(a);return re;
    }
}
void del(node* rt)
{
    if(rt == NULL) return;
    del(rt->ls),del(rt->rs);delete(rt);
}
int main()
{
    scanf("%d%d",&n,&m);
    for (int i = 1; i <= n; i++) scanf("%d",&a[i]);
    build(root,1,n);
    while(m--)
    {
        char s[10]; int posi,tot;
        scanf("%s",s);
       if(s[0] == 'I')
        {
            scanf("%d%d",&posi,&tot);
            for (int i = 1; i <= tot; i++) scanf("%d",&a[i]);
            node* use; build(use,1,tot);
            pair<node*,node*>tmp = split(root,posi);
            root = merge(merge(tmp.first,use),tmp.second);
        }
		else if(s[0] == 'D')
        {
            scanf("%d%d",&posi,&tot);
            pair<node*,node*>p = split(root,posi - 1),q = split(p.second,tot);
            del(q.first),root = merge(p.first,q.second);
        }
		else if(s[0] == 'M' && s[2] == 'K')//区间修改
        {
            int c; scanf("%d%d%d",&posi,&tot,&c);
            pair<node*,node*>p = split(root,posi - 1),q = split(p.second,tot);
            q.first->change = c; maintain(q.first);
            root = merge(merge(p.first,q.first),q.second);
        }
		else if(s[0]=='R')
		{
			scanf("%d%d",&posi,&tot);
            pair<node*,node*>p=split(root,posi-1),q=split(p.second,tot);
			q.first->swp^=1;maintain(q.first);
			root=merge(merge(p.first,q.first),q.second);
		}
		else if(s[0]=='G')//求和
		{	
			scanf("%d%d",&posi,&tot);
			pair<node*,node*>p=split(root,posi-1),q=split(p.second,tot);
			printf("%d\n",q.first?q.first->sum:0);
			root=merge(merge(p.first,q.first),q.second);
		}
		else if(s[0]=='M')//最大子段
		{
			printf("%d\n",root->maxall);
		}
    }
}