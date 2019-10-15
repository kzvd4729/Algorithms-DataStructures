/*
1-->2-->3-->4-->5-->6
topological order of this graph is 1 2 3 4 5 6
topological order of a dag ensures for each node no node in the left side of that
node is reachable from that node.
if this property is not maintained then there might be cycle.
*/
int vis[N+2];
vector<int>adj[N+2],rv[N+2],tp,com;
void dfs1(int node)//for topological order
{
  vis[node]=1;
  for(auto x:adj[node])
    if(!vis[x])dfs1(x);
  tp.push_back(node);
}
void dfs2(int node)
{
  vis[node]=1;com.push_back(node);
  for(auto x:rv[node])
    if(!vis[x])dfs2(x);
}
void solve(int n)
{
  for(int i=1;i<=n;i++)
    if(!vis[i])dfs1(i);
  for(int i=1;i<=n;i++)vis[i]=0;
  reverse(tp.begin(),tp.end());
  for(auto x:tp)
  {
    if(!vis[x])dfs2(x);
    //print component
    com.clear();
  }
}
void clear(int n)
{
  for(int i=1;i<=n;i++)
  {
    adj[i].clear(),rv[i].clear();
    vis[i]=0;
  }
  tp.clear();
}
