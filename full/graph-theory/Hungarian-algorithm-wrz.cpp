bool match(int x)
{
    for(int i = last[x]; i; i = e[i].next)
    {
        int y = e[i].to; 
        if(vis[y])continue;
        vis[y] = 1;
        if(!mat[y] || match(mat[y]))
        {
            mat[y] = x;
            return 1;
        }
    }
    return 0;
}
void check()
{
    for(int i = 1; i <= n; i++)
    {
        memset(vis,0,sizeof(vis));
        if(match(i))ans++;
    }
}