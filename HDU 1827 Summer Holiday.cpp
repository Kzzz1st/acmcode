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
const int maxn = 2e3+5;
int head[maxn],tot;
struct Edge{
    int to,next;
}edge[maxn];
void add_edge(int u,int v)
{
    edge[tot].to=v;
    edge[tot].next=head[u];
    head[u]=tot++;
}
int m,n;
int dfn[maxn],vis[maxn],low[maxn],Time;
int col[maxn],cnt;
int w[maxn];
int a[maxn];
stack<int>sk;
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
        ++cnt;
        do
        {
            y=sk.top(); sk.pop();
            vis[y]=0;
            col[y]=cnt;
            w[cnt]=min(a[y],w[cnt]);
        }while (x!=y);
    }
}
void init()
{
     cnt=Time=tot=0;
     while (!sk.empty()) sk.pop();
     for(int i=0;i<maxn;i++)
     {
         dfn[i]=low[i]=0,vis[i]=col[i]=0,head[i]=-1,w[i]=INF;
     }
}
int main()
{
    while (~scanf("%d%d",&n,&m))
    {
        init();
        for(int i=1;i<=n;i++) a[i]=read();
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
                if(col[u]!=col[v]) ++In[col[v]];
            }
        int res=0,ans=0;
        for(int i=1;i<=cnt;i++)
            if(!In[i]) ans++,res+=w[i];

        printf("%d %d\n",ans,res);
    }
    return 0;
}
