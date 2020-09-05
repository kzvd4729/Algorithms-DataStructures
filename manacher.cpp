//od[i] is largest palindromic substring centered at i;
vector<int>od;
//ev[i] is largest palindromic substring centered at i and i+1;
vector<int>ev;
void manacher(string s)
{
  int n=s.size();
  od.resize(n);
  for(int i=0,l=0,r=-1;i<n;i++)
  {
    int k=(i>r)?1:min(od[l+r-i],r-i+1);
    while(0<=i-k&&i+k<n&&s[i-k]==s[i+k])k++;
    od[i]=k--;
    if(i+k>r)l=i-k,r=i+k;
  }
  ev.resize(n);
  for(int i=0,l=0,r=-1;i<n;i++)
  {
    int k=(i>r)?0:min(ev[l+r-i+1],r-i+1);
    while(0<=i-k-1&&i+k<n&&s[i-k-1]==s[i+k])k++;
    ev[i]=k--;
    if(i+k>r)l=i-k-1,r=i+k;
  }
  for(int i=0;i<n;i++)od[i]=od[i]*2-1;
  ev.erase(ev.begin());
  for(int i=0;i<n-1;i++)ev[i]=ev[i]*2;
}
int st[N+2],ed[N+2];//number of palindrome starting at i and ending at i
void addtional(int n)//n=s.size();
{
  for(int i=0;i<n;i++)
    st[i-od[i]/2]++,st[i+1]--,ed[i]++,ed[i+od[i]/2+1]--;
  for(int i=0;i<n-1;i++)
    st[i-ev[i]/2+1]++,st[i+1]--,ed[i+1]++,ed[i+1+ev[i]/2]--;
  for(int i=1;i<n;i++)st[i]+=st[i-1],ed[i]+=ed[i-1];
}
bool isPalindrome(int i,int j)//0 indexed
{
  if((j-i+1)%2)return od[(i+j)/2]>=j-i+1;
  else return ev[(i+j)/2]>=j-i+1;
}
