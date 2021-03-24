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
const int maxn = 2e3+5;
struct E{
    int to,next;
}e[maxn];
int tot,head[maxn];
int dep[maxn],f[maxn][50],lg[maxn];
int ans[maxn];
bool In[maxn];
void add_e(int u,int v)
{
    e[tot]={v,head[u]};
    head[u]=tot++;
}
void init(int n)
{
    tot=0;
    memset(f,0,sizeof(f));
    for(int i=0;i<maxn;i++)
        dep[i]=0,head[i]=-1,ans[i]=0,In[i]=false;
    for(int i=1;i<=n;i++)
        lg[i]=lg[i-1]+(1<<lg[i-1]==i);
}
void dfs(int x,int fa)
{
    f[x][0]=fa,dep[x]=dep[fa]+1;
    for(int i=1;(1<<i)<=dep[x];i++)
        f[x][i]=f[f[x][i-1]][i-1];
    for(int i=head[x];i!=-1;i=e[i].next)
        if(e[i].to!=fa) dfs(e[i].to,x);
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
      int n;
    while (~scanf("%d",&n))
    {
        init(n);
        for(int i=1;i<=n;i++)
        {
            int u,k;
            scanf("%d:(%d)", &u, &k);
            for(int j=1;j<=k;j++)
            {
                int v=read();
                add_e(u,v),add_e(v,u);
                In[v]=true;
            }
        }
        for(int i=1;i<=n;i++)
            if(!In[i]) {dfs(i,0); break;}
        int q=read();
        for(int i=1;i<=q;i++)
        {
            char ch; int u,v;
            cin >> ch;
            scanf("%d%d)", &u, &v);
            ans[LCA(u,v)]++;
        }
        for(int i=1;i<=n;i++)
            if(ans[i]) printf("%d:%d\n",i,ans[i]);
    }
    return 0;
}
