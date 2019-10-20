//loop over submask. complexity little better than n^2
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
