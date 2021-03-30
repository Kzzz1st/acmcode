#include <set>
#include <map>
#include <list>
#include <cmath>
#include <stack>
#include <queue>
#include <string>
#include <bitset>
#include <vector>
#include<cstring>
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
#define INF 0x3f3f3f3f
typedef unsigned long long ull;
inline int read(){int s=0,w=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();return s*w;}
const int maxn = 5e4+5;
struct E{
    int to,next;
}e[maxn<<2];
int tot,head[maxn];
void add_e(int u,int v)
{
    e[tot]={v,head[u]};
    head[u]=tot++;
}
int dp[15][maxn];
int vec[15],cnt;
int Val;
int p[11]={1,2,4,8,16,32,64,128,256,512,1024};

int dfs(int pos,int sta,bool limit)
{
    if(pos==-1) return sta>=0;
    if(!limit&&dp[pos][sta]!=-1) return dp[pos][sta];
    int up=limit?vec[pos]:9;
    int ans=0;
    for(int i=0;i<=up;i++)
    {
        int x=i*p[pos];
        if((sta-x)<0) continue;
        ans+=dfs(pos-1,sta-x,limit&&i==vec[pos]);
    }
    if(!limit) dp[pos][sta]=ans;

    return ans;
}
int solve(int n)
{
    cnt=0;
    while (n) vec[cnt++]=n%10,n/=10;
    return dfs(cnt-1,Val,true);
}
int main()
{
    int t=read(),cas=0;
    memset(dp,-1,sizeof(dp));
    while (t--)
    {
        int a=read(),b=read();
        Val=0;
        cnt=0;
        if(a==0) vec[cnt++]=0;
        else {
            while (a) vec[cnt++]=a%10,a/=10;
        }
        Val+=vec[0];
        for(int i=1;i<cnt;i++)
            Val+=vec[i]*p[i];

        printf("Case #%d: %d\n",++cas,solve(b));
    }
    return 0;
}
