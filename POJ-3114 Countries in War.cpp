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
const int maxn = 5e2+5;
int head[maxn],tot;
struct Edge{
    int to,next;
}edge[maxn*maxn];
void add_edge(int u,int v)
{
    edge[tot].to=v;
    edge[tot].next=head[u];
    head[u]=tot++;
}
int m,n;
int dfn[maxn],vis[maxn],low[maxn],Time;
int col[maxn],cnt;
stack<int>sk;
int dis[maxn][maxn],mp[maxn][maxn];
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
        }while (x!=y);
    }
}
void init()
{
     cnt=Time=tot=0;
     while (!sk.empty()) sk.pop();
     for(int i=0;i<maxn;i++)
     {
         dfn[i]=low[i]=0,vis[i]=col[i]=0,head[i]=-1;
         for(int j=0;j<maxn;j++)
             mp[i][j]=dis[i][j]=INF,mp[i][i]=dis[i][i]=0;
     }
}
void Floyd(int N)
{
    for(int k=1;k<=N;k++)
        for(int i=1;i<=N;i++)
           for(int j=1;j<=N;j++)
               if(dis[i][j] > dis[i][k] + dis[k][j])
                   dis[i][j] = dis[i][k] + dis[k][j];
}
int main()
{
    while (~scanf("%d%d",&n,&m))
    {
        if(!n && !m) break;
        init();
        for(int i=1;i<=m;i++)
        {
            int u=read(),v=read(),w=read();
            mp[u][v]=w;
            add_edge(u,v);
        }
        for(int i=1;i<=n;i++)
            if(!dfn[i]) Tarjan(i);
        for(int i=1;i<=n;i++)
        {
            for(int k=head[i];k!=-1;k=edge[k].next)
            {
                int u=i,v=edge[k].to;
                if(col[u]!=col[v]) dis[col[u]][col[v]]=min(dis[col[u]][col[v]],mp[u][v]);
                else dis[col[u]][col[v]]=dis[col[v]][col[u]]=0;
            }
        }
        Floyd(cnt);
        int q=read();
        while (q--)
        {
            int u=read(),v=read();

            if(dis[col[u]][col[v]]!=INF) printf("%d\n",dis[col[u]][col[v]]);
            else puts("Nao e possivel entregar a carta");
        }
        puts("");
    }
    return 0;
}
