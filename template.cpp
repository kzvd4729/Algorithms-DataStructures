#include<bits/stdc++.h>
#define long long long
using namespace std;
#define SP(x) cerr<<#x<<" = "<<x<<endl
#define DP(x) cerr<<#x<<" = "<<x.first<<" "<<x.second<<endl
#define F cerr<<"flag"<<endl
template<typename T>//container
void P(T v)
{
  cerr<<"( ";
  for(auto x:v)cerr<<x<<" ";
  cerr<<")"<<endl;
}
void PB(int x)//print in binary format
{
  cerr<<x<<" = ";vector<int>v;
  while(x){v.push_back(x%2);x/=2;}
  for(int i=v.size()-1;i>=0;i--)cerr<<v[i];
  cerr<<endl;
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
