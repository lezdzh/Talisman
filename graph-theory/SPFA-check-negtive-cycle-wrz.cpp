int inq[N], inqt[N], dis[N];
bool SPFA()
{
	queue<int> q;
	for(int i = 1; i <= n; i++) dis[i] = 0, q.push(i), inq[i] = 1; // 全部入队
	for(; !q.empty(); )
	{
		int x = q.front(); q.pop(); inq[x] = 0;
		for(int i = last[x]; i; i = e[i].next)
		{
			int y = e[i].to; 
			if(dis[x] + e[i].val < dis[y])
			{
				dis[y] = dis[x] + e[i].val;
				if(!inq[y])
				{
					if(++inqt[y] > n) return false; // 入队n次即有负环
					inq[y] = 1;
					q.push(y);
				}
			}
		}
	}
	return true;
}
/*
	步骤：
	1.建好原图
	2.SPFA() // 若返回为true表示无负环，false表示有负环
	
	多次调用时记得清空inqt等数组
	有负环时理论复杂度是O(n^2)的
*/