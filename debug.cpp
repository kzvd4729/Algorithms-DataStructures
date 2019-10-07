#define _sp(x) cerr<<#x<<" = "<<x<<endl
#define _dp(x) cerr<<#x<<" = "<<x.first<<" "<<x.second<<endl
#define _f cerr<<"flag"<<endl
template<typename T>//container
void _p(T v)
{
  cerr<<"( ";
  for(auto x:v)cerr<<x<<" ";
  cerr<<")"<<endl;
}
