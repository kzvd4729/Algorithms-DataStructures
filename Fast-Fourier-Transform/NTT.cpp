/*
so, the main thing about converting polynomial into a sample form is to evalute
at n distinct point(highest degree of the polynomial is n-1).
a number g is called primitive root of prime p if g^i (1 to p-1) generates
all number from 1 to p-1(in any order).
now imagine we have to calculate ntt modulo prime p. g is the generator of p.
if p=17, g=3; in the base case of the recursion when n=1,we can use 3^0.
when n=2 we can use sample 3^0 and 3^8 as (3^0)^2=(3^8)^2=3^0. when n=4 we can
use 3^0, 3^8, 3^4, 3^12. when n=8 3^0, 3^8, 3^4, 3^12, 3^2, 3^10, 3^16, 3^14.
and so on. as 3 is the generator every power guarantee distinct number.
in sorted order:- //actually 3^0 is 3^(p-1) in this case 3^16
3^16
3^8 3^16
3^4 3^8 3^12 3^16
3^2 3^4 3^6 3^8 3^10 3^12 3^14 3^16
3^1 3^2 3^3 3^4 3^5 3^6 3^7 3^8 3^9 3^10 3^11 3^12 3^13 3^14 3^15 3^16

the maximum number of sample we can take is 2^k which divides p-1.
so to ensure 2^k sample, p have to be in the form c*2^k+1.
of course we can use less power of 2 than k for sample.
*/
const int mod=786433;//c*2^k+1 form, 2^k>maximum degree of polynomial
const int g=10;//primitive root or generator
vector<int>r;
void bitReverse(int n)//n is power of 2
{
  r.resize(n);for(int i=0;i<n;i++)r[i]=0;
  int p=0;while((1<<p)<n)p++;
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<p;j++)
      if(i&(1<<j))r[i]|=(1<<(p-j-1));
  }
}
int big(int b,int p)
{
  int ret=1;
  while(p)
  {
    if(p%2)ret=(1LL*ret*b)%mod;
    b=(1LL*b*b)%mod;p/=2;
  }
  return ret;
}
void dft(vector<int>&a,bool inv)
{
  int n=a.size();
  for(int i=0;i<n;i++)
    if(r[i]<i)swap(a[i],a[r[i]]);
  for(int ln=2;ln<=n;ln*=2)//1 doesn't need to be calculated.
  {
    int m=inv?big(g,mod-1-(mod-1)/ln):big(g,(mod-1)/ln);
    for(int i=0;i<n;i+=ln)//every ln length segment in this level
    {
      int r=1,u,v;
      for(int j=0;j<ln/2;j++)
      {
        u=a[i+j],v=(1LL*r*a[i+j+ln/2])%mod;//even and odd
        a[i+j]=u+v<mod?u+v:u+v-mod;
        a[i+j+ln/2]=u-v>=0?u-v:u-v+mod;
        r=(1LL*r*m)%mod;
      }
    }
  }
  if(inv)
  {
    int ni=big(n,mod-2);
    for(auto &x:a)x=(1LL*x*ni)%mod;
  }
}
//a^0+a^1+a^2+a^3+... format
vector<int>multiply(vector<int>a,vector<int>b)
{
  int sz=a.size()+b.size();
  int n=1;while(n<sz)n<<=1;bitReverse(n);
  a.resize(n);b.resize(n);
  dft(a,false);dft(b,false);
  for(int i=0;i<n;i++)a[i]=(1LL*a[i]*b[i])%mod;
  dft(a,true);return a;
}
