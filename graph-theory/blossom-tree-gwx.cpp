const int maxn = 50;
const int maxm = 500;

vector <int> G[maxn];
int ans, l[maxm];
int n, m, mx, match[maxn], q[maxn], head, tail;
int pred[maxn], base[maxn], st, fi, nbase;
bool inq[maxn], inb[maxn];
struct edge
{
	int u, v;
}e[maxm];

void push(int u)
{
	q[tail++] = u;
	inq[u] = 1;
}

int pop()
{
	return q[head++];
}

int FindCommonAncestor(int u, int v)
{
	bool inp[maxn];
	for(int i = 0; i < n; i++)
		inp[i] = 0;
	while(true)
	{
		u = base[u];
		inp[u] = 1;
		if(u == st)
			break;
		u = pred[match[u]];
	}
	while(true)
	{
		v = base[v];
		if(inp[v])
			break;
		v = pred[match[v]];
	}
	return v;
}

void ResetTrace(int u)
{
	int v;
	while(base[u] != nbase)
	{
		v = match[u];
		inb[base[u]] = inb[base[v]] = 1;
		u = pred[v];
		if(base[u] != nbase)
			pred[u] = v;
	}
}

void BlossomContract(int u, int v)
{
	nbase = FindCommonAncestor(u, v);
	for(int i = 0; i < n; i++)
		inb[i] = 0;
	ResetTrace(u);
	ResetTrace(v);
	if(base[u] != nbase)
		pred[u] = v;
	if(base[v] != nbase)
		pred[v] = u;
	for(int i = 0; i < n; i++)
		if(inb[base[i]])
		{
			base[i] = nbase;
			if(!inq[i])
				push(i);
		}
}

bool FindAP(int u)
{
	bool found = 0;
	for(int i = 0; i < n; i++)
		pred[i] = -1, base[i] = i;
	for(int i = 0; i < n; i++)
		inq[i] = 0;
	st = u; fi = -1;
	head = tail = 0;
	push(st);
	while(head < tail)
	{
		int u = pop();
		for(int i = G[u].size() - 1; i >= 0; i--)
		{
			int v = G[u][i];
			if(base[u] != base[v] && match[u] != v)
			{
				if(v == st || (match[v] >= 0 && pred[match[v]] >= 0))
					BlossomContract(u, v);
				else if(pred[v] == -1)
				{
					pred[v] = u;
					if(match[v] >= 0)
						push(match[v]);
					else
					{
						fi = v;
						return 1;
					}					
				}
			}	
		}
	}
	return found;
}

void AP()
{
	int u = fi, v, w;
	while(u >= 0)
	{
		v = pred[u];
		w = match[v];
		match[v] = u;
		match[u] = v;
		u = w;	
	}
}

int FindMaxMatching()
{
	int res = 0;
	for(int i = 0 ; i < n; i++)
		match[i] = -1;
	for(int i = 0 ; i < n; i++)
		if(match[i] == -1)
			if(FindAP(i))
				AP();
	for(int i = 0 ; i < n; i++)
		if(match[i] != -1)
			res++;
	return res / 2;
}
