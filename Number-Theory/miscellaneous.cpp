vector<int>d[N+2];
void divisors(void)
{
  for(int i=1;i<=N;i++)
  {
    for(int j=i;j<=N;j+=i)d[j].push_back(i);
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

/*
res[n] = sumOf(i/gcd(i,n)) for i=1 to n
*/
long phi[N+2],res[N+2];
void calPhi(void)
{
  for(int i=1;i<=N;i++)
  {phi[i]+=i;for(int j=i+i;j<=N;j+=i)phi[j]-=phi[i];}
  for(int i=1;i<=N;i++)
  {for(int j=i;j<=N;j+=i)res[j]+=i*phi[i];}
  for(int i=1;i<=N;i++)res[i]=(res[i]+1)/2;
}

/*
res[n] = sumOf(gcd(i,n)) for i=1 to n
*/
long phi[N+2],res[N+2];
void calPhi(void)
{
  for(int i=1;i<=N;i++)
  {phi[i]+=i;for(int j=i+i;j<=N;j+=i)phi[j]-=phi[i];}
  for(int i=1;i<=N;i++)
  {for(int j=i+i;j<=N;j+=i)res[j]+=i*phi[j/i];}
  for(int i=1;i<=N;i++)res[i]+=i;
}