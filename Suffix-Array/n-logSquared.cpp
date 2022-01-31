/*
complexity n lg^2(n). with single hash
*/
const int mod=1000001011,b=193;
int pw[N+2];
void cal(int n)
{
  pw[0]=1;
  for(int i=1;i<=n;i++)pw[i]=(1LL*pw[i-1]*b)%mod;
}
int h[N+2];string s;//global string
void makeHash()
{
  int hs=0,i=0;
  for(auto x:s){hs=(1LL*hs*b+x)%mod;h[i++]=hs;}
}
int get(int i,int j)
{
  int x=h[j];if(!i)return x;x=x-(1LL*h[i-1]*pw[j-i+1])%mod;
  if(x<0)x+=mod;return x;
}
int sz;
bool cmp(int a,int b)
{
  int mx=sz-max(a,b);int lo=0,hi=mx,md;
  while(lo<=hi)
  {
    int md=(lo+hi)/2;if(get(a,a+md)==get(b,b+md))lo=md+1;
    else hi=md-1;
  }
  if(a+lo==sz)return true;if(b+lo==sz)return false;
  return s[a+lo]<s[b+lo];
}
vector<int>suffixSort()
{
  sz=s.size();cal(sz);makeHash();
  vector<int>v;
  for(int i=0;i<sz;i++)v.push_back(i);
  sort(v.begin(),v.end(),cmp);
  return v;
}