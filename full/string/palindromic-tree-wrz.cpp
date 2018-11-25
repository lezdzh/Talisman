char s[N], out[N];
struct PT
{
    PT *fail, *next[A];
    int len;
}mem[N], *tot, *null, *root1, *root0, *last;
PT *newPT()
{
    PT *p = ++tot;
    *p = *null; return p;
}
void init()
{
    null = tot = mem;
    null->fail = null;
    for(int i = 0; i < A; i++) null->next[i] = null;
    null->len = 0;
    root1 = newPT(); root1->fail = root1; root1->len = -1;
    root0 = newPT(); root0->fail = root1; last = root1;
}
int extend(int c, int i) // 返回这一次是否多了一个回文子串
{
    PT *p = last;
    for(; s[i-p->len-1] != c+'a'; p = p->fail);
    if(p->next[c] != null) {last = p->next[c]; return 0;}
    PT *np = p->next[c] = last = newPT(); np->len = p->len + 2;
    if(p->len == -1) np->fail = root0;
    else 
    {
        for(p=p->fail; s[i-p->len-1] != c+'a'; p = p->fail);
        np->fail = p->next[c];
    }
    return 1;
}
void main()
{
    scanf("%s",s+1); init();
    for(int i = 1, ii = strlen(s+1); i <= ii; i++)
        out[i] = extend(s[i]-'a', i)?'1':'0';
    puts(out+1);
}