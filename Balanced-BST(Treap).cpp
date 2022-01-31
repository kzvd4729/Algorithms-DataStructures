int tr;
struct treap
{
  int lt,rt,dt,pri,sz;
}bst[N+2];
void cal(int nd)
{
  int l=bst[nd].lt,r=bst[nd].rt;
  bst[nd].sz=bst[l].sz+bst[r].sz+1;
}
//left tree will contain value <= vl.
pair<int,int>splitbyValue(int nd,int vl)
{
  if(!nd)return {0,0};pair<int,int>p;
  if(bst[nd].dt<=vl)
  {
    p=splitbyValue(bst[nd].rt,vl);
    bst[nd].rt=p.first;cal(nd);
    return {nd,p.second};
  }
  else
  {
    p=splitbyValue(bst[nd].lt,vl);
    bst[nd].lt=p.second;cal(nd);
    return {p.first,nd};
  }
}
pair<int,int>splitbySize(int nd,int ss)
{
  if(!nd)return {0,0};pair<int,int>p;
  if(bst[bst[nd].lt].sz>=ss)
  {
    p=splitbySize(bst[nd].lt,ss);
    bst[nd].lt=p.second;cal(nd);
    return {p.first,nd};
  }
  else
  {
    p=splitbySize(bst[nd].rt,ss-bst[bst[nd].lt].sz-1);
    bst[nd].rt=p.first;cal(nd);
    return {nd,p.second};
  }
}
//lt and rt are bst and max element of lt <= minimum of rt
int join(int lt,int rt)
{
  if(!lt)return rt;if(!rt)return lt;
  if(bst[lt].pri>=bst[rt].pri)
  {
    bst[lt].rt=join(bst[lt].rt,rt);
    cal(lt);return lt;
  }
  else
  {
    bst[rt].lt=join(lt,bst[rt].lt);
    cal(rt);return rt;
  }
}
//lt and rt are bst
/*int join2(int lt,int rt)
{
  if(bst[lt].mx<=bst[rt].mn)return join(lt,rt);
  if(bst[rt].mx<=bst[lt].mn)return join(rt,lt);
  if(bst[lt].pri>=bst[rt].pri)
  {
    pair<int,int>p=splitbyValue(rt,bst[lt].dt);
    bst[lt].lt=join2(p.first,bst[lt].lt);
    bst[lt].rt=join2(p.second,bst[lt].rt);
    cal(lt);return lt;
  }
  else
  {
    pair<int,int>p=splitbyValue(lt,bst[rt].dt);
    bst[rt].lt=join2(p.first,bst[rt].lt);
    bst[rt].rt=join2(p.second,bst[rt].rt);
    cal(rt);return rt;
  }
}*/

int add(int root,int vl)
{
  pair<int,int>p=splitbyValue(root,vl);

  bst[++tr]={0,0,vl,rand(),1};
  root=join(p.first,tr);
  root=join(root,p.second);

  return root;
}
int erase(int root,int vl)
{
  pair<int,int>p=splitbyValue(root,vl-1);
  pair<int,int>p2=splitbySize(p.second,1);

  return join(p.first,p2.second);
}
