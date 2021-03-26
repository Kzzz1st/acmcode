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
const int maxn = 1e3+5;
int head[maxn],tot;
int dfn[maxn],low[maxn],Time;
bool bri[2000005];
int col[maxn],cnt;
int Min;
int n,m;
bool vis[maxn];
struct E{
    int to,next,val;
}e[2000005];
void add_e(int u,int v,int w){
    e[tot]={v,head[u],w};
    head[u]=tot++;
}
void init(){
    tot=cnt=Time=0;
    Min=INF;
    memset(bri,false,sizeof(bri));
    for(int i=0;i<maxn;i++)
        head[i]=-1,low[i]=dfn[i]=col[i]=0,vis[i]=false;
}
void Tarjan(int x,int fa){
    dfn[x]=low[x]=++Time;
    for(int i=head[x];i!=-1;i=e[i].next){
        int y=e[i].to;
        if(!dfn[y]){
            Tarjan(y,i),low[x]=min(low[x],low[y]);
            if(low[y]>dfn[x]) bri[i^1]=bri[i]=true,Min=min(Min,e[i].val);
        }
        else if(i!=(fa^1)) low[x]=min(low[x],dfn[y]);
    }
}
void dfs(int x){
    col[x]=cnt;
    for(int i=head[x];i!=-1;i=e[i].next){
        int y=e[i].to;
        if(bri[i]||col[y]) continue;
        dfs(y);
    }
}
void dfscol(int x){
    vis[x]=true;
    for(int i=head[x];i!=-1;i=e[i].next){
        int y=e[i].to;
        if(vis[y]) continue;
        vis[y]=true;
        dfscol(y);
    }
}
int U[1000006],V[1000005];
int main()
{
    while (~scanf("%d%d",&n,&m)&&n&&m)
    {
        init();
        for(int i=1;i<=m;i++){
            int u=read(),v=read(),w=read();
            U[i]=u,V[i]=v;
            add_e(u,v,w),add_e(v,u,w);
        }
        for(int i=1;i<=n;i++) if(!dfn[i]) Tarjan(i,i);
        for(int i=1;i<=n;i++) if(!col[i]) ++cnt,dfs(i);
        tot=0;
        memset(head,-1,sizeof(head));
        for(int i=1;i<=m;i++){
            int u=col[U[i]],v=col[V[i]];
            if(u==v) continue;
            add_e(u,v,0),add_e(v,u,0);
        }
        dfscol(1);
        int Cut=0;
        for(int i=1;i<=cnt;i++) if(!vis[i]) Cut++;
        if(Cut) puts("0");
        else if(cnt==1) puts("-1");
        else printf("%d\n",Min?Min:1);
    }
    return 0;
}
