/*
x=a1(mod m1)       x=a2(mod m2)        solve for x.....
x=a1+m1*k1         x=a2+m2*k2
so, a1+m1*k1 = a2+m2*k2
=> m1*(-k1)+m2*k2 = a1-a2
using extended gcd, we can solve m1*x'+m2*y' = g(gcd(m1,m2)) for x',y'.

if(a1-a2) is not divided by g then there is no solution.

multiplying both side by (a1-a2)/g we get
m1*x'*((a1-a2)/g)+m2*y'*((a1-a2)/g) = a1-a2

so k1 = -x'*(a1-a2)/g
thus x = (a1+m1*x'*(a2-a1)/g)%(lcm(m1,m2)).

as lcm(m1,m2) can be greater than 1e9 there might be overflow.
ca (mod cb) = (a mod b)*c
lcm(m1,m2) = m1*(m2/g)
so, (m1*x'*(a2-a1)/g)%(lcm(m1,m2)) = m1*(x'*(a2-a1)/g)%(m2/g)

overall, (a1+m1*(x'*(a2-a1)/g)%(m2/d))%lcm(m1,m2);
*/
//solves the equation ax+by=gcd(a,b)
long exgcd(long a,long b,long &x,long &y)
{
  if(!b){x=1,y=0;return a;}
  long x1,y1;
  long g=exgcd(b,a%b,x1,y1);
  x=y1,y=x1-(a/b)*y1;
  return g;
}
//if all m are relative prime with other than the congruent equation have
//a unique solution
//remainder vector and modulo vector. modulo doesn't need to be co prime
long crt(vector<long>&a,vector<long>&m)
{
  long ans=a[0],lcm=m[0];
  for(int i=1;i<a.size();i++)
  {
    long x,y;long g=exgcd(lcm,m[i],x,y);
    if((a[i]-ans)%g!=0)assert(0);//no solution
    long md=(lcm/g)*m[i];
    ans=(ans+lcm*((x*((a[i]-ans)/g))%(m[i]/g)))%md;
    lcm=md;ans=(ans+lcm)%lcm;
  }
  return ans;
}
