/*
suffix link of v = u. path from root to u matches with suffix of state v, and
among those state, length of u is maximum(length of u is smaller than length of v)

suffix link form a tree rooted at 0.
*/
struct node
{
  int next[26],link;
}trie[N+2];
int nw;
void insrt(string s)
{
  int now=0,n=s.size();
  for(int i=0;i<n;i++)
  {
    int c=s[i]-'a';
    if(!trie[now].next[c])trie[now].next[c]=++nw;
    now=trie[now].next[c];
  }
}
void bfs(void)
{
  queue<int>q;q.push(0);
  while(q.size())
  {
    int v=q.front(),u=trie[v].link;q.pop();
    for(int c=0;c<26;c++)
    {
      int nx=trie[v].next[c];
      if(nx)
      {
        q.push(nx);if(!v)trie[nx].link=0;
        else trie[nx].link=trie[u].next[c];
      }
      else trie[v].next[c]=trie[u].next[c];
    }
  }
}
void clear(void)
{
  memset(trie,0,sizeof(trie));
  nw=0;
}
