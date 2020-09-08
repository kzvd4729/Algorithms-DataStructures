/*
there are n piles of stones. player alternatively removes stone
from any pile(atleast one). the player who removes the last
stone loses(wins for the normal nim).
*/
int misereNim(int n)//0 if first player wins
{
  int m=0,f=0,x=0;
  for(int i=1;i<=n;i++)
  {
    m+=(bool)a[i];f|=(a[i]>1);
    x^=a[i];
  }
  if(f==0)return m%2;
  else return !((bool)(x));
}
