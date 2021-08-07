/*
strongly connected component for directed graph.
ad vector stores the directed edges where rv stores reverse edges.
consider a dag 1-->2-->3-->4-->5, topological order will be 5 4 3 2 1.

consider a node u and an adjacent vertex of u in the reverse graph is v.
v should be in the right side side of u in topological order. if not there
must be a cycle including u and v which messes up the topological order.
*/
int vis[N+2];
vector<int>ad[N+2],rv[N+2],ord,com;
void topo(int node)
{
  vis[node]=1;
  for(auto x:ad[node])
    if(!vis[x])topo(x);
  ord.push_back(node);
}
void dfs(int node)
{
  com.push_back(node);vis[node]=1;
  for(auto x:rv[node])
    if(!vis[x])dfs(x);
}
void solve(int n)
{
  for(int i=1;i<=n;i++)
    if(!vis[i])topo(i);
  for(int i=1;i<=n;i++)vis[i]=0;
  for(int i=n-1;i>=0;i--)
  {
    if(vis[ord[i]])continue;
    com.clear();dfs(ord[i]);

    // work with the component

  }
}
void addEdge(int u,int v)// there is a directed edge from u to v
{
  // if(u==v)assert(0);
  ad[u].push_back(v);
  rv[v].push_back(u);
}
