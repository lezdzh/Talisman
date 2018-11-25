// 对都是数字的数组做SA时要保证数组中没有0，否则height等可能由于s[0]=s[n+1]=0出问题
// 多次使用要保证s[0]=s[n+1]=0
char s[N];
int n, t1[N], t2[N], sa[N], rank[N], sum[N], height[N], lef, rig; // 数组开两倍
void SA_build()
{
    int *x = t1, *y = t2, m = 30;
    for(int i = 1; i <= n; i++) sum[x[i] = s[i] - 'a' + 1]++;
    for(int i = 1; i <= m; i++) sum[i] += sum[i-1];
    for(int i = n; i >= 1; i--) sa[sum[x[i]]--] = i;
    for(int k = 1; k <= n; k <<= 1)
    {
        int p = 0;
        for(int i = n-k+1; i <= n; i++) y[++p] = i;
        for(int i = 1; i <= n; i++) if(sa[i] - k > 0) y[++p] = sa[i] - k;

        for(int i = 1; i <= m; i++) sum[i] = 0;
        for(int i = 1; i <= n; i++) sum[x[i]]++;
        for(int i = 1; i <= m; i++) sum[i] += sum[i-1];
        for(int i = n; i >= 1; i--) sa[sum[x[y[i]]]--] = y[i];

        swap(x, y);
        for(int i = 1; i <= n; i++)
            x[sa[i]] = x[sa[i-1]] + (y[sa[i]] == y[sa[i-1]] && y[sa[i]+k] == y[sa[i-1]+k] ? 0 : 1);
        m = x[sa[n]];
        if(m == n) break;
    }
    for(int i = 1; i <= n; i++) rank[sa[i]] = i;
    for(int i = 1, k = 0; i <= n; height[rank[i++]] = k?k--:k)
        for(; s[i+k] == s[sa[ran[i]-1]+k] && i+k <= n && sa[ran[i]-1]+k <= n; k++);
}
