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


/*
grid spfa with multisource.
be careful, a lot of change have to be made
*/
long d[N+2][N+2];
int qd[N+2][N+2];
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
bool isFree(int x,int y)
{
  return ((a[x][y]!=-1) && (x>=1) && (x<=n) && (y>=1) && (y<=m));
}
void spfa(int n,int m,vector<vector<int> >sr)
{
  for(int i=1;i<=n;i++)
  {
    for(int j=1;j<=m;j++)
      d[i][j]=INF,qd[i][j]=0;
  }
  queue<pair<int,int> >q;
  for(auto x:sr)
  {
    qd[x[0]][x[1]]=1;d[x[0]][x[1]]=x[2];
    q.push({x[0],x[1]});
  }
  while((int)q.size())
  {
    pair<int,int>p=q.front();q.pop();
    int x=p.first,y=p.second;
    qd[x][y]=0;

    for(int i=0;i<4;i++)
    {
      int xx=x+dx[i],yy=y+dy[i];
      if(d[x][y]+w<d[xx][yy] && isFree(xx,yy))
      {
        d[xx][yy]=d[x][y]+w;
        if(!qd[xx][yy])q.push({xx,yy}),qd[xx][yy]=1;
      }
    }
  }
}
