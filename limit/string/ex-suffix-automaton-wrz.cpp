struct sam
{
	sam *fail, *next[A]; int len;
}mem[N<<1], *tot, *null, *root;
sam* newsam(){*++tot = *null;return tot;}
void init()
{
	null = tot = mem; null->fail = null; null->len = 0;
	for(int i = 0; i < A; i++) null->next[i] = null;
	root = newsam();
}
sam* extend(sam *p, int v)
{
	if(p->next[v] != null)
	{
		sam *q = p->next[v];
		if(p->len + 1 == q->len) return q;
		else
		{
			sam *nq = newsam(); *nq = *q; nq->len = p->len + 1; 
			q->fail = nq;
			for(; p->next[v] == q && p != null; p = p->fail) p->next[v] = nq;
			return nq;
		}
	}
	else
	{
		sam *np = newsam(); np->len = p->len + 1;
		for(; p->next[v] == null && p != null; p = p->fail) p->next[v] = np;
		if(p == null) np->fail = root;
		else
		{
			sam *q = p->next[v];
			if(p->len + 1 == q->len) np->fail = q;
			else
			{
				sam *nq = newsam(); *nq = *q; nq->len = p->len + 1;
				np->fail = q->fail = nq;
				for(; p->next[v] == q && p != null; p = p->fail) p->next[v] = nq;
			}
		}
		return np;
	}
}
void build_tree(){for(sam *i = tot; i != mem; i--) addedge(i->fail - mem, i - mem);}