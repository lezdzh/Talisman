#include <cstdio>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;

typedef long long ll;
#define min(a, b)  ((a) < (b) ? (a) : (b))
#define max(a, b)  ((a) > (b) ? (a) : (b))
#define ABS(x)  ((x) > 0 ? (x) : (-(x)))

const int maxn = 1e5 + 5;
int cnt, root;
struct node
{
	int pri, val, c, s;
	int ch[2];
	int cmp(int x) const {
		if(x == val) return -1;
		return x < val ? 0 : 1;
	}
} a[maxn];

void maintain(int u)  {
	a[u].s = a[u].c + a[a[u].ch[0]].s + a[a[u].ch[1]].s;
}

void rotate(int &u, int d)
{
	int tmp = a[u].ch[d ^ 1];
	a[u].ch[d ^ 1] = a[tmp].ch[d];
	a[tmp].ch[d] = u;
	maintain(u); maintain(tmp);
	u = tmp;
}

void insert(int &u, int val)
{
	if(!u)  {u = ++cnt; a[cnt] = (node){rand(), val, 1, 1}; return;}
	a[u].s++;
	int d = a[u].cmp(val);
	if(d == -1)  {a[u].c++; return;}
	insert(a[u].ch[d], val);
	if(a[a[u].ch[d]].pri > a[u].pri) rotate(u, d ^ 1);
}

int find(int u, int val, int comp, int &res)
{
	int d = a[u].cmp(val);
	if(!u) return -1;
	if(d == -1) return u;
	if(d == comp)
	{
		if(d) res = max(res, a[u].val);
		else res = min(res, a[u].val);
	}
	return find(a[u].ch[d], val, comp, res);
}

void remove(int &u)
{
	if(!a[u].ch[0]) u = a[u].ch[1];
	else if(!a[u].ch[1]) u = a[u].ch[0];
	else
	{
		int d = a[a[u].ch[0]].pri < a[a[u].ch[1]].pri ? 0 : 1;
		rotate(u, d); remove(a[u].ch[d]);
	}
}

void del(int &u, int val)
{
	if(find(root, val, -2, val) == -1) return;
	a[u].s--;
	int d = a[u].cmp(val);
	if(d == -1)
	{
		a[u].c--;
		if(!a[u].c) remove(u);
	}
	else del(a[u].ch[d], val);
}

int find_rank(int u, int val)
{
	int d = a[u].cmp(val);
	if(d == -1) return 1 + a[a[u].ch[0]].s;
	if(d == 0) return find_rank(a[u].ch[0], val);
	return a[u].s - a[a[u].ch[1]].s + find_rank(a[u].ch[1], val);
}

int find_k(int u, int k)
{
	if(k <= a[a[u].ch[0]].s) return find_k(a[u].ch[0], k);
	if(k > a[a[u].ch[0]].s + a[u].c) return find_k(a[u].ch[1], k - a[a[u].ch[0]].s - a[u].c);
	return a[u].val;
}

int pre(int val)
{
	int ans = INT_MIN;
	int pos = find(root, val, 1, ans);
	if(pos != -1 && a[pos].ch[0])
	{
		pos = a[pos].ch[0];
		while(a[pos].ch[1]) pos = a[pos].ch[1];
		ans = max(ans, a[pos].val);
	}
	return ans;
}

int post(int val)
{
	int ans = INT_MAX;
	int pos = find(root, val, 0, ans);
	if(pos != -1 && a[pos].ch[1])
	{
		pos = a[pos].ch[1];
		while(a[pos].ch[0]) pos = a[pos].ch[0];
		ans = min(ans, a[pos].val);
	}
	return ans;
}

int main()
{
	srand(19991014);
	int n, opt, x;
	scanf("%d", &n);
	while(n--)
	{
		scanf("%d%d", &opt, &x);
		switch(opt) {
		case 1: insert(root, x); break;
		case 2: del(root, x); break;
		case 3: printf("%d\n", find_rank(root, x)); break;
		case 4: printf("%d\n", find_k(root, x)); break;
		case 5: printf("%d\n", pre(x)); break;
		case 6: printf("%d\n", post(x)); break;
		}
	}
	return 0;
}
