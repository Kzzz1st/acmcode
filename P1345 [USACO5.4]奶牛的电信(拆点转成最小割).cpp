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
const int N = 1e5+5;
int tot,head[maxn],dep[maxn];
struct E{
    int to,next,val;
}e[N<<2];
void add_e(int u,int v,int w){
    e[tot]={v,head[u],w};
    head[u]=tot++;
}
struct Node{
    int u,v;
}node[maxn];
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

        int res=dfs(y,t,min(In,e[i].val));

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
        ans+=dfs(s,t,1e5);
    return ans;
}
int main()
{
    int n=read(),m=read(),s=read(),t=read();

    tot=0;
    int id=n;
    memset(head,-1,sizeof(head));

    for(int i=1;i<=n;i++){
        if(i!=s&&i!=t) {
            node[i].u=i,node[i].v=id+i;
            add_e(i,id+i,1),add_e(id+i,i,0);
        }
        else node[i].v=node[i].u=i;
    }
    for(int i=1;i<=m;i++){

        int u=read(),v=read();

        add_e(node[u].v,node[v].u,1e5);
        add_e(node[v].u,node[u].v,0);

        add_e(node[v].v,node[u].u,1e5);
        add_e(node[u].u,node[v].v,0);
    }
    int flow=Dinic(s,t);

    printf("%d\n",flow);

    return 0;
}
/*
9 12 1 2
1 3
1 4
1 5
2 6
2 7
2 8
3 9
4 9
5 9
6 9
7 9
8 9
1
 */
