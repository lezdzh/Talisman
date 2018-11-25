struct node
{
    node *ch[2], *fa;
    uint v, sum, k, b; int rev, siz;
}mem[N], *tot, *null, *pos[N];
void init()
{
    null = tot = mem;
    null->ch[0] = null->ch[1] = null->fa = null;
    null->v = null->sum = null->b = null->rev = null->siz = 0; null->k = 1;
    for(int i = 1; i <= n; i++) pos[i] = ++tot, *pos[i] = *null, pos[i]->v = pos[i]->sum = 1;
}
int type(node *x){return x->fa->ch[1]==x?1:0;}
int isroot(node *x){return x->fa->ch[type(x)] != x;}
void mswap(node *&x, node *&y){node *t = x; x = y; y = t;}
void pushup(node *x)
{
    x->sum = (x->v + x->ch[0]->sum + x->ch[1]->sum) % MOD; 
    x->siz = (x->ch[0]->siz + x->ch[1]->siz + 1) % MOD;
}
void pushdown(node *x)
{
    if(x->rev) 
    {
        x->rev = 0, x->ch[0]->rev ^= 1, x->ch[1]->rev ^= 1;
        mswap(x->ch[0]->ch[0], x->ch[0]->ch[1]);
        mswap(x->ch[1]->ch[0], x->ch[1]->ch[1]);
    }
    for(int i = 0; i <= 1; i++)
    {
        x->ch[i]->v = (x->k * x->ch[i]->v % MOD + x->b) % MOD;
        x->ch[i]->sum = (x->ch[i]->sum * x->k % MOD + x->b * x->ch[i]->siz % MOD) % MOD;
        (x->ch[i]->k *= x->k) %= MOD;
        (x->ch[i]->b *= x->k) %= MOD, (x->ch[i]->b += x->b) %= MOD;
    }
    x->k = 1;  x->b = 0;
}
void update(node *x){if(!isroot(x))update(x->fa); pushdown(x);}
void rotate(node *x)
{
    node *f = x->fa; int d = type(x);
    x->fa = f->fa, !isroot(f) ? x->fa->ch[type(f)] = x : 0;
    (f->ch[d] = x->ch[d^1]) != null ? f->ch[d]->fa = f : 0;
    f->fa = x, x->ch[d^1] = f; pushup(f);
}
void splay(node *x)
{
    update(x);
    for(; !isroot(x); )
    {
        if(isroot(x->fa)) rotate(x);
        else if(type(x) == type(x->fa)) rotate(x->fa), rotate(x);
        else rotate(x),rotate(x);
    }
    pushup(x);
}
void access(node *x)
{
    node *tmp = null;
    for(; x != null; )
    {
        splay(x);
        x->ch[1] = tmp;
        pushup(x);
        tmp = x;
        x = x->fa;
    }
}
void makeroot(node *x)
{
    access(x);
    splay(x);
    x->rev ^= 1;
    swap(x->ch[0], x->ch[1]);
}
void link(node *x, node *y)
{
    makeroot(x);
    x->fa = y;
}
void cut(node *x, node *y)
{
    makeroot(x); access(y);
    splay(y); y->ch[0] = x->fa = null; 
    pushup(y);
}