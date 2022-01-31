/*
represented tree: the actual tree. tree we want to
represent. actual tree are forest of some rooted trees.
like dsu tree.

preferred child: u is called preferred child of v if
last accessed node in v's subtree is in u's subtree.
preferred child can be null if v is last accessed node
or v has no accessed node.

preferred edge: edge between node and preferred child.

preferred path: continuous path where each edge is
preferred edge. preferred path can be a single node.
a tree will have many preferred path. each preferred
path is node disjoint and every node is in exactly one
preferred path.

splay tree: splay trees represent
preferred path. one splay tree for each path. splay
trees are balanced binary search tree where nodes are 
keyed by their depth in actual tree.

path-parent pointer: path parent pointer connects two
splay trees. path parent pointer is stored in the root
of splay tree and points to parent of the topmost
(lowest depth) node of preferred path. so a path parent
pointer is an edge of represented tree which is not
preferred.
*/
struct node
{
  int p,ch[2];//parent and child;
  long dt,sm;//value of the node and sum of subtree(in splay)
  bool rev;//splay tree operation.
  int sz;//size of the subtree(in splay).
  long lz;//lazy add
  node(){}
  node(int v):p(-1),dt(v),sm(v),rev(0),sz(1),lz(0){
      ch[0]=ch[1]=-1;
  }
};
node t[N+2];
void tooLazy(int x)//lazy propagation
{
  if(t[x].lz)
  {
    t[x].dt+=t[x].lz,t[x].sm+=t[x].lz*t[x].sz;
    if(t[x].ch[0]+1)t[t[x].ch[0]].lz+=t[x].lz;
    if(t[x].ch[1]+1)t[t[x].ch[1]].lz+=t[x].lz;
  }
  if(t[x].rev)
  {
    swap(t[x].ch[0],t[x].ch[1]);
    if(t[x].ch[0]+1)t[t[x].ch[0]].rev^=1;
    if(t[x].ch[1]+1)t[t[x].ch[1]].rev^=1;
  }
  t[x].lz=0,t[x].rev=0;
}
void cal(int x)//splay tree operation
{
  t[x].sz=1,t[x].sm=t[x].dt;
  for(int i=0;i<2;i++)
  {
    if(t[x].ch[i]+1==0)continue;
    tooLazy(t[x].ch[i]);
    t[x].sz+=t[t[x].ch[i]].sz;t[x].sm+=t[t[x].ch[i]].sm;
  }
}
bool isRoot(int x)
{
  return (t[x].p==-1)||((t[t[x].p].ch[0]!=x)&&(t[t[x].p].ch[1]!=x));
}
void rotate(int x)//splay tree 
{
  int p=t[x].p,pp=t[p].p;
  if(!isRoot(p))t[pp].ch[t[pp].ch[1]==p]=x;
  bool d=t[p].ch[0]==x;
  t[p].ch[!d]=t[x].ch[d],t[x].ch[d]=p;
  if(t[p].ch[!d]+1)t[t[p].ch[!d]].p=p;
  t[x].p=pp,t[p].p=x;cal(p),cal(x);
}
int splay(int x)//splay tree
{
  while(!isRoot(x))
  {
    int p=t[x].p,pp=t[p].p;
    if(!isRoot(p))tooLazy(pp);
    tooLazy(p),tooLazy(x);
    if(!isRoot(p))rotate((t[pp].ch[0]==p)^(t[p].ch[0]==x)?x:p);
    rotate(x);
  }
  return tooLazy(x),x;
}
int access(int v)
{
  int last=-1;
  for(int w=v;w+1;cal(last=w),splay(v),w=t[v].p)
    splay(w),t[w].ch[1]=(last==-1?-1:v);
  return last;
}
void init(int v,int w){t[v]=node(w);}//node v initialization with value w.
int findRoot(int v)
{
  access(v),tooLazy(v);
  while(t[v].ch[0]+1)v=t[v].ch[0],tooLazy(v);
  return splay(v);
}
bool isConnected(int v,int w)
{
  access(v),access(w);
  return v==w?true:t[v].p!=-1;
}
void makeRoot(int v)
{
  access(v);t[v].rev^=1;
}
long query(int u,int v)//query on path u-v
{
  makeRoot(v),access(u);
  return t[u].sm;
}
void update(int u,int v,int x)//add x to all node in u-v path
{
  makeRoot(v),access(u);
  t[u].lz+=x;
}
void add(int u,int v)//add an edge between u and v.
{
  if(isConnected(u,v))return ;
  makeRoot(v);t[v].p=u;
}
void cut(int u,int v)//cut edge between u and v, given they already have edge.
{
  makeRoot(v),access(u);
  t[u].ch[0]=t[t[u].ch[0]].p=-1;
}
int lca(int u,int v)//lca between u and v.
{
  access(u);return access(v);
}
