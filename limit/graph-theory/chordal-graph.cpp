/*定义	我们称连接环中不相邻的两个点的边为弦. 一个无向图称为弦图, 当
图中任意长度都大于3 的环都至少有一个弦. 弦图的每一个诱导子图一定是
弦图.
单纯点	设N(v)表示与点v相邻的点集. 一个点称为单纯点当v+N(v)的
诱导子图为一个团. 引理: 任何一个弦图都至少有一个单纯点, 不是完全图
的弦图至少有两个不相邻的单纯点.
完美消除序列	一个序列v1, v2, ..., vn满足vi在vi, vi+1, ..., vn的诱导子
图中为一个单纯点. 一个无向图是弦图当且仅当它有一个完美消除序列.
最大势算法	最大势算法能判断一个图是否是弦图. 从n到1的顺序依次给
点标号 标号为i 的点出现在完美消除序列的第i个 . 设labeli表示第i个点
与多少个已标号的点相邻, 每次选择labeli最大的未标号的点进行标号.
然后判断这个序列是否为完美序列. 如果依次判断vi+1, ..., .vn 中
所有与vi相邻的点是否构成一个团, 时间复杂度为O(nm). 考虑优化,
设vi+1, ..., vn中所有与vi 相邻的点依次为vj1,...,vjk. 只需判断vj1是否
与vj2,...,vjk相邻即可. 时间复杂度O(n + m).
弦图的染色	按照完美消除序列中的点倒着给图中的点贪心染尽可能最小
的颜色, 这样一定能用最少的颜色数给图中所有点染色. 弦图的团数=染色
数.
最大独立集	完美消除序列从前往后能选就选. 最大独立集=最小团覆盖.*/

template <int MAXN = 100000, int MAXM = 100000>
struct chordal_graph {
	int n; edge_list <MAXN, MAXM> e;
	int id[MAXN], seq[MAXN];
	void init () {
		struct point {
			int lab, u;
			point (int lab = 0, int u = 0) : lab (lab), u (u) {}
			bool operator < (const point &a) const { return lab < a.lab; } };
		std::fill (id, id + n, -1);
		static int label[MAXN]; std::fill (label, label + n, 0);
		std::priority_queue <point> q;
		for (int i = 0; i < n; ++i) q.push (point (0, i));
		for (int i = n - 1; i >= 0; --i) {
			for (; ~id[q.top ().u]; ) q.pop ();
			int u = q.top ().u; q.pop (); id[u] = i;
			for (int j = e.begin[u], v; ~j; j = e.next[j])
				if (v = e.dest[j], !~id[v]) ++label[v], q.push (point (label[v], v)); }
		for (int i = 0; i < n; ++i) seq[id[i]] = i; }
	bool is_chordal () {
		static int vis[MAXN], q[MAXN]; std::fill (vis, vis + n, -1);
		for (int i = n - 1; i >= 0; --i) {
			int u = seq[i], t = 0, v;
			for (int j = e.begin[u]; ~j; j = e.next[j])
				if (v = e.dest[j], id[v] > id[u]) q[t++] = v;
			if (!t) continue; int w = q[0];
			for (int j = 0; j < t; ++j) if (id[q[j]] < id[w]) w = q[j];
			for (int j = e.begin[w]; ~j; j = e.next[j]) vis[e.dest[j]] = i;
			for (int j = 0; j < t; ++j) if (q[j] != w && vis[q[j]] != i) return 0;
		}
		return 1; }
	int min_color () {
		int res = 0;
		static int vis[MAXN], c[MAXN];
		std::fill (vis, vis + n, -1);
		std::fill (c, c + n, n);
		for (int i = n - 1; i >= 0; --i) {
			int u = seq[i];
			for (int j = e.begin[u]; ~j; j = e.next[j]) vis[c[e.dest[j]]] = i;
			int k; for (k = 0; vis[k] == i; ++k);
			c[u] = k; res = std::max (res, k + 1);
		}
		return res; } };