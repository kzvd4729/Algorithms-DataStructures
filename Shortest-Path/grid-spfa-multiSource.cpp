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
