/*
mo's on tree path: complexity n sqrt(n)

solves the query on tree path offline.
*/
int ent[N+2],ext[N+2],tim,flt[N+N+2],sp[N+2][21],lev[N+2],vis[N+2];
struct query
{
  int lt,rt,lc,id;
}qr[N+2];
bool cmp(query a,query b)
{
  if(a.lt/sq!=b.lt/sq)return a.lt<b.lt;return a.rt<b.rt;
}
void dfs(int node,int par,int h)
{
  ent[node]=++tim,sp[node][0]=par,flt[tim]=node,lev[node]=h;
  for(auto x:adj[node])if(x!=par)dfs(x,node,h+1);
  ext[node]=++tim,flt[tim]=node;
}
void sparse(int n)
{
  for(int j=1;j<=20;j++)
  {
    for(int i=1;i<=n;i++)
    {
      sp[i][j]=sp[i][j-1];
      if(sp[i][j-1]!=-1)sp[i][j]=sp[sp[i][j-1]][j-1];
    }
  }
}
int lca(int u,int v)
{
  if(lev[u]<lev[v])swap(u,v);
  for(int i=20;i>=0;i--)if(lev[u]-(1<<i)>=lev[v])u=sp[u][i];
  if(u==v)return u;
  for(int i=20;i>=0;i--)if(sp[u][i]!=sp[v][i])u=sp[u][i],v=sp[v][i];
  return sp[u][0];
}
//eveything is 1 indexed
void solve(vector<pair<int,int> >vc,int n)
{
  dfs(1,-1,0);sparse(n);int q=0;
  for(auto x:vc)
  {
    ++q;
    int u=x.first,v=x.second,lc=lca(x.first,x.second);
    if(ent[u]>ent[v])swap(u,v);
    if(u==lc)qr[q]={ent[u],ent[v],0,q};//don't need lc;
    else qr[q]={ext[u],ent[v],lc,q};
  }
  sort(qr+1,qr+q+1,cmp);qr[0].lt=1,qr[0].rt=0;
  for(int l=1;l<=q;l++)
  {
    for(int i=qr[l].lt;i<qr[l-1].lt;i++)
    {
      int x=flt[i];vis[x]^=1;
      if(vis[x]);//add;
      else ;//remove
    }
    for(int i=qr[l-1].rt+1;i<=qr[l].rt;i++)
    {
      int x=flt[i];vis[x]^=1;
      if(vis[x]);//add;
      else ;//remove
    }
    for(int i=qr[l-1].lt;i<qr[l].lt;i++)
    {
      int x=flt[i];vis[x]^=1;
      if(vis[x]);//add;
      else ;//remove
    }
    for(int i=qr[l].rt+1;i<=qr[l-1].rt;i++)
    {
      int x=flt[i];vis[x]^=1;
      if(vis[x]);//add;
      else ;//remove
    }
    //store current answer to ans[qr[l].id];
    if(qr[l].lc);//add value of lc with ans[qr[l].id];
  }
}
