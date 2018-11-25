#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define BASE 10000
#define L 20005
using namespace std;
int p;
char s[10*L];
struct bigint
{
	int num[L], len;
	bigint(int x = 0)
	{
		memset(num,0,sizeof(num));
		len = 1;
		num[0] = x;
	}
	bigint operator + (bigint b)
	{
		bigint c;
		c.len = max(b.len, len);
		for(int i = 0; i < c.len; i++)
		{
			c.num[i] += num[i] + b.num[i];
			c.num[i+1] = c.num[i] / BASE;
			c.num[i] %= BASE;
		}
		if(c.num[c.len])c.len++;
		return c;
	}
	bigint operator - (bigint b)
	{
		bigint c;
		c.len = max(len, b.len);
		for(int i = 0; i < c.len; i++)
		{
			c.num[i] += num[i] - b.num[i];
			if(c.num[i] < 0)
			{
				c.num[i] += BASE;
				c.num[i+1]--;
			}
		}
		while(!c.num[c.len-1] && c.len > 1)c.len--;
		return c;
	} 
	void operator -= (int b)
	{
		num[0] -= b;
		for(int i = 0; i < len; i++)
		{
			num[i+1] += num[i] / BASE;
			num[i] %= BASE;
			if(num[i] < 0)num[i] += BASE, num[i+1]--;
		}
		while(!num[len-1] && len > 1) len--;
	}
	bigint operator * (bigint b)
	{
		bigint c;
		c.len = len + b.len;
		for(int i = 0; i < len; i++)
		{
			for(int j = 0; j < b.len; j++)
			{
				c.num[i+j] += num[i] * b.num[j];
				c.num[i+j+1] += c.num[i+j] / BASE;
				c.num[i+j] %= BASE;
			}
		}
		if(!c.num[c.len-1] && c.len > 1)c.len--;
		return c;
	}
	bigint operator * (int b)
	{
		bigint c;
		for(int i = 0; i < len; i++)
			c.num[i] = num[i] * b; // long long
		for(int i = 0; i < len; i++)
		{
			c.num[i+1] += c.num[i] / BASE;
			c.num[i] %= BASE;
		}
		c.len = len;
		while(c.num[c.len])c.len++;
		return c;
	}
	bool substract(bigint b, int pos)
	{
		if(len < b.len - pos)return false;
		else if(len == b.len-pos)
			for(int i = len-1; i>=0; i--)
				if(num[i] < b.num[i+pos])return false;
				else if(num[i] > b.num[i+pos])break;
		for(int i = 0; i < len; i++)
		{
			num[i] -= b.num[i+pos];
			if(num[i] < 0)
			{
				num[i] += BASE;
				num[i+1] --;
			}
		}
		while(!num[len-1] && len > 1)len--;
		return true;
	}

	// remember to change [BASE] to 10 !!!
	// [this] is the remainder
	bigint operator / (bigint b) 
	{
		bigint c;
		if(len < b.len)return c;
		int k = len - b.len;
		c.len = k + 1;  
		for(int i = len-1; i>=0; i--)
		{
			if(i>=k)b.num[i] = b.num[i-k];
			else b.num[i] = 0;
		}
		b.len = len;
		for(int i = 0; i <= k; i++)
			while(this->substract(b,i)) c.num[k-i]++;
		for(int i = 0; i < c.len; i++)
		{
			c.num[i+1] += c.num[i] / BASE;
			c.num[i] %= BASE;
		}
		while(!c.num[c.len-1] && c.len > 0) c.len--; 
		return c;
	}

	// [this] is not the remainder
	bigint operator / (int b)
	{
		bigint c;
		int tmp = 0;
		for(int i = len-1; i>=0; i--)
		{
			tmp = tmp * BASE + num[i];
			c.num[i] = tmp / b;
			tmp %= b;
		}
		for(c.len = len; !c.num[c.len-1] && c.len > 1; c.len--);
		return c;
	}
	bool scan()
	{
		int n = -1;
		char ch = getchar();
		while(ch < '0' || ch > '9') if(ch == EOF)return false; else ch = getchar();
		while(ch >= '0' && ch <= '9') s[++n] = ch - '0', ch = getchar();
		len = 0;
		for(int i = n; i >= 0; i-=4)
		{
			num[len] += s[i];
			if(i>=1)num[len] += s[i-1] * 10;
			if(i>=2)num[len] += s[i-2] * 100;
			if(i>=3)num[len] += s[i-3] * 1000;
			++len;
		}
		return true;
	}
	void clr()
	{
		memset(num,0,sizeof(num));
	}
	void print()
	{
		printf("%d",num[len-1]);
		for(int i = len-2; i>=0; i--)
			printf("%04d",num[i]);
		printf("\n");
	}
};