/* range assign, range query */
int sg[4*N+8],lz[4*N+8];
void build(int nd,int lo,int hi)
{
  lz[nd]=-1;
  if(lo==hi)
  {
    sg[nd]=b[lo-1]-'0';return ;
  }
  int md=(lo+hi)/2;
  build(nd*2,lo,md);build(nd*2+1,md+1,hi);
 
  sg[nd]=sg[nd*2]+sg[nd*2+1];
}
void tooLazy(int nd,int lo,int hi)
{
  if(lz[nd]==-1)return ;
 
  sg[nd]=(hi-lo+1)*lz[nd];
  if(lo==hi)return;
 
  lz[nd*2]=lz[nd];lz[nd*2+1]=lz[nd];
  lz[nd]=-1;
}
void upd(int nd,int lo,int hi,int lt,int rt,int vl)
{
  tooLazy(nd,lo,hi);
  if(lo>rt||hi<lt)return ;
  if(lo>=lt&&hi<=rt)
  {
    lz[nd]=vl;tooLazy(nd,lo,hi);
    return ;
  }
  int md=(lo+hi)/2;
  upd(nd*2,lo,md,lt,rt,vl);
  upd(nd*2+1,md+1,hi,lt,rt,vl);
 
  sg[nd]=sg[nd*2]+sg[nd*2+1];
}
int get(int nd,int lo,int hi,int lt,int rt)
{
  tooLazy(nd,lo,hi);
  if(lo>rt||hi<lt)return 0;
  if(lo>=lt&&hi<=rt)return sg[nd];
  int md=(lo+hi)/2;
  return get(nd*2,lo,md,lt,rt)+get(nd*2+1,md+1,hi,lt,rt);
}