/*
Arpa's trick. range min,max in O(1). offline. linear memory.
sort range query by their right side, answer every query ending i when 1 to i has
been processed.
*/
int par[N+2],aa[N+2];
inline int get(int x)
{
  if(x==par[x])return x;
  return par[x]=get(par[x]);
}
//for max
void process(int n)
{
  stack<int>st;
  for(int i=1;i<=n;i++)
  {
    while(st.size()&&aa[st.top()]<=aa[i])
      par[st.top()]=i,st.pop();
    par[i]=i;st.push(i);
    /*answer all query ending at i*/
  }
}
