/*
dominator tree: works on directed graph(doesnt need to be dag). graph have to be
single rooted. workes only with the nodes that are reachable from root. 
builds a dominator tree. if a node is deleted in the original graph each node in 
the the subtree of that node in the dominator tree will be disconnected from the
source in original graph.
*/
vector<int>dir[N+2],par[N+2],dom[N+2],topo;
int vis[N+2],lvl[N+2],sp[N+2][20+2];
void dfs(int node)
{
  vis[node]=1;
  for(auto x:dir[node])if(!vis[x])dfs(x);
  topo.push_back(node);
}
int lca(int u,int v)
{
  if(lvl[u]<lvl[v])swap(u,v);
  for(int i=19;i>=0;i--)
  {
    if(sp[u][i]==-1)continue;
    if(lvl[sp[u][i]]>=lvl[v])u=sp[u][i];
  }
  if(u==v)return u;
  for(int i=19;i>=0;i--)
  {
    if(sp[u][i]==-1||sp[u][i]==sp[v][i])continue;
    u=sp[u][i];v=sp[v][i];
  }
  return sp[u][0];
}
void upd(int pr,int ch)
{
  sp[ch][0]=pr;
  for(int i=1;i<20;i++)
  {
    if(sp[ch][i-1]==-1)break;
    sp[ch][i]=sp[sp[ch][i-1]][i-1];
  }
  lvl[ch]=lvl[pr]+1;dom[pr].push_back(ch);
}
void solve(vector<pair<int,int> >ed,int s)//directed graph is in ed
{
  for(auto x:ed)
  {
    dir[x.first].push_back(x.second);
    par[x.second].push_back(x.first);
  }
  dfs(s);reverse(topo.begin(),topo.end());
  memset(sp,-1,sizeof(sp));
  for(int i=1;i<topo.size();i++)
  {
    int x=topo[i];int dm=par[x][0];
    for(int j=1;j<par[x].size();j++)
      dm=lca(dm,par[x][j]);
    upd(dm,x);
  }
}
