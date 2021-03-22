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
const int maxn = 5e3+5;
int head[maxn],tot;
struct Edge{
    int to,next;
}e[maxn*10];
void add_e(int u,int v)
{
    e[tot]={v,head[u]};
    head[u]=tot++;
}
bool vis[maxn];
int dfn[maxn],low[maxn],cnt,Time;
int col[maxn];
vector<int>vec[maxn];
stack<int>sk;
int num[maxn],In[maxn];
void init()
{
    Time=cnt=tot=0;
    while (!sk.empty()) sk.pop();
    for(int i=0;i<maxn;i++)
        In[i]=0,num[i]=col[i]=dfn[i]=low[i]=0,vec[i].clear(),head[i]=-1,vis[i]=false;
}
void  Tarjan(int x)
{
    vis[x]=true;
    dfn[x]=low[x]=++Time;
    sk.push(x);
    for(int i=head[x];i!=-1;i=e[i].next)
    {
        int y=e[i].to;
        if(!dfn[y]) Tarjan(y),low[x]=min(low[x],low[y]);
        else if(vis[y]) low[x]=min(low[x],low[y]);
    }
    if(dfn[x]==low[x])
    {
        int y; ++cnt;
        do{
            y=sk.top(); sk.pop();
            vis[y]=false;
            col[y]=cnt;
            num[cnt]++;
            vec[cnt].push_back(y);
        }while (x!=y);
    }
}
int n,m;
int U[maxn*10],V[maxn*10];
int dp[maxn];
void dfs(int x,int fa)
{
     dp[fa]+=num[x];
     vis[x]=true;
     for(int i=head[x];i!=-1;i=e[i].next)
     {
         int y=e[i].to;
         if(!vis[y]) dfs(y,fa);
     }
}
int ans[maxn],N;
void solve(int cas)
{
     int Max=0;
     for(int i=1;i<=cnt;i++)
     {
         if(In[i]==0)
         {
             memset(vis,false,sizeof(vis));
             dfs(i,i);
         }
     }
     for(int i=1;i<=cnt;i++) Max=max(Max,dp[i]);

     N=0;
     for(int i=1;i<=cnt;i++)
         if(Max==dp[i])
         {
             for(int j=0;j<num[i];j++)
                 ans[++N]=vec[i][j];
         }

     printf("Case %d: %d\n",cas,Max-1);

     sort(ans+1,ans+N+1);

     printf("%d",ans[1]-1);
     for(int i=2;i<=N;i++)
         printf(" %d",ans[i]-1);

     printf("\n");
}

int main()
{
    int t=read(),cas=0;
    while (t--)
    {
        init(); ++cas;
        n=read(),m=read();
        for(int i=1;i<=m;i++)
        {
            int u=read(),v=read();
            u++,v++; U[i]=u,V[i]=v;
            add_e(u,v);
        }

        for(int i=1;i<=n;i++)
            if(!dfn[i]) Tarjan(i);

        tot=0;
        memset(dp,0,sizeof(dp));
        memset(head,-1,sizeof(head));
        for(int i=1;i<=m;i++)
            if(col[U[i]]!=col[V[i]])
            {
                int u=col[U[i]],v=col[V[i]];
                add_e(v,u),In[u]++;
            }

        solve(cas);
    }
    return 0;
}
/*
2
6 7
0 1
1 2
2 0
2 3
3 4
4 5
5 3
Case 1: 5
3 4 5

1
4 3
0 1
2 1
1 3
Case 1: 3
3

3
6 6
0 1
0 2
2 3
1 3
1 5
2 4

Case 1: 4
3

 */
