/*
mb(1)=1;
mb(n)=(-1)^cnt; where n is squre free and cnt is number of prime factor;
otherwise mb(n)=0;
***mobius sum of divisor of a number is 0, except 1 is 1;
***number of integer in a container co-prime with n is sum(mb(d)*cnt(d)), for
all divisor d of n. cnt(d) is the number of element in the container multiple
of d;
***all pair coPrime = sum(mb[i]*ncr(cnt[i],2)). cnt[i]=number of multiple of i in
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
