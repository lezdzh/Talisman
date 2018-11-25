//zkw-segment-tree
int n, M, q;
int d[N << 1];  
inline void build(int n) {  
    for(M = 1; M < n; M <<= 1);  
    for(int i = M + 1; i <= M + n; i++) t[i] = in();
    //sum
    for(int i = M - 1; i; --i) d[i] = d[i << 1] + d[i << 1 | 1]; 
    //max
    for(int i = M - 1; i; --i) d[i] = max(d[i << 1], d[i << 1 | 1]);  
    //min  
    for(int i = M - 1; i; --i) d[i] = min(d[i << 1], d[i << 1 | 1]);  
}  

//单点修改
void change(int x, int v) {  
    t[x = M + x] += v;  
    while(x) d[x >>= 1] = d[x << 1] + d[x << 1 | 1];  
}  

//区间查询
int Sum(int s,int t,int Ans=0){  
    for (s = s + M - 1, t = t + M + 1; s ^ t ^ 1; s >>= 1, t >>= 1) {  
        if(~ s & 1) Ans += d[s ^ 1];  
        if(t & 1) Ans += d[t ^ 1];  
    }
    return Ans;  
} 
    void Sum(int s,int t,int L=0,int R=0){  
        for(s=s+M-1,t=t+M+1;s^t^1;s>>=1,t>>=1){  
            L+=d[s],R+=d[t];  
            if(~s&1) L=min(L,d[s^1]);  
            if(t&1) R=min(R,d[t^1]);  
        }  
        int res=min(L,R);while(s) res+=d[s>>=1];  
    }  
//单点查询
//差分，当前点的值为该点和其父节点的差值
void build(int n) {  
    for(M = 1; M <= n + 1; M <<= 1);
    for(int i = M + 1; i <= M + n; i++) d[i] = in();  
    for(int i = M - 1; i; --i) {
    	d[i] = min(d[i << 1], d[i << 1 | 1]), 
    	d[i << 1] -= d[i], 
    	d[i << 1 | 1] -= d[i];
    }  
} 

void Sum(int x, int res = 0) {  
    while(x) res += d[x], x >>= 1;
    return res;  
} 
//区间最小(差分)
void Sum(int s, int t, int L = 0, int R = 0) {  
    for(s = s + M - 1, t = t + M + 1; s ^ t ^ 1; s >>= 1, t >>= 1) {  
        L += d[s], R += d[t];  
        if(~ s & 1) L = min(L, d[s ^ 1]);  
        if(t & 1) R = min(R, d[t ^ 1]);  
    }  
    int res = min(L, R);
    while(s) res += d[s >>= 1];  
}    
//区间加法，维护最小值(差分)
void Add(int s, int t, int v, int A = 0) {  
    for(s = s + M - 1, t = t + M + 1; s ^ t ^ 1;s >>= 1, t >>= 1) {  
        if(~ s & 1) d[s ^ 1] += v;
        if(t & 1) d[t ^ 1] += v;  
        A = min(d[s], d[s ^ 1]);
        d[s] -= A, d[s ^ 1] -= A, d[s >> 1] += A;  
        A = min(d[t], d[t^1]);
        d[t] -= A, d[t ^ 1] -=A, d[t >> 1] += A;  
    }  
    while(s) {
    	A = min(d[s], d[s ^ 1]), 
    	d[s] -= A, 
    	d[s ^ 1] -= A,
    	d[s >>= 1] += A;
    }  
}  

 
