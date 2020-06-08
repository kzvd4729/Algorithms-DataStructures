int tr;
struct treap
{
  int lt,rt,dt,pri,sz;
}bst[N+2];
void cal(int node)
{
  bst[node].sz=bst[bst[node].lt].sz+bst[bst[node].rt].sz+1;
}
//left tree will contain value <= vl.
pair<int,int>splitbyValue(int node,int vl)
{
  if(!node)return {0,0};pair<int,int>p;
  if(bst[node].dt<=vl)
  {
    p=splitbyValue(bst[node].rt,vl);
    bst[node].rt=p.first;cal(node);
    return {node,p.second};
  }
  else
  {
    p=splitbyValue(bst[node].lt,vl);
    bst[node].lt=p.second;cal(node);
    return {p.first,node};
  }
}
pair<int,int>splitbySize(int node,int ss)
{
  if(!node)return {0,0};pair<int,int>p;
  if(bst[bst[node].lt].sz>=ss)
  {
    p=splitbySize(bst[node].lt,ss);
    bst[node].lt=p.second;cal(node);
    return {p.first,node};
  }
  else
  {
    p=splitbySize(bst[node].rt,ss-bst[bst[node].lt].sz-1);
    bst[node].rt=p.first;cal(node);
    return {node,p.second};
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
