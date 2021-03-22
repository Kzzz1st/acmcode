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
const int maxn = 1e5+5;
int tot,head[maxn];
int dnf[maxn],low[maxn],Time;
bool vis[maxn];
int In[maxn],Out[maxn];
struct Edge{
    int to,next;
}edge[maxn];
void add_edge(int u,int v)
{
    edge[tot].to=v;
    edge[tot].next=head[u];
    head[u]=tot++;
}
stack<int>sk;
int Col[maxn],col;
void Tarjan(int x)
{
    vis[x]=true;
    sk.push(x);
    dnf[x]=low[x]=++Time;

    for(int i=head[x];i!=-1;i=edge[i].next)
    {
        int y=edge[i].to;
        if(!dnf[y]) Tarjan(y),low[x]=min(low[x],low[y]);
        else if(vis[y]) low[x]=min(low[x],dnf[y]);
    }
    if(dnf[x]==low[x])
    {
        int y;
        Col[x]=++col;
        do
        {
            y=sk.top(); sk.pop();
            vis[y]=false;
            Col[y]=col;
        }while (x!=y);
    }
}
void init(int n,int m)
{
    while (!sk.empty()) sk.pop();
    Time=tot=0; col=0;
    for(int i=0;i<=max(n,m);i++)
        dnf[i]=0,low[i]=0,vis[i]=false,head[i]=-1,Out[i]=0,In[i]=0,Col[i]=0;
}
int u[maxn],v[maxn];
int main()
{
    int t=read();
    while (t--)
    {
        int n=read(),m=read();
        init(n,m);
        for(int i=1;i<=m;i++)
            u[i]=read(),v[i]=read(),add_edge(u[i],v[i]);

        for(int i=1;i<=n;i++)
            if(!dnf[i]) Tarjan(i);

        for(int i=1;i<=n;i++)
            for(int k=head[i];k!=-1;k=edge[k].next)
                if(Col[i]!=Col[edge[k].to]) ++In[Col[edge[k].to]],++Out[Col[i]];

        int cnt1=0,cnt2=0;
        if(col==1){ puts("0");continue;}
        for(int i=1;i<=col;i++)
        {
            if(In[i]==0) cnt1++;
            if(Out[i]==0) cnt2++;
        }
        printf("%d\n",max(cnt2,cnt1));
    }
    return 0;
}
