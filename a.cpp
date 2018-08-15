#include<bits/stdc++.h>
#define N 1234
using namespace std;
char s[N];
int main()
{
	int T; scanf("%d",&T);
	for(int tt = 0;T--;)
	{
		printf("%d ",++tt);
		int p;
		scanf("%d%s",&p,s+1);
		for(int i = 1; i <= strlen(s+1); i++) if(i!=p)printf("%c",s[i]);puts("");
	}
}
