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
const int maxn = 4e5+5;
int head[maxn],tot;
struct Edge{
    int to,next;
}e[maxn];
void add(int u,int v)
{
    e[tot]={v,head[u]};
    head[u]=tot++;
}
int dfn[maxn],low[maxn],Time;
int n,m,cut;
bool bri[maxn];
int col[maxn],cnt;
int pre[maxn],dep[maxn];
void init()
{
    tot=0,Time=0,cut=0,cnt=0;
    memset(bri,0,sizeof(bri));
    for(int i=1;i<maxn;i++)
        dfn[i]=low[i]=col[i]=0,head[i]=-1,pre[i]=0,dep[i]=0;
}
void Tarjan(int x,int fa)
{
    dfn[x]=low[x]=++Time;
    for(int i=head[x];i!=-1;i=e[i].next)
    {
        int y=e[i].to;
        if(y==fa) continue;
        if(!dfn[y])
        {
            Tarjan(y,x),low[x]=min(low[x],low[y]);
            if(low[y]>dfn[x]) cut++,bri[i]=bri[i^1]=true;
        }
        else low[x]=min(low[x],dfn[y]);
    }
}
void dfs(int x)
{
    col[x]=cnt;
    for(int i=head[x];i!=-1;i=e[i].next)
    {
        int y=e[i].to;
        if(col[y]||bri[i]) continue;
        dfs(y);
    }
}
void Predfs(int x,int fa)
{
    for(int i=head[x];i!=-1;i=e[i].next)
    {
        int y=e[i].to;
        if(y==fa) continue;
        dep[y]=dep[x]+1,pre[y]=x;
        Predfs(y,x);
    }
}
int U[maxn],V[maxn];
int fa[maxn];
int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}
void LCA(int x,int y)
{
      while (x!=y)
      {
          --cut;
          if(dep[x]>dep[y]) fa[x]=pre[x],x=find(pre[x]);
          else fa[y]=pre[y],y=find(pre[y]);
      }
}
int main()
{
    int cas=0;
    while (~scanf("%d%d",&n,&m)&n&&m)
    {
        init();

        for(int i=1;i<=m;i++)
        {
            int u=read(),v=read();
            U[i]=u,V[i]=v;
            add(u,v),add(v,u);
        }

        for(int i=1;i<=n;i++) if(!dfn[i]) Tarjan(i,i);

        for(int i=1;i<=n;i++) if(!col[i]) ++cnt,dfs(i);

        tot=0;
        memset(head,-1,sizeof(head));

        for(int i=1;i<=n;i++) fa[i]=i;

        for(int i=1;i<=m;i++)
        {
            int u=col[U[i]],v=col[V[i]];
            if(u==v) continue;
            int fx=find(U[i]),fy=find(V[i]);
            if(fx!=fy) fa[fx]=fy,add(u,v),add(v,u);
        }

        for(int i=1;i<=n;i++) fa[i]=i;

        Predfs(1,-1);
        int q=read();

        printf("Case %d:\n",++cas);
        while (q--)
        {
            int u=read(),v=read();
            u=col[u],v=col[v];
            int fx=find(u),fy=find(v);
            LCA(fx,fy);
            printf("%d\n",cut);
        }
        printf("\n");
    }
    return 0;
}
