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
