pair<int,int>par[N+2];
pair<int,int>find(int x)
{
  if(x!=par[x].first)
  {
    int pr=par[x].second;par[x]=find(par[x].first);
    par[x].second^=pr;
  }
  return par[x];
}
//return false if adding this edge cause odd cycle
bool add(int a,int b)
{
  pair<int,int>pa=find(a),pb=find(b);
  if(pa.first==pb.first)return pa.second!=pb.second;
  par[pb.first]={pa.first,pa.second^pb.second^1};
  return true;
}
void init(int n)
{
  for(int i=1;i<=n;i++)par[i]={i,0};
}
