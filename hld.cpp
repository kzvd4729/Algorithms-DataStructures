int sub[N+2],ent[N+2],tim,anc[N+2],par[N+2],lev[N+2];
void dfs(int n,int p,int l)
{
  sub[n]=1,par[n]=p,lev[n]=l;
  for(auto x:adj[n])
  {
    if(x==p)continue;dfs(x,n,l+1);sub[n]+=sub[x];
  }
}
void hld(int n,int p)
{
  ent[n]=++tim;//add to the ds
  int mx=-1,b=-1;
  for(auto x:adj[n])
  {
    if(x==p)continue;if(sub[x]>mx)mx=sub[x],b=x;
  }
  if(b!=-1){anc[b]=anc[n];hld(b,n);}
  for(auto x:adj[n])
  {
    if(x==p||x==b)continue;anc[x]=x;hld(x,n);
  }
}
int hQry(int u,int v)//query on path u,v;
{
  while(true)
  {
    if(lev[u]<lev[v])swap(u,v);
    if(anc[u]==anc[v])
    {
      //return qry(ent[v],ent[u]); v is the lca
    }
    if(lev[anc[u]]<lev[anc[v]])swap(u,v);
    //qry(ent[anc[u]],ent[u])
    u=par[anc[u]];
  }
}
void solve(int n)
{
  dfs(1,-1,0);anc[1]=1;hld(1,-1);
}
