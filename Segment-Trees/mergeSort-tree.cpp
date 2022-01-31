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