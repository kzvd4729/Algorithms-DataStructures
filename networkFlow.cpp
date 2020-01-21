//..............................................................................
/*
flow with demands: capacity is defined by two values lo and hi, hi is maximum
allowable flow for this edge. lo is least amount flow that have to be sent in
this edge. to solve the problem add nsr and nsn. add an edge from nsr to 
every v, capacity will be sum of lo(ui-->v) for all u. also add an
edge from every u to nsn, capacity will be sum of lo(u-->vi) for all v.
add a final edge to sn to sr with infinite capacity. flow of this edge define
total flow of whole network. if all edges connected eith nsr is ed.f==ed.c then
the network satisfy all lower bound. otherwise not. the network will return an
arbitrary flow. by changing capacity of sn-->sr edge we can find the minimum flow
which satisfy all lower bound.
project and instrument problem: n project needs some subset m instrument. each 
project have some revenue and each instrument have some cost. select a subset of
project to maximize revenue. connect sr with project with capacity revenue and
sn with instrument with capacity cost. connect project with corresponding instrument
with infinite capacity. revenue will be (sum of revenue)-flow().
*/
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

/*
not sure about complexity. may be EV^2 log(V)
*/
struct edge
{
  int a,b,f,c,d;
};
int sr,sn;//sr=0,sn=last node+1;
vector<edge>ed;
vector<int>adj[N+2];
void clear(void)
{
  ed.clear();
  for(int i=0;i<=sn;i++)
    adj[i].clear();
}
void addEdge(int a,int b,int c,int d)
{
  edge e;e={a,b,0,c,d};
  adj[a].push_back(ed.size());
  ed.push_back(e);e={b,a,0,0,-d};
  adj[b].push_back(ed.size());
  ed.push_back(e);
}
int dis[N+2],inq[N+2],mnf[N+2],pth[N+2];
//pth stores the min cost path in reverse order
//mnf stores the bottleneck flow of the min cost path.
pair<int,int>spfa(void)
{
  for(int i=0;i<=sn;i++)dis[i]=inf;
  queue<int>q;q.push(sr);
  dis[sr]=0,inq[sr]=1,mnf[sr]=inf;
  while(!q.empty())
  {
    int u=q.front();q.pop();inq[u]=0;
    for(auto id:adj[u])
    {
      int v=ed[id].b;
      if(ed[id].c>ed[id].f&&dis[v]>dis[u]+ed[id].d)
      {
        dis[v]=dis[u]+ed[id].d,pth[v]=id;
        mnf[v]=min(mnf[u],ed[id].c-ed[id].f);
        if(!inq[v])q.push(v),inq[v]=1;
      }
    }
  }
  if(dis[sn]==inf)return {0,0};
  int v=sn;
  while(v!=sr)//sending maximum flow through the min cost path
  {
    int id=pth[v];
    ed[id].f+=mnf[sn],ed[id^1].f-=mnf[sn];
    v=ed[id].a;
  }
  return {mnf[sn],dis[sn]*mnf[sn]};
}
pair<int,int>mcmf(void)
{
  int flow=0,cost=0;
  while(true)
  {
    pair<int,int>p=spfa();
    if(!p.first)return {flow,cost};
    flow+=p.first,cost+=p.second;
  }
}
