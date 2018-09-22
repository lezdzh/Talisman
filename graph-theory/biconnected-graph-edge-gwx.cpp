//G[i]: 第i个边双联通分量中有哪些点
void tarjan(int u, int pa)
{
    d[u] = l[u] = ++timer;
    for(int i = tail[u]; i; i = e[i].next)
    {
        if(!d[e[i].v])
        {
            st[++top] = i;
            tarjan(e[i].v, u);
            l[u] = min(l[u], l[e[i].v]);
            if(l[e[i].v] >= d[u])
            {
                bcc++;
                while(true)
                {
                    int now = st[top--];
                    if(vst[e[now].u] != bcc)
                    {
                        vst[e[now].u] = bcc;
                        G[bcc].push_back(e[now].u);
                    }
                    if(vst[e[now].v] != bcc)
                    {
                        vst[e[now].v] = bcc;
                        G[bcc].push_back(e[now].v);
                    }
                    if(now == i) break;
                }
            }
        }
        else if(e[i].v != pa)
            l[u] = min(l[u], d[e[i].v]);
    }
}
