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
/*
basic D&C dft function
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
*/
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