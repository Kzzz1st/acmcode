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
int head[maxn],tot,n;
bool vis[maxn];
int dfn[maxn],low[maxn],Time;
void add_edge(int u,int v)
{
    edge[tot].to=v;
    edge[tot].next=head[u];
    head[u]=tot++;
}
int gra[maxn],cnt;
stack<int>sk;
void Tarjan(int x)
{
    vis[x]=true;
    dfn[x]=low[x]=++Time;
    sk.push(x);
    for(int i=head[x];i!=-1;i=edge[i].next)
    {
        int y=edge[i].to;
        if(!dfn[y]) Tarjan(y),low[x]=min(low[x],low[y]);
        else if(vis[y]) low[x]=min(low[x],low[y]);
    }
    if(dfn[x]==low[x])
    {
        gra[x]=++cnt;
        int y;
        do
        {
            y=sk.top(); sk.pop();
            vis[y]=false;
            gra[y]=cnt;
        }while (x!=y);
    }
}
int In[maxn],Out[maxn];
int main()
{
    n=read();
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n;i++)
    {
        int v;
        while (~scanf("%d",&v))
        {
            if(v==0) break;
            add_edge(i,v);
        }
    }
    for(int i=1;i<=n;i++)
        if(!dfn[i]) Tarjan(i);
    if(cnt==1) printf("%d\n%d\n",1,0);
    else {
        for(int i=1;i<=n;i++)
            for(int k=head[i];k!=-1;k=edge[k].next)
            {
                int v=edge[k].to;
                if(gra[i]!=gra[v]) ++In[gra[v]],++Out[gra[i]];
            }
        int ans1=0,ans2=0;
        for(int i=1;i<=cnt;i++)
        {
            if(In[i]==0) ans1++;
            if(Out[i]==0) ans2++;
        }
        printf("%d\n%d\n",ans1,max(ans1,ans2));
    }
    return 0;
}
