#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<cstring>
#include<map>
#include<bitset>
#include<assert.h>
#include<algorithm>
#include<iomanip>
#include<cmath>
#include<set>
#include<queue>
#include<sstream>
#include<unordered_map>
#include<unordered_set>
#include<chrono>
#include<stack>
#include<deque>
#include<random>
#define long long long
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int knightX[]={2,1,-1,-2,-2,-1,1,2};
int knightY[]={1,2,2,1,-1,-2,-2,-1};
const int N=1e6;
long aa[N+2];
int stringToNum(string x)
{
  if((int)x.size()==0)assert(0);
  int ml=1,b=0,ret=0;
  if(x[0]=='-')ml=-1,b=1;
  for(int i=b;i<(int)x.size();i++)
    ret=ret*10+x[i]-'0';
  return ret*ml;
}
string numToString(int x)
{
  if(x==0)return "0";
  string ret;
  while(x)
  {
    int r=x%10;x/=10;
    ret.push_back((char)(r+'0'));
  }
  reverse(ret.begin(),ret.end());
  return ret;
}
void compress(int n)
{
  vector<int>v;
  for(int i=1;i<=n;i++)v.push_back(aa[i]);

  sort(v.begin(),v.end());
  v.erase(unique(v.begin(),v.end()),v.end());

  map<int,int>mp;
  for(int i=0;i<v.size();i++)mp[v[i]]=i+1;

  for(int i=1;i<=n;i++)aa[i]=mp[aa[i]];
}
const int mod=1e9+7;
int big(int b,int p)
{
  int r=1;
  while(p)
  {
    if(p&1)r=(1LL*r*b)%mod;b=(1LL*b*b)%mod;p/=2;
  }
  return r;
}
int fac[N+2];
void init()
{
  fac[0]=1;
  for(int i=1;i<=N;i++)fac[i]=(1LL*fac[i-1]*i)%mod;
}
int ncr(int n,int r)
{
  int ret=(1LL*fac[n]*big(fac[r],mod-2))%mod;
  return (1LL*ret*big(fac[n-r],mod-2))%mod;
}
bool isPrime(int x)
{
  for(int i=2;i<x;i++)if(x%i==0)return false;
  return true;
}
bool isP[N+2];vector<int>pr;
void seive(int n)
{
  pr.push_back(2);isP[1]=1;
  for(int i=4;i<=n;i+=2)isP[i]=1;
  int sq=sqrt(n+1);
  for(int i=3;i<=n;i+=2)
  {
    if(isP[i])continue;pr.push_back(i);
    if(i>sq)continue;
    for(int j=i*i;j<=n;j+=2*i)isP[j]=1;
  }
}
const int inf=1010580540;
const long infL=4340410370284600380LL;
void info()
{
  memset(aa,-60,sizeof aa);//inf for int and infL for long;
}
int main()
{
  //freopen("inp.txt","r",stdin);
  //freopen("out.txt","w",stdout);
  ios_base::sync_with_stdio(0);cin.tie(0);

  
  return 0;
}
