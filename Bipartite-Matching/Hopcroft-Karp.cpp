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