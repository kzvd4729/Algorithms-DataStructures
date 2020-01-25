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

/*
mb(1)=1;
mb(n)=(-1)^cnt; where n is squre free and cnt is number of prime factor;
otherwise mb(n)=0;
***mobius sum of divisor of a number is 0, except 1 is 1;
***number of integer in a container co-prime with n is sum(mb(d)*cnt(d)), for
all divisor d of n. cnt(d) is the number of element in the container multiple
of d;
***all pair gcd = sum(mb[i]*ncr(cnt[i],2)). cnt[i]=number of multiple of i in
the array. for three element it is ncr(cnt[i],3) and so on. it depends on
how many times the loop is executed.
*/
int mb[N+2],vis[N+2];
void mobius()
{
  for(int i=1;i<=N;i++)mb[i]=1;
  for(int i=2;i<=N;i++)
  {
    if(vis[i])continue;
    for(int j=i;j<=N;j+=i)
    {
      mb[j]*=-1;vis[j]=1;
      if(i<=30000&&(j%(i*i)==0))mb[j]=0;
    }
  }
}
