/*
point update range min with index
*/
pair<int,int>seg[5*N+2];
void build(int node,int lo,int hi)
{
  if(lo==hi){seg[node]={aa[lo],lo};return ;}
  int md=(lo+hi)/2;
  build(node*2,lo,md);build(node*2+1,md+1,hi);
  seg[node]=min(seg[node*2],seg[node*2+1]);
}
void upd(int node,int lo,int hi,int id,int vl)
{
  if(lo==hi){seg[node].first=vl;return ;}
  int md=(lo+hi)/2;
  if(id<=md)upd(node*2,lo,md,id,vl);
  else upd(node*2+1,md+1,hi,id,vl);
  seg[node]=min(seg[node*2],seg[node*2+1]);
}
pair<int,int>get(int node,int lo,int hi,int lt,int rt)
{
  if(lo>rt||hi<lt)return {2e9,0};
  if(lo>=lt&&hi<=rt)return seg[node];
  int md=(lo+hi)/2;
  pair<int,int>p1=get(node*2,lo,md,lt,rt);
  pair<int,int>p2=get(node*2+1,md+1,hi,lt,rt);
  return min(p1,p2);
}