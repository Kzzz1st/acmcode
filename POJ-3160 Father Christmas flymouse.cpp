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
#define ls rt<<1
#define rs rt<<1|1
using namespace std;
typedef long long ll;
#define INF 0x3f3f3f3f
typedef unsigned long long ull;
inline int read(){int s=0,w=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();return s*w;}
const int maxn = 2e5+5;
int tot,head[maxn];
int dnf[maxn],low[maxn],vis[maxn],Time;
struct Edge{
    int to,next;
}edge[maxn];
stack<int>sk;
int a[maxn],Col;
void add_edge(int u,int v)
{
    edge[tot].to=v;
    edge[tot].next=head[u];
    head[u]=tot++;
}
int g[maxn],sum[maxn];
void Tarjan(int x)
{
    vis[x]=1;
    dnf[x]=low[x]=++Time;
    sk.push(x);
    for(int i=head[x];i!=-1;i=edge[i].next)
    {
        int y=edge[i].to;
        if(!dnf[y]) Tarjan(y),low[x]=min(low[y],low[x]);
        else if(vis[y]) low[x]=min(low[x],low[y]);
    }
    if(dnf[x]==low[x])
    {
        int y; Col++;
        sum[Col]+=g[x];
        while (true)
        {
            y=sk.top(); sk.pop();
            vis[y]=0; a[y]=Col;
            if(x==y) break;
            sum[Col]+=g[y];
        }
    }
}
int u[maxn],v[maxn],m,n;
int In[maxn],dp[maxn];
void Topsort()
{
    queue<int>q;
    for(int i=1;i<=n;i++) dp[i]=sum[i];

    for(int i=1;i<=Col;i++) if(In[i]==0) q.push(i);

    while (!q.empty())
    {
        int x=q.front(); q.pop();
        for(int i=head[x];i!=-1;i=edge[i].next)
        {
            int y=edge[i].to;
            if(--In[y]==0) q.push(y);
            dp[y]=max(dp[y],sum[y]+dp[x]);
        }
    }
}
void init()
{
    while (!sk.empty()) sk.pop();
    Time=tot=0;
    for(int i=0;i<max(n,m);i++)
        dnf[i]=0,vis[i]=0,low[i]=0,head[i]=-1,dp[i]=0,a[i]=0,Col=0,sum[i]=0,g[i]=0;
}
int main()
{
    while (~scanf("%d%d",&n,&m))
    {
        int x;
        init();
        for(int i=1;i<=n;i++) x=read(),g[i]=max(0,x);

        for(int i=1;i<=m;i++)
        {
            u[i]=read(),v[i]=read();
            u[i]++,v[i]++;
            add_edge(u[i],v[i]);
        }

        for(int i=1;i<=n;i++)
            if(!dnf[i]) Tarjan(i);

        memset(head,-1,sizeof(head)),tot=0;

        for(int i=1;i<=m;i++)
            if(a[u[i]]!=a[v[i]])
                add_edge(a[u[i]],a[v[i]]),++In[a[v[i]]];

        Topsort();

        int ans=0;
        for(int i=1;i<=n;i++) ans=max(dp[i],ans);
        printf("%d\n",ans);

    }
    return 0;
}
