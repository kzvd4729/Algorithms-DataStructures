int d[N+2][240+2],pt[N+2];//upto 1e6
void divisors(void)
{
  for(int i=1;i<=N;i++)
  {
    for(int j=i;j<=N;j+=i)d[j][++pt[j]]=i;
  }
}
int phi[N+2];
void calPhi(void)
{
  for(int i=1;i<=N;i++)
  {
    phi[i]+=i;
    for(int j=i+i;j<=N;j+=i)phi[j]-=phi[i];
  }
}
