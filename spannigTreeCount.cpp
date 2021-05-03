/*
Graph is given in adjacency vetor, works for
multiedge. complexity n^3.
*/
int numberOfSpanningTrees(int n)
{
  vector<vector<int> >a(n+2,vector<int>(n+2,0));
  for(int i=1;i<=n;i++)
  {
    for(auto x:ad[i])a[i][x]++;
    a[i][i]=ad[i].size()*-1;
  }
  for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)a[i][j]*=-1;

  for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)a[i][j]=(a[i][j]+mod)%mod;


  int det=1;n--;
  for(int i=1;i<=n;i++)
  {
    if(a[i][i]==0)
    {
      for(int j=i+1;j<=n;j++)
      {
        if(a[j][i]!=0)
        {
          swap(a[i],a[j]);
          det=(det*(-1)+mod)%mod;
          break;
        }
      }
      if(a[i][i]==0)return 0;
    }

    det=(1LL*det*a[i][i])%mod;
    int ml=big(a[i][i],mod-2);

    for(int j=1;j<=n+1;j++)a[i][j]=(1LL*a[i][j]*ml)%mod;
    for(int j=i+1;j<=n;j++)
    {
      int ji=a[j][i];
      for(int k=1;k<=n+1;k++)
      {
        a[j][k]-=(1LL*a[i][k]*ji)%mod;
        a[j][k]=(a[j][k]+mod)%mod;
      }
    }
  }
  return det;
}
