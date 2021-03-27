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
const int Maxn=1e6+5;
int head[maxn],tot;
struct E{
    int to,next;
}e[Maxn];
int n,m;
int dfn[maxn],low[maxn],Time;
int col[maxn],cnt;
bool bri[Maxn];
bool vis[Maxn],v[maxn];
void add_e(int u,int v){
    e[tot]={v,head[u]};
    head[u]=tot++;
}
void init(){
    tot=Time=cnt=0;
    memset(vis,false,sizeof(vis));
    memset(bri,false,sizeof(bri));
    for(int i=1;i<maxn;i++)
        dfn[i]=low[i]=col[i]=0,head[i]=-1,v[i]=false;
}
void Tarjan(int x,int fa){
    dfn[x]=low[x]=++Time;
    for(int i=head[x];i!=-1;i=e[i].next){
        int y=e[i].to;
        if(!dfn[y]){
            Tarjan(y,i),low[x]=min(low[x],low[y]);
            if(low[y]>dfn[x]) bri[i]=bri[i^1]=true;
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
void Put(int x){
    for(int i=head[x];i!=-1;i=e[i].next){
        int y=e[i].to;
        if(vis[i]) continue;
        if(bri[i]){
            vis[i]=vis[i^1]=true;
            printf("%d %d\n%d %d\n",x,y,y,x);
            continue;
        }
        vis[i]=vis[i^1]=true;
        printf("%d %d\n",x,y);
        Put(y);
    }
}
int main()
{
    int cas=0;
    while (~scanf("%d%d",&n,&m)&&n&&m){
        init();
        for(int i=1;i<=m;i++){
            int u=read(),v=read();

            add_e(u,v),add_e(v,u);
        }
        for(int i=1;i<=n;i++) if(!dfn[i]) Tarjan(i,i);
        for(int i=1;i<=n;i++) if(!col[i]) ++cnt,dfs(i);
        printf("%d\n\n",++cas);
        for(int i=1;i<=n;i++)
            if(!v[col[i]]) Put(i);

        puts("#");
    }
    return 0;
}
