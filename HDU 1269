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
#define lson rt<<1,l,mid
#define rson rt<<1|1,mid+1,r
#define lowbit(x)  ((x)&-(x))
typedef unsigned long long ull;
#define freedom() ios::sync_with_stdio(false);
inline int read(){int s=0,w=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();return s*w;}
const int maxn = 1e5+5;
struct Edge{
    int to,next;
}edge[maxn];
int head[maxn],tot;
bool vis[maxn];
int dfn[maxn],low[maxn],tim;
int Pos;
void add_edge(int u,int v)
{
    edge[tot].to=v;
    edge[tot].next=head[u];
    head[u]=tot++;
}
void Tarjan(int x)
{
    vis[x]=true;
    dfn[x]=low[x]=++tim;
    for(int i=head[x];i!=-1;i=edge[i].next)
    {
        int y=edge[i].to;
        if(!dfn[y]) Tarjan(y),low[x]=min(low[x],low[y]);
        else if(vis[y]) low[x]=min(low[x],low[y]);
    }
    if(dfn[x]==low[x])
        Pos++;
}
int n,m;
int main()
{
    while (~scanf("%d%d",&n,&m),n||m)
    {
        tot=0,tim=0,Pos=0;
        memset(head,-1,sizeof(head));
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        memset(vis,false,sizeof(vis));

        for(int i=1;i<=m;i++)
        {
            int u=read(),v=read();
            add_edge(u,v);
        }
        for(int i=1;i<=n;i++)
            if(!dfn[i])
                Tarjan(i);
        if(Pos==1) puts("Yes");
        else puts("No");
    }
    return 0;
}
