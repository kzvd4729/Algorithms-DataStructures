int kmp[N+2];
void doKmp(string s)
{
  int n=s.size();kmp[0]=0;
  for(int i=1;i<n;i++)
  {
    int now=kmp[i-1];kmp[i]=0;
    while(true)
    {
      if(s[now]==s[i]){kmp[i]=now+1;break;}
      if(!now)break;now=kmp[now-1];
    }
  }
}



/*
z[i] means maximum length of substring starting from i matches with prefix.
*/
vector<int>zFunction(string s)
{
  int n=s.size();vector<int>z(n);
  z[0]=0;//l,r maintains a window with maximum r
  for(int i=1,l=0,r=0;i<n;i++)
  {
    if(i<=r)z[i]=min(r-i+1,z[i-l]);//inside the window
    while(i+z[i]<n&&s[z[i]]==s[i+z[i]])z[i]++;//brute-force
    if(i+z[i]-1>r)l=i,r=i+z[i]-1;//r update
  }
  return z;
}
