struct node
{
    node *ch[2], *fa;
    ll key; int siz, tag;
}mem[N*20], *tot, *null, *root;
void init()
{
    root = null = tot = mem;
    null->ch[0] = null->ch[1] = null->fa = null;
    null->key = null->siz = null->tag = 0;
}
int type(node *x){return x->fa->ch[1]==x;}
node *newnode(ll key)
{
    node *p = ++tot; *p = *null;
    p->key = key; p->siz = 1;
    return p;
}
void pushup(node *x)
{
    x->siz = x->ch[0]->siz + x->ch[1]->siz + 1;
}
void rotate(node *x)
{
    node *f =  x->fa; int d = type(x);
    (x->fa = f->fa) != null ? x->fa->ch[type(f)] = x : 0;
    (f->ch[d] = x->ch[!d]) != null ? f->ch[d]->fa = f : 0;
    x->ch[!d] = f, f->fa = x, pushup(f);
}
void pushdown(node *x)
{
    if(x->tag)
    {
        int &tag = x->tag;
        if(x->ch[0] != null) x->ch[0]->key += tag, x->ch[0]->tag += tag;
        if(x->ch[1] != null) x->ch[1]->key += tag, x->ch[1]->tag += tag;
        tag = 0;
    }
}
void update(node *x)
{
    if(x==null) return;
    update(x->fa);
    pushdown(x);
}
void splay(node *x, node *top)
{
    update(x);
    for(;x->fa!=top;)
    {
        if(x->fa->fa == top) rotate(x);
        else if(type(x) == type(x->fa)) rotate(x->fa), rotate(x);
        else rotate(x), rotate(x);
    }
    if(top == null) root = x;
    pushup(x);
}
void insert(node *x, node *f, node *p, int d)
{
    if(x == null)
    {
        p->fa = f, f->ch[d] = p;
        return;
    }
    pushdown(x);
    if(p->key < x->key) insert(x->ch[0], x, p ,0);
    else insert(x->ch[1], x, p, 1);
    pushup(x);
}
 
void insert(node *p)
{
    if(root == null) root = p, p->fa = p->ch[0] = p->ch[1] = null;
    else insert(root, null, p, 0), splay(p, null);
}
node *findl(node *x){return x->ch[0]==null?x:findl(x->ch[0]);}
node *findr(node *x){return x->ch[1]==null?x:findr(x->ch[1]);}
void insertlr()
{
    insert(newnode(-INF));
    insert(newnode(INF));
}
void delet(node *p)
{
    splay(p, null);
    node *lp = findr(p->ch[0]), *rp = findl(p->ch[1]);    
    if(lp == null && rp != null) root = p->ch[1], root->fa = null;
    else if(lp != null && rp == null) root = p->ch[0], root->fa = null;
    else if(lp == null && rp == null)root = null;
    else
    {
        splay(rp, null); splay(lp,rp);
        lp->ch[1] = null; splay(lp,null);
    }
}
node* findk(node *p, int k)
{
    for(; ; )
    {
        pushdown(p);
        if(p->ch[0]->siz >= k) p = p->ch[0];
        else if(p->ch[0]->siz + 1 == k) {splay(p, null); return p;}
        else k -= p->ch[0]->siz + 1, p = p->ch[1];
    }
}
node* findv(node *p, int v)
{
    node* ret = null;
    for(; p!=null; )
    {
        pushdown(p);
        if(p->key >= v) ret = p, p = p->ch[0];
        else p = p->ch[1];
    }
    splay(ret, null);
    return ret;
}
void addv(node *p, int v)
{
    if(p == null) return;
    p->key += v;
    p->tag += v;
}