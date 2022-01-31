/*
automata is a dag
every state defines some substring with same suffix
suffix link of a state defines a unique substring(thats why we need clone)
reversed suffix link form suffix tree
*/
struct automata
{
  int len,link,next[26];
}aut[N+N+2];//2*insrt function call
int sz,last,occur[N+N+2];
void init(void)
{
  for(int i=0;i<=N+N;i++)
  {
    memset(aut[i].next,0,sizeof(aut[i].next));
    occur[i]=0;
  }
  sz=0,last=0,aut[0].link=-1;
}
void insrt(int c)
{
  int now=++sz;aut[now].len=aut[last].len+1;
  int p,q,cl;occur[now]=1;
  for(p=last;p!=-1&&!aut[p].next[c];p=aut[p].link)
    aut[p].next[c]=now;
  if(p==-1)aut[now].link=0;
  else
  {
    q=aut[p].next[c];
    if(aut[p].len+1==aut[q].len)aut[now].link=q;
    else
    {
      cl=++sz;aut[cl].len=aut[p].len+1;
      aut[cl].link=aut[q].link;
      memcpy(aut[cl].next,aut[q].next,sizeof(aut[cl].next));
      for( ;p!=-1&&aut[p].next[c]==q;p=aut[p].link)
        aut[p].next[c]=cl;
      aut[now].link=aut[q].link=cl;
    }
  }
  last=now;
}
void occurences(int n)//n=string size;
{
  vector<vector<int> >vLen(n+2);
  for(int i=1;i<=sz;i++)
    vLen[aut[i].len].push_back(i);
  for(int i=n;i>=1;i--)
    for(auto x:vLen[i])
      occur[aut[x].link]+=occur[x];
}
