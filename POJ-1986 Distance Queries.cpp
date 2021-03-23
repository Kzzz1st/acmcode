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
const int maxn = 5e5+5;
int head[maxn],tot;
struct E{
    int to,next,val;
}e[maxn<<1];
void add(int u,int v,int w)
{
    e[tot]={v,head[u],w};
    head[u]=tot++;
}
// 倍增法求LCA 模板
int dis[maxn];
int f[maxn][50],lg[maxn],dep[maxn];
void dfs(int x,int fa)
{
    f[x][0]=fa,dep[x]=dep[fa]+1;

    for(int i=1;(1<<i)<=dep[x];i++)
        f[x][i]=f[f[x][i-1]][i-1];

    for(int i=head[x];i!=-1;i=e[i].next)
        if(e[i].to!=fa) dis[e[i].to]=dis[x]+e[i].val,dfs(e[i].to,x);
}
int LCA(int x,int y)
{
    if(dep[x]<dep[y]) swap(x,y);

    while (dep[x]>dep[y]) x=f[x][lg[dep[x]-dep[y]]-1];

    if(x==y) return x;

    for(int i=lg[dep[x]]-1;i>=0;i--)
        if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];

    return f[x][0];
}
int main()
{
    int n=read(),m=read();
    memset(head,-1,sizeof(head));
    for(int i=1;i<=m;i++)
    {
        int u=read(),v=read(),w=read(); char op; cin>>op;
        add(u,v,w),add(v,u,w);
    }
    for(int i=1;i<=n;i++)
        lg[i]=lg[i-1]+(1<<lg[i-1]==i);
    dfs(1,0);
    int q=read();
    while (q--)
    {
        int u=read(),v=read();
        printf("%d\n",dis[u]+dis[v]-2*dis[LCA(u,v)]);
    }
    return 0;
}

