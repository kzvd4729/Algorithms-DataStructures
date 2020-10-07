int tot,mark[N+2],sz[N+2];
vector<int>ad[N+2];
void reckon(int nd,int pr)
{
  tot++;sz[nd]=1;
  for(auto x:ad[nd])
  {
    if(mark[x]||x==pr)continue;
    reckon(x,nd);sz[nd]+=sz[x];
  }
}
int findCenter(int nd,int pr)
{
  for(auto x:ad[nd])
  {
    if(x==pr||mark[x])continue;
    if(sz[x]>tot/2)return findCenter(x,nd);
  }
  return nd;
}
void centroid(int nd,int pr)
{
  tot=0;reckon(nd,-1);
  int center=findCenter(nd,-1);
  mark[center]=1;

  //calculate all pair path going through center.

  for(auto x:ad[center])
  {
    if(mark[x])continue;
    centroid(x,center);
  }
}
