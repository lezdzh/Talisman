void add(int now)
{
    int k = 0;
    for(int i = 1; i <= n; i++)
    {
        int c = s[i] - 'A';
        if(!ch[k][c])
            ch[k][c] = ++cnt;
        k = ch[k][c];
    }
    ed[k] = 1;     //或vector全部记录
    id[now] = k;
}

void build()
{
    q.push(0);
    while(!q.empty())
    {
        int u = q.front(), v;
        q.pop();
        for(int i = 0; i < m; i++)
            if(v = ch[u][i])
            {
                int k = pa[u];
                while(k && !ch[k][i])
                    k = pa[k];
                if(u)
                    pa[v] = ch[k][i];
                q.push(v);
            }
            else
                ch[u][i] = ch[pa[u]][i];
    }
}
