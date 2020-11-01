int d[N+2],qd[N+2];
void spfa(int n,int sr)
{
  for(int i=1;i<=n;i++)d[i]=inf,qd[i]=0;
  queue<int>q;q.push(sr);qd[sr]=1,d[sr]=0;
  while(q.size())
  {
    int u=q.front();q.pop();qd[u]=0;
    for(auto x:adj[u])
    {
      if(d[u]+x.second<d[x.first])
      {
        d[x.first]=d[u]+x.second;
        if(!qd[x.first])q.push(x.first),qd[x.first]=1;
      }
    }
  }
}

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
