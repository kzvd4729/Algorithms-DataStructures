#include<bits/stdc++.h>
#define long long long
using namespace std;
#define F cerr<<"flag"<<endl
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
unsigned int R(unsigned int lo,unsigned int hi)
{
  unsigned int df=(hi-lo+1);
  return lo+rng()%df;
}
template<typename T>//vector print
void P(T v,int l=0,int r=-1)
{
  if(r==-1)r=v.size()-1;
  cerr<<"( ";
  for(int i=l;i<=r;i++)cerr<<v[i]<<" ";
  cerr<<")"<<endl;
}
template<typename T>
void P(T *aa,int l,int r)//array print
{
  cerr<<"( ";
  for(int i=l;i<=r;i++)cerr<<aa[i]<<" ";
  cerr<<")"<<endl;
}
template<typename T>
void UN(vector<T>&v)//make unique
{
  sort(v.begin(),v.end());
  v.erase(unique(v.begin(),v.end()),v.end());
}
const int N=1e6;
int main()
{
  //freopen("inp.txt","r",stdin);
  //freopen("out.txt","w",stdout);
  ios_base::sync_with_stdio(0);cin.tie(0);



  return 0;
}
