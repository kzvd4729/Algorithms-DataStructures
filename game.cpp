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

/*
staircase nim: their is an arry of coin indexed 0 to n-1. in a move
a player can choose an index(>0) and move some coin to i-1. player
can not make a move loses. 
coin of even position has nothing to do. if some player moves some
coin from even position to odd position other palyer can move those
coin to even position again. so state of game doesn't change.
answer is xor of odd position.
*/
