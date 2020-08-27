/*
complexity n lg^2(n). with single hash
*/
const int mod=1000001011,b=193;
int pw[N+2];
void cal(int n)
{
  pw[0]=1;
  for(int i=1;i<=n;i++)pw[i]=(1LL*pw[i-1]*b)%mod;
}
int h[N+2];string s;//global string
void makeHash()
{
  int hs=0,i=0;
  for(auto x:s){hs=(1LL*hs*b+x)%mod;h[i++]=hs;}
}
int get(int i,int j)
{
  int x=h[j];if(!i)return x;x=x-(1LL*h[i-1]*pw[j-i+1])%mod;
  if(x<0)x+=mod;return x;
}
int sz;
bool cmp(int a,int b)
{
  int mx=sz-max(a,b);int lo=0,hi=mx,md;
  while(lo<=hi)
  {
    int md=(lo+hi)/2;if(get(a,a+md)==get(b,b+md))lo=md+1;
    else hi=md-1;
  }
  if(a+lo==sz)return true;if(b+lo==sz)return false;
  return s[a+lo]<s[b+lo];
}
vector<int>suffixSort()
{
  sz=s.size();cal(sz);makeHash();
  vector<int>v;
  for(int i=0;i<sz;i++)v.push_back(i);
  sort(v.begin(),v.end(),cmp);
  return v;
}

/* n lgn*/
struct suffixArray
{
  char t[N+12];int idx[N+12];//N is atleast 300
  int n,c[N+12],RA[N+12],SA[N+12],tRA[N+12],tSA[N+12];
  void init(string s)
  {
    n=s.size();
    for(int i=0;i<n;i++)t[i]=s[i];
    t[n++]='#';t[n]='\0';
  }
  void countingSort(int k)
  {
    memset(c,0,sizeof c);
    for(int i=0;i<n;i++)c[i+k<n?RA[i+k]:0]++;
    for(int i=0,sm=0;i<max(300,n);i++)
    {
      int d=c[i];c[i]=sm;sm+=d;
    }
    for(int i=0;i<n;i++)tSA[c[SA[i]+k<n?RA[SA[i]+k]:0]++]=SA[i];
    for(int i=0;i<n;i++)SA[i]=tSA[i];
  }
  void buildSA()
  {
    for(int i=0;i<n;i++)RA[i]=t[i];
    for(int i=0;i<n;i++)SA[i]=i;
    for(int k=1,r;k<n;k<<=1)
    {
      countingSort(k);countingSort(0);tRA[SA[0]]=r=0;
      for(int i=1;i<n;i++)  
        tRA[SA[i]]=(RA[SA[i]]==RA[SA[i-1]]&&RA[SA[i]+k]==RA[SA[i-1]+k])?r:++r;
      for(int i=0;i<n;i++)RA[i]=tRA[i];
      if(RA[SA[n-1]]==n-1)break;
    }
    //suffixes are sorted in index SA[1] to SA[n-1];
    //use SA index 1 to s.size() for outside use;
  }
  int phi[N+12],tmp[N+12],lcp[N+12];
  void computeLCP()
  {
    phi[SA[0]]=-1;
    for(int i=1;i<n;i++)phi[SA[i]]=SA[i-1];
    for(int i=0,l=0;i<n;i++)
    {
      if(phi[i]==-1){tmp[i]=0;continue;}
      while(t[i+l]==t[phi[i]+l])l++;
      tmp[i]=l;l=max(l-1,0);
    }
    for(int i=0;i<n;i++)lcp[i]=tmp[SA[i]];//lcp with previous suffix in sorted order
    for(int i=0;i<n;i++)idx[SA[i]]=i;//order of suffix i in sorted list
  }
  void print()
  {
    for(int i=0;i<n;i++)printf("%2d\t%2d\t%s\n",SA[i],lcp[i],t+SA[i]);
  }
};
