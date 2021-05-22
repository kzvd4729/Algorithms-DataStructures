/*
add +1 in a segment or -1 in a segment. it is guaranteed that sum will
never be negative. determine number of on index.
*/
int cnt[4*N+8],sm[4*N+8],dsm[4*N+8];
void upd(int node,int lo,int hi,int lt,int rt,int vl)
{
  if(lo>rt||hi<lt)return;
  if(lo>=lt&&hi<=rt)
  {
    cnt[node]+=vl;
    if(cnt[node])sm[node]=hi-lo+1;else sm[node]=dsm[node];
    return;
  }
  int md=(lo+hi)/2;
  upd(node*2,lo,md,lt,rt,vl),upd(node*2+1,md+1,hi,lt,rt,vl);
  dsm[node]=sm[node*2]+sm[node*2+1];
  if(cnt[node])sm[node]=hi-lo+1;else sm[node]=dsm[node];
}

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


/*
merge sort segment tree. 
*/
vector<int>seg[4*N+8];
void build(int nd,int lo,int hi)
{
  if(lo==hi){seg[nd].push_back(a[lo]);return;}
  int md=(lo+hi)/2;
  build(nd*2,lo,md);build(nd*2+1,md+1,hi);

  seg[nd].resize((int)seg[nd*2].size()+(int)seg[nd*2+1].size());
  merge(seg[nd*2].begin(),seg[nd*2].end(),seg[nd*2+1].begin(),seg[nd*2+1].end(),seg[nd].begin());
}
int get(int nd,int lo,int hi,int lt,int rt,int x,int y)//numbers in x-y range
{
  if(lo>rt||hi<lt)return 0;
  if(lo>=lt&&hi<=rt)
    return upper_bound(seg[nd].begin(),seg[nd].end(),y)-lower_bound(seg[nd].begin(),seg[nd].end(),x);

  int md=(lo+hi)/2;
  return get(nd*2,lo,md,lt,rt,x,y)+get(nd*2+1,md+1,hi,lt,rt,x,y);
}

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

/*
initialy array is filled with 1. assign 0 to a segment. find a range sum
*/
int seg[5*N+2],lazy[5*N+2];
void build(int node,int lo,int hi)
{
  if(lo==hi){seg[node]=1;return ;}int md=(lo+hi)/2;
  build(node*2,lo,md);build(node*2+1,md+1,hi);
  seg[node]=seg[node*2]+seg[node*2+1];
}
void tooLazy(int node,int lo,int hi)
{
  if(!lazy[node])return ;seg[node]=0;if(lo==hi)return ;
  lazy[node*2]=1;lazy[node*2+1]=1;lazy[node]=0;
}
void upd(int node,int lo,int hi,int lt,int rt)
{
  tooLazy(node,lo,hi);if(lo>rt||hi<lt)return;
  if(lo>=lt&&hi<=rt){lazy[node]=1;tooLazy(node,lo,hi);return ;}
  int md=(lo+hi)/2;
  upd(node*2,lo,md,lt,rt);upd(node*2+1,md+1,hi,lt,rt);
  seg[node]=seg[node*2]+seg[node*2+1];
}
int get(int node,int lo,int hi,int lt,int rt)
{
  tooLazy(node,lo,hi);if(lo>rt||hi<lt)return 0;
  if(lo>=lt&&hi<=rt)return seg[node];int md=(lo+hi)/2;
  return get(node*2,lo,md,lt,rt)+get(node*2+1,md+1,hi,lt,rt);
}


/*
number of distinct element in a range
*/
int sz;
struct segment
{
  int l,r,sm;
}seg[42*N+2];//2*lg(mx)*N
void upd(int node,int lo,int hi,int pnode,int id,int vl)
{
  if(lo==hi){seg[node].sm=seg[pnode].sm+vl;return ;}
  int md=(lo+hi)/2;
  if(id<=md)
  {
    seg[node].l=++sz;
    upd(seg[node].l,lo,md,seg[pnode].l,id,vl);
    seg[node].r=seg[pnode].r;
  }
  else
  {
    seg[node].r=++sz;
    upd(seg[node].r,md+1,hi,seg[pnode].r,id,vl);
    seg[node].l=seg[pnode].l;
  }
  seg[node].sm=seg[seg[node].l].sm+seg[seg[node].r].sm;
}
int get(int node,int lo,int hi,int lt,int rt)
{
  if(lo>=lt&&hi<=rt)return seg[node].sm;
  if(lo>rt||hi<lt)return 0;
  int md=(lo+hi)/2;
  return get(seg[node].l,lo,md,lt,rt)+get(seg[node].r,md+1,hi,lt,rt);
}
int last[N+2],root[N+2];
void solve(int n,int mx)
{
  for(int i=1;i<=n;i++)
  {
    int x;cin>>x;int tmp=++sz;
    upd(tmp,1,mx,root[i-1],i,1);
    if(last[x]){root[i]=++sz;upd(root[i],1,mx,tmp,last[x],-1);}
    else root[i]=tmp;
    
    last[x]=i;
  }
  //cout<<get(root[right],1,N,left,right)<<"\n";
}

/*
range add min query
*/
long seg[5*N+2],lazy[5*N+2];
void tooLazy(int node,int lo,int hi)
{
  seg[node]+=lazy[node];
  if(lo!=hi)
    lazy[node*2]+=lazy[node],lazy[node*2+1]+=lazy[node];
  lazy[node]=0;
}
void upd(int node,int lo,int hi,int lt,int rt,long ad)
{
  tooLazy(node,lo,hi);
  if(lo>rt||hi<lt)return ;
  if(lo>=lt&&hi<=rt)
  {
    lazy[node]+=ad;tooLazy(node,lo,hi);return ;
  }
  int md=(lo+hi)/2;
  upd(node*2,lo,md,lt,rt,ad);upd(node*2+1,md+1,hi,lt,rt,ad);
  seg[node]=min(seg[node*2],seg[node*2+1]);
}
long get(int node,int lo,int hi,int lt,int rt)
{
  tooLazy(node,lo,hi);
  if(lo>rt||hi<lt)return 1e18;
  if(lo>=lt&&hi<=rt)
    return seg[node];
  int md=(lo+hi)/2;
  return min(get(node*2,lo,md,lt,rt),get(node*2+1,md+1,hi,lt,rt));
}

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

