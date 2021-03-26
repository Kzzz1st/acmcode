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
const int maxn = 2e5+5;
int head[maxn],tot;
int dfn[maxn],low[maxn],Time;
bool bri[maxn*10];
int col[maxn],cnt;
int n,m;
struct E{
    int to,next;
}e[maxn*10];
int cut;
int dp[maxn];
void add_e(int u,int v){
    e[tot]={v,head[u]};
    head[u]=tot++;
}
void init(){
    tot=0;
    Time=cnt=0; cut=0;
    memset(bri,false,sizeof(bri));
    for(int i=0;i<maxn;i++)
        head[i]=-1,dfn[i]=low[i]=col[i]=0,dp[i]=0;
}
void Tarjan(int x,int fa){
    dfn[x]=low[x]=++Time;
    for(int i=head[x];i!=-1;i=e[i].next){
        int y=e[i].to;
//        if(y==fa) continue;
        if(!dfn[y]){
            Tarjan(y,i),low[x]=min(low[x],low[y]);
            if(low[y]>dfn[x]) bri[i]=bri[i^1]=true,cut++;
        }
        else if(i!=(fa^1)) low[x]=min(low[x],dfn[y]);
    }
}
void dfs(int x){
    col[x]=cnt;
    for(int i=head[x];i!=-1;i=e[i].next){
        int y=e[i].to;
        if(col[y]||bri[i]) continue;
        dfs(y);
    }
}
int U[maxn*10],V[maxn*10];
void Dfs(int x,int fa){
    for(int i=head[x];i!=-1;i=e[i].next){
        int y=e[i].to;
        if(y==fa) continue;
        dp[y]=dp[x]+1;
        Dfs(y,x);
    }
}
int main()
{
    while (~scanf("%d%d",&n,&m)&&n&&m){
        init();
        for(int i=1;i<=m;i++){
            int u=read(),v=read();
            U[i]=u,V[i]=v;
            add_e(u,v),add_e(v,u);
        }
        for(int i=1;i<=n;i++) if(!dfn[i]) Tarjan(i,i);
  //      printf("%d\n",cut);
        for(int i=1;i<=n;i++) if(!col[i]) ++cnt,dfs(i);
        tot=0;
        memset(head,-1,sizeof(head));
        for(int i=1;i<=m;i++){
            int u=col[U[i]],v=col[V[i]];
            if(u==v) continue;
            add_e(u,v),add_e(v,u);
        }
        Dfs(1,0);
        int Max=-1,pos=0;
        for(int i=1;i<=cnt;i++)
            if(Max<dp[i]) Max=dp[i],pos=i;
        memset(dp,0,sizeof(dp));
        Dfs(pos,0);
        Max=-1;
        for(int i=1;i<=cnt;i++)
            Max=max(Max,dp[i]);
        int ans=cut-Max;
        printf("%d\n",ans);

    }
    return 0;
}
/*
3 3
1 2
2 1
2 3
 */
