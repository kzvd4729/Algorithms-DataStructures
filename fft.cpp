/*
a polynomial of degree n-1(maximum power), with n distinct sample
the polynomial can be uniquely determined. in other way from n sample
the polynomial of degree n-1 can be uniquely determined.
two polynomial multiplication takes n^2 time. but in sample form, multiplication
takes linear time. we convert the polynomials in the sample form in nlgn,
multiply them in n time and go back to polynomial form in nlgn time.
once we convert a polynomial in sample form we can do some operation on it,
like multiplication of several sample, power by anything, multiply by any number.
and the end of the day, go back to polynomial land.
1 x0 x0^2 x0^3 x0^4 ...   a0      b0
1 x1 x1^2 x1^3 x1^4 ... x a1  =   b1
1 x2 x2^2 x2^3 x2^4 ...   a2      b2
....
the matrix is called vandermonde matrix. bi is the value at point ai.
to get ai back from bi we need to calculate the inverse of vandermonde matrix.
luckily the inverse is
      1 x0^-1 x0^-2 x0^-3 x0^-4 ...   b0      a0
1/n * 1 x1^-1 x1^-2 x1^-3 x1^-4 ... x b1  =   a1
      1 x2^-1 x2^-2 x2^-3 x2^-4 ...   b2      a2
....
now we know how to convert between polynomial to sample and vice verse.
but complexity is still n^2.
divide and conquer: we will divide the polynomial in two segment. one containing
only even entries and other with odd entries. polynomial A=even(x^2)+x*odd(x^2).
so the idea is divide polynomial is half, evaluate at n points at each recursion
level, still (n^2)lgn. but we have the freedom to choose n points as we wish.
every number other than 0 has two square root. imagine in the base case when
polynomial size is 1, we evaluate at point 1. now at the previous step when the
size is 2, we can use -1 and 1 to evaluate because we already computed the
value of even(x^2) and odd(x^2). when the size is 4 we can use i,-i,1,-1.
every point evaluation is completed in O(1) and thus the complexity will be nlgn.
and as points being double at every step we need the polynomial to be power of 2.
just by padding extra 0 coefficient to the higher degree of the polynomial.
but i,-i and all their square root are complex number.
imagine a unit circle in complex plain.
1, -1 are 180 degree far, call them second roots of unity
1, i, -1, -i are 90 degree far, call them fourth roots of unity
eighth roots of unity are 45 degree far from each other.
so we represent complex number by their polar angle cos+isin.
we find the angle of the roots of unity, multiply to rotate point uniformly.
*/
const double pi=acos(-1.0);
struct complx
{
  double x,y;
  complx(double a=0,double b=0):x(a),y(b){}
  complx operator+(complx c){return complx(x+c.x,y+c.y);}
  complx operator-(complx c){return complx(x-c.x,y-c.y);}
  complx operator*(complx c){return complx(x*c.x-y*c.y,x*c.y+y*c.x);}//complx
  complx operator/(double d){return complx(x/d,y/d);}
  void operator*=(complx c){double a=x*c.x-y*c.y,b=x*c.y+y*c.x;x=a,y=b;}
  void operator/=(double d){x/=d,y/=d;}
};
void dft(vector<complx>&a,bool inv)
{
  int n=a.size();if(n==1)return ;
  vector<complx>a0(n/2),a1(n/2);

  for(int i=0;i<n/2;i++)
    a0[i]=a[2*i],a1[i]=a[2*i+1];
  dft(a0,inv);dft(a1,inv);

  double ang=2*pi/n*(inv?-1:1);
  complx r(1),m(cos(ang),sin(ang));
  for(int i=0;i<n/2;i++)
  {
    a[i]=a0[i]+r*a1[i];
    a[i+n/2]=a0[i]-r*a1[i];
    if(inv)
      a[i]/=2,a[i+n/2]/=2;//overall divided by n
    r*=m;
  }
}
/*
turns out we can convert divide and conquer algorithm into an iterative one.
in first recursion level last bit 0 element will be in first half and other in
second half. this is true for other recursion level as well.
so we can shuffle the order of the element by reversing the bit so that every
recursion level becomes continuous and thus allow iterative implementation
*/
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
void dft(vector<complx>&a,bool inv)
{
  int n=a.size();
  for(int i=0;i<n;i++)
    if(r[i]<i)swap(a[i],a[r[i]]);

  for(int ln=2;ln<=n;ln*=2)//1 doesn't need to be calculated.
  {
    double ang=2*pi/ln*(inv?-1:1);
    complx m(cos(ang),sin(ang));//multiplier, roots of unity
    for(int i=0;i<n;i+=ln)//every ln length segment in this level
    {
      complx r(1),u,v;//unit angle
      for(int j=0;j<ln/2;j++)
      {
        u=a[i+j],v=r*a[i+j+ln/2];//even and odd
        a[i+j]=u+v,a[i+j+ln/2]=u-v;//positive in the first half
        r*=m;
      }
    }
  }
  if(inv)for(auto &x:a)x/=n;
}
//polynomial of the form a0x^0+a1x^1+a2x^2+a3x^3+.....
vector<int>multiply(vector<int>&a,vector<int>&b)
{
  vector<complx>fa(a.begin(),a.end());//all real part
  vector<complx>fb(b.begin(),b.end());//all real part
  int n=1;while(n<a.size()+b.size())n*=2;
  fa.resize(n);fb.resize(n);//padding higher degree with 0 coefficient

  bitReverse(n);//for iterative implementation

  dft(fa,false);dft(fb,false);//now in sample form

  for(int i=0;i<n;i++)//scalar operation on sample
    fa[i]*=fb[i];

  dft(fa,true);//inverse transform

  vector<int>ret(n);
  for(int i=0;i<n;i++)
    ret[i]=round(fa[i].x);
  return ret;
}
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
