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
int head[maxn],tot;
struct Edge{
    int to,next;
}edge[maxn];
void add_edge(int u,int v)
{
    edge[tot]={v,head[u]};
    head[u]=tot++;
}
int dfn[maxn],vis[maxn],low[maxn],Time,cnt;
int gra[maxn],col[maxn];
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
    if(low[x]==dfn[x])
    {
        gra[x]=++cnt;
        int y;
        do
        {
            y=sk.top(); sk.pop();
            vis[y]=0;
            gra[y]=cnt;
            col[cnt]++;
        }while (x!=y);
    }
}
void init(int n)
{
    tot=0,cnt=0,Time=0;
    while (!sk.empty()) sk.pop();
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n;i++) dfn[i]=0,low[i]=0,vis[i]=0,col[i]=0;
}
int main()
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
    int In[maxn]={0},Out[maxn]={0};
    for(int i=1;i<=n;i++)
        for(int k=head[i];k!=-1;k=edge[k].next)
        {
            int u=i,v=edge[k].to;
            if(gra[u]!=gra[v]) ++In[gra[v]],++Out[gra[u]];
        }
    int ans=0,g=0;
    for(int i=1;i<=cnt;i++)
    {
        if(Out[i]==0) ans++,g=i;
    }
    if(ans>1) puts("0");
    else printf("%d\n",col[g]);
    return 0;
}
