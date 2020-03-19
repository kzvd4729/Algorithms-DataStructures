/*
complexity E*sqrt(V)
edges are unidirectional(left side to right side).
each bfs starts from all free node(nodes that are not paired yet) of left side
and by altering from left to right choses all paths ending free node of
right side.
nodes of both side are independent of each other, they can have same name.
dfs selects all those path and makes pair.
every time exactly two free nodes are paired, so matching increases by one.

minimum vertex cover: (=) maximum bipartite match.
maximum independent set: (=) n-maximum bipartite match.
path cover problem: minimum number of paths that cover all nodes. only solveable
for dag. to solve path cover problem take all node of the graph to left side
and make another copy of all node to right side. now assign directed edge from
left to right. mpc will be n-maximum match
*/
int a,b;//number of nodes in left and right side(both numbered from 1).
int lft[N+2],rgt[N+2],dis[N+2];vector<int>adj[N+2];
void clean()
{
  for(int i=1;i<=a;i++)lft[i]=0,adj[i].clear();
  for(int i=1;i<=b;i++)rgt[i]=0;
}
bool bfs(void)
{
  queue<int>q;
  for(int i=1;i<=a;i++)
  {
    if(!lft[i])q.push(i),dis[i]=0;else dis[i]=inf;
  }
  dis[0]=inf;
  while(q.size())
  {
    int u=q.front();q.pop();
    for(auto v:adj[u])
    {
      if(dis[rgt[v]]<=dis[u]+1)continue;//keeping distance only for left side
      dis[rgt[v]]=dis[u]+1;if(rgt[v])q.push(rgt[v]);
    }
  }
  return dis[0]!=inf;
}
bool dfs(int u)
{
  if(!u)return true;
  for(auto v:adj[u])
  {
    if(dis[u]+1==dis[rgt[v]])
    {
      if(dfs(rgt[v])){lft[u]=v;rgt[v]=u;return true;}
    }
  }
  return false;
}
int hopkroft(void)
{
  int match=0;
  while(bfs())
  {
    for(int i=1;i<=a;i++)
    {
      if(dis[i])continue;if(dfs(i))match++;
    }
  }
  return match;
}

/*
kuhn for bipartite matching. worst complexity ve
*/
//nodes of each side are numbered independently
bool used[N+2];int mt[N+2];
vector<int>adj[N+2];//only edge from left to right
bool tryKuhn(int v)
{
  if(used[v])return false;used[v]=true;
  for(auto u:adj[v])
  {
    if(mt[u]==-1||tryKuhn(mt[u]))
    {
      mt[u]=v;return true;
    }
  }
  return false;
}
bool usd[N+2];
int solve(int a,int b)
{
  for(int i=1;i<=b;i++)mt[i]=-1;
  for(int i=1;i<=a;i++)usd[i]=false;
  for(int i=1;i<=a;i++)
  {
    for(auto x:adj[i])
    {
      if(mt[x]!=-1)continue;
      mt[x]=i;usd[i]=true;break;
    }
  }
  for(int i=1;i<=a;i++)
  {
    if(usd[i])continue;
    for(int j=1;j<=a;j++)used[j]=false;
    tryKuhn(i);
  }
  int ret=0;
  for(int i=1;i<=b;i++)if(mt[i]!=-1)ret++;
  for(int i=1;i<=a;i++)adj[i].clear();
  return ret;
}

/*
return minimum cost for n matching. can be modified for maximum.
*/
//nodes of each side are numbered independently
const int INF=1e9;//should be greater than overall matching cost
int cost[N+2][N+2];
int hungarian(int n,int m)
{
  vector<int>u(n+1),v(m+1),p(m+1),way(m+1);
  for(int i=1;i<=n;i++)
  {
    p[0]=i;int j0=0;
    vector<int>minv(m+1,INF);
    vector<char>used(m+1,false);
    do
    {
      used[j0]=true;int i0=p[j0],delta=INF,j1;
      for(int j=1;j<=m;j++)
      {
        if(!used[j])
        {
          int cur=cost[i0][j]-u[i0]-v[j];
          if(cur<minv[j])minv[j]=cur,way[j]=j0;
          if(minv[j]<delta)delta=minv[j],j1=j;
        }
      }
      for(int j=0;j<=m;j++)
      {
        if(used[j])u[p[j]]+=delta,v[j]-=delta;
        else minv[j]-=delta;
      }
      j0=j1;
    }while(p[j0]!=0);
    do 
    {
      int j1=way[j0];p[j0]=p[j1];
      j0=j1;
    }while(j0);
  }
  int ret=0;
  for(int i=1;i<=m;i++)ret+=cost[p[i]][i];
  return ret;
}
