/* 
Dynamic segment tree: range add, kth number
have to change a lot, won't compile
*/
struct segment
{
  int l,r;
  long sm,lz;
  segment():l(0),r(0),sm(0),lz(0){}
};
vector<segment>sg(2);
long nw=1;

void tooLazy(long nd,long lo,long hi)
{
  if(sg[nd].lz==0)return ;
  //sg[nd].sm+=1LL*sg[nd].lz*(hi-lo+1);
  if(lo!=hi)
  {
    long md=(lo+hi)/2;
    sg[sg[nd].l].lz+=sg[nd].lz;
    sg[sg[nd].l].sm+=(md-lo+1)*sg[nd].lz;
    sg[sg[nd].r].lz+=sg[nd].lz;
    sg[sg[nd].r].sm+=(hi-md)*sg[nd].lz;
  }
  sg[nd].lz=0;
}
void upd(long nd,long lo,long hi,long lt,long rt)
{
  if(lo>rt || hi<lt)return ;
  if((!sg[nd].l) && (lo!=hi))sg[nd].l=++nw,sg.push_back(segment());
  if((!sg[nd].r) && (lo!=hi))sg[nd].r=++nw,sg.push_back(segment());
  tooLazy(nd,lo,hi);
  if(lo>=lt && hi<=rt)
  {
    sg[nd].lz++;sg[nd].sm+=hi-lo+1;
    tooLazy(nd,lo,hi);
    return ;
  }

  long md=(lo*1LL+hi*1LL)/2;
  upd(sg[nd].l,lo,md,lt,rt);upd(sg[nd].r,md+1,hi,lt,rt);
  sg[nd].sm=sg[sg[nd].l].sm+sg[sg[nd].r].sm;
}
long ans=-1;
void get(long nd,long lo,long hi,long rm)
{
  if((!sg[nd].l) && (lo!=hi))sg[nd].l=++nw,sg.push_back(segment());
  if((!sg[nd].r) && (lo!=hi))sg[nd].r=++nw,sg.push_back(segment());
  tooLazy(nd,lo,hi);
  
  if(sm(lo,hi)-sg[nd].sm<rm)return ;

  if(lo==hi)
  {
    if(ans!=-1)assert(0);
    ans=lo;rm=0;return ;
  }

  long md=(lo*1LL+hi*1LL)/2;
  
  get(sg[nd].l,lo,md,rm);if(ans!=-1)return ;
  
  long lft=sm(lo,md)-sg[sg[nd].l].sm;
  get(sg[nd].r,md+1,hi,rm-lft);

  //sg[nd].sm=sg[sg[nd].l].sm+sg[sg[nd].r].sm;
}

