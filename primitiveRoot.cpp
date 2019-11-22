/*
we will only define here primitive root for prime number.
a number g is called primitive root of prime p if g^i (1 to p-1) generates
all number from 1 to p-1(in any order).
primitive root is also called generator.
*/
//a naive approach
int primitiveRoot(int p)
{
  vector<int>v(p);v[0]=1;
  for(int i=2;i<p;i++)
  {
    for(int j=1;j<p;j++)v[j]=0;
    int pw=1,f=0;
    for(int j=1;j<p;j++)
    {
      pw=(1LL*pw*i)%p;
      if(v[pw]){f=1;break;}
      v[pw]=1;
    }
    if(!f)return i;
  }
  return -1;
}
