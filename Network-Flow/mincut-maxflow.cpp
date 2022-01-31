/*
maximum flow with dinic algorithm. complexity EV^2(far better).
a reverse edge is added to maintain the alternative path.
*/
struct edge
{
  int a,b,f,c;
};
int sr,sn;//sr=0,sn=last node+1;
vector<edge>ed;vector<int>adj[N+2];
void clear(void)
{
  ed.clear();
  for(int i=0;i<=sn;i++)adj[i].clear();
}
void addEdge(int a,int b,int c)
{
  edge e;e={a,b,0,c};
  adj[a].push_back(ed.size());
  ed.push_back(e);e={b,a,0,0};
  //e={b,a,0,c};//for bidirectional
  adj[b].push_back(ed.size());
  ed.push_back(e);
}
//finding all possible path. normal bfs
int dis[N+2],pt[N+2];
bool bfs(void)
{
  for(int i=0;i<=sn;i++)dis[i]=inf;
  queue<int>q;q.push(sr);dis[sr]=0;
  while(q.size())
  {
    int u=q.front();q.pop();
    for(auto x:adj[u])
    {
      int v=ed[x].b;
      if(dis[v]==inf&&ed[x].f<ed[x].c)dis[v]=dis[u]+1,q.push(v);
    }
  }
  return dis[sn]!=inf;
}
/*
pushing positive flow through a path. each dfs for a path.
it is possible to push flow through all the path at once.(not better complexity)
*/
int dfs(int u,int flow)
{
  if(!flow||u==sn)return flow;
  //if there was not possible before, it is not possible now.
  for( ;pt[u]<adj[u].size();pt[u]++)
  {
    int id=adj[u][pt[u]];int v=ed[id].b;
    if(dis[v]!=dis[u]+1)continue;
    if(int pushed=dfs(v,min(flow,ed[id].c-ed[id].f)))
    {
      ed[id].f+=pushed;ed[id^1].f-=pushed;return pushed;
    }
  }
  return 0;
}
int dinic(void)
{
  int flow=0;
  while(bfs())
  {
    for(int i=0;i<=sn;i++)pt[i]=0;
    while(int pushed=dfs(sr,inf))flow+=pushed;
  }
  return flow;
}
