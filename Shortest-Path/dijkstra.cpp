int d[N+2],vs[N+2];
void dijkstra(int s,int n)
{
  for(int i=1;i<=n;i++)d[i]=inf,vs[i]=0;d[s]=0;
  priority_queue<pair<int,int> >pq;pq.push({0,s});
  
  while(pq.size())
  {
    pair<int,int>p=pq.top();pq.pop();
    int nd=p.second;if(vs[nd])continue;
    vs[nd]=1;

    for(auto x:adj[nd])
    {
      if(d[nd]+x.second<d[x.first])
      {
        d[x.first]=d[nd]+x.second;
        pq.push({-d[x.first],x.first});
      }
    }
  }
}
