//…¢ÒŠpoj¹ûî}2774
#include<cstdio>
#include<cstring>
#define sz 100010*2
char s[sz],ss[sz];
int L,tot=0,fa[sz*2],son[sz*2][27],step[sz*2],first,last,right[sz*2];
int qq[sz*2],son2[sz*2][27];
int sa[sz],sa_n,rank[sz],height[sz];
bool sign[sz*2],cov[sz*2],ok;
void add(char c)
{	int p=last,np=++tot; step[np]=step[last]+1;
	for(;p&&!son[p][c];p=fa[p]) son[p][c]=np;
	if(!p) fa[np]=first;
	else if(step[son[p][c]]==step[p]+1){fa[np]=son[p][c]; sign[son[p][c]]=1;}
	else
	{	int q=son[p][c],nq=++tot;
		fa[nq]=fa[q]; for(int i=0;i<=26;i++) son[nq][i]=son[q][i];
		step[nq]=step[p]+1; fa[q]=fa[np]=nq; sign[nq]=1;
		for(;p&&son[p][c]==q;p=fa[p]) son[p][c]=nq;
	}last=np;
}
void dfs(int x)
{	ok=1; for(int i=0+(x==1);i<=26;i++) if(son2[x][i]){dfs(son2[x][i]); ok=0;}
	if(ok){sa[++sa_n]=L-right[x]+1; rank[sa[sa_n]]=sa_n;}
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("out.txt","w",stdout);
	int i,j,k,len,op,ed,x;
	scanf("%s",s+1); len=strlen(s+1); s[len+1]='a'-1;
	L=0; for(i=len+1;i>=1;i--) ss[++L]=s[i];
	tot=first=last=sign[1]=1; step[1]=0;
	for(i=1;i<=L;i++) add(ss[i]-'a'+1);
	op=ed=0; for(i=1;i<=tot;i++) if(!sign[i]) qq[++ed]=i;
	while(op<ed)
	{	x=qq[++op];
		if(!right[x]) right[x]=step[x];
		if(fa[x]&&!right[fa[x]]) right[fa[x]]=right[x];
		if(fa[x]&&!cov[fa[x]]){qq[++ed]=fa[x]; cov[fa[x]]=1;}
	}
	for(i=1;++i<=tot;son2[fa[i]][s[L-right[i]+step[fa[i]]+1]-'a'+1]=i);
	sa_n=0; dfs(1);
	for(i=1,k=0;i<=len;height[rank[i++]]=k)
		for(k?k--:0,j=sa[rank[i]-1];s[i+k]==s[j+k];k++);
	printf("%d\n",tot);
	for(int i=1;i<=tot;i++)printf("%d ",right[i]);puts("");
	printf("SuffixArray\n"); for(i=1;i<=len;i++) printf("%d ",sa[i]); printf("\n");
	printf("Rank\n"); for(i=1;i<=len;i++) printf("%d ",rank[i]); printf("\n");
	printf("Height\n"); for(i=1;i<=len;i++) printf("%d ",height[i]); printf("\n");
	return 0;
}

