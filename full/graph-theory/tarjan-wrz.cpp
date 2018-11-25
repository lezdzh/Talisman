void tarjan(int x) // 找割点
{
    low[x] = dfn[x] = ++timer;
    int siz = 0;
    for(int i = last[x]; i; i = e[i].next)
    {
        int y = e[i].to;
        if(!dfn[y])
        {
            tarjan(y); siz++;
            cmin(low[x], low[y]);
            if(x != 1 && low[y] >= dfn[x]) cut[x] = 1;
        }
        else cmin(low[x], dfn[y]);
    }
    if(x == 1 && siz > 1) cut[1] = 1; 
}

void tarjan(int x) // 有向图 缩
{
    dfn[x] = low[x] = ++timer; sta[++stacnt] = x; insta[x] = 1;
    for(int i = last[x]; i; i = e[i].next)
    {
        int y = e[i].to; 
        if(!dfn[y]) tarjan(y), low[x] = min(low[x], low[y]); // 根据不同需求适当修改
        else if(insta[y])low[x] = min(low[x], dfn[y]);
    }
    if(low[x] == dfn[x])
    {
        bel[x] = ++bcnt; insta[x] = 0;
        for(; sta[stacnt] != x; stacnt--)
            bel[sta[stacnt]] = bcnt, insta[sta[stacnt]] = 0;
        stacnt--;
    }
}