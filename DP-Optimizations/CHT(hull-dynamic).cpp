//hull Dynamic: slow
const long inv=-(1LL<<62);//doesn't matter min or max query
bool Min;//true for min query false for max query
struct line
{
  long m,b;
  mutable function<const line*()>succ;
  bool operator<(const line &rhs)const
  {
    if(rhs.b!=inv)return m<rhs.m;
    const line *s=succ();
    if(!s)return 0;
    long x=rhs.m;
    return b-s->b<(s->m-m)*x;
  }
};
struct hullDynamic:public multiset<line>
{
  bool bad(iterator y)
  {
    auto z=next(y);
    if(y==begin())
    {
      if(z==end())return 0;
      return y->m==z->m&&y->b<=z->b;
    }
    auto x=prev(y);
    if(z==end())return y->m==x->m&&y->b<=x->b;
    return 1.0*(x->b-y->b)*(z->m-y->m)>=1.0*(y->b-z->b)*(y->m-x->m);
  }
  void add(long m,long b)
  {
    if(Min)m*=-1,b*=-1;
    auto y=insert({m,b});
    y->succ=[=]{return next(y)==end()?0:&*next(y);};
    if(bad(y)){erase(y);return;}
    while(next(y)!=end()&&bad(next(y)))erase(next(y));
    while(y!=begin()&&bad(prev(y)))erase(prev(y));
  }
  long get(long x)
  {
    auto l=*lower_bound((line){x,inv});
    long ret=l.m*x+l.b;
    if(Min)ret*=-1;return ret;
  }
  void _clear(){clear();}
}st;
