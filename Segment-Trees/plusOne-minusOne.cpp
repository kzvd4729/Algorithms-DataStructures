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
