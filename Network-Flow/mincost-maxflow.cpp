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
