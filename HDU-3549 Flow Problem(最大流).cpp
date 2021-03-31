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
const int maxn = 2e2+5;
const int N = 1e3+5;
int tot,head[maxn];
struct E{
    int to,next,val;
}e[N<<2];
void add_e(int u,int v,int w){
    e[tot]={v,head[u],w};
    head[u]=tot++;
}
int dep[maxn];
bool bfs(int s,int t)
{
    memset(dep,0,sizeof(dep));
    queue<int>q; q.push(s);
    dep[s]=1;
    while (!q.empty()){
        int x=q.front(); q.pop();
        for(int i=head[x];i!=-1;i=e[i].next){
            int y=e[i].to;
            if(!e[i].val||dep[y]) continue;
            dep[y]=dep[x]+1;
            q.push(y);
        }
    }
    return dep[t];
}
int dfs(int x,int t,int In)
{
    if(x==t) return In;
    int Out=0;
    for(int i=head[x];i!=-1;i=e[i].next){
        int y=e[i].to;
        if(!e[i].val||dep[y]!=dep[x]+1) continue;
        int res=dfs(y,t,min(e[i].val,In));
        e[i].val-=res,e[i^1].val+=res;
        In-=res,Out+=res;
    }
    if(In!=Out) dep[x]=0;
    return Out;
}
int Dinic(int s,int t)
{
    int ans=0;
    while (bfs(s,t))
        ans+=dfs(s,t,INF);
    return ans;
}
int main()
{
    int t=read(),cas=0;
    while (t--){
        tot=0;
        memset(head,-1,sizeof(head));
        int n=read(),m=read();
        for(int i=1;i<=m;i++){
            int u=read(),v=read(),w=read();
            add_e(u,v,w),add_e(v,u,0);
        }
        printf("Case %d: %d\n",++cas,Dinic(1,n));
    }
    return 0;
}
