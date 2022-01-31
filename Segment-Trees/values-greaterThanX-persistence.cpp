/*
number of values greater than equal to x in prefix.
*/
struct persistent
{
  int l,r,sm;
}seg[N*20+2];
int rot[N+2],nw;
void upd(int node,int pnode,int lo,int hi,int id)
{
  if(lo==hi){seg[node].sm=seg[pnode].sm+1;return ;}
  int md=(lo+hi)/2;
  if(id<=md)
  {
    if(!seg[node].l)seg[node].l=++nw;upd(seg[node].l,seg[pnode].l,lo,md,id);
    seg[node].r=seg[pnode].r;
  }
  else
  {
    if(!seg[node].r)seg[node].r=++nw;upd(seg[node].r,seg[pnode].r,md+1,hi,id);
    seg[node].l=seg[pnode].l;
  }
  seg[node].sm=seg[seg[node].l].sm+seg[seg[node].r].sm;
}
int get(int node,int lo,int hi,int vl)
{
  if(lo>=vl)return seg[node].sm;if(hi<vl)return 0;
  int md=(lo+hi)/2;
  return get(seg[node].l,lo,md,vl)+get(seg[node].r,md+1,hi,vl);
}
void solve(int n)
{
  for(int i=1;i<=n;i++){rot[i]=++nw;upd(rot[i],rot[i-1],1,n,aa[i]);}
}
