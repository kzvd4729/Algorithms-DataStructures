/*
dp divide and conquer optimization.
dp[i]=dp[j-1]+cost(j,i); if optimum j is non decreasing with i then divide and
conquer can solve this with nlogn instead of n^2.

sample code is for dp[i][j]=dp[i-1][k-1]+cost[k][j]. i is constant.
lo hi hold range for j and lt rt are possible k.
*/
void dfs(int i,int lo,int hi,int lt,int rt)
{
  if(lo>hi)return ;
  int j=(lo+hi)>>1;int &mn=dp[i][j],op;
  for(int k=lt,r=min(j,rt);k<=r;k++)
  {
    int now=ds[k][j]+dp[i-1][k-1];
    if(now<mn)mn=now,op=k;
  }
  dfs(i,lo,j-1,lt,op);dfs(i,j+1,hi,op,rt);
}
