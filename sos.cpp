/*
dp[x]=sum of all aa[i] such that x&i=i;
i is the submask of x.
*/
int dp[N+2],aa[N+2];
void brutforce(int n)
{
  for(int msk=0;msk<(1<<n);msk++)
  {
    for(int i=0;i<(1<<n);i++)
    {
      if(msk&i==i)
        dp[msk]+=aa[i];
    }
  }
}
void suboptimal(int n)
{
  for(int msk=0;msk<(1<<n);msk++)
  {
    dp[msk]=aa[0];
    for(int i=msk;i>0;i=(i-1)&msk)
      dp[msk]+=aa[i];
  }
}
//sum over subset
void sos(int n)
{
  for(int i=0;i<(1<<n);i++)
    dp[i]=aa[i];
  //loop order matters
  for(int i=0;i<n;i++)
  {
    for(int msk=0;msk<(1<<n);msk++)
    {
      if(msk&(1<<i))
        dp[msk]+=dp[msk^(1<<i)];
    }
  }
}
//sum of id where msk is subset of id
void sos(int n)
{
  for(int i=0;i<(1<<n);i++)
    dp[i]=aa[i];
  for(int i=0;i<n;i++)
  {
    for(int msk=(1<<n)-1;msk;msk--)
    {
      if(!(msk&(1<<i)))
        dp[msk]+=dp[msk^(1<<i)];
    }
  }
}
