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
const int maxn = 2e4+5;
int tot,head[maxn];
struct E{
    int to,next,val;
}e[maxn<<2];
int n,m;
int f[maxn];
int deep[maxn];
void add_e(int u,int v,int w){
    e[tot]={v,head[u],w};
    head[u]=tot++;
}
void init(){
    tot=0;
    for(int i=0;i<maxn;i++) head[i]=-1,f[i]=0,deep[i]=0;
}
bool bfs(int s,int t)
{
    memset(deep,0,sizeof(deep));
    queue<int>q;
    q.push(s);
    deep[s]=1;
    while (!q.empty())
    {
        int x=q.front(); q.pop();
        for(int i=head[x];i!=-1;i=e[i].next)
        {
            int y=e[i].to;
            int w=e[i].val;

            if(deep[y]||!w) continue;

            deep[y]=deep[x]+1;
            q.push(y);
        }
    }
    return deep[t];
}
int dfs(int x,int t,int In)
{
    if(x==t) return In;
    int Out=0;
    for(int i=head[x];i!=-1;i=e[i].next)
    {
        int y=e[i].to;
        if(e[i].val&&deep[y]==deep[x]+1)
        {
            int res=dfs(y,t,min(e[i].val,In));

            e[i].val-=res;
            e[i^1].val+=res;
            In-=res;
            Out+=res;
        }
    }
    if(In!=Out) deep[x]=0;
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
    while (~scanf("%d%d",&n,&m))
    {
        init();
        int Max=0;
        int s=0,t=2e4;
        for(int i=1;i<=n;i++){
            int num=0;
            for(int j=0;j<m;j++){
                int x=read();
                if(x) num+=(1<<j);
            }
            f[num]++,Max=max(Max,num);
        }

        for(int i=1;i<=Max;i++)
            if(f[i]) add_e(s,i,f[i]),add_e(i,s,0);

        for(int i=1;i<=Max;i++)
             if(f[i]){
                 for(int k=0;k<m;k++)
                     if(i&(1<<k)) add_e(i,Max+1+k,1e5),add_e(Max+1+k,i,0);
             }

        for(int i=1;i<=m;i++){
            int x=read();
            if(x) add_e(Max+i,t,x),add_e(t,Max+i,0);
        }


        int ans=Dinic(s,t);

        if(ans<n) puts("NO");

        else puts("YES");

    }
    return 0;
}
