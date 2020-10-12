/*
basis for xor: S is set of some positive integer.
B is another set. we call B basis
of S if every element of S can be represented by xor value
of some subset of B and size of B is minimum possible.
*/
vector<int>b;//size of basis will always be <= log
bool isPossible(int x)
{
  for(auto y:b)x=min(x,x^y);
  return !x;
}
void insertX(int x)//online insert
{
  if(isPossible(x))return ;
  for(auto &y:b)if((x^y)<y)y^=x;
  b.push_back(x);sort(b.begin(),b.end());
}
//number of distinct possible value(0 included).
int maxSize()
{
  int p=1;
  for(int i=0;i<b.size();i++)p*=2;
  return p;
}
int kth(int k)
{
  int ret=0;k--;
  for(int i=0;i<b.size();i++)if((k>>i)&1)ret^=b[i];
  return ret;
}
