struct heap 
{ 
	heap *ch[2]; 
	int dis, siz, v; 
}mem[N*2], *h[N], *null, *tot; 
heap* newheap()
{
	heap *p = ++tot; 
	*p = *null; 
	return p;
} 
void init() 
{ 
	null = tot = mem; 
	null->ch[0] = null->ch[1] = null; 
	null->v = null->dis = null->siz = 0; 
	for(int i = 1; i <= n; i++) h[i] = null; 
} 
heap *merge(heap *x, heap *y) // big 
{
	if(x == null) return y; 
	if(y == null) return x; 
	if(x->v < y->v) swap(x, y); 
	x->ch[1] = merge(x->ch[1], y); 
	if(x->ch[0]->dis < x->ch[1]->dis) swap(x->ch[0], x->ch[1]); 
	x->dis = x->ch[1]->dis + 1; 
	x->siz = x->ch[0]->siz + x->ch[1]->siz + 1; 
	return x; 
} 
heap *pop(heap *x){return merge(x->ch[0], x->ch[1]);}
int main()
{
	init();
	heap *a = newheap(); a->siz = 1; a->v = 233;
	heap *b = newheap(); b->siz = 1; b->v = 233;
	heap *c = merge(a, b);
}

