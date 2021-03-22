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
const int maxn = 5e4+5;
int tot,head[maxn];
struct E{
    int to,next;
}e[maxn*10];
stack<int>sk;
int Time;
bool vis[maxn];
int n,m;
int cnt,col[maxn],dfn[maxn],low[maxn];
void add_e(int u,int v)
{
    e[tot]={v,head[u]};
    head[u]=tot++;
}
void Tarjan(int x)
{
    dfn[x]=low[x]=++Time;
    vis[x]=1;
    sk.push(x);
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
            y=sk.top(); sk.pop();
            vis[y]=0;
            col[y]=cnt;

        }while (x!=y);
    }
}
int U[maxn*10],V[maxn*10],W[maxn*10],a[maxn*10];
void init()
{
    tot=0,Time=0,cnt=0;
    for(int i=0;i<maxn;i++)
        dfn[i]=0,low[i]=0,head[i]=-1,vis[i]=0;
    for(int i=1;i<maxn;i++)
        col[i]=0;
    for(int i=0;i<maxn*10;i++)
        a[i]=INF;
}
int main()
{
    while (~scanf("%d%d",&n,&m))
    {
        init();
        for(int i=1;i<=m;i++)
        {
            int u=read(),v=read(),w=read();
            U[i]=u+1,V[i]=v+1,W[i]=w;
            add_e(u+1,v+1);
        }
        for(int i=1;i<=n;i++)
            if(!dfn[i]) Tarjan(i);

        for(int i=1;i<=m;i++)
        {
            int u=col[U[i]],v=col[V[i]];
            if(u!=v)
            {
                a[v]=min(a[v],W[i]);
            }
        }
        ll ans=0;
        for(int i=1;i<=cnt;i++)
            if(a[i]!=INF) ans+=a[i];
        printf("%lld\n",ans);
    }
    return 0;
}
