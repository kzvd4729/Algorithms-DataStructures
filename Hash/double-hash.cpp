const int mod1=1000001011,mod2=1000009999;
const int b1=193,b2=307;//greater than maximum value
int pw1[N+2],pw2[N+2];
void calPower()
{
  pw1[0]=1;pw2[0]=1;
  for(int i=1;i<=N;i++)
  {
    pw1[i]=(1LL*pw1[i-1]*b1)%mod1;
    pw2[i]=(1LL*pw2[i-1]*b2)%mod2;
  }
}
struct hsh
{
  vector<pair<int,int> >v;string s;
  void init(string _s)
  {
    v.clear();s=_s;
  }
  pair<int,int>makeHash()
  {
    int hs1=0,hs2=0;
    for(auto x:s)
    {
      hs1=(1LL*hs1*b1+x)%mod1;
      hs2=(1LL*hs2*b2+x)%mod2;
      v.push_back({hs1,hs2});
    }
    return {hs1,hs2};
  }
  pair<int,int>segment(int lt,int rt)
  {
    int x=v[rt].first,y=v[rt].second;
    if(!lt)return {x,y};
    x=x-(1LL*v[lt-1].first*pw1[rt-lt+1])%mod1;
    y=y-(1LL*v[lt-1].second*pw2[rt-lt+1])%mod2;
    if(x<0)x+=mod1;if(y<0)y+=mod2;
    return {x,y};
  }
}hs;