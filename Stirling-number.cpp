/*
stirling number of seocond kind:
there are n different object(distinguishable) and k identical boxes
(indistinguishable). how many ways to put object into boxes such that each box
have atleast one object.
boxes are considered to be set. permutation of object in box doesn't matter.
if boxes are distinguishable multiply by k!
           1   k        
formula:  ---  ∑   (-1)^i kCi (k-i)^n
           k!  i=0
both k can be crossed out. after reformulating:
(-1)^i 1/(i!)  *  1/(k-i)! (k-i)^n
for fixed n we can calculte for all k using fft
for stirling(3,2) there are three ways {1|23} {2|13} {3|12}
*/
int fac[N+2];
void init(int n)
{
  fac[0]=1;for(int i=1;i<=n;i++)fac[i]=(1LL*fac[i-1]*i)%mod;
}
void stirling(int n,int k)
{
  init(N);vector<int>a,b,c;
  for(int i=0;i<=n;i++)
  {
    a.push_back((big(-1,i)*big(fac[i],mod-2)+mod)%mod);
    b.push_back((1LL*big(i,n)*big(fac[i],mod-2))%mod);
  }
  c=multiply(a,b);//ntt multiply
  //each index in c means stirling(n,i)
}
