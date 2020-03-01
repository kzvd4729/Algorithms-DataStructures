/*
we will only define here primitive root for prime number(modulo prime).
a number g is called primitive root of prime p if g^i (1 to p-1) generates
all number from 1 to p-1(in any order).
primitive root is also called generator.
*/
int big(int b,int p,int m)
{
  int ret=1;
  while(p){if(p&1)ret=(1LL*ret*b)%m;b=(1LL*b*b)%m;p/=2;}
  return ret;
}
int generator(int p)
{
  vector<int>fact;
  int phi=p-1,n=phi;
  for(int i=2;i*i<=n;i++)
  {
  	if(n%i)continue;fact.push_back(i);
    while(n%i==0)n/=i;
  }
  if(n>1)fact.push_back(n);
  for(int res=2;res<=p;res++)
  {
    bool ok=true;
    for(size_t i=0;i<fact.size()&&ok;i++)
      ok&=big(res,phi/fact[i],p)!=1;
    if(ok)return res;
  }
  return -1;
}
