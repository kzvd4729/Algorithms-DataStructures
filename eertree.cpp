/*
there can be atmost n distinct palindromic substring of a string of length n.
every node of an eertree is a palindromic substring(and two roots for odd even)
a transition marked c from X to Y means Y=cXc;
a suffix link from X to Y means Y is proper suffix of X.
*/
pair<int,int>dp[N+2];//minimum odd and even factorization, 1 indexed
int nw,last;//last keeps track of the lps suffix of till inserted string
struct node
{
  int next[26],len,link;

  int dif,sLink;//for factorization
  pair<int,int>tmp;//for factorization
}pal[N+2];int occur[N+2];

void init()
{
  pal[0].link=0;pal[0].len=-1;//odd length root
  pal[1].link=0;pal[1].len=0;//even length root
  nw=1,last=1;

  dp[0]={N+3,0};

  for(int i=0;i<N+2;i++)
  {
    pal[i].tmp={N+2,N+2};occur[i]=0;
    memset(pal[i].next,0,sizeof pal[i].next);
  }
}
void build(string s)
{
  s="#"+s;
  for(int p=1;p<s.size();p++)
  {
    while(s[p-pal[last].len-1]!=s[p])last=pal[last].link;
    int x=pal[last].link,c=s[p]-'a';
    while(s[p-pal[x].len-1]!=s[p])x=pal[x].link;//finding suffix link
    if(!pal[last].next[c])
    {
      pal[last].next[c]=++nw;pal[nw].len=pal[last].len+2;
      if(pal[nw].len==1)pal[nw].link=1;
      else pal[nw].link=pal[x].next[c];

      last=pal[last].next[c];

      /**for factorization**/
      int xx=pal[last].link;
      pal[last].dif=pal[last].len-pal[xx].len;
      if(pal[last].dif==pal[xx].dif)pal[last].sLink=pal[xx].sLink;
      else pal[last].sLink=last;

    }
    else last=pal[last].next[c];
    occur[last]++;

    /**for factorization**/
    dp[p]={N+2,N+2};
    for(int j=last;pal[j].len>0; )
    {
      int sfl=pal[j].link,srl=pal[j].sLink;
      int slv=pal[srl].link;

      pal[j].tmp=dp[p-(pal[slv].len+pal[j].dif)];
      if(pal[j].dif==pal[sfl].dif)
      {
        pal[j].tmp.first=min(pal[j].tmp.first,pal[sfl].tmp.first);
        pal[j].tmp.second=min(pal[j].tmp.second,pal[sfl].tmp.second);
      }
      pair<int,int>vl=pal[j].tmp;
      dp[p].first=min(dp[p].first,vl.second+1);
      dp[p].second=min(dp[p].second,vl.first+1);
      j=slv;
    }
  }
  for(int i=nw;i>=2;i--)occur[pal[i].link]+=occur[i];
}
