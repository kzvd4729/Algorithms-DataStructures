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
