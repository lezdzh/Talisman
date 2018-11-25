struct SAM
{
    SAM *next[A], *fail;
    int len, mi, mx;
}mem[N], *tot, *null, *root, *last, *q[N];
SAM *newSAM(int len)
{
    SAM *p = ++tot;
    *p = *null; 
    p->len = p->mi = len;
    p->mx = 0;
    return p;
}
void init()
{
    null = tot = mem;
    for(int i = 0; i < A; i++) null->next[i] = null;
    null->fail = null;
    null->len = null->mi = null->mx = 0;
    root = last = newSAM(0);
}
void extend(int v)
{
    SAM *p = last, *np = newSAM(p->len + 1); last = np;
    for(; p->next[v] == null && p != null; p = p->fail) p->next[v] = np;
    if(p==null) np->fail = root;
    else
    {
        SAM *q = p->next[v];
        if(q->len == p->len+1) np->fail = q;
        else
        {
            SAM *nq = newSAM(p->len+1);
            memcpy(nq->next, q->next, sizeof(nq->next));
            nq->fail = q->fail;
            q->fail = np->fail = nq;
            for(; p->next[v] == q && p != null; p = p->fail) p->next[v] = nq;
        }
    }
}