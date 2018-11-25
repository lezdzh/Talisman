const int maxn = 1005;
int n, m;
int S, T, K;
int dist[maxn], cnt[maxn];
bool vst[maxn];
vector<pair<int, int>> G[maxn], H[maxn];    //正图&反图
struct node
{
    ll d;
    int id;
    node(){}
    node(ll d, int id): d(d), id(id) {}
    bool operator< (const node &other) const{
        return d + dist[id] > other.d + dist[other.id];
    }
};

priority_queue <pair<ll, int>> q;
priority_queue <node> Q;

void init()
{
    for(int i = 1; i <= n; ++i) 
        G[i].clear(), H[i].clear(), cnt[i] = 0;
}

void dijkstra(int S)
{
    memset(dist, 127, sizeof(dist));
    memset(vst, 0, sizeof(vst));
    while(!q.empty()) q.pop();
    dist[S] = 0;
    q.push(make_pair(0, S));
    for(int i = 1; i <= n; ++i)
    {
        if(q.empty()) break;
        while(vst[q.top().second]) q.pop();
        int u = q.top().second; q.pop();
        vst[u] = 1;
        for(auto i: H[u])
        {
            if(dist[i.first] > dist[u] + i.second)
            {
                dist[i.first] = dist[u] + i.second;
                q.push(make_pair(-dist[i.first], i.first));
            }
        }
    }
}

int solve()
{
    while(!Q.empty()) Q.pop();
    Q.push(node(0, S));
    while(!Q.empty())
    {
        auto u = Q.top(); Q.pop();
        if(++cnt[u.id] > K) continue;
        if(u.d + dist[u.id] > ti) continue;
        if(u.id == T && cnt[T] == K)
            return u.d;
        for(auto i: G[u.id])
            Q.push(node(u.d + i.second, i.first));
    }
    return -1;
}