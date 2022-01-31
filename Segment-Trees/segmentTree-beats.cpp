/*
segment tree beats: range add operation. range trim operation
(a[i]=x if a[i]>x).sum query. ......not enough tested.
*/
struct segment
{
  long ad,mx,sm;
  long firstMx,secondMx;
  long fr;
}sg[4*N+8];
void merge(int nd)
{
  sg[nd].sm=sg[nd*2].sm+sg[nd*2+1].sm;
  if(sg[nd*2].firstMx==sg[nd*2+1].firstMx)
  {
    sg[nd].firstMx=sg[nd*2].firstMx;
    sg[nd].secondMx=max(sg[nd*2].secondMx,sg[nd*2+1].secondMx);
    sg[nd].fr=sg[nd*2].fr+sg[nd*2+1].fr;
  }
  else if(sg[nd*2].firstMx>sg[nd*2+1].firstMx)
  {
    sg[nd].firstMx=sg[nd*2].firstMx;
    sg[nd].secondMx=max(sg[nd*2].secondMx,sg[nd*2+1].firstMx);
    sg[nd].fr=sg[nd*2].fr;
  }
  else 
  {
    sg[nd].firstMx=sg[nd*2+1].firstMx;
    sg[nd].secondMx=max(sg[nd*2].firstMx,sg[nd*2+1].secondMx);
    sg[nd].fr=sg[nd*2+1].fr;
  }
  sg[nd].ad=0;sg[nd].mx=inf;
}
void build(int nd,int lo,int hi)
{
  if(lo==hi)
  {
    sg[nd]={0,inf,a[lo],a[lo],-inf,1};
    return ;
  }
  int md=(lo+hi)/2;
  build(nd*2,lo,md);build(nd*2+1,md+1,hi);
  merge(nd);
}
void pushDown(int nd,int lo,int hi)
{
  sg[nd].sm+=(hi-lo+1)*sg[nd].ad;
  sg[nd].firstMx+=sg[nd].ad,sg[nd].secondMx+=sg[nd].ad;
  if(lo!=hi)
  {
    sg[nd*2].ad+=sg[nd].ad,sg[nd*2].mx+=sg[nd].ad;
    sg[nd*2+1].ad+=sg[nd].ad,sg[nd*2+1].mx+=sg[nd].ad;
  }
  if(sg[nd].mx<sg[nd].firstMx)
  {
    sg[nd].sm-=(sg[nd].firstMx-sg[nd].mx)*sg[nd].fr;
    sg[nd].firstMx=sg[nd].mx;
  }
  if(lo!=hi)
  {
    sg[nd*2].mx=min(sg[nd*2].mx,sg[nd].mx);
    sg[nd*2+1].mx=min(sg[nd*2+1].mx,sg[nd].mx);
  }
  sg[nd].ad=0;sg[nd].mx=inf;
}
// add vl in a segment
void add(int nd,int lo,int hi,int lt,int rt,int vl)
{
  pushDown(nd,lo,hi);
  if(lo>rt||hi<lt)return ;
  if(lo>=lt&&hi<=rt)
  {
    sg[nd].ad+=vl;sg[nd].mx=min(inf,sg[nd].mx+vl);
    pushDown(nd,lo,hi);return ;
  }
  int md=(lo+hi)/2;
  add(nd*2,lo,md,lt,rt,vl);add(nd*2+1,md+1,hi,lt,rt,vl);
  merge(nd);
}
// in l to r segment change a[i]=vl if a[i]>vl;
void trim(int nd,int lo,int hi,int lt,int rt,int vl)
{
  pushDown(nd,lo,hi);
  if(lo>rt||hi<lt)return ;
  if(lo>=lt&&hi<=rt&&sg[nd].secondMx<=vl)
  {
    sg[nd].mx=min(vl*1LL,sg[nd].mx);
    pushDown(nd,lo,hi);return ;
  }
  int md=(lo+hi)/2;
  trim(nd*2,lo,md,lt,rt,vl);trim(nd*2+1,md+1,hi,lt,rt,vl);
  merge(nd);
}
long get(int nd,int lo,int hi,int lt,int rt)//range sum
{
  pushDown(nd,lo,hi);
  if(lo>rt||hi<lt)return 0;
  if(lo>=lt&&hi<=rt)return sg[nd].sm;
  int md=(lo+hi)/2;
  return get(nd*2,lo,md,lt,rt)+get(nd*2+1,md+1,hi,lt,rt);
}
