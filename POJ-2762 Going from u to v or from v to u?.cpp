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
const int maxn = 1e4+5;
int head[maxn],tot;
struct Edge{
    int to,next;
}edge[maxn],e[maxn];
void add_edge(int u,int v)
{
    edge[tot]={v,head[u]};
    head[u]=tot++;
}
int Tot,Head[maxn];
void add(int u,int v)
{
    e[Tot]={v,Head[u]};
    Head[u]=Tot++;
}
int dfn[maxn],vis[maxn],low[maxn],Time;
int col[maxn],cnt;
int dis[maxn];
stack<int>sk;
void init(int n)
{
    tot=Time=cnt=0; Tot=0;
    memset(Head,-1,sizeof(Head));
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n;i++) low[i]=dfn[i]=col[i]=0,dis[i]=INF,vis[i]=0;
}
void Tarjan(int x)
{
    dfn[x]=low[x]=++Time;
    vis[x]=1;
    sk.push(x);
    for(int i=head[x];i!=-1;i=edge[i].next)
    {
        int y=edge[i].to;
        if(!dfn[y]) Tarjan(y),low[x]=min(low[x],low[y]);
        else if(vis[y]) low[x]=min(low[x],low[y]);
    }
    if(dfn[x]==low[x])
    {
        int y;
        col[x]=++cnt;
        do{
            y=sk.top(); sk.pop();
            vis[y]=0;
            col[y]=cnt;
        }while (x!=y);
    }
}
bool spfa(int s)
{
    memset(dis,INF,sizeof(dis));
    memset(vis,0,sizeof(vis));
    queue<int>q;
    vis[s]=1,dis[s]=0;
    q.push(s);
    while (!q.empty())
    {
        int x=q.front();q.pop();
        vis[x]=0;
        for(int i=Head[x];i!=-1;i=e[i].next)
        {
            int y=e[i].to;
            if(dis[y]>dis[x]+1)
            {
                dis[y]=dis[x]+1;
                if(!vis[y]) q.push(y),vis[y]=1;
            }
        }
    }
    for(int i=1;i<=cnt;i++)
        if(dis[i]==cnt-1) return true;
    return false;
}
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
            add_edge(u,v);
        }
        for(int i=1;i<=n;i++)
            if(!dfn[i]) Tarjan(i);


        int In[maxn]={0};
        for(int i=1;i<=n;i++)
            for(int k=head[i];k!=-1;k=edge[k].next)
            {
                int u=i,v=edge[k].to;
                if(col[u]!=col[v]) add(col[u],col[v]),In[col[v]]++;
            }
        int g=0,s=-1;
        for(int i=1;i<=cnt;i++)
            if(!In[i]) g++,s=i;
        if(g==0) puts("Yes");
        else if(g>1) puts("No");
        else if(spfa(s)) puts("Yes");
        else puts("No");
    }
    return 0;
}
