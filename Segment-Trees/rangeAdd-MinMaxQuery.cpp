/* range add min max query */
int mn[4*N+8],lz[4*N+8],mx[4*N+8];
void tooLazy(int nd,int lo,int hi)
{
  mn[nd]+=lz[nd];mx[nd]+=lz[nd];
  if(lo!=hi)lz[nd*2]+=lz[nd],lz[nd*2+1]+=lz[nd];
  lz[nd]=0;
}
void upd(int nd,int lo,int hi,int lt,int rt,int ad)
{
  tooLazy(nd,lo,hi);
  if(lo>rt||hi<lt)return ;
  if(lo>=lt&&hi<=rt)
  {
    lz[nd]+=ad;tooLazy(nd,lo,hi);return ;
  }
  int md=(lo+hi)/2;
  upd(nd*2,lo,md,lt,rt,ad);upd(nd*2+1,md+1,hi,lt,rt,ad);
  mn[nd]=min(mn[nd*2],mn[nd*2+1]);
  mx[nd]=max(mx[nd*2],mx[nd*2+1]);
}
int getMin(int nd,int lo,int hi,int lt,int rt)
{
  tooLazy(nd,lo,hi);
  if(lo>rt||hi<lt)return 1e9;
  if(lo>=lt&&hi<=rt)return mn[nd];
  int md=(lo+hi)/2;
  return min(getMin(nd*2,lo,md,lt,rt),getMin(nd*2+1,md+1,hi,lt,rt));
}
int getMax(int nd,int lo,int hi,int lt,int rt)
{
  tooLazy(nd,lo,hi);
  if(lo>rt||hi<lt)return -1e9;
  if(lo>=lt&&hi<=rt)return mx[nd];
  int md=(lo+hi)/2;
  return max(getMax(nd*2,lo,md,lt,rt),getMax(nd*2+1,md+1,hi,lt,rt));
}