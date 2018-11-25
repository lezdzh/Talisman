struct ACAM
{
    ACAM *next[S], *fail;
    int ban;
}mem[N], *tot, *null, *root, *q[N];
ACAM *newACAM()
{
    ACAM *p = ++tot;
    *p = *null; return p;
}
void init()
{
    null = tot = mem;
    for(int i = 0; i < alpha; i++) null->next[i] = null;
    null->fail = null; null->ban = 0;
    root = newACAM();
}
void inser(char *s)
{
    ACAM *p = root;
    for(int i = 0; s[i]; i++)
    {
        int w = s[i] - 'a';
        if(p->next[w] == null) p->next[w] = newACAM();
        p = p->next[w];
    }
    p->ban = 1;
}
void build()
{
    root->fail = root; int head = 0, tail = 0;
    for(int i = 0; i < alpha; i++)
    {
        if(root->next[i] == null) root->next[i] = root;
        else root->next[i]->fail = root, q[tail++] = root->next[i];
    }
    for(; head < tail; head++)
    {
        ACAM *p = q[head];
        p->ban |= p->fail->ban;
        for(int i = 0; i < alpha; i++)
        {
            if(p->next[i] == null) p->next[i] = p->fail->next[i];
            else p->next[i]->fail = p->fail->next[i], q[tail++] = p->next[i];
        }
    }
}