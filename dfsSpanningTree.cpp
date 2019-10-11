/*
take care for disconnected graph.
*/
vector<int>adj[N+2],tree[N+2];//rooted tree
vector<pair<int,int> >br;
vector<int>bkadj[N+2];//edges doesn't belong to the tree(end nodes are in a chain)

int vis[N+2],lev[N+2];
void dfs(int node,int par,int lv)
{
  vis[node]=1,lev[node]=lv;
  for(auto x:adj[node])
  {
    if(x==par)continue;
    if(vis[x])
    {
      bkadj[node].push_back(x);
      bkadj[x].push_back(node);
    }
    else
    {
      tree[node].push_back(x);
      tree[x].push_back(node);
      dfs(x,node,lv+1);
    }
  }
}
int bridge(int node,int par)
{
  int mn=1e9;
  for(auto x:bkadj[node])
    mn=min(mn,lev[x]);
  for(auto x:tree[node])
  {
    if(x==par)continue;
    mn=min(mn,bridge(x,node));
  }
  if(mn>=lev[node]&&par!=-1)
    br.push_back({par,node});
  return mn;
}
