/*
euler path: starts from any vertex, visits every edge exactly once.
euler circuit: starts from any vertex, visits every edge exactly once and
               returns to the start vertex.
for directed graph.
*/
int in[N+2],out[N+2];vector<int>cir;//circuit
bool eulerCircuit(int n,int start)
{
  for(int i=1;i<=n;i++)if(in[i]!=out[i])return false;
  stack<int>st;st.push(start);
  while(!st.empty())
  {
    int u=st.top();
    if(adj[u].size()==0)
    {
      cir.push_back(u);st.pop();
    }
    else
    {
      st.push(adj[u].back());adj[u].pop_back();
    }
  }
  reverse(cir.begin(),cir.end());
  return true;
}
void solve(int n)//adj graph is given
{
  for(int i=1;i<=n;i++)
  {
    for(auto x:adj[i])out[i]++,in[x]++;
  }
  eulerCircuit(n,1);
}
