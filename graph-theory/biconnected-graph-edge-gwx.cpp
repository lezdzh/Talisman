//G[i]: 第i个边双联通分量中有哪些点
void tarjan(int u, int pa)
{
    d[u] = l[u] = ++timer;
    for(int i = t[u]; i; i = a[i].next)
    {
        if(!d[a[i].v])
        {
            st[++top] = i;
            tarjan(a[i].v, u);
            l[u] = min(l[u], l[a[i].v]);
            if(l[a[i].v] >= d[u])
            {
                bcc++;
                while(true)
                {
                    int now = st[top--];
                    if(vst[a[now].u] != bcc)
                    {
                        vst[a[now].u] = bcc;
                        G[bcc].push_back(a[now].u);
                    }
                    if(vst[a[now].v] != bcc)
                    {
                        vst[a[now].v] = bcc;
                        G[bcc].push_back(a[now].v);
                    }
                    if(now == i)
                        break;
                }
            }
        }
        else if(a[i].v != pa)
            l[u] = min(l[u], d[a[i].v]);
    }
}
