//loop over submask. complexity little better than 3^n
int cnt=0;
for(int msk=0;msk<(1<<17);msk++)
{
  for(int sub=msk;sub>0;sub=(sub-1)&msk)
    cnt++;
}
//merge two sorted vector
vector<int>a,b,c;
a={1,2,3,4};
b={2,5,6,7};
c.resize((int)a.size()+(int)b.size());
merge(a.begin(),a.end(),b.begin(),b.end(),c.begin());

//loop until clock
while(clock()<CLOCKS_PER_SEC*2.0){
}

//fast optimization
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")

//stl comparator overload
struct cmp
{
  bool operator()(int a,int b)const{
    return a>b;
  }
};
//set<int,cmp>st;

//diagonal element order. for 2x2 matrix: 11->21->12->22
for(int i=1;i<=n;i++)
    for(int j=1;j<=min(i,m);j++)int rw=i-j+1,cl=j;
for(int i=2;i<=m;i++)
    for(int j=i;j<=min(m,i+n-1);j++)int rw=n-(j-i),cl=j;
