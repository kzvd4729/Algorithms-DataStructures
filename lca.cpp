int lev[N+2],sp[N+2][21];
vector<int>adj[N+2];
void reckon(int n,int p,int h)
{
  sp[n][0]=p;lev[n]=h;
  for(auto x:adj[n])
    if(x!=p)reckon(x,n,h+1);
}
void sparse(int n)
{
  for(int j=1;j<=20;j++)
  {
    for(int i=1;i<=n;i++)
    {
      sp[i][j]=sp[i][j-1];
      if(sp[i][j-1]!=-1)
        sp[i][j]=sp[sp[i][j-1]][j-1];
    }
  }
}
int lca(int u,int v)
{
  if(lev[u]<lev[v])swap(u,v);
  for(int i=20;i>=0;i--)
  {
    if(lev[u]-(1<<i)>=lev[v])
      u=sp[u][i];
  }
  if(u==v)return u;
  for(int i=20;i>=0;i--)
  {
    if(sp[u][i]==sp[v][i])continue;
    u=sp[u][i],v=sp[v][i];
  }
  return sp[u][0];
}
