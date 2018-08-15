const int INF = 1 << 29; // 有时候要开longlong
int dis[N], inq[N];
struct item{int x, dis;};
bool operator < (item a, item b){return a.dis > b.dis;}
void dijk(int S) // S为源点，dis数组即到各点最短路
{
	for(int i = 1; i <= n; i++) dis[i] = INF;
	priority_queue<item> q;
	q.push((item){S, dis[S] = 0});
	for(; !q.empty(); )
	{
		int x = q.top().x; q.pop();
		if(inq[x]) continue; inq[x] = 1;
		for(int i = last[x]; i; i = e[i].next)
		{
			int y = e[i].to;
			if(dis[x] + e[i].val < dis[y])
				q.push((item){y, dis[y] = dis[x] + e[i].val});
		}
	}
}