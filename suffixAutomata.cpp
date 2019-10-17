/*
automata is a dag.
every state defines some substring with same suffix.
suffix link of a state defines a unique substring(thats why we need clone)
reversed suffix link form suffix tree
*/
struct node
{
  int len,link,next[26];
}aut[N+N+2];//2*insrt function call
int sz,last;
void init(void)//must call before insert
{
  aut[0].link=-1;
}
void insrt(int c)
{
  int now=++sz;aut[now].len=aut[last].len+1;
  int p,q,cl;
  for(p=last;p!=-1&&!aut[p].next[c];p=aut[p].link)
    aut[p].next[c]=now;
  if(p==-1)
    aut[now].link=0;
  else
  {
    q=aut[p].next[c];
    if(aut[p].len+1==aut[q].len)
      aut[now].link=q;
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
void clean(int n)
{
  for(int i=0;i<=n+n;i++)
    memset(aut[i].next,0,sizeof(aut[i].next));
  sz=0,last=0;
}
