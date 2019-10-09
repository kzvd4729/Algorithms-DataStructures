//loop over submask. complexity little better than n^2
int cnt=0;
for(int msk=0;msk<(1<<17);msk++)
{
  for(int sub=msk;sub>0;sub=(sub-1)&msk)
    cnt++;
}
