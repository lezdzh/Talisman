void KMP_next(char *s, int len, int *next)
{
    next[1] = 0; int p = 0;
    for(int i = 2; i <= len; i++)
    {
        for(; s[p+1] != s[i] && p; p = next[p]);
        if(s[p+1] == s[i]) ++p;
        next[i] = p;
    }
}