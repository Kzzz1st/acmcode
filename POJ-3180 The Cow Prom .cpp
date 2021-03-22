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
const int maxn = 1e5+5;
int head[maxn],tot;
struct Edge{
    int to,next;
}edge[maxn],e[maxn];
void add_edge(int u,int v)
{
    edge[tot]={v,head[u]};
    head[u]=tot++;
}
int dfn[maxn],vis[maxn],low[maxn],Time;
int col[maxn],cnt;
stack<int>sk;
int ro[maxn];
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
        do
        {
            y=sk.top(); sk.pop();
            vis[y]=0;
            col[y]=cnt;
            ro[cnt]++;
        }while (x!=y);
    }
}

int main()
{
    int n=read(),m=read();
    memset(head,-1,sizeof(head));
    for(int i=1;i<=m;i++)
    {
        int u=read(),v=read();
        add_edge(u,v);
    }
    for(int i=1;i<=n;i++)
        if(!dfn[i]) Tarjan(i);
    int ans=0;
    for(int i=1;i<=cnt;i++)
        if(ro[i]>1) ans++;
    printf("%d\n",ans);
    return 0;
}
