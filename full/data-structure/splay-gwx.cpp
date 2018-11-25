struct node
{
    int pa, ch[2], s, f;
}a[maxn];

void flip(int u)
{
    a[u].f ^= 1;    
    swap(a[u].ch[0], a[u].ch[1]);
}

void pushdown(int k)
{
    if(!k)  return;
    int l = a[k].ch[0], r = a[k].ch[1];
    if(a[k].flip)
    {
	flip(l);
	flip(r);
	a[k].flip ^= 1;
    }
}
    
int pre(int u)
{
    u = a[u].ch[0];
    while(a[u].ch[1])
	u = a[u].ch[1];
    return u;
}

int post(int u)
{
    u = a[u].ch[1];
    while(a[u].ch[0])
	u = a[u].ch[0];
    return u;
}

void maintain(int u)
{
    int l = a[u].ch[0], r = a[u].ch[1];
    a[u].s = a[l].s + a[r].s + 1;
}

void rotate(int u)
{
    int x = a[u].pa, y = a[x].pa, d = (a[x].ch[1] == u);
    if(!y)
	root = u;
    else
	a[y].ch[a[y].ch[1] == x] = u;
    a[x].ch[d] = a[u].ch[d ^ 1];
    a[a[u].ch[d ^ 1]].pa = x;
    a[u].ch[d ^ 1] = x;
    a[x].pa = u;
    a[u].pa = y;
    maintain(x);
    maintain(u);
}

void splay(int u, int pa)  //u的父亲为pa
{
    int t;
    for(t = u; a[t].pa != pa; t = a[t].pa)
	st[++top] = t;
    pushdown(t);
    for(; top; top--)
    	pushdown(st[top]);   //pushdown the tags

    while(a[u].pa != pa)
    {
	int x = a[u].pa, y = a[x].pa;
	if(y == pa)
	{
	    rotate(u);
	    return;
	}
	if((a[x].ch[0] == u) ^ (a[y].ch[0] == x))
	    rotate(u);
	else
	    rotate(x);
	rotate(u);
    }
}

void splay2(int u, int &g)  //将u旋转到g
{
    while(u != g)
    {
	int x = a[u].pa, y = a[x].pa;
	if(x == g)
	{
	    rotate(u);
	    return;
	}
	if((a[x].ch[0] == u) ^ (a[y].ch[0] == x))
	    rotate(u);
	else
	    rotate(x);
	rotate(u);
    }
}

int find_kth(int u, int k) 
{
    pushdown(u);
    int size = a[a[u].ch[0]].s;
    if(k <= size)
	return find_kth(a[u].ch[0], k);
    if(k > size + 1)
	return find_kth(a[u].ch[1], k - size - 1);
    return u;
}

int get(int l, int r)
{
    int L = find_kth(root, l), R = find_kth(root, r + 2);  //L = pre(l), R = post(r)
    splay(L, 0);  //splay2(L, root)
    splay(R, L);  //splay2(R, a[root].ch[1])
    return a[R].ch[0];
}

int new_node() //recycle
{
    int res = q.front();
    q.pop();
    a[res].init();
    return res;
}

int build(int l, int r, int pa)
{
    if(l > r)
	return 0;
    int mid = (l + r) >> 1, u = new_node();
    a[u].pa = pa;
    a[u].s = 1;
    a[u].ch[0] = build(l, mid - 1, u);
    a[u].ch[1] = build(mid + 1, r, u);
    maintain(u);
    return u;
}

void recycle(int u)
{
    q.push(u);
    if(a[u].ch[0])
	recycle(a[u].ch[0]);
    if(a[u].ch[1])
	recycle(a[u].ch[1]);
}

void del(int l, int r)
{
    int r = get(l, r);
    recycle(a[r].ch[0]);
    a[a[r].pa].ch[0] = 0;
    maintain(a[r].pa);
    maintain(root);
}
