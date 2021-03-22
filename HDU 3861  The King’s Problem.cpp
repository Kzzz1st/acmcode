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
#define lowbit(x)  ((x)&-(x))
typedef unsigned long long ull;
#define freedom() ios::sync_with_stdio(false);
inline int read(){int s=0,w=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();return s*w;}
const int maxn = 5e3+5;
int tot,head[maxn];
struct E{
    int to,next;
}e[100005],edge[100005];
int sk[maxn],K;
int Time;
bool vis[maxn];
int cnt,col[maxn],dfn[maxn],low[maxn];
void add_e(int u,int v)
{
    e[tot]={v,head[u]};
    head[u]=tot++;
}
void Tarjan(int x)
{
    vis[x]=true;
    dfn[x]=low[x]=++Time;
    sk[++K]=x;
    for(int i=head[x];i!=-1;i=e[i].next)
    {
        int y=e[i].to;
        if(!dfn[y]) Tarjan(y),low[x]=min(low[x],low[y]);
        else if(vis[y]) low[x]=min(low[x],low[y]);
    }
    if(dfn[x]==low[x])
    {
        int y;
        ++cnt;
        do
        {
            y=sk[K--];
            vis[y]=false;
            col[y]=cnt;
        }while (x!=y);
    }
}
int Tot;
void add(int u,int v)
{
    edge[Tot]={v,low[u]};
    low[u]=Tot++;
}
bool find(int x)
{
    for(int i=low[x];i!=-1;i=edge[i].next)
    {
        int y=edge[i].to;
        if(!vis[y])
        {
            vis[y]=true;
            if(dfn[y]==0||find(dfn[y]))
            {
                dfn[y]=x;
                return true;
            }
        }
    }
    return false;
}
int solve()
{
    for(int i=0;i<=cnt;i++) dfn[i]=0;
    int ans=0;
    for(int i=1;i<=cnt;i++)
    {
        for(int j=1;j<=cnt;j++) vis[j]=0;
        if(find(i)) ans++;
    }
    return cnt-ans;
}
void init(int n)
{
    Time=0;
    Tot=0;
    tot=cnt=0;
    K=0;
    for(int i=0;i<=n;i++)
        head[i]=-1,low[i]=dfn[i]=0,col[i]=0,vis[i]=false,sk[i]=0;
}
int U[100005],V[100005];
int main()
{
    int t=read();
    while (t--)
    {
        int n=read(),m=read();

        init(n);
        for(int i=1;i<=m;i++)
        {
            int u=read(),v=read();
            U[i]=u,V[i]=v;
            add_e(u,v);
        }

        for(int i=1;i<=n;i++)
            if(!dfn[i]) Tarjan(i);

        for(int i=0;i<=cnt;i++) low[i]=-1;

        for(int i=1;i<=m;i++)
        {
            int u=col[U[i]],v=col[V[i]];
            if(u!=v) add(u,v);
        }
        printf("%d\n",solve());
    }
    return 0;
}
