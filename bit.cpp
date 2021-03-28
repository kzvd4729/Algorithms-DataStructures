/*
range update range sum.
*/
long bit[2][N+2];
void upd(int x,long ml,long sm)
{
  for( ;x<=N;x+=(x&-x))
    bit[0][x]+=ml,bit[1][x]+=sm;
}
long get(int x)
{
  long ml=0,sm=0,bg=x;
  for( ;x>0;x-=(x&-x))
    ml+=bit[0][x],sm+=bit[1][x];
  return ml*bg+sm;
}
long getRange(int lo,int hi)
{
  return get(hi)-get(lo-1);
}
void addRange(int lo,int hi,long vl)
{
  upd(lo,vl,-vl*(lo-1));
  upd(hi,-vl,vl*hi);
}
