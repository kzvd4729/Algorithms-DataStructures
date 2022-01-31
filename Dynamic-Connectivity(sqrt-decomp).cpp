/*
sqrt decomposition for dynamic connectivity. complexity (n+q)sqrt(n+q).
well, complexity is actually a little worse.
complexity far worse then divide and conquer way.
*/
int par[N+2],par2[N+2],com,qr[N+2];
map<pair<int,int>,int>mp;
vector<vector<int> >ed,tmp,onl;
int get(int x)
{
  if(x==par[x])return x;
  return par[x]=get(par[x]);
}
int get2(int x)
{
  if(x==par2[x])return x;
  return par2[x]=get2(par2[x]);
}
void add(int u,int v)
{
  int p1=get(u),p2=get(v);
  if(p1!=p2)par[p1]=p2,com--;
}
void add2(int u,int v)
{
  int p1=get2(u),p2=get2(v);
  if(p1!=p2)par2[p1]=p2,com--;
}
void solve()
{
  int n,q;cin>>n>>q;
  for(int i=0;i<q;i++)
  {
    string s;cin>>s;
    int u,v;if(s!="?")cin>>u>>v;
    if(u>v)swap(u,v);
    if(s=="+")//add edge(not added before)
    {
      ed.push_back({u,v,i,q});//stores active time for each edge
      mp[{u,v}]=ed.size();
    }
    else if(s=="-")ed[mp[{u,v}]-1][3]=i;//remove edge(already there)
    else qr[i]=1;
  }
  for(int bl=0; ;bl++)
  {
    int l=bl*sq,r=min((bl+1)*sq,q)-1;if(l>r)break;
    for(int i=1;i<=n;i++)par[i]=i;
    tmp.clear();com=n;
    for(auto &x:ed)
    {
      if(x[2]<l&&x[3]>r)add(x[0],x[1]);//edges which are going over current block
      if((x[2]>=l&&x[2]<=r)||(x[3]>=l&&x[3]<=r))//end point at current block
        tmp.push_back(x);
    }
    for(int i=l;i<=r;i++)
    {
      int remm=com;if(!qr[i])continue;
      onl.clear();
      for(auto &x:tmp)
      {
        if(x[2]<i&&x[3]>i)
        {
          onl.push_back(x);//have effect on current query
          int r=get(x[0]);par2[x[0]]=r,par2[r]=r;
          r=get(x[1]);par2[x[1]]=r,par2[r]=r;
        }
      }
      for(auto &x:onl)add2(x[0],x[1]);
      cout<<com<<"\n";com=remm;
    }
  }
}
