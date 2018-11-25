#define N 1000005 // (10^9)^(2/3)
#define M 3333331 // hash siz
int prime[N], notprime[N], pcnt, mu[N], pre[N];
int hash[M], nocnt; struct node{int id, f, next;}no[1000000];
int F(int n) // calculate mu[1]+mu[2]+...+mu[n]
{
	if(n<N) return pre[n];
	int h = n%M; for(int i = hash[h]; i; i = no[i].next) if(no[i].id == n) return no[i].f;
	int ret = 1;
	for(int i = 2, j; i <= n; i = j + 1)
	{
		j = n/(n/i);
		ret -= F(n/i) * (j-i+1);
	}
	no[++nocnt] = (node){n, ret, hash[h]};
	hash[h] = nocnt;
	return ret;
}
void init()
{
    mu[1] = 1;
    for(int i = 2; i < N; i++)
    {
        if(!notprime[i]) prime[++pcnt] = i, mu[i] = -1;
        for(int j = 1; j <= pcnt && prime[j] * i < N; j++) 
        {
            notprime[prime[j] * i] = 1;
            if(i % prime[j]) mu[prime[j] * i] = -mu[i]; 
            else {mu[prime[j] * i] = 0; break;}
        }
    }
    for(int i = 1; i < N; i++) pre[i] = pre[i-1] + mu[i];
}

/*
	用之前必须先init()
	如果n很大，求和记得开long long
	如果有取模，求和记得改取模
*/