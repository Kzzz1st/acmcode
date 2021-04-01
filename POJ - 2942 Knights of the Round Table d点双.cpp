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
const int N = 1e6+5;
int tot,head[maxn];
struct E{
    int to,next;
}e[N<<2];
int n,m;
int dfn[maxn],low[maxn],Time;
stack<int>sk;
bool ans[maxn];
void add_e(int u,int v){
    e[tot]={v,head[u]};
    head[u]=tot++;
}
int cnt;
vector<int>vec[maxn];
bool cut[maxn],mp[maxn][maxn];
void init(){

    while (!sk.empty()) sk.pop();
    tot=0; Time=0; cnt=0;
    for(int i=0;i<maxn;i++)
        dfn[i]=low[i]=0,head[i]=-1,vec[i].clear(),cut[i]=false,ans[i]=false;
    for(int i=0;i<maxn;i++)
        for(int j=0;j<maxn;j++) mp[i][j]=true;

}
void Tarjan(int x,int fa)
{
    dfn[x]=low[x]=++Time; sk.push(x);
    int Fa=0;
    if(x==fa&&head[x]==-1){
        sk.pop();
        vec[++cnt].push_back(x);
        return;
    }
    for(int i=head[x];i!=-1;i=e[i].next){
        int y=e[i].to;
        if(y==fa) continue;
        if(!dfn[y]){
            Tarjan(y,x); low[x]=min(low[x],low[y]);
            if(low[y]>=dfn[x]){
                ++cnt; int top=0;
                while (top!=y){
                    top=sk.top(); sk.pop();
                    vec[cnt].push_back(top);
                }
                vec[cnt].push_back(x); Fa++;
                if(x!=fa||Fa>1) cut[x]=true;
            }
        }
        else low[x]=min(low[x],dfn[y]);
    }
}
int vis[maxn];
bool now[maxn];
bool find(int x)
{
    for(int i=head[x];i!=-1;i=e[i].next){
        int y=e[i].to;
        if(!now[y]) continue;

        if(vis[y]&&vis[x]==vis[y]) return true;

        else if(!vis[y]) {
            vis[y]=3-vis[x];
            if(find(y)) return true;
        }
    }
    return false;
}
int solve()
{

    for(int i=1;i<=cnt;i++)
    {
        for(int k=0;k<maxn;k++) now[k]=vis[k]=0;

        int len=vec[i].size();

        for(int k=0;k<len;k++) now[vec[i][k]]=true;

        vis[vec[i][0]]=1;

        if(find(vec[i][0]))
            for(int k=0;k<len;k++) ans[vec[i][k]]=true;
    }

    int res=0;
    for(int i=1;i<=n;i++)
        if(!ans[i]) res++;

    return res;

}
void Input()
{
    for(int i=1;i<=m;i++){
        int u=read(),v=read();
        mp[u][v]=mp[v][u]=false;
    }

    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(i!=j&&mp[i][j]) add_e(i,j);

    for(int i=1;i<=n;i++) if(!dfn[i]) Tarjan(i,i);
}
int main()
{
    while (~scanf("%d%d",&n,&m))
    {
        if(n==0&&m==0) break;
        init();
        Input();
        solve();
        printf("%d\n",solve());
    }
    return 0;
}
