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
const int maxn = 1e6+5;
struct E{
    int to,next;
}e[maxn<<2];
int tot,head[maxn],n;
int f[maxn],dep[maxn],Size[maxn];
void add_e(int u,int v)
{
    e[tot]={v,head[u]};
    head[u]=tot++;
}
void dfsdep(int x,int fa)
{
    for(int i=head[x];i!=-1;i=e[i].next)
    {
        int y=e[i].to;
        if(y==fa) continue;
        dep[y]=dep[x]+1;
        dfsdep(y,x);
        Size[x]+=Size[y];
    }
}
void dfs(int x,int fa)
{
    for(int i=head[x];i!=-1;i=e[i].next)
    {
        int y=e[i].to;
        if(y==fa) continue;
        f[y]=f[x]-Size[y]+(n-Size[y]);
        dfs(y,x);
    }
}
int main()
{
    n=read();
    memset(head,-1,sizeof(head));
    for(int i=1;i<n;i++)
    {
        int u=read(),v=read();
        add_e(u,v),add_e(v,u);
    }
    for(int i=1;i<=n;i++) Size[i]=1;
    dfsdep(1,0);
    for(int i=1;i<=n;i++) f[1]+=dep[i];
    dfs(1,0);
    int Min=1e9;
    for(int i=1;i<=n;i++) Min=min(Min,f[i]);
    printf("%d\n",Min);

    return 0;
}
