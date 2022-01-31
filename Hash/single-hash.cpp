/* single hash */
const int mod=1000001011;
const int b=193;//greater than maximum value
int pw[N+2];
void calPower()
{
  pw[0]=1;
  for(int i=1;i<=N;i++)
    pw[i]=(1LL*pw[i-1]*b)%mod;
}
struct hsh
{
  vector<int>v;string s;
  void init(string _s)
  {
    v.clear();s=_s;
  }
  int makeHash()
  {
    int hs=0;
    for(auto x:s)
    {
      hs=(1LL*hs*b+x)%mod;
      v.push_back(hs);
    }
    return hs;
  }
  int segment(int lt,int rt)
  {
    int x=v[rt];if(!lt)return x;
    x=x-(1LL*v[lt-1]*pw[rt-lt+1])%mod;
    if(x<0)x+=mod;return x;
  }
}hs;
